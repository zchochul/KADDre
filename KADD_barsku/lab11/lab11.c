double Liniowa(double *x, double *par){
if(x[0]<0.8 || x[0]>1.2){ //jeśli obszar spoza sygnału to z ||
return par[0]+ par[1]*x[0];
}
else{
TF1::RejectPoint();//omijamy ...
return 0;
}
}

double LiniowabezRP(double *x, double *par){

return par[0]+ par[1]*x[0];


}

double gauss(double *x, double *par){

return par[0]*TMath::Exp(-0.5*TMath::Power(((x[0]-par[1])/par[2]),2));


}


double tloisygnal(double *x, double *par){

return par[0]+ par[1]*x[0] + par[2]*TMath::Exp(-0.5*TMath::Power(((x[0]-par[3])/par[4]),2));


}

void lab11(){
	Double_t w = 600;
   Double_t h = 600;
   TCanvas *c = new TCanvas("c", "c", w, h);
   c->Divide(1,1);
   
	c->cd(1);
double a,b,d,e,f;
a=1;
b=1;
 TFile *ifile = new TFile("example_data.root");
 TH1D *hist = (TH1D*)ifile->Get("hist");


TF1 *f1 = new TF1("f1", Liniowa,0.0,2.0,2);
f1->SetParameters(1,1);
hist->Fit("f1","0");
b = f1->GetParameter(0);
a = f1->GetParameter(1);

TF1 *f2 = new TF1("f2", LiniowabezRP,0.0,2.0,2);
f2->SetLineColor(3);
f2->SetParameters(b,a);

//hist->Draw();
//f2->Draw("same");

 TH1D *hist2 = hist;
	for(int i =1; i <=hist->GetNbinsX(); i++ ){
	hist2->SetBinContent(i,hist2->GetBinContent(i)-f2->Eval(hist->GetBinCenter(i)));
	}
	

TF1 *f3 = new TF1("f3", gauss,0.0,2.0,3);
f3->SetParameters(320,1,0.05);

hist2->Fit("f3");
d= f3->GetParameter(0);
e = f3->GetParameter(1);
f = f3->GetParameter(2);

TF1 *f4 = new TF1("f4",tloisygnal,0.0,2.0,5);
f4->SetParameters(b,a,d,e,f);
f4->Draw("same");
}
