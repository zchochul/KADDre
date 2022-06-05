double fcn (double *x, double *params) {
	if (x[0]>=0 && x[1] >=0)
		return params[0] * TMath::Sin(x[0]*x[1]);
	return 0;
	}
	
void lab14 (void) {
	
	// FUNKCJA NORMOWANIE
	int N = 100000;
	TF2 *fun =  new TF2 ("fun", fcn, 0, TMath::Pi()/2, 0, TMath::Pi()/2, 1);
	fun -> SetParameter(0, 1);
	double norm = fun -> Integral(0, TMath::Pi()/2, 0, TMath::Pi()/2);
	cout << "Stała normująca c = " << 1/norm << "\n";
	fun -> SetParameter(0, 1/norm);
	
	// WYPELNIENIE
	double x, y;
	TH2D *hist = new TH2D("hist", "Gestosc prawdopodobienstwa", 30, 0, TMath::Pi()/2, 30, 0, TMath::Pi()/2);
	for (int i = 0; i < N; i++) {
		fun -> GetRandom2(x, y);
		hist -> Fill(x, y);
	}
	
	// HISTOGRAM NORMOWANIE
	double normhist = hist -> Integral(1, 30, 1, 30, "width");
	hist -> Scale(1/normhist);
	
	TCanvas *window = new TCanvas ("window", "Zadanie 3", 800, 800);
	window -> Divide(2, 2);
	window -> cd(1);
	hist -> Draw("LEGO1");
	fun -> GetXaxis() -> SetTitle("x");
	fun -> GetYaxis() -> SetTitle("y");
	fun -> GetZaxis() -> SetTitle("f(x, y)");
	fun -> SetTitle("f(x, y)");
	
	// DISTRYBUANTA
	window -> cd(2);
	TH2D *dys = new TH2D ("dys", "Dystrybuanta", 30, 0, TMath::Pi()/2, 30, 0, TMath::Pi()/2);
	for(double iix = 1; iix <= 30; iix++) {
		for(double iiy = 1; iiy <= 30; iiy ++) {
			dys -> SetBinContent(iix, iiy, (hist -> Integral(1, iix, 1, iiy, "width")));
		}
	}
	
	dys -> Draw("LEGO1");
	dys -> GetXaxis() -> SetTitle("x");
	dys -> GetYaxis() -> SetTitle("y");
	dys -> GetZaxis() -> SetTitle("F(x, y)");
	dys -> SetTitle("F(x, y)");
	
	// GESTOSC X
	window -> cd(3);
	TH1 *funcx = (TH1*) (hist -> ProjectionX());
	funcx -> Draw("");
	funcx -> SetTitle("Gestosc brzegowa x");
	funcx -> GetXaxis() -> SetTitle("x");
	funcx -> GetYaxis() -> SetTitle("g(x)");
	
	// GESTOSC Y
	window -> cd(4);
	TH1 *funcy = (TH1*) (hist -> ProjectionY());
	funcy -> Draw(""); 
	funcy -> SetTitle("Gestosc brzegowa y");
	funcy -> GetXaxis() -> SetTitle("y");
	funcy -> GetYaxis() -> SetTitle("h(y)");
	
	// WARTOSCI
	cout << "\nWartosci oczekiwane: E(X) = " << hist -> GetMean(1) << ", \nE(Y) = " << hist -> GetMean(2);
	cout << "\nOdchylenie standardowe: dla X = " << hist -> GetRMS(1) << ", \ndla Y = " << hist -> GetRMS(2);
	cout << "\nKowariancja = " << hist -> GetCovariance(1, 2);
	cout << "\nWspolczynnik korelacji = " << hist -> GetCorrelationFactor(1, 2) << endl;
}
