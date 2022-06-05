double fcn (double *x, double *params) {
	if (x[0] >= 0 && x[1] >= 0)
		return params[0] * TMath::Power(x[0], params[1]) * TMath::Power(x[1], params[2]);
	return 0;
	}
	
void lab13(void) {
	
	TF2 *fun =  new TF2 ("fun", fcn, 0, 1, 0, 1, 3);
	TCanvas *window = new TCanvas ("window", "Zadanie 2", 800, 800);
	fun -> SetParameter(0, 1);
	fun -> SetParameter(1, 1);
	fun -> SetParameter(2, 3);
	
	double norm = fun -> Integral(0, 1, 0, 1);
	fun -> SetParameter(0, 8);
	cout << "Stała normująca c = " << 1/norm << "\n";

	window -> Divide(2, 2);
	window -> cd(1);
	fun -> Draw("SURF1");
	fun -> GetXaxis() -> SetTitle("x");
	fun -> GetYaxis() -> SetTitle("y");
	fun -> GetZaxis() -> SetTitle("f(x, y)");
	fun -> SetTitle("f(x, y)");
	
	window -> cd(2);
	TGraph2D *dys = new TGraph2D ();
	int n = 0;
	for(double ix = 0; ix <= 1.; ix += 1./20) {
		for(double iy = 0; iy <= 1.; iy += 1./20) {
			n++;
			dys -> SetPoint(n, ix, iy, (fun -> Integral(0, ix, 0, iy)));
		}
	}
	dys -> Draw("SURF1");
	dys -> GetXaxis() -> SetTitle("x");
	dys -> GetYaxis() -> SetTitle("y");
	dys -> GetZaxis() -> SetTitle("F(x, y)");
	dys -> SetTitle("F(x, y)");
	
	TH2 *func = (TH2*) (fun -> GetHistogram());
	window -> cd(3);
	TH1 *funcx = (TH1*) (func -> ProjectionX());
	funcx -> Draw("L");
	funcx -> SetTitle("Gestosc brzegowa x");
	funcx -> GetXaxis() -> SetTitle("x");
	funcx -> GetYaxis() -> SetTitle("g(x)");
	
	window -> cd(4);
	TH1 *funcy = (TH1*) (func -> ProjectionY());
	funcy -> Draw("L"); 
	funcy -> SetTitle("Gestosc brzegowa y");
	funcy -> GetXaxis() -> SetTitle("y");
	funcy -> GetYaxis() -> SetTitle("h(y)");
}
