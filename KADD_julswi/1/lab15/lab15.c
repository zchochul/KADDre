void lab15 (void) {
	// 1
	TH2D *x1 = new TH2D("x1", "hist12", 100, 1.5, 5, 100, 0, 2.5); //X1 X2
	TH2D *x2 = new TH2D("x2", "hist23", 100, 0.5, 2.5, 100, 4, 16); //X2 X3
	TH2D *x3 = new TH2D("x3", "hist13", 100, 1.5, 5, 100, 4, 16); //X1 X3
	
	 ifstream ifile1, ifile2, ifile3;
	 ifile1.open("Dane1.dat");
	 ifile2.open("Dane2.dat");
	 ifile3.open("Dane3.dat");
	 double val1, val2, val3;
	 while (ifile1 >> val1) {
		 ifile2 >> val2;
		 ifile3 >> val3;
		 x1 -> Fill(val1, val2);
		 x2 -> Fill(val2, val3);
		 x3 -> Fill(val1, val3);
	 }
	 ifile1.close();
	 ifile2.close();
	 ifile3.close();
	 
	 TCanvas *window = new TCanvas ("window", "Zadanie 5", 800, 800);
	window -> Divide(2, 2);
	window -> cd(1);
	x1 -> Draw("COLZ");
	window -> cd(2);
	x2 -> Draw("COLZ");
	window -> cd(3);
	x3 -> Draw("COLZ");
	
	double x1av = x1 -> GetMean(1);
	double x2av = x1 -> GetMean(2);
	double x3av = x2 -> GetMean(2);
	
	cout << "\nWartosci oczekiwane: E(X1) = " << ceil(x1av * 100.0) / 100.0 << ", \nE(X2) = " << ceil(x2av * 100.0) / 100.0 << ", \nE(X3) = " << ceil(x3av * 100.0) / 100.0;
	cout << "\nOdchylenie standardowe: dla X1 = " << x1 -> GetRMS(1) << ", \ndla X2 = " << x1 -> GetRMS(2) << ", \ndla X3 = " << x2 -> GetRMS(2);
	cout << "\nKowariancja: (X1, X2) = " << x1 -> GetCovariance(1, 2) << "\n(X2, X3) = " << x2 -> GetCovariance(1, 2) << "\n(X1, X3) = " << x3 -> GetCovariance(1, 2);
	
	//2 MACIERZ KOWARIANCJI X
	TMatrixD matx(3, 3);
	matx[0][0] = (x1 -> GetRMS(1)) * (x1 -> GetRMS(1));
	matx[0][1] = x1 -> GetCovariance(1, 2);
	matx[0][2] = x3 -> GetCovariance(1, 2);
	matx[1][0] = x1 -> GetCovariance(1, 2);
	matx[1][1] = (x1 -> GetRMS(2)) * (x1 -> GetRMS(2));
	matx[1][2] = x2 -> GetCovariance(1, 2);
	matx[2][0] = x3 -> GetCovariance(1, 2);
	matx[2][1] = x2 -> GetCovariance(1, 2);
	matx[2][2] = (x3 -> GetRMS(2)) * (x3 -> GetRMS(2));
	cout << "\nMacierz kowariancji X: \n";
	matx.Print();
	
	//MACIERZ SREDNICH X
	TMatrixD xmat(3, 1);
	xmat[0][0] = x1av;
	xmat[1][0] = x2av;
	xmat[2][0] = x3av;
	
	//MACIERZ T
	TMatrixD t(2, 3);	
	t[0][0]  = 3;	
	t[0][1]  = 2;	
	t[0][2]  = 1;	
	t[1][0]  = 5;	
	t[1][1]  = 2;	
	t[1][2]  = 0;	
	
	TMatrixD a(2, 1);
	a[0][0] = 0;
	a[1][0] = 2;
	
	// 3 MACIERZ WARTOŚCI ŚREDNICH Y
	TMatrixD maty(2, 1);
	maty = t * xmat + a;
	
	// 4 MACIERZ KOWARIANCJI Y
	TMatrixD covy(2,2);
	covy = t * matx * t.Transpose(t);
	cout << "\nMacierz kowariancji Y: \n";
	covy.Print();
	
	// 5
	double uy1 = TMath::Sqrt(covy[0][0]);
	double uy2 = TMath::Sqrt(covy[1][1]);
	
	cout << "\nWartosci oczekiwane: E(Y1) = " << maty[0][0] << ", \nE(Y2) = " << maty[1][0] << endl;
	cout << "u(Y1) = " << uy1 << endl << "u(Y2) = " << uy2 << endl;
	// 6
	cout << "Wspolczynnik korelacji (Y1, Y2) = " << covy[0][1] / uy1 / uy2 << endl << "(Y2, Y1) = " << covy[1][0] / uy1 / uy2 << endl;
}
