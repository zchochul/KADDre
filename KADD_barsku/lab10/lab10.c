
double dopasuj(int st, int n, double *tj, double *yj, double *sigmaj,double *wsp, double *bwsp){
	st++;
	TMatrixD *wektory = new TMatrixD(n,1);
     for(int j=0; j<n; j++) (*wektory)(j,0) = yj[j];
	
	TMatrixD *macierzA = new TMatrixD(n,st);
    for(int j=0; j<n; j++){
       (*macierzA)(j,0) = 1;
    } 
	
	for(int j=0; j<n; j++){
		for(int jj=0; jj<st; jj++){
            (*macierzA)(j,jj) = TMath::Power(tj[j],(double)jj);                  
      }         
    }
	
 	TMatrixD *macierzGy = new TMatrixD(n,n);
     for(int j=0; j<n; j++) (*macierzGy)(j,j) = 1/sigmaj[j]/sigmaj[j];
	
     TMatrixD *macierzH = new TMatrixD(n,n);    
     for(int j=0; j<n; j++){ 
		(*macierzH)(j,j) = 1/sigmaj[j];
	}


	
	TMatrixD *macierzAA = new TMatrixD(*macierzH,TMatrixD::kMult,*macierzA);
	
	TMatrixD *macierzcc =new TMatrixD(*macierzH,TMatrixD::kMult,*wektory);
	
	
	TMatrixD *macierzAAT = new TMatrixD(TMatrix::kTransposed,*macierzAA);
	TMatrixD *macierzAATAA = new TMatrixD(*macierzAAT,TMatrixD::kMult,*macierzAA);
	
	macierzAATAA->Invert();
	TMatrixD *macierzAATAAiAAT = new TMatrixD(*macierzAATAA,TMatrixD::kMult,*macierzAAT);
	TMatrixD *x =  new TMatrixD(*macierzAATAAiAAT,TMatrixD::kMult,*macierzcc);
	for(int j=0; j<st; j++){ 
	wsp[j] = (*x)(j,0);
	}
	for(int j=0; j<st; j++){ 
	bwsp[j] = (*macierzAATAA)(j,j);
	}
	
	TMatrixD *eta = new TMatrixD(*macierzA,TMatrixD::kMult,*x);
	double M =0;
	for(int j=0; j<n; j++) {
	M += (yj[j]-eta(j,0))/sigmaj[j]*(yj[j]-eta(j,0))/sigmaj[j];
	}
	return M;
}





double pdf(double *x, double *k){
	return TMath::Power(x[0],k[0]/2-1)*TMath::Exp(-x[0]/2)/TMath::Power(2,k[0]/2)/TMath::Gamma(k[0]/2);

}




bool testChi2(double T,double alpha, int ndf){

TF1 *ff = new TF1("ff", pdf,0.0,20.0,1);
ff->SetParameter(0,ndf);
if (1-alpha >ff->Integral(0,T)) {
return true;
}
else{
return false;
}
}




void lab10(){

   Double_t w = 600;
   Double_t h = 600;
   TCanvas *c = new TCanvas("c", "c", w, h);
   c->Divide(1,1);
   
   double val,vall;
   int i =0;
   double t[15], y[15], sigma[15],sigmax[15];
 
   ifstream ifile;
   ifile.open("dane.dat");
   
   while(ifile>>val && ifile>>vall){
    t[i] = val;
    y[i] = vall;
    sigma[i] = TMath::Power(vall,0.5);
	sigmax[i] =0;
    i++;
   }

	ifile.close();
	TGraphErrors *gr = new TGraphErrors(15,t,y,sigmax,sigma);
	c->cd(1);
	gr->Draw("ALP");
	double wsp[10], bwsp[10];

	for(int j=0; j<6; j++) {
	TF1 *poi1 = new TF1("poi1","[0]+[1]*x+[2]*x^2+[3]*x^3+[4]*x^4+[5]*x^5",0,15);
poi1->SetParameters(wsp[0],wsp[1],wsp[2],wsp[3],wsp[4],wsp[5]);
poi1->SetLineColor(j+1);
poi1->Draw("same");
cout<<"Dla wielomianu stopnia"<<j<<endl;
if(testChi2(dopasuj(j,15,t,y,sigma,wsp,bwsp),0.01,14-j)){
cout<<"Nie ma podstaw"<<endl;
}
else{
cout<<"Nalezy odrzucic"<<endl;
}
      
   
 }   
    
     
     
   
   
}
