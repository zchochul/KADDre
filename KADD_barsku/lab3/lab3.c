double f(double *x, double *par){
	if((x[0]*x[1]>=0)&&(x[0]*x[1]<=TMath::Pi()))
		return par[0]*sin(x[0]*x[1]);
	else
		return 0;
}


void lab3(){
   Double_t w = 600;
   Double_t h = 600;
   TCanvas *c = new TCanvas("c", "c", w, h);
   c->Divide(2,2);

TF2 *f1 = new TF2("f1", "[0]*sin(x*y)", 0,TMath::Pi()/2,0,TMath::Pi()/2);

f1->SetParameter(0,1);
f1->SetParameter(0,1/(f1->Integral(0,TMath::Pi()/2,0,TMath::Pi()/2)));
cout<<f1->Integral(0,TMath::Pi()/2,0,TMath::Pi()/2)<<endl;
//c->cd(1);
//f1->Draw("surf2");
double x,y;

TH2D *t1 = new TH2D("t1","t1",20,0,TMath::Pi()/2,20,0,TMath::Pi()/2);
t1->GetXaxis()->SetTitle("x");
t1->GetYaxis()->SetTitle("y");
t1->SetTitle("Gestosc");
for(int i =1; i<30000; i++){
	f1->GetRandom2(x,y);
	t1->Fill(x,y);
	}
t1->Scale(1./(t1->Integral()));
c->cd(1);
t1->Draw("lego2");


TH2D *t2 = new TH2D("t2","t2",20,0,TMath::Pi()/2,20,0,TMath::Pi()/2);
t2->GetXaxis()->SetTitle("x");
t2->GetYaxis()->SetTitle("y");
t2->SetTitle("Dystrybuanta");
for(int ii=1; ii<21; ii++){
	for(int jj=1; jj<21; jj++){
		t2->SetBinContent(ii,jj,t1->Integral(1,ii,1,jj));
		}
	}
c->cd(2);
t2->Draw("lego2");


cout<<"E(X)="<<t1->GetMean(1)<<endl;
cout<<"E(y)="<<t1->GetMean(2)<<endl;
cout<<"RMS(X)="<<t1->GetRMS(1)<<endl;
cout<<"RMS(Y)="<<t1->GetRMS(2)<<endl;
cout<<"COV(X,Y)="<<t1->GetCovariance()<<endl;
cout<<"RHO(X,Y)="<<t1->GetCorrelationFactor()<<endl;


TH1D *t3 = t1->ProjectionX();
t3->GetXaxis()->SetTitle("x");
t3->GetYaxis()->SetTitle("y");
t3->SetTitle("g(x)");
c->cd(3);
t3->Draw();

TH1D *t4 = t1->ProjectionY();
t4->GetXaxis()->SetTitle("x");
t4->GetYaxis()->SetTitle("y");
t4->SetTitle("h(y)");
c->cd(4);
t4->Draw();

}
