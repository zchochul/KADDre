void lab12(void) {
	TF1 *fun = new TF1 ("fun", "TMath::Exp(-x/[0])/[0]", 0, 100);
	fun-> SetParameter(0, 4);
	
	TF1 *dys = new TF1 ("dys", "1 - TMath::Exp(-x/[0])", 0, 100);
	dys-> SetParameter(0, 4);
	
	TCanvas *window = new TCanvas ("window", "Zadanie 2", 800, 400);
	window -> Divide(2,1);
	
	window -> cd(1);
	fun -> Draw();
	
	window -> cd(2);
	dys -> Draw();
	fun -> DrawIntegral("same");
	
	double prob;
	prob = (dys -> Eval(8)) - (dys -> Eval(2));
	cout << "Prawdpod. od 5 do 8 - " << prob;
	
	cout << "\nWartosc oczekiwana = " << (fun -> Mean(0, 100));
	
	cout << "\nWariancja = " << (fun -> Variance(0, 100)); 
	
	cout << "\nModa rozkładu = " << (fun -> GetMaximumX());
	
	cout << "\nKwantyle \n- kwartyl dolny = " << (dys -> GetX(0.25)) << "\n- mediana = " << (dys -> GetX(0.5)) << "\n- kwartyl górny = " << (dys-> GetX(0.75));
	
}
