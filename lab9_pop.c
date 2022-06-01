TF1 *fun1;

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
			fun2->DrawCopy();
		else
			fun2->DrawCopy("Same");	
	}
	
	//Gauss FIT
	c1->cd(3);
	double m=0; //liczba splotow
	double u=0;
	double n=1000; //liczba iteracji
	do{
		m++;
		TH1D *h1 = new TH1D("h", ";;Y Axis", 100, -0.5, 4);
		TF1 *fun1 = new TF1("fun1", "gaus", -0.5, 4);
		
		for(int i = 0; i<n; i++){
			u = 0;
			for(int j =0; j<m; j++){
				u+=gRandom->Uniform(0,1);
			}
			h1->Fill(u);
		}
		h1->Fit(fun1);
		cout<<"ratio = " <<fun1->GetChisquare()/fun1->GetNDF() <<endl;
	}while(fun1->GetChisquare()/fun1->GetNDF()>1.0);
	
	
}
