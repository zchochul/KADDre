double minn = 0;
double maxx = 1;
double xx,yy;

TF1 *g = new TF1("g", "TMath::Exp(-5*x)", minn,maxx);
TF1 *s = new TF1("s", "[0]+[1]*x", minn,maxx);




TF1 *S = new TF1("S", "[0]*x+[1]*x*x+[2]", minn,maxx);
TF1 *OS = new TF1("OS","-TMath::Sqrt(x/[1]+([0]*[0]-4*[1]*[2])/4/[1]/[1])-[0]/2/[1]",S->GetMinimum(minn,maxx),S->GetMaximum(minn,maxx));
//S->SetParameters(1,-1,0);

double losujVonNeumann(TF1 *g, double min, double max){
	do{
		xx = gRandom->Uniform(min,max);
		yy = gRandom->Uniform(0,g->GetMaximum(min,max));
	}
	while(yy > g->Eval(xx));
}

double wydajnoscVonNeumann(TF1 *g, double min, double max, int n){
	int m =0;
    for(int ii=0; ii<n; ii++){
        xx = gRandom->Uniform(min,max);
        yy = gRandom->Uniform(0,g->GetMaximum(min,max));
       if(yy < g->Eval(xx)){ 
            m++;
        }   
    }
    return (double)m/n;
}

double calkaVonNeumann(TF1 *g, double min, double max, int n){
      int m =0;
    for(int ii=0; ii<n; ii++){
        xx = gRandom->Uniform(min,max);
        yy = gRandom->Uniform(0,g->GetMaximum(min,max));
       if(yy < g->Eval(xx)){ 
            m++;
        }   
    }
    return (double)m/n*(max-min)*g->GetMaximum(min,max);

}

double u,Y,X;
double calkaVonNeumannZPomoc(TF1 *g, TF1 *s, double min, double max, int n, double &wydajnosc){
int m=0;
	 for(int ii=0; ii<n; ii++){
		u = gRandom->Uniform(min,max);
		X =  gRandom->Uniform(S->GetMinimum(min,max),S->GetMaximum(min,max));
		Y = OS->Eval(X);
	if(u< (g->Eval(Y))/(s->Eval(Y))){ 
            m++;
        }
	}
	wydajnosc =(double)m/n;
    return (double)m/n*(max-min)*s->GetMaximum(min,max)/2.;


}



void lab6(){

	s->SetParameters(1,-1);
	S->SetParameters(1,-0.5,0);
	OS->SetParameters(1,-0.5,0);


	Double_t w = 600;
   	Double_t h = 600;
   	TCanvas *c = new TCanvas("c", "c", w, h);
   	c->Divide(2,1);
	
	TF1 *f1 = new TF1("f1", "TMath::Sqrt(1-x*x)", 0,1);
	TGraph *t1 = new TGraph();
	TGraph *t2 = new TGraph();
	int n=0;
	double x,y;

	
	for(int ii=0; ii<10000; ii++){
		x = gRandom->Uniform(1);
        y = gRandom->Uniform(1);
        if(y < f1->Eval(x)){
            t1->SetPoint(ii,x,y); 
            n++;
        }
       else t2->SetPoint(ii,x,y);
	}


	c->cd(1);
	t1->SetMarkerColor(5);
	t2->SetMarkerColor(9);
	t1->Draw("A*");
	t2->Draw("* ,same");
	f1->Draw("same");

	cout<<"PI = "<<(double)n/10000*4<<endl;


	cout<<"Zadanie 2"<<endl;


	cout<<"wydajnosc = "<<wydajnoscVonNeumann(g, minn, maxx, 10000)<<endl;
	cout<<"calka = "<<calkaVonNeumann(g, minn, maxx, 10000)<<endl;


	cout<<"Zadanie 3"<<endl;
double wydajnosc;
	cout<<"calka = "<<calkaVonNeumannZPomoc(g, s, minn, maxx, 10000,wydajnosc)<<endl;
	cout<<"wydajnosc = "<<wydajnosc<<endl;


}
