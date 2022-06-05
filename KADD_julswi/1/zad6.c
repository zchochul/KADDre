double functiona ( int iteracje ) {
		double N_all=0;
		double N_ac=0;
		double N_od=0;
		TGraph *akcept = new TGraph();
		TGraph *odrzuc =new TGraph();
		TRandom *r=new TRandom();
		double x,y;
		for(int i=0;i<iteracje;i++){
			N_all++;
			x=r->Uniform();
			y=r->Uniform();
			if(x*x+y*y<=1){
				 N_ac++;
				akcept->SetPoint(N_ac,x,y);				
			}
			else{
				N_od++;
				odrzuc->SetPoint(N_od,x,y);
			}
		}
		akcept->Draw("AP");
		akcept->SetMarkerColor(kRed);
		odrzuc->Draw("SameP");
		return 4*N_ac/N_all;
	}
double losujVonNeumann (TF1 *g, double min, double max){
	TRandom *r=new TRandom();
	double u=0,y=0;
	while(g->Eval(y)>=u){
		u=r->Uniform(g->GetMaximum(min,max));
		y=r->Uniform(min,max);
		
	}
	
	return y;
}
double wydajnoscVonNeumann (TF1 *g , double min , double max , int n ){
	TRandom *r=new TRandom();
	double u=0,y=0,n_ac=0;
	for(int i=0;i<n;i++){
		u=r->Uniform(g->GetMaximum(min,max));
		y=r->Uniform(min,max);
		if(g->Eval(y)<u) n_ac++;
		
	}
	return n_ac/n;
}
double odwrotnaDystrybuanta ( double x , double a , double b ) {
	return -b/a + TMath::Sqrt(2*x/a + (b*b)/(a*a));
}
double calkaVonNeumann (TF1 *g , double min , double max , int n ){
	return wydajnoscVonNeumann(g,min,max,n)*(max-min)*g->GetMaximum();
}
double calkaFunkcjiLiniowej( double x , double a , double b ) {
	return a*x*x/2 + b*x ;
}
double calkaVonNeumannZPomoc (TF1 *g , TF1 *s , double min , double max , int n , double &wydajnosc ){
	TRandom *r=new TRandom();
	double u=0,y=0,n_ac=0;
	double x=0;
	for(int i=0;i<n;i++){
		u=r->Uniform();
		x=r->Uniform(calkaFunkcjiLiniowej(min,s->GetParameter(0),s->GetParameter(1)),calkaFunkcjiLiniowej(max,s->GetParameter(0),s->GetParameter(1)));
		y=odwrotnaDystrybuanta(x, s->GetParameter(0),s->GetParameter(1));
		if(g->Eval(y)/s->Eval(y)<u) n_ac++;
		
	}
	wydajnosc=n_ac/n;
	return wydajnosc*(max-min)*(g->Eval(min)+g->Eval(max))/2;
}
void zad6(){
	Double_t w = 1000;
	Double_t h = 800;
	TCanvas *okno = new TCanvas("okno", "okno", w, h);
	okno->Divide(2,2);
	okno->cd(1);
	cout<<functiona(200000)<<endl;
	okno->cd(2);
	double min=0;
	double max=10;
	TF1 *g=new TF1("g","0.4+sin(TMath::Pi()*(x+1.2))/(TMath::Pi()*(x+1.2)+1)",min,max);
	cout<<g->Integral(min,max)<<endl;
	cout<<calkaVonNeumann(g,min,max,1000)<<endl<<wydajnoscVonNeumann(g,min,max,1000)<<endl;
	double wyd=0;
	TF1 *s=new TF1("s","[0]*x+[1]",min,max);
	s->SetParameter(0,(g->Eval(max)-g->Eval(min)/(max-min)));
	s->SetParameter(1,g->Eval(min)-min*s->GetParameter(0));
	cout<<calkaVonNeumannZPomoc(g,s,min,max,1000,wyd)<<endl<<wyd<<endl;
	
}
