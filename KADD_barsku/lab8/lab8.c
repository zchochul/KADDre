double pdf(double *x, double *k){
	return TMath::Power(x[0],k[0]/2-1)*TMath::Exp(-x[0]/2)/TMath::Power(2,k[0]/2)/TMath::Gamma(k[0]/2);

}

double dys(double *x, double *k){
TF1 *ff = new TF1("ff", pdf,0.0,30.0,1);
ff->SetParameter(0,k[0]);
return ff->Integral(0,x[0]);

}

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

double funkcja( double *x, double *param){
	if(x[0] > param[0] && x[0] < param[1]){
		return 1./(param[1]-param[0]);
	}
	else{
		return 0;
	} 
};


void lab8(){

	Double_t w = 600;
	Double_t h = 600;
	TCanvas *c = new TCanvas("c", "c", w, h);
	c->Divide(2,2);
	
	TF1 *f1 = new TF1("f1", pdf,0.0,30.0,1);
	f1->SetParameter(0,1);
	c->cd(1);
	f1->DrawCopy();
for(int i=2; i<21; i++){
	TF1 *f2 = new TF1("f2", pdf,0.0,30.0,1);
	f2->SetParameter(0,i);
	f2->SetLineColor(i);
	f2->DrawCopy("SAME");
}

	TF1 *f3 = new TF1("f3", dys,0.0,30.0,1);
	f3->SetParameter(0,2);
	c->cd(2);
	f3->DrawCopy();
for(int i=1; i<21 ;i++){
	TF1 *f4 = new TF1("f4", dys,0.0,30.0,1);
	f4->SetParameter(0,i);
	f4->SetLineColor(i);
	f4->DrawCopy("SAME");
}

c->cd(3);
int n =10;
TF1 **functions; 
for(int i=0; i<n ;i++){
	TH1D *t = new TH1D("t","t",100,0,9);
	functions = new TF1*[i+1];
	for(int j=0; j<i+1 ;j++){
		functions[j] = new TF1("ft", funkcja,0.0,1.0,2);
		functions[j]->SetParameters(0,1);
		
	}
	splot(functions,i+1,t,10000);
	TF1 *Ga = new TF1("Ga","gaus",0.0,n);
	t->Fit(Ga);
	if(Ga->GetChisquare()/Ga->GetNDF() <1.0 ){
	n = i;
	break;
	}

	

}
cout<<"n = "<<i<<endl;


}
