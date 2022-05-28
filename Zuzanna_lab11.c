//Zuzanna Chochulska lab11
#include <iostream>
#include <vector>
#define alphaa 0.01
#define number_of_measurements 15

void read(string name, vector<double> &bins, vector<double> &measurements, vector<double> &sigma_measurements)
{
    double value1,value2;
    ifstream ifile;
	ifile.open(name);
    ifile >> value1 >> value2;
    while(!ifile.eof())
    {
        bins.push_back(value1);
        measurements.push_back(value2); 
        sigma_measurements.push_back(TMath::Sqrt(value2)); 
        ifile >> value1 >> value2;
    }
	ifile.close();
}  

//CHI^2
double prob_dist(double *x, double *params){
	//cout << "I'm in prob_dist" << endl;
	return 1./(TMath::Gamma(params[0])*pow(2,params[0]))*pow(x[0],params[0]-1)*TMath::Exp(-0.5*x[0]);
}
double cumu_dist(double *x, double *params){
	//cout << "I'm in cumu_dist" << endl;
	TF1 *dys = new TF1("",prob_dist,0,50,1); 
    dys -> SetParameter(0,params[0]*0.5); 
    return dys -> Integral(params[1],x[0]);
}

bool Chi2Test(double Test, double alpha, int ndf, double &critical){
	//cout << "I'm in chi_test" << endl;
	TF1 *chi2 = new TF1(" ", cumu_dist, 0, 50, 2);
    chi2 -> SetParameter(0,ndf);
    chi2 -> SetParameter(1,0.01);
    critical = chi2 -> GetX(1. - alpha);
	
    if(Test < critical)
		return true;
	else 
		return false;
	
}

void fitting(int stopien, int n_pomiarow, vector<double> &t_j,vector<double> &y_j, vector<double> &sigma_j, double *wsp, double *wsp_sigma)
{
    int counter;
    read("dane11.dat", t_j, y_j, sigma_j);
    TMatrixD *MacierzA = new TMatrixD(n_pomiarow,stopien+1);
    TMatrixD *MacierzC = new TMatrixD(n_pomiarow,1);
    TMatrixD *MacierzG_y = new TMatrixD(n_pomiarow,n_pomiarow);
    TMatrixD *MacierzH = new TMatrixD(n_pomiarow,n_pomiarow);
    for(int i = 0; i < n_pomiarow; i++)
    {
        (*MacierzA)(i,0) = 1;
        (*MacierzC)(i,0) = y_j[i];
        (*MacierzH)(0,0) = 1/(sigma_j[0]);
        (*MacierzG_y)(0,0) = 1/(pow(sigma_j[0],2));
        for(int j = 1; j < stopien+1; j++){(*MacierzA)(i,j) = pow(t_j[i],j);}
        for(int jj = 0; jj < n_pomiarow; jj++) {if(i == jj) {(*MacierzG_y)(i,jj) = 1/(pow(sigma_j[jj],2)); (*MacierzH)(i,jj) = 1/(sigma_j[jj]);}}
    }
    TMatrixD *MacierzAPrim = new TMatrixD(n_pomiarow,stopien+1);
    TMatrixD *MacierzCPrim = new TMatrixD(n_pomiarow,1);
    MacierzAPrim -> Mult(*MacierzH,*MacierzA);
    MacierzCPrim -> Mult(*MacierzH,*MacierzC);
    TMatrixD *MacierzAPrimT = new TMatrixD(TMatrixD::kTransposed,*MacierzAPrim);
    TMatrixD *MacierzAA_T = new TMatrixD(*MacierzAPrimT, TMatrixD::kMult, *MacierzAPrim);
    TMatrixD Macierzminusjeden = MacierzAA_T -> Invert();
    TMatrixD *MacierzAPrimT_CPrim = new TMatrixD(*MacierzAPrimT, TMatrixD::kMult, *MacierzCPrim);
    TMatrixD *MacierzX_falka = new TMatrixD(Macierzminusjeden, TMatrixD::kMult, *MacierzAPrimT_CPrim);
    for(int n = 0; n < stopien+1; n++) {for(int m = 0; m < stopien+1; m++){if(m == n) {wsp_sigma[m] = TMath::Sqrt((Macierzminusjeden)(n,m));}}}
    for(int z = 0; z < MacierzX_falka -> GetNrows(); z++) {wsp[z] = (*MacierzX_falka)(z,0);}
    TMatrixD *Macierz_eta_falka = new TMatrixD(*MacierzA, TMatrixD::kMult, *MacierzX_falka);
    TMatrixD *Macierzroznicminusjeden = new TMatrixD(TMatrixD::kTransposed,*MacierzC - *Macierz_eta_falka);
    TMatrixD *Macierz_1_2 = new TMatrixD(*Macierzroznicminusjeden, TMatrixD::kMult,*MacierzG_y);
    TMatrixD *Macierz_2_2 = new TMatrixD(*Macierz_1_2, TMatrixD::kMult, *MacierzC - *Macierz_eta_falka);
    for(int kk = 0; kk < MacierzX_falka -> GetNrows(); kk++) 
    {
        if(kk == 0)
        {
            cout << "Wielomian stopnia: " << stopien << endl; 
            cout << "M = " << (*Macierz_2_2)(0,0) << endl;
            cout << "NDF = " << n_pomiarow - stopien - 1 << endl;
            cout << "Alfa = " << alphaa << endl; 
            double kwant;
            if(Chi2Test((*Macierz_2_2)(0,0), alphaa, n_pomiarow - stopien - 1, kwant))
            {cout << "Kwantyl = " << kwant << endl; cout << "Stopień " << stopien << ": " << "Akceptujemy" << endl;} 
            else 
            {cout << "Kwantyl = " << kwant << endl; cout << "Stopień " << stopien << ": " << "Odrzucamy" << endl;}
        } 
        cout << "x_" << kk << " = " << wsp[kk] << " +- " << wsp_sigma[kk] << endl;
    }
    cout << "===========================" << endl;
}

//function for generating y(x) value
double polynomials(double *x, double *params) 
{
	double val = 0;
	for(int i = 0; i <= params[0]; i++)
    {
        val += params[i+1]*pow(x[0], i);
    }
	return val;
}

int Zuzanna_lab11(void)
{
    TCanvas *c1 = new TCanvas("c1","Results",500, 500); //canvas
    TLegend *leg = new TLegend(0.1,0.9,0.5,0.5); //Legend
    vector<double> xs,ys, u_y; 
    double coefficients[6],coefficients_sigma[6];
    for(int p = 0; p <= 5; p++)
    {
        fitting(p,number_of_measurements,xs,ys, u_y, coefficients,coefficients_sigma);
        if(p == 0)
        {
            TGraphErrors *gr = new TGraphErrors(xs.size(),&xs[0],&ys[0],0,&u_y[0]);
            gr -> SetMarkerColor(kBlack);
            gr -> SetMarkerStyle(kFullCircle);
            gr -> SetTitle("Wyniki dopasowan MNK; t, x(#Theta); y, liczba obserwacji");
            gr -> Draw("ALP");
        }
        TF1 *fa0 = new TF1(" ",polynomials,0,15,p+2);
        fa0 -> SetParameter(0,p);
        for(int o = 0; o < p+1; o++) {fa0 -> SetParameter(o+1, coefficients[o]);} 
        fa0 -> SetLineColor(p+1);
        string x = "st"+to_string(p);
        const char *tab = x.c_str();
        leg -> AddEntry(fa0,tab,"l");
        fa0 -> Draw("SAME");
    }
    leg -> Draw();
    return 0;
}