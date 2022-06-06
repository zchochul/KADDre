
double ff(double *x, double *pam){
return pam[2]*(x[0]-pam[0]*x[0]*x[0])*pow(x[1],pam[1]);
}

void lab2(){

Double_t w = 600;
Double_t h = 600;
TCanvas *c = new TCanvas("c", "c", w, h);
c->Divide(2,2);

double x[2];
double pam[3];
TF2 *q = new TF2("q",ff,0,1,0,1,3);
q->SetParameters(1,2,1);
q->SetParameters(1, 2,1/(q->Integral(0,1,0,1)));
q->GetXaxis()->SetTitle("x");
q->GetYaxis()->SetTitle("y");
c->cd(1);
gStyle->SetOptStat(0);
q->Draw("surf2");
q->SetTitle("Gestosc");
q->SetTitle("do;sa;qwq");


TH2D *t = new TH2D("t","t",10,0,1,10,0,1);
for(int i = 1; i<11; i++){
for(int j = 1; j<11; j++){
t->SetBinContent(i,j,q->Integral(0,(double)i/10,0,(double)j/10));
}
}
t->GetXaxis()->SetTitle("x");
t->GetYaxis()->SetTitle("y");
t->SetTitle("Dystrybuanta");
c->cd(2);
t->Draw("surf2");

TGraph *g = new TGraph();
for(int i = 0;  i<10; i++){
g->SetPoint(i,(double)i/10,q->Integral((double)i/10, (double)i/10+0.1,0,1));
}
g->GetXaxis()->SetTitle("x");
g->GetYaxis()->SetTitle("g(x)");
c->cd(3);
g->Draw("AC*");

TGraph *g1 = new TGraph();
for(int i = 0;  i<10; i++){
g1->SetPoint(i,(double)i/10,q->Integral(0,1,(double)i/10, (double)i/10+0.1));
}
g1->GetXaxis()->SetTitle("y");
g1->GetYaxis()->SetTitle("h(y)");
c->cd(4);
g1->Draw("AC*");








}
