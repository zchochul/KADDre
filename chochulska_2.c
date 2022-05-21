//Zuzanna Chochulska kol 2

double fcn(double *x, double *params)
	{
		if((x[0]>=0) &&  (x[1]>= 0))
			return params[0]*(x[0] + x[1])*TMath::Exp(-(x[0]+x[1]));
		return 0;
	}
	
void chochulska_2(){
	TCanvas *c1 = new TCanvas();
	c1-> Divide(2,2);
	
	double xmin = 0;
	double xmax = 5;
	double ymin = 0;
	double ymax = 5;
	int nparams = 1;
	
	TF2 *fun1 = new TF2("fun1",fcn,xmin,xmax,ymin,ymax,nparams);
	fun1->SetParameter(0,1);
	
	//c
	Double_t c = 1./(fun1->Integral(xmin,ymax,ymin,ymax));
	fun1->SetParameter(0,c);
	
	//random histograms
	TH2D *fun2 = new TH2D("fun2", "Gestosc f(x,y)", 20, xmin, xmax, 20, ymin, ymax);
	
	//filling with random
	  double px, py;
	for (Int_t i = 0; i < 50000; i++) {
      fun1->GetRandom2(px,py);
      fun2->Fill(px,py);
   }
   
   //scaling (normalizacja)
    fun2->Scale(1./fun2->Integral());
   
	c1->cd(1);
	fun2->GetXaxis()->SetTitle("x");
	fun2->GetYaxis()->SetTitle("y");
	fun2->GetZaxis()->SetTitle("f(x,y)");
	fun2->Draw("lego1");
	
	//Distribution
	TH2D *fun3 = new TH2D("fun3", "Dystrybuanta F(x,y)", 20, xmin, xmax, 20, ymin, ymax);
	
	//filling distribution
	
	for(int xs = 0; xs <= 20 ; xs+= 1){
		for(int ys=0; ys <= 20 ; ys+= 1)
		{
			fun3->SetBinContent(xs, ys, fun2->Integral(0,xs, 0, ys));
		}
	}
	
	c1->cd(2);
	fun2->GetXaxis()->SetTitle("x");
	fun2->GetYaxis()->SetTitle("y");
	fun2->GetZaxis()->SetTitle("F(x,y)");
	fun3->Draw("lego1");


	//Marginal distribution
	TH1D * projh2X = fun2->ProjectionX();
	
	c1->cd(3);
	projh2X ->Draw();
	
	TH1D * projh2Y = fun2->ProjectionY();
	c1->cd(4);
	projh2Y ->Draw();
	
	//Covariance
	double covxy = fun2 -> GetCovariance(1,2);
	cout <<"cov(X, Y)= " <<covxy << endl;
}
