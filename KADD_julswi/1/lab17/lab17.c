int seedd;

double generator (int g, int m) {
	int val = (g * seedd) % m;
	seedd = val;
	return (double) val / m;
}

void lab17(void) {

	seedd = time(NULL);
	int N = 10000;
	double val, val1;
	
	TH1D *hist1 = new TH1D ("Histogram 1", "hist1", 100, 0, 1);
	TH1D *hist2 = new TH1D ("Histogram 2", "hist2", 100, 0, 1);
	TH1D *hist3 = new TH1D ("Histogram 3", "hist3", 100, 0, 1);
	TH2D *hCorr1 = new TH2D("Histogram korelacji 1", "hCorr1", 100, 0, 1, 100, 0, 1);
	TH2D *hCorr2 = new TH2D("Histogram korelacji 2", "hCorr2", 100, 0, 1, 100, 0, 1);
	TH2D *hCorr3 = new TH2D("Histogram korelacji 3", "hCorr3", 100, 0, 1, 100, 0, 1);
	
	TCanvas *c1 = new TCanvas();
	c1-> Divide(2,3);
	
	ofstream ofile;
	ofile.open("Dane1.dat");
	for (int i = 0; i < N; i++) {
		val1 = val;
		val = generator (23, 97);
		ofile << val << endl;
		hist1 -> Fill(val);
		hCorr1 -> Fill(val1, val);
	}
	ofile.close();
	c1->cd(1);
	hCorr1->Draw("colz");
	c1->cd(2);
	hist1->Draw();
	
	seedd  = time(NULL);
	ofile.open("Dane2.dat");
	for (int i = 0; i < N; i++) {
		val1 = val;
		val = generator (223, 12799);
		ofile << val << endl;
		hist2 -> Fill(val);
		hCorr2 -> Fill(val1, val);
	}
	ofile.close();
	c1->cd(3);
	hCorr2->Draw("colz");
	c1->cd(4);
	hist2->Draw();
	
	seedd  = time(NULL);
	ofile.open("Dane3.dat");
	for (int i = 0; i < N; i++) {
		val1 = val;
		val = generator (16807, 147483647);
		ofile << val << endl;
		hist3 -> Fill(val);
		hCorr3 -> Fill(val1, val);
	}
	ofile.close();
	c1->cd(5);
	hCorr3->Draw("colz");
	c1->cd(6);
	hist3->Draw();
	
	/*
	TF1 *fun1 = new TF1("fun1", "1./[0] * TMath::Exp(-x/[0])", 0, 8);
	fun1 -> SetParameter(0, 3);
	TF1 *dys = new TF1("dys", "-[0] * TMath::Log(1 - x)", 0, 8);
	dys -> SetParameter(0, 3);
	
	TH1D *hf1 = new TH1D ("Histogram funkcji 1", "hf1", 100, 0, 8);
	TH1D *hf2 = new TH1D ("Histogram funkcji 2", "hf2", 100, 0, 8);
	TH1D *hf3 = new TH1D ("Histogram funkcji 3", "hf3", 100, 0, 8);
	TH1D *hf4 = new TH1D ("Histogram funkcji 4", "hf4", 100, 0, 8);
	
	TCanvas *c2 = new TCanvas();
	c2-> Divide(4, 1);
	c2 -> cd(1);
	ifstream ifile;
	ifile.open("Dane1.dat");
	for (int i = 0; i < N; i++) {
		ifile >> val;
		hf1 -> Fill(dys -> Eval(val));
	}	
	ifile.close();
	hf1 -> Scale(1 / hf1 -> Integral("width"));
	hf1 -> Draw();
	fun1 -> Draw("Same");

	c2 -> cd(2);
	ifile.open("Dane2.dat");
	for (int i = 0; i < N; i++) {
		ifile >> val;
		hf2 -> Fill(dys -> Eval(val));
	}	
	ifile.close();
	hf2 -> Scale(1 / hf2 -> Integral("width"));
	hf2 -> Draw();
	fun1 -> Draw("Same");
	
	c2 -> cd(3);
	ifile.open("Dane3.dat");
	for (int i = 0; i < N; i++) {
		ifile >> val;
		hf3 -> Fill(dys -> Eval(val));
	}	
	ifile.close();
	hf3 -> Scale(1 / hf3 -> Integral("width"));
	hf3 -> Draw();
	fun1 -> Draw("Same");
	
	c2 -> cd(4);
	for (int i = 0; i < N; i++) {
		val = gRandom -> Rndm(1);
		hf4 -> Fill(dys -> Eval(val));
	}	
	hf4 -> Scale(1 / hf4 -> Integral("width"));
	hf4 -> Draw();
	fun1 -> Draw("Same");
	*/
}
