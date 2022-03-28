
void lab5(){
	
	TCanvas *c1 = new TCanvas();
	c1-> Divide(2,2);
	
	double x1min = 1.5, x1max = 5.0;
	double x2min = 0.0, x2max = 3.0;
	double x3min = 4.0, x3max = 16.0;
	TH2D *h12 = new TH2D("h12","Hist12",100,x1min,x1max,100,x2min,x2max);
	TH2D *h13 = new TH2D("h13","Hist13",100,x1min,x1max,100,x3min,x3max);
	TH2D *h23 = new TH2D("h13","Hist23",100,x2min,x2max,100,x3min,x3max);
	
	
	ifstream ifile1;
	ifile1.open("Dane1.dat");
	double val1;
	
	ifstream ifile2;
	ifile2.open("Dane2.dat");
	double val2;
	
	ifstream ifile3;
	ifile3.open("Dane3.dat");
	double val3;
	
	//Histogram X1 X2
	while(ifile1>>val1 && ifile2>>val2 && ifile3>>val3)
	{
		h12->Fill(val1, val2);
		h13->Fill(val1, val3);
		h23->Fill(val2, val3);
		
	}
	c1->cd(1);
	h12->Draw("colz");
	
	c1->cd(2);
	h13->Draw("colz");
	
	c1->cd(3);
	h23->Draw("colz");
	
	ifile1.close();
	ifile2.close();
	ifile3.close();
	
	double y1, y2;
	double x1 = h12->GetMean(1);
	double x2 = h12->GetMean(2);
	double x3 = h23->GetMean(2);
	
	TMatrixD matcov(3,3);
	
	double covx1x2 = h12 -> GetCovariance(1,2);
	double covx1x3 = h13 -> GetCovariance(1,2);
	double covx2x3 = h23 -> GetCovariance(1,2);
	
	double sigmax1 = (h12 -> GetRMS(1))*(h12 -> GetRMS(1));
	double sigmax2 = (h12 -> GetRMS(2)) * (h12 -> GetRMS(2));
	double sigmax3 = (h23 -> GetRMS(2)) * (h23 -> GetRMS(2));
	
	matcov(0,0) = sigmax1;
	matcov(1,1) = sigmax2;
	matcov(2,2) = sigmax3;
	
	matcov(0,1) = covx1x2;
	matcov(1,0) = covx1x2;
	
	matcov(0,2) = covx1x3;
	matcov(2,0) = covx1x3;
	
	matcov(1,2) = covx2x3;
	matcov(2,1) = covx2x3;
	
	matcov.Print();
	
	TMatrixD tmat(2,3);
	tmat(0,0) = 2;
	tmat(0,1) = 5;
	tmat(0,2) = 1;
	
	tmat(1,0) = 0.5;
	tmat(1,1) = 4;
	tmat(1,2) = 0;
	
	tmat.Print();
	
	TMatrix help1 = tmat * matcov;
	TMatrix covhelp(3,2);
	covhelp.Transpose(tmat);
	
	TMatrix result = help1 * covhelp;
	
	result.Print();
	
	double errory1 = sqrt(result(0,0));
	double errory2 = sqrt(result(1,1));
	cout << "error Y1= " << errory1 << endl;
	cout << "error Y2= " << errory2 << endl;
	
	
	double y1 = 2 * x1 + 5 * x2 + x3;
	double y2 = 3 + 0.5 * x1 + 4 * x2;
	
	cout << "Y1 = " << y1 << endl;
	cout << "Y2 = " << y2 << endl;
	
	double corfac =  result(0,1)/sqrt(result(0,0) * result(1,1));
	cout <<"corfac(X, Y)= " <<corfac << endl;
	
}
