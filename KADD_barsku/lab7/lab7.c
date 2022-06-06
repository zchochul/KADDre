double funkcja( double *x, double *param){
	if(x[0] > param[0] && x[0] < param[1]){
		return 1./(param[1]-param[0]);
	}
	else{
		return 0;
	} 
};


double norm( double *x, double *param){
return ROOT::Math::gaussian_pdf(x[0],param[1],param[0]);
};




double l;
void splot(TF1 **f, int k, TH1D *h, int n){
	for(int ii = 0; ii<n; ii++){
	l = 0;
		for(int jj = 0; jj<k; jj++){
			l += f[jj]->GetRandom();
		}	
	h->Fill(l);
	}

}

int de;
void deska(TH1D *h, int n, int ll, double p){
for(int ii = 0; ii<n; ii++){
	de = 0;
		for(int jj = 0; jj<ll; jj++){
			if (gRandom->Uniform(1) > p){
				de += 1;
			} 
			else{
				de -= 1;
			}
		}
	h->Fill(de);
	}
}


void lab7(){

Double_t w = 600;
Double_t h = 600;
TCanvas *c = new TCanvas("c", "c", w, h);
c->Divide(2,2);

TF1 *f1 = new TF1("f1", funkcja,0.0,3.0,2);
TF1 *f2 = new TF1("f1", funkcja,0.0,3.0,2);
TF1 *f3 = new TF1("f1", funkcja,0.0,3.0,2);
f1->SetParameters(-1,5);
f2->SetParameters(-1,5);
f3->SetParameters(-1,5);
TF1 **functions = new TF1*[3];
TF1 **functionsNorm = new TF1*[2];


TF1 *f4 = new TF1("f4", norm,-3.0,5.0,2);
TF1 *f5 = new TF1("f5", norm,-3.0,5.0,2);
f4->SetParameters(1.0,0.3);
f5->SetParameters(2.0,0.5);


functions[0] = f1;
functions[1] = f2;
functions[2] = f3;

TH1D *t = new TH1D("t","t",100,0,9);
splot(functions,3,t,10000);
TH1D *t1 = new TH1D("t1","t1",100,0,6);
splot(functions,2,t1,10000);
c->cd(1);
t->Draw();
c->cd(2);
t1->Draw();



functionsNorm[0] = f4;
functionsNorm[1] = f5;
TH1D *tnorm = new TH1D("tn","tn",100,0,6);
splot(functionsNorm,2,tnorm,10000);
c->cd(3);
tnorm->Draw();


TH1D *tdesk = new TH1D("td","td",41,-20,20);
deska(tdesk,10000,41,0.5);
c->cd(4);
tdesk->Draw();

cout<<"EX1 = "<<f4->Mean(-10,10)<<endl;
cout<<"EX2 = "<<f5->Mean(-10,10)<<endl;

cout<<"stdev1 = "<<TMath::Sqrt(f4->Variance(-10,10))<<endl;
cout<<"stdev2 = "<<TMath::Sqrt(f5->Variance(-10,10))<<endl;


cout<<"EXPLOT="<<tnorm->GetMean(1)<<endl;
cout<<"RMSPLOT(X)="<<tnorm->GetRMS(1)<<endl;
}
