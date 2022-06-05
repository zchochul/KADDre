double Liniowa(double *x, double *par){
	if(x[0]>=1.2 || x[0]<=0.8) { 
		return par[0]+ par[1]*x[0];
	}
	else{
		TF1::RejectPoint();
		return 0;
	}
}

double Ciagla(double *x, double *par){
	return par[0]+ par[1]*x[0];
}

double FGauss(double *x, double *par) {
	if(x[0]>=0.7 && x[0]<=1.3) { 
		return par[2]*TMath::Exp(-((x[0] - par[0])/par[1])*((x[0] - par[0])/par[1])/2);
	}
		else{
		TF1::RejectPoint();
		return 0;
	}
}

double wszystko(double *x, double *par) {
	return par[2]*TMath::Exp(-((x[0] - par[0])/par[1])*((x[0] - par[0])/par[1])/2) + par[3] + par[4] * x[0];
}

void lab11 (void) {
	TFile *ifile = new TFile("file.root");
	TH1D *hist = (TH1D*)ifile->Get("hist");
	TF1 *fl = new TF1("liniowa", Liniowa, 0, 2, 2);
	
	TCanvas *window = new TCanvas ("window", "Zadanie 11", 800, 800);
	window -> Divide(2, 1);
	window -> cd(1);
	hist -> Draw();
	hist -> Fit("liniowa", "LR", 0, 2);
	fl = hist -> GetFunction("liniowa");
	fl -> Draw("same");
	
	TF1 *ciagla = new TF1("ciagla", Ciagla, 0, 2, 2);
	ciagla -> SetParameters(fl -> GetParameter(0), fl -> GetParameter(1));
	ciagla -> SetLineColor(kGreen);
	ciagla -> Draw("same");
	
	TH1D *h = new TH1D("histogram", "histogram", 100, 0, 2);
	for (int i = 0; i < 100; i++) 
		h -> SetBinContent(i, hist -> GetBinContent(i) - ciagla -> Eval(hist -> GetBinCenter(i)));
	window -> cd(2);
	h -> Draw(); 
	
	TF1 *gauss = new TF1("gau", "gaus", 0, 2, 3);
	gauss -> SetParameters(1, 1, 100);
	h -> Fit("gaus");
	gauss = h -> GetFunction("gaus");
	gauss -> Draw("same");
	
	double mu = gauss -> GetParameter(1);
	double sigma = gauss -> GetParameter(2);
	TF1 *w = new TF1("w", wszystko, 0, 2, 5);
	
	w -> SetParameter(0, mu);
	w -> SetParameter(1, sigma);
	w -> SetParameter(2, gauss -> GetParameter(0));
	w -> SetParameter(3, ciagla -> GetParameter(0));
	w -> SetParameter(4, ciagla -> GetParameter(1));
	window -> cd(1);
	w -> SetLineColor(6);
	w -> Draw("same L");
	
	double a = gauss -> Integral(mu - 2 * sigma, mu + 2 * sigma);
	double b = w -> Integral(mu - 2 * sigma, mu + 2 * sigma);
	cout << "Czystosc = " << a / b << endl;
}
