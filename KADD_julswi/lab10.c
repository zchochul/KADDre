 double chi2(TH1D *h, TF1 *f, int kmax) {
	double sum = 0;
	double tmp;
	for (int i = 0; i < kmax; i++) {
		tmp = (h -> GetBinContent(i+1) - f -> Eval(i+0.5)) * (h -> GetBinContent(i+1) - f -> Eval(i+0.5));
		sum += tmp / (f -> Eval(i+0.5));
	}
	return sum;
}

int testchi2(double T, double alpha, int ndf) {
	TF1 *chi = new TF1("chi", "[0] * TMath::Power(x, [1] - 1) * TMath::Exp(-1 * x/2)", 0, 20);
	int k = 1 / (TMath::Gamma(ndf) * TMath::Power(2, ndf));
	chi -> SetParameter(0, k);
	chi -> SetParameter(1, ndf);
	double spr = chi -> Integral(0, T);
	if ((1 - alpha) < spr) {
		return 1;
	}
	else 
		return 0;
}


void lab10(void) {
	int kmax = 9;
	TH1D *hist = new TH1D("hist", "histogram", 9, 0, 9);
	ifstream ifile;
	ifile.open("dane10.txt");
	double val1, val2;
	while (ifile >> val1) {
		ifile >> val2;
		hist -> SetBinContent(val1+1, val2);
	}
	ifile.close();
	TCanvas *window = new TCanvas ("window", "Zadanie 10", 800, 800);
	hist -> Draw();
	double lambda, sum1 = 0., sum2 = 0.;
	for (int i = 0; i < kmax ; i++) {
		sum1 += hist -> GetBinContent(i+1) * i;
		sum2 += hist -> GetBinContent(i+1);
	}
	lambda = sum1 / sum2;
	
	TF1 *fitted = new TF1("poifit", "[1]*TMath::PoissonI(x, [0])", 0, 9);
	fitted -> SetParameter(1, hist -> Integral());
	fitted -> SetParameter(0, 1);
	hist -> Fit("poifit", "LR", 0, 9);
	fitted = hist -> GetFunction("poifit");
	fitted -> Draw("same");
	
	TF1 *poison = new TF1("poi", "[1]*TMath::PoissonI(x, [0])", 0, 9);
	poison -> SetParameter(0, lambda);
	poison -> SetParameter(1, hist -> Integral());

	poison -> SetLineColor(kBlue);
	poison -> Draw("same");
	cout << "lambda: " << lambda << endl;
	
	double T = chi2(hist, fitted, kmax);
	int ndf = 8;
	double alpha = 0.01;
	int spr = testchi2(T, alpha, ndf);
	cout << "Statystyka testowa T: " << T << endl;
	cout << "T/NDF: " << T / 8 << endl;
	cout << "lambda ROOT: " << fitted -> GetParameter(0) << endl;
	
	cout << "Chi kwadrat: " << fitted -> GetChisquare() << endl;
	cout << "Chi kwadrat / NDF: " << fitted -> GetChisquare() / 7 << endl;
	if (spr == 1)
		cout << "Odrzucamy hipotezę" << endl;
	else if (spr == 0)
		cout << "Brak podstaw do odrzucenia hipotezy" << endl;
	
}
