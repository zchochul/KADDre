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

void lab10(){
	TCanvas *c1 = new TCanvas();
	TH1D *hist = new TH1D("h", ";;Y Axis", 9, 0, 9);

	
	ifstream ifile1;
	ifile1.open("dane10.txt");
	int val1, bin;
	int sum1 = 0;
	int sum2 = 0;
	
	//bin - k 
	//val1 - n_k
	while(ifile1>>bin>>val1){
		sum1 += bin*val1;
		sum2 += val1;
		for (int i =0; i < val1; i++){
			hist -> Fill(bin);
		}
	}
	ifile1.close();
	
	cout << (double)sum1/sum2 <<endl;
	TF1 *fun1= new TF1("fun1", "[1]*TMath::PoissonI(x, [0])", 0, 9);
	fun1->SetParameter(0, (double)sum1/sum2);
	fun1 ->SetParameter(1, sum2);
	
	
	TF1 *fun2= new TF1("fun2", "[1]*TMath::PoissonI(x, [0])", 0, 9);
	fun2->SetParameter(0, 2);
	fun2 ->FixParameter(1, sum2);
	hist->Fit(fun2, "LR");
	fun2->SetLineColor(kBlue);
	
	double T=0.0;
	double nk, npk;
	for (int i=1; i<9; i++){
		nk = hist->GetBinContent(i);
		npk = fun1->Eval(i-1);
		T+= TMath::Power((double)(nk - npk),2)/(npk);
	}
	cout << "T= " << T << endl;
	fun1->Draw();
	hist->Draw("Same");
	fun2->Draw("Same");
	
	int ndf = 6;
	cout <<"fun1 Fit = " <<fun2->GetChisquare()/ndf << endl;
	cout <<"fun2 Fit = " <<fun2->GetChisquare()/ndf << endl;
	
	int k = ndf;
	double xmin = 0;
	double xmax = 100;
	for (int i=0; i<20; i++){
		funx = new TF1(Form("fun%d", i),fcn,xmin,xmax, k);
		funx->SetParameter(0,ndf);
		
		if(i==0)
			fun1->Draw();
		else
			fun1->Draw("Same");
		
		funx->SetLineColor(i);
		funx->SetMaximum(0.5);
	}
	const Int_t nq = 1;
	Double_t xq[nq] = {0.99};
	Double_t yq[nq];
	funx->GetQuantiles(nq,yq,xq);
	cout << yq[0] << endl;
	
	if(fun2->GetChisquare()/ndf < yq[0])
		cout<< "Everything is okay" <<endl;
	else 
		cout << "bigger than chi critical" <<endl; 
}
