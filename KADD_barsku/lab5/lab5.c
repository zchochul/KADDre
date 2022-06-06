void lab5() {

	
   Double_t w = 600;
   Double_t h = 600;
   TCanvas *c = new TCanvas("c", "c", w, h);
   c->Divide(2,2);
	
	

	TH2D *h12 = new TH2D("h12","h12",100,1.5,5.,100,0.,3.);
    TH2D *h13 = new TH2D("h13","h13",100,1.5,5.,100,4.,16.);
    TH2D *h23 = new TH2D("h23","h23",100,0.,3.,100,4.,16.);  

	ifstream ifile1,ifile2,ifile3;
	ifile1.open("Dane1.dat");
	ifile2.open("Dane2.dat");
	ifile3.open("Dane3.dat");
	
	double val1,val2,val3,X1,X2,X3,rms1,rms2,rms3,Y1,Y2;
	while(ifile1>>val1 && ifile2>>val2 && ifile3>>val3){	
		h12->Fill(val1,val2);
        h13->Fill(val1,val3);
        h23->Fill(val2,val3);    
    }
    ifile1.close();
	ifile2.close();
	ifile3.close();
    c->cd(1);
    h12->Draw("colz");
    c->cd(2);
    h13->Draw("colz");
    c->cd(3);
    h23->Draw("colz");

	X1 =h12->GetMean(1);
    X2 =h12->GetMean(2);
    X3 =h13->GetMean(2);
    rms1=h12->GetRMS(1);
    rms2=h12->GetRMS(2);
    rms3=h13->GetRMS(2);
    cout<<"X1 = "<<X1<<"	u(X1) = "<<rms1<<endl;
    cout<<"X2 = "<<X2<<"	u(X2) = "<<rms2<<endl;
    cout<<"X3 = "<<X3<<"	u(X3) = "<<rms3<<endl;
    
	

	TMatrixD Cx(3,3);	
	Cx(0,0) = TMath::Power(h12->GetRMS(1),2);
	Cx(1,1) = TMath::Power(h12->GetRMS(2),2);
	Cx(2,2) = TMath::Power(h13->GetRMS(2),2);
	Cx(0,1) = h12->GetCovariance();
	Cx(1,0) = h12->GetCovariance();
	Cx(1,2) = h23->GetCovariance();
	Cx(2,1) = h23->GetCovariance();
	Cx(2,0) = h13->GetCovariance();
	Cx(0,2) = h13->GetCovariance();
	cout<<"Macierz kowariancji zmiennych X:"<<endl;
	Cx.Print();


	Y1 = 2.5 + 1.5*X1 + 3*X3;
	Y2 = 2*X1 + 0.3*X2 +X3;
	cout<<"Y1 = "<<Y1<<endl;
    cout<<"Y2 = "<<Y2<<endl;


	TMatrixD T(2,3);

	T(0,0)=1.5;
	T(0,1)=0.;
	T(0,2)=3.;
	T(1,0)=2.;
	T(1,1)=0.3;
	T(1,2)=1.;

	TMatrixD Ttrans(3,2);
	Ttrans.Transpose(T);

	TMatrixD Cy(2,2);
	Cy = T*Cx*Ttrans;
	
	cout<<"Macierz kowariancji zmiennych Y:"<<endl;
	Cy.Print();

	
	cout<<Form("u(Y1)=%.2f",TMath::Power(Cy(0,0),0.5))<<endl;
	cout<<Form("u(Y2)=%.2f",TMath::Power(Cy(1,1),0.5))<<endl;
	

	cout<<Form("rho(Y1,Y2) = %.2f",Cy(1,0)/TMath::Power(Cy(0,0),0.5)/TMath::Power(Cy(1,1),0.5))<<endl;
	
	


}
