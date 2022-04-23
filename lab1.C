int lab1 () {
	TCanvas * c1 = new TCanvas("c", "c", 500, 500);
	TF1 *fun1 = new TF1("fun1", "1./[0] * TMath::Exp(-x/[0])", 0, 50);
	fun1->SetParameter(0, 6);
	
	
	Double_t a = fun1 -> Integral(0,50);
	cout<< a<<endl;
	
	
	
	
	
	c1 -> Divide (2,1);
	c1-> cd(1);
	fun1 -> Draw();
	c1-> cd(2);
	//cumulative
	fun1->DrawIntegral();
	
	//P(5<x<10)
	Double_t b = fun1 -> Integral(5,10);
	cout<< b <<endl;
	
	//Expected value
	Double_t mean = fun1 -> Mean(0,50);
	cout<< mean <<endl;
	
	//Variance
	Double_t variance = fun1 -> Variance(0,50);
	cout << variance << endl;
	
	//Mode
	Double_t mode = fun1 -> GetMaximumX(0,50);
	cout << mode << endl;
	
	//Quantiles
	const Int_t nq = 3;
	Double_t xq[nq] = {0.25,0.5,0.75};
	Double_t yq[nq];
	fun1->GetQuantiles(nq,yq,xq);
	
	/*
    const Int_t nshots = 10;
	Double_t xq[nq];  // position where to compute the quantiles in [0,1]
    Double_t yq[nq];  // array to contain the quantiles
    for (Int_t i=0;i<nq;i++) 
		xq[i] = Float_t(i+1)/nq;
	
	 for (Int_t shot=0;shot<nshots;shot++) {

    }
	*/
	for (Int_t i=0; i <nq; i++)
		cout << yq[i] << endl;
	return 0;	
}
