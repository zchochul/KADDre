
	
void lab6(){
/*
	TCanvas *c1 = new TCanvas();
	c1-> Divide(2,3);
	
	TH1D *hUniform1 = new TH1D("hUniform1","Uniform distribution",100,0,1);
	TH2D *hCorr1 = new TH2D("hCorr1","Correlation",100,0,1,100,0,1);
	
	TH1D *hUniform2 = new TH1D("hUniform2","Uniform distribution",100,0,1);
	TH2D *hCorr2 = new TH2D("hCorr2","Correlation",100,0,1,100,0,1);
	
	TH1D *hUniform3 = new TH1D("hUniform3","Uniform distribution",100,0,1);
	TH2D *hCorr3 = new TH2D("hCorr3","Correlation",100,0,1,100,0,1);
	
	const int N = 1000000;
	 
	int m1 = 97;
	int g1 = 23;
	ofstream ofile;
	ofile.open("data1.dat");
	unsigned int x1[N];
	unsigned int x1[0] = time(NULL);
	for(int i=0;i<N;i++){
		x1[i+1]= (g1*x1[i] )%m1;
		ofile<< x1[i]<<endl;
		hCorr1->Fill((double)x1[i]/m1, (double)x1[i+1]/m1);
		hUniform1-> Fill((double)x1[i]/m1);
		
	}
	
	ofile.close();
	c1->cd(1);
	hCorr1->Draw("colz");
	
	c1->cd(2);
	hUniform1->Draw();
	
	int m2 = 32363;
	int g2 = 157;
	ofstream ofile;
	ofile.open("data2.dat");
	unsigned int x2[N];
	unsigned int x2[0] = time(NULL);
	for(int i=0;i<N;i++){
		x2[i+1]= (g2*x2[i] )%m2;
		ofile<< x2[i]<<endl;
		hCorr2->Fill((double)x2[i]/m2, (double)x2[i+1]/m2);
		hUniform2-> Fill((double)x2[i]/m2);
	}
	ofile.close();
	c1->cd(3);
	hCorr2->Draw("colz");
	
	c1->cd(4);
	hUniform2->Draw();
	
	int m3 = 147483647;
	int g3 = 16807;
	ofstream ofile;
	ofile.open("data3.dat");
	int x3[N];
	int x3[0] = time(NULL);
	for(int i=0;i<N;i++){
		x3[i+1]= (g3*x3[i] )%m3;
		ofile<< x3[i]<<endl;
		hCorr3->Fill((double)x3[i]/m3, (double)x3[i+1]/m3);
		hUniform3-> Fill((double)x3[i]/m3);
	}
	ofile.close();
	c1->cd(5);
	hCorr3->Draw("colz");
	
	c1->cd(6);
	hUniform3->Draw();
*/
	/////////////////////////////////
	TF1 *fun1 = new TF1("fun1", "1./[0] * TMath::Exp(-x/[0])", 0, 8);
	fun1->SetParameter(0, 2);
	int N2 = 10000;
	unsigned int m3 = 147483647;
	unsigned int g3 = 16807;
	TH1D *hUniform4 = new TH1D("hUniform4","Uniform distribution",100,0,10);
	ifstream ifile;
	ifile.open("data3.dat");
	double val;
	
		for(int i=0;i<N2;i++){
			ifile >> val;
			hUniform4->Fill(-2*TMath::Log(1-(double)val/m3));
		}
	
	ifile.close();
	TCanvas *c2 = new TCanvas();
	hUniform4->Scale(1./(hUniform4->Integral("width")));
	hUniform4->Draw();
	fun1->Draw("same");
}
