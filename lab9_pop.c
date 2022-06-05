TF1 *fun1;

void splot(int k, TH1D *h, int n) {
	double u, sum = 0.0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			u = gRandom -> Uniform(0, 1);
			sum += u;
		}
		h -> Fill(sum);
		sum = 0.0;
	}
} 

double fcn(double *x, double *k)
	{
		if(x[0]>0)
			return (TMath::Power(x[0], k[0]/2 -1)*TMath::Exp(-x[0]/2))/(TMath::Gamma(k[0]/2)*TMath::Power(2, k[0]/2));
		return 0;
	}
	
double cdf(double *x, double *k)
{
	if(x[0]>0)
	{		
		fun1->SetParameter(0,k[0]);
		return fun1->Integral(0,x[0]);
	}
	return 0;
}


void lab9_pop(){
	TCanvas *c1 = new TCanvas();
	c1-> Divide(2,2);
	
	double xmin = 0;
	double xmax = 30;
	int k = 1;
	
	c1->cd(1);
	for (int i=0; i<20; i++){
		fun1 = new TF1(Form("fun%d", i),fcn,xmin,xmax, k);
		fun1->SetParameter(0,i);
		
		if(i==0)
			fun1->Draw();
		else
			fun1->Draw("Same");
		
		fun1->SetLineColor(i);
		//fun1->GetYAxis()->SetRangeUser(0, 0.5);
		fun1->SetMaximum(0.5);
	}
	
	//Cumulative distribution
	c1->cd(2);
	k = 1;
	for (int j=0; j<20; j++){

		TF1 *fun2 = new TF1(Form("fun2%d", j),cdf,xmin,xmax, k);
		fun2->SetParameter(0,j);
		
		if(j==0)
			fun2->Draw();
		else
			fun2->Draw("Same");	
	}
	
	//Gauss FIT
	c1->cd(3);
	int n = 2, ss;
	double chisq;
	TF1 *gauss = new TF1();
	TH1D *hist;
	do {
		hist = new TH1D("hist", "histogram", 100, 0, 10);
		splot(n, hist, 10000);
		hist -> Fit("gaus");
		gauss = hist -> GetFunction("gaus");
		ss = gauss -> GetNDF();
		chisq = gauss -> GetChisquare();
		n++;
	}
	while(chisq/ss >= 1);
	
}
