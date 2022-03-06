int test(){
	TF1 *fun1= new TF1("fun1", "TMath::Sin(x)", 0, 2*TMath::Pi());
	
	TF1 *fun2 = new TF1("fun2", "TMath::Cos(x)", 0, 2*TMath::Pi());
	
	TH1D *hist = new TH1D("h", ";;Y Axis", 6, 0, 6);
	
	
	TGraph* gr = new TGraph();
	
	int pips[] = {1,	2, 	3, 	4, 	5, 	6 };
	int throws[] = {2, 	1, 	5, 	4, 	10, 	12 };
	for (int i=0; i<6; i++ ){
		hist -> SetBinContent(pips[i], throws[i]);
		gr-> SetPoint(i, throws[i], pips[i]);
		}
	
	gr -> SetMarkerSize(2);
	gr -> SetMarkerStyle(22);
	
	TCanvas *c1 = new TCanvas("c1", "window 1", 10, 10, 800, 800);
	c1 -> Divide(2,2);
	
	c1-> cd(1);
	fun1->SetLineColor(kBlue);
	fun1 -> Draw();
	
	c1-> cd(2);
	fun2 ->Draw();
	
	c1-> cd(3);
	fun1 -> Draw();
	fun2 -> Draw("same");
	
	c1-> cd(4);
	hist -> Draw();
	
	TCanvas *c2 = new TCanvas("c2", "window 2", 10, 10, 800, 800);
	//gr -> GetXAxis()->SetTitle("fun graph");
	gr -> Draw("AP");
	return 1;
}

