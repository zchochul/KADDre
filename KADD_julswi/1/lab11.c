void lab11(void){
	TF1 *fun1 = new TF1("fun1", "cos(x)", 0, 2*TMath::Pi());
	fun1 -> SetLineColor(kBlue);
	TF1 *fun2 = new TF1("fun2", "sin(x)/x", 0, 2*TMath::Pi());
	fun2 -> SetLineColor(kGreen);
	TCanvas *window = new TCanvas ("window", "Zadanie1", 500, 500);
	window -> Divide(2, 2);
	window -> cd(1);
	fun1 -> GetXaxis() -> SetTitle("x");
	fun1 -> SetTitle("cos(x)");
	fun1 -> DrawCopy();
	
	window -> cd(2);
	fun2 -> GetXaxis() -> SetTitle("x");
	fun2 -> SetTitle("sin(x)/x");
	fun2 -> Draw();
	
	window -> cd(3);
	fun1 -> GetXaxis() -> SetTitle("x");
	fun1 -> SetTitle("sin(x)/x i cos(x)");
	fun1 -> Draw();
	fun2 -> Draw("same");
	
	double oczka[6] = {1, 2, 3, 4, 5, 6};
	double rzuty[6] = {15, 3, 12, 25, 6, 19};
	TH1D *histo = new TH1D ("histo", "Histogram", 6, 0.0, 6.0);
	
	for (int i = 1; i <= (histo -> GetNbinsX()); i++) {
		histo -> SetBinContent(i, rzuty[i-1]);
	}
	
	window -> cd(4);
	histo -> Draw();
	
	TGraph *graph = new TGraph(6, rzuty, oczka);
	graph -> SetName("Wykres 1");
	graph -> SetMarkerStyle(kFullSquare);
	
	TCanvas *window1 = new TCanvas("window1", "Wykres", 500, 400);
	graph -> Draw("ap");
}
