#include <iostream>
#include <vector>
#define alfaa 0.005
#define n_pom 7
void wczytaj(string nazwa, vector<double> &biny, vector<double> &obserwacje, vector<double> &u_obserwacje)
{
    double val1,val2;
    ifstream ifile;
	ifile.open("dane.dat");
    ifile >> val1 >> val2;
    while(!ifile.eof()) {biny.push_back(val1); obserwacje.push_back(val2); u_obserwacje.push_back(0.6); ifile >> val1 >> val2;}
	ifile.close();
}  

Double_t gestosc(double *x, double *parms) {return 1./(TMath::Gamma(parms[0])*pow(2,parms[0]))*pow(x[0],parms[0]-1)*TMath::Exp(-0.5*x[0]);}
Double_t dyst(double *x, double *parms) {TF1 *dys = new TF1("",gestosc,0,50,1); dys -> SetParameter(0,parms[0]*0.5); return dys -> Integral(parms[1],x[0]);}

bool testChi2(double T, double alpha, int ndf, double &SS)
{
    TF1 *kw = new TF1(" ", dyst, 0, 50, 2);
    kw -> SetParameter(0,ndf);
    kw -> SetParameter(1,0.01);
    SS = kw -> GetX(1. - alpha);
    if(T < SS) {return true;} else {return false;}
}

void dopasuj(int stopien, int n_pomiarow, vector<double> &t_j,vector<double> &y_j, vector<double> &sigma_j, double *wsp, double *wsp_sigma)
{
    int counter;
    wczytaj("dane.dat", t_j, y_j, sigma_j);
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
            cout << "Alfa = " << alfaa << endl; 
            double kwant;
            if(testChi2((*Macierz_2_2)(0,0), alfaa, n_pomiarow - stopien - 1, kwant))
            {cout << "Kwantyl = " << kwant << endl; cout << "Stopie?? " << stopien << ": " << "Akceptujemy" << endl;} 
            else 
            {cout << "Kwantyl = " << kwant << endl; cout << "Stopie?? " << stopien << ": " << "Odrzucamy" << endl;}
        } 
        cout << "x_" << kk << " = " << wsp[kk] << " +- " << wsp_sigma[kk] << endl;
    }
    cout << "===========================" << endl;
}

double wielomian(double *x, double *params) 
{
	double value = 0;
	for(int v = 0; v <= params[0]; v++) {value += params[v+1]*pow(x[0], v);}
	return value;
}

int zad3(void)
{
    TCanvas *can1 = new TCanvas("can1","okienko1",900,800);
    TLegend *leg = new TLegend(0.1,0.9,0.4,0.6);
    vector<double> cos,coscontent,niep;
    double wspolczynniki[6],wspolczynniki_sigma[6];
    for(int p = 0; p <= 5; p++)
    {
        dopasuj(p,n_pom,cos,coscontent,niep,wspolczynniki,wspolczynniki_sigma);
        if(p == 0)
        {
            TGraphErrors *gr = new TGraphErrors(cos.size(),&cos[0],&coscontent[0],0,&niep[0]);
            gr -> SetMarkerColor(kBlack); gr -> SetMarkerStyle(kFullCircle);
            gr -> SetTitle("Wyniki dopasowan MNK; t, cos(#Theta); y, liczba obserwacji");
            gr -> Draw("ALP");
        }
        TF1 *fa0 = new TF1(" ",wielomian,0,15,p+2);
        fa0 -> SetParameter(0,p);
        for(int o = 0; o < p+1; o++) {fa0 -> SetParameter(o+1, wspolczynniki[o]);} 
        fa0 -> SetLineColor(p+1);
        string x = "st"+to_string(p);
        const char *tab = x.c_str();
        leg -> AddEntry(fa0,tab,"l");
        fa0 -> Draw("SAME");
    }
    leg -> Draw();
    return 0;
}
