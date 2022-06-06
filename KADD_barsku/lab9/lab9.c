double T;
double chi2(TH1D *h, TF1 *f){
T=0;
for(int i=1; i <10; i++){
	T+=(h->GetBinContent(i)- f->Eval(i-1))*(h->GetBinContent(i)- f->Eval(i-1))/(f->Eval(i-1));
}
return T;
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

void lab9(){

 Double_t w = 600;
 Double_t h = 600;
 TCanvas *c = new TCanvas("c", "c", w, h);
 c->Divide(1,2);

TH1D *t = new TH1D("t","t",9,0,9);



ifstream ifile1;
ifile1.open("dane10.txt");
double val, vall,lambda,sumxy,sumy,lambdar;
sumxy = 0;
sumy = 0;
while(ifile1>>val && ifile1>>vall){
sumxy += val*vall;
sumy += vall;
t->SetBinContent(val+1,vall);
}
ifile1.close();
lambda = sumxy/sumy;
TF1 *poi = new TF1("poi","[1]*TMath::PoissonI(x,[0])",0,8);
poi->SetParameters(1,1);
c->cd(1);
t->Fit("poi","LR");
lambdar = poi->GetParameter(0);

TF1 *poi1 = new TF1("poi1","[1]*TMath::PoissonI(x,[0])",0,8);
poi1->SetParameter(0,lambda);
poi1->SetParameter(1,t->Integral(1,9));
poi1->SetLineColor(8);
poi1->Draw("same");
if(testChi2(chi2(t,poi),0.01,7)){
cout<<"Nie ma podstaw"<<endl;
}
else{
cout<<"Nalezy odrzucic"<<endl;
}

cout<<"statystyka testowa = "<<chi2(t,poi)<<endl;
cout<<"lamda = "<<lambda<<endl;
cout<<"lamdaROOT = "<<lambdar<<endl;

cout<<"chi2= "<<poi->GetChisquare()<<endl;
cout<<"ndfroot= "<<poi->GetNDF()<<endl;
cout<<"ndf= "<<t->GetNbinsX()-1<<endl;
cout<<"T/NDF= "<<chi2(t,poi)/(t->GetNbinsX()-1)<<endl;
cout<<"chi2/NDF= "<<poi->GetChisquare()/poi->GetNDF()<<endl;
}
