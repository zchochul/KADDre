//Zuzanna Chochulska kol 1
void chochulska_1(){
	TCanvas * c1 = new TCanvas("c", "c", 500, 500);
	TF1 *fun1 = new TF1("fun1", "1./( TMath::Sqrt(1+x))", 0, 1);
	
	//setting parameter
	Double_t a = fun1 -> Integral(0,1);
	fun1->SetParameter(0, 1/a);
	
	c1 -> Divide (2,1);
	c1-> cd(1);
	fun1 -> SetTitle("Gestosc prawdopodobienstwa");
	fun1->GetXaxis()->SetTitle("x");
	fun1->GetYaxis()->SetTitle("f(x)");
	fun1 -> Draw();
	
	//cumulativ
	c1-> cd(2);
	fun1->DrawIntegral();
	
	//P(0.1 < X > 0.2)
	Double_t b = fun1 -> Integral(0.1,0.2);
	cout<< "P(0.1 < X > 0.2)= " << b <<endl;
	
	//Expected value
	Double_t mean = fun1 -> Mean(0,1);
	cout<<"Expected value = " << mean <<endl;
	
	//Quantiles
	const Int_t nq = 1;
	Double_t xq[nq] = {0.4};
	Double_t yq[nq];
	fun1->GetQuantiles(nq,yq,xq);
	
	for (Int_t i=0; i <nq; i++)
		cout <<"Quantil "<< xq[i]<< "= "<< yq[i] << endl;
}
