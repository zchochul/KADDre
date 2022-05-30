TH1D *hist;

double modelTF1(double *x, double *par) 
{ 
 double mu    = par[3]; 
 double sigma = par[4]; 
 double norm  = 1./sqrt(2.*TMath::Pi())/sigma; 
 double G     = norm*exp(-0.5 *pow((x[0]-mu)/sigma,2));  //unormowana funkcja Gaussa
 double BinWidth = hist->GetBinWidth(1); 
 return par[0] + par[1]*x[0] + par[2] * BinWidth * G; 
}

double model(double x, double *par) 
{ 
 double mu    = par[3]; 
 double sigma = par[4]; 
 double norm  = 1./sqrt(2.*TMath::Pi())/sigma; 
 double G     = norm*exp(-0.5 *pow((x-mu)/sigma,2));  //unormowana funkcja Gaussa
 double BinWidth = hist->GetBinWidth(1); 
 return par[0] + par[1]*x + par[2] * BinWidth * G; 
}

void fcn(int &npar, double *gin, double &f, double *par, int iflag){
	int n = hist->GetNbinsX();
	
	double res = 0;
	for (int i = 1; i<= n; i++){
		double xval = hist->GetBinCenter(i);
		double yval = hist->GetBinContent(i);
		res += TMath::Power(( model(xval, par) - yval )/ TMath::Sqrt(yval), 2);
	}
	f = res;
	
}
void lab12(){
	TCanvas *c1 = new TCanvas();
	TFile *ifile = new TFile("example_data.root");
	hist = (TH1D*)ifile->Get("hist");
	
	TMinuit *gMinuit = new TMinuit(5); //liczba parametrów wynika z definicji funkcji teoretycznej
	gMinuit->SetFCN(fcn); //minuit ma skorzystac z fcn
	
	gMinuit->DefineParameter(0, "p0",    100., 1.,    0.,  200.); //ustawiamy parametry
	gMinuit->DefineParameter(1, "p1",    -50., 1.,    -100.,  200.);
	gMinuit->DefineParameter(2, "area",    2000., 1.,    0.,  5000.);
	gMinuit->DefineParameter(3, "mean",    2., 1.,    0.,  200.);
	gMinuit->DefineParameter(4, "width",    500., 1.,    0.,  2000.);
	
	gMinuit->Command("MIGRAD");        
	gMinuit->Command("MINOS");
	
	double p0 =1;
	double p1 =1; 
	double area =1;
	double mean=1;
	double width = 1;
	double ep0=1;
	double ep1 = 1;
	double earea =1;
	double emean = 1;
	double ewidth = 1;
	
	gMinuit->GetParameter(0, p0, ep0);
	gMinuit->GetParameter(1, p1, ep1);
	gMinuit->GetParameter(2, area, earea);
	gMinuit->GetParameter(3, mean, emean);
	gMinuit->GetParameter(4, width, ewidth);
	 
	 

    TF1 *fun1= new TF1("fun1", modelTF1 , 0, 2, 5);
	fun1->SetParameter(0, p0);
	fun1->SetParameter(1, p1);
	fun1->SetParameter(2, area);
	fun1->SetParameter(3, mean);
	fun1->SetParameter(4, width);

 
	hist->Draw();
	fun1 -> Draw("Same");
}
