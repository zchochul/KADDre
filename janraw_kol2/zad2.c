TF1 *fun_chi;

double fit_func(double *x, double *params){
	if (x[0] > 0){
		return (params[0]*TMath::Exp(-params[1]*x[0]) +
				params[2]*TMath::Exp(-params[3]*x[0]));
	}
	return 0;
}
double chi(double *x, double *params){
	if (x[0] > 0){
		return (TMath::Power(x[0], 0.5 * params[0] - 1)
		* TMath::Power(TMath::E(), -0.5 * x[0]))
		/ (TMath::Gamma(0.5 * params[0]) * TMath::Power(2, 0.5*params[0]));
	}
	return 0;
}
void zad2()
{

	
	
	double x1min = 0, x1max = 2;
	TH1D *hist1 = new TH1D("hist1","Data",22,x1min,x1max);
	hist1->GetYaxis()->SetRangeUser(0, 600);
	
	
	//Tak się czyta z pliku, ale u mnie nie chce to dzialac
	ifstream ifile1;
	ifile1.open("dane_sw.txt");
	
	double x, y;
	while(ifile1>>x>>y)
	{
		for(int i = 0; i < y; i++)
		{
			
			hist1->Fill(x);
		}
	}
	ifile1.close();
	
	
	
	
	
	TCanvas *window = new TCanvas("window", "Zadanie2", 500, 500);
	window->cd(1);
	hist1->Draw();
	
	
	int top = 0,
		bottom = 0;
	
	
	for (int i = 1; i < 9; i++)
	{
		top += (i-1)*hist1->GetBinContent(i);
		bottom += hist1->GetBinContent(i);
		
	}
	double lambda = (double) top / bottom;
	

	
	
	
	
	TF1 *fun2 = new TF1("f2", fit_func, 0, 2, nparams = 4);
	//fun2->FixParameter(0, hist1->GetEntries());
	hist1->Fit(fun2, "LRN");
	fun2->SetLineColor(kBlue);
	
	
	fun2->Draw("Same");
	
	
	
	cout<<"Lambda of the highest likelihood: "<<lambda<<endl;
	cout<<"Lambda (ROOT Fit): "<<fun2->GetParameter(1)<<endl;
	
	double T = 0;
	for (int  i = 1; i < 9; i++ )
	{
		T += TMath::Power((hist1->GetBinContent(i) - (*fun2)(i-1)), 2) / (*fun2)(i-1);
	}
	cout<<"chi2 (value of the test statistics T): "<<T<<endl;
	
	double ndf = 6;
	double alpha = 0.01;
	
	double chi_xmin = 0, chi_xmax = 30, chi_nparams = 1;
	
	TF1 *chi = new TF1("chi", chi, chi_xmin, chi_xmax, chi_nparams);
	chi -> SetParameter(0, ndf);
	
	const Int_t nq = 1;
	Double_t xq[nq] = {1-alpha}; 
    Double_t yq[nq];
    chi -> GetQuantiles(nq,yq,xq);
	
	if (T < yq[0]) cout << "Hipoteza przyjeta" << endl;
	else cout << "Hipoteza odrzucona" << endl;
	
	cout << "Quantile: " << yq[0] << endl;
	
}
