void splot(int k, TH1D *h, int n) {
	double u, sum = 0.0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			u = gRandom -> Uniform(0, 1);
			sum += u;
		}
		h -> Fill(sum);
		sum = 0.0;
	}
} 


void lab19 (void) {
	TF1 *chi = new TF1("chi", "[0] * TMath::Power(x, [1] - 1) * TMath::Exp(-1 * x/2)", 0, 20);
	TF1 *allchi[20];
	double lambda, k;
	TMultiGraph *graph1 = new TMultiGraph();
	TMultiGraph *graph2 = new TMultiGraph();
	for (int i = 2; i < 21; i++) {
		allchi[i-1] = new TF1();
		lambda = (double) i/2;
		k = 1 / (TMath::Gamma(lambda) * TMath::Power(2, lambda));
		chi -> Copy(*allchi[i-1]);
		allchi[i-1] -> SetParameter(0, k);
		allchi[i-1] -> SetParameter(1, lambda);
		allchi[i-1] -> SetLineColor(i);
		graph1 -> Add(new TGraph(allchi[i-1]));
		graph2 -> Add((TGraph*) (allchi[i-1]) -> DrawIntegral());
	}
	TCanvas *c1 = new TCanvas("c1", "Zadanie 9.1", 800, 500);
	c1 -> Divide(2, 1);
	c1 -> cd(1);
	graph1 -> Draw("AL");
	c1 -> cd(2);
	graph2 -> Draw("AL");

	int n = 2, ss;
	double chisq;
	TF1 *gauss = new TF1();
	TH1D *hist;
	do {
		hist = new TH1D("hist", "histogram", 100, 0, 10);
		splot(n, hist, 10000);
		hist -> Fit("gaus");
		gauss = hist -> GetFunction("gaus");
		ss = gauss -> GetNDF();
		chisq = gauss -> GetChisquare();
		n++;
	}
	while(chisq/ss >= 1);
	
	cout << n << endl;
	
	TCanvas *c2 = new TCanvas("c2", "Zadanie 9.2", 500, 500);
	c2 -> cd(1);
	hist -> Draw();
	gauss -> Draw("same"); 
	
}
