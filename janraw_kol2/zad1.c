//param[0] = \mu
//param[1] = \sigma
double norm_distr(double *x, double *param)
{
	double przed_exp = 1.0/(param[1]*TMath::Sqrt(2*TMath::Pi()));
	double exp = TMath::Exp(-.5*TMath::Power((x[0] - param[0])/param[1], 2));
	
	return przed_exp * exp;
}
void splot(TF1 **f, int k, TH1D *h, int n){
	for(int i = 0; i<n;i++){
		double sum = 0.0;
		for(int j = 0; j<k;j++){
			sum+=f[j]->GetRandom();
		}
		
		h->Fill(sum);
	}
}
void zad1(){
	/*
	 * Kropka pierwsza
	 */
	TF1 *norms[12];
	
	for(int i = 0; i<12; i++)
	{
		norms[i] = new TF1("norms"+i, norm_distr, -10, 20, 2);
		norms[i]->SetParameter(0,.4);
		norms[i]->SetParameter(1,.8);
	}
	
	TH1D *h = new TH1D("h","Splot 12",40,-10,20);
	
	
	TCanvas *c1 = new TCanvas("c1","Splot 12",200,10,500,300);
	c1->Divide(2,2);
	c1->cd(1);
	splot(norms, 12, h, 10000);
	h->Draw();
	
	TF1 *f1;
	int m = 0;
	double u = 0;
	int n = 10000;
	do{
		m++;
		f1 = new TF1("f1", "gaus", -.5, m);
		
		h->Fit(f1);
	}
	while(f1->GetChisquare()/f1->GetNDF()>1);
	cout<<"chi^2/NDF value: "<<f1->GetChisquare()/f1->GetNDF()<<endl;
	
	/*
	 * Kropka druga
	 */
	
	TF1 *normal_distr = new TF1("normal_distr", norm_distr, -10, 20, 2);
	normal_distr->SetParameter(0,0.);
	normal_distr->SetParameter(1,.5);
	
	TF1 *uniform = new TF1("uniform", "0*x+1",0,1);
	
	
	
	
	
	
	
	TF1 *functions[2] = {
		normal_distr,
		uniform
	};
	
	
	TH1D *h2 = new TH1D("h2","Splot 2",40,-5,5);
	splot(functions, 2, h2, 10000);
	
	c1->cd(2);
	h2->Draw();
	
}

