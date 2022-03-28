double fcn(double *x, double *params)
	{
		if((0 <= x[0]*x[1]) &&  (x[0]*x[1]<= TMath::Pi()))
			return params[0]*TMath::Sin(x[0]*x[1]);
		return 0;
	}
	
void lab4(){
	TCanvas *c1 = new TCanvas();
	c1-> Divide(2,2);
	
	double xmin = 0;
	double xmax = TMath::Pi()/2;
	double ymin = 0;
	double ymax = TMath::Pi()/2;
	int nparams = 1;
	
	TF2 *fun1 = new TF2("fun1",fcn,xmin,xmax,ymin,ymax,nparams);
	fun1->SetParameter(0,1);
	
	//c
	Double_t c = 1./(fun1->Integral(0,TMath::Pi()/2,0,TMath::Pi()/2));
	fun1->SetParameter(0,c);
	//cout<< c<< endl;
	
	//c1->cd(1);
	//fun1->Draw("Surf1");
	
	//random histograms
	TH2D *fun2 = new TH2D("fun2", "gestosc", 20, xmin, xmax, 20, ymin, ymax);
	
	//filling with random
	  double px, py;
	for (Int_t i = 0; i < 50000; i++) {
      fun1->GetRandom2(px,py);
      fun2->Fill(px,py);
   }
   
   //scaling
    fun2->Scale(1./fun2->Integral());
   
	c1->cd(1);
	fun2->Draw("lego1");
	
	
	
	//Distribution
	TH2D *fun3 = new TH2D("fun3", "distribution", 20, xmin, xmax, 20, ymin, ymax);
	
	//filling
	
	for(int xs = 0; xs <= 20 ; xs+= 1){
		for(int ys=0; ys <= 20 ; ys+= 1)
		{
			fun3->SetBinContent(xs, ys, fun2->Integral(0,xs, 0, ys));
		}
	}
	
	c1->cd(2);
	fun3->Draw("lego1");
	
	//marginal
	
	TH1D * projh2X = fun2->ProjectionX();
	
	c1->cd(3);
	projh2X ->Draw();
	
	TH1D * projh2Y = fun2->ProjectionY();
	c1->cd(4);
	projh2Y ->Draw();
	
	//expected value mean
	double Ex = fun2 -> GetMean(1);
	cout <<"E(X)= " <<Ex << endl;
	
	double Ey = fun2 -> GetMean(2);
	cout <<"E(Y)= " <<Ey << endl;

	double sigmax = fun2 -> GetRMS(1);
	cout << "sigma(X)= " << sigmax << endl;
	
	double sigmay = fun2 -> GetRMS(2);
	cout << "sigma(Y)= " << sigmay << endl;
	
	double covxy = fun2 -> GetCovariance(1,2);
	cout <<"cov(X, Y)= " <<covxy << endl;

	double corfac = fun2 -> GetCorrelationFactor(1,2);
	cout <<"corfac(X, Y)= " <<corfac << endl;
	
}
