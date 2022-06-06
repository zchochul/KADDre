void lab1(){
   Double_t w = 600;
   Double_t h = 600;
TCanvas *c = new TCanvas("c","c",w,h);
c->SetWindowSize(w + (w - c->GetWw()), h + (h - c->GetWh()));
c->Divide(2,2);

TF1 *f1 = new TF1("f1", "TMath::Exp(-x/[0])/[0]",0,100);
f1->SetParameter(0,10);
c->cd(1);
f1->Draw();

double f(double x, double a){
	return -TMath::Exp(-x/a)+1;
}

TF1 *f2 = new TF1("f2", "f(x,10)",0,100);
f2->SetParameter(0,10);
c->cd(2);
f2->Draw();


double tabx[100];
double taby[100];

tabx[0] = 0.5;
taby[0] = f1->Eval(tabx[0])*1;

for(int i=1; i<100;i++){
tabx[i] = tabx[i-1] + 1;
taby[i] = f1->Eval(tabx[i])*1+taby[i-1];
}

TGraph *t = new TGraph(100,tabx,taby);

c->cd(3);
t->Draw("ap*");

cout<<"P(25<=x<=50) = "<<f(50,10)-f(25,10)<<endl;

cout<<"Mean = "<<f1->Mean(0,1000)<<endl;
cout<<"Variance = "<<f1->Variance(0,100)<<endl;
cout<<"Mode = "<<f1->GetMaximumX()<<endl;
cout<<"dolny = "<<f2->GetX(0.25,0,100)<<endl;
cout<<"mediana = "<<f2->GetX(0.5,0,100)<<endl;
cout<<"decyl07 = "<<f2->GetX(0.7,0,100)<<endl;
cout<<"decyl09 = "<<f2->GetX(0.9,0,100)<<endl;




}
