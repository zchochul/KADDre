
	double fcn(double *x, double *params)
	{
		if(x[0]>=0 && x[0] <= 1 && x[1]>=0 && x[0] <= 1 )
			return params[0]*TMath::Power(x[0], params[1])*TMath::Power(x[1], params[2]);
		return 0;
	}

void lab3(){
	TCanvas *c1 = new TCanvas();
	c1-> Divide(2,2);
	double xmin = 0;
	double xmax = 1;
	double ymin = 0;
	double ymax = 1;
	int nparams = 3;
	TF2 *fun1 = new TF2("fun1",fcn,xmin,xmax,ymin,ymax,nparams);
	fun1->SetParameters(1,1,2);
	c1->cd(1);
	fun1->SetTitle("Gestosc");
	fun1->GetXaxis()->SetTitle("x");
	fun1->GetYaxis()->SetTitle("y");
	fun1->GetZaxis()->SetTitle("f(x,y)");
	fun1->Draw("Surf1");
	
	//finding c value
	
	Double_t c = fun1->Integral(0,1,0,1);
	fun1->SetParameter(0,1/c);
	cout<< c<< endl;
	
	//F(x,y)
	TGraph2D *g = new TGraph2D();
	int count = 0;
	for(Double_t xs = 0; xs <=1 ; xs+= 1./30){
		for(Double_t ys=0; ys <=1 ; ys+= 1./30 )
		{
			g->SetPoint(count, xs, ys, fun1->Integral(0,xs, 0, ys));
			count++;
		}
	}
	c1->cd(2);
	g->SetTitle("Dystrybuanta");
	g->GetXaxis()->SetTitle("x");
	g->GetYaxis()->SetTitle("y");
	g->GetZaxis()->SetTitle("F(x,y)");
	g->Draw("surf1");
	
	//Marginal g(x)
	TGraph *fung = new TGraph();
	int count1 = 0;
	for(Double_t xs = 0; xs <=1 ; xs+= 1./30){
		fung -> SetPoint(count1, xs, fun1->Integral(xs-1./100,xs,0,1));
		count1++;
	}
	c1->cd(3);
	fung->SetMarkerSize(1.5);
	fung->SetMarkerStyle(22);
	fung->SetTitle("Gestosc brzegowa g(x)");
	fung->GetXaxis()->SetTitle("x");
	fung->GetYaxis()->SetTitle("g(x)");
	fung->Draw("APL");
	
	//Marginal h(y)
	TGraph *funh = new TGraph();
	int count2 = 0;
	for(Double_t ys = 0; ys <=1 ; ys+= 1./30){
		funh -> SetPoint(count2, ys, fun1->Integral(0,1, ys-1./100,ys));
		count2++;
	}
	c1->cd(4);
	funh->SetMarkerSize(1.5);
	funh->SetMarkerStyle(22);
	funh->SetTitle("Gestosc brzegowa h(y)");
	funh->GetXaxis()->SetTitle("y");
	funh->GetYaxis()->SetTitle("h(y)");
	funh->Draw("APL");
	
}
