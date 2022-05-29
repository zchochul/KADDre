#include <iostream>
#include <vector>

#define alphaa 0.01
#define number_of_measurements 15

void read(string name, vector<double> &bins, vector<double> &vals, vector<double> &val_error){
	//cout << "I'm in read" << endl;
	double val1, val2;
	ifstream ifile;
	ifile.open(name);
	ifile >> val1 >> val2;
	while(!ifile.eof()){
		bins.push_back(val1); //x
		vals.push_back(val2); //y
		val_error.push_back(TMath::Sqrt(val2)); //u(y)
		ifile >> val1 >> val2;
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
static int counter = 0;

void fitting(int stopien, int n_pomiarow, vector<double> &t_j,vector<double> &y_j, vector<double> &sigma_j, double *wsp, double *wsp_sigma){
	// stopien means degree (of polynomial)
	// n_pomiarow means number od measures
	
	cout << "~~~~~~~~~~~~" << counter <<"~~~~~~~~~~~~~" << endl;
    read("dane11.dat", t_j, y_j, sigma_j); //reading the data
    TMatrixD *matrix_A = new TMatrixD(n_pomiarow,stopien+1); //matrix A
    TMatrixD *matrix_C = new TMatrixD(n_pomiarow,1); //matrix C
    TMatrixD *matrix_G_y = new TMatrixD(n_pomiarow,n_pomiarow); //matrix G_y
    TMatrixD *matrix_H = new TMatrixD(n_pomiarow,n_pomiarow); //matrix H

	//filling the matrices
    for(int i = 0; i < n_pomiarow; i++)
    {
        (*matrix_A)(i,0) = 1;
        (*matrix_C)(i,0) = y_j[i];
        (*matrix_H)(0,0) = 1/(sigma_j[0]);
        (*matrix_G_y)(0,0) = 1/(pow(sigma_j[0],2));
        for(int j = 1; j < stopien+1; j++)
		{
			(*matrix_A)(i,j) = pow(t_j[i],j);
		}
        for(int jj = 0; jj < n_pomiarow; jj++)
		{
			if(i == jj) 
			{
				(*matrix_G_y)(i,jj) = 1/(pow(sigma_j[jj],2));
				(*matrix_H)(i,jj) = 1/(sigma_j[jj]);
			}
		}
    }

	//creating matrices for help
    TMatrixD *matrix_APrim = new TMatrixD(n_pomiarow,stopien+1); 
    TMatrixD *matrix_CPrim = new TMatrixD(n_pomiarow,1);
	//filling them
    matrix_APrim -> Mult(*matrix_H,*matrix_A); //A' = H * A 
    matrix_CPrim -> Mult(*matrix_H,*matrix_C); //c' = H * C

	//creating and filling more
	//aim is to create: x~ = -(A'^T A')^{-1} A'^T c'
    TMatrixD *matrix_A_Prim_T = new TMatrixD(TMatrixD::kTransposed,*matrix_APrim); //A'^T
    TMatrixD *matrix_AA_T = new TMatrixD(*matrix_A_Prim_T, TMatrixD::kMult, *matrix_APrim); // (A'^T A')
    TMatrixD matrix_minus1 = matrix_AA_T -> Invert(); //(A'^T A')^{-1}
    TMatrixD *matrix_A_Prim_T_CPrim = new TMatrixD(*matrix_A_Prim_T, TMatrixD::kMult, *matrix_CPrim); //A'^T c'
    TMatrixD *matrix_x_wave = new TMatrixD(matrix_minus1, TMatrixD::kMult, *matrix_A_Prim_T_CPrim); //x~ = -(A'^T A')^{-1} A'^T c'

    for(int n = 0; n < stopien+1; n++)
	{
		for(int m = 0; m < stopien+1; m++)
		{
			if(m == n)
			{
				wsp_sigma[m] = TMath::Sqrt((matrix_minus1)(n,m));
			}
		}
	}

    for(int z = 0; z < matrix_x_wave -> GetNrows(); z++)
	{
		wsp[z] = (*matrix_x_wave)(z,0);
	}

    TMatrixD *matrix_eta_wave = new TMatrixD(*matrix_A, TMatrixD::kMult, *matrix_x_wave); //eta = A * x~
    TMatrixD *matrix_subtraction_one = new TMatrixD(TMatrixD::kTransposed,*matrix_C - *matrix_eta_wave);
    TMatrixD *matrix_1_2 = new TMatrixD(*matrix_subtraction_one, TMatrixD::kMult,*matrix_G_y);
    TMatrixD *matrix_2_2 = new TMatrixD(*matrix_1_2, TMatrixD::kMult, *matrix_C - *matrix_eta_wave);

    for(int i = 0; i < matrix_x_wave -> GetNrows(); i++) 
    {
        if(i == 0)
        {
			// Printing info
            cout << "Degree of polynomial: " << stopien << endl; 
            cout << "M = " << (*matrix_2_2)(0,0) << endl;
            cout << "NDF = " << n_pomiarow - stopien - 1 << endl;
            cout << "Alpha = " << alphaa << endl; 

            double quantile;
			//chi^2 test
            if(Chi2Test((*matrix_2_2)(0,0), alphaa, n_pomiarow - stopien - 1, quantile))
            {
				cout << "Quantile = " << quantile << endl;
				cout << "Degree " << stopien << ": " << "No grounds for rejection" << endl;
			} 
            else 
            {
				cout << "Quantile = " << quantile << endl;
				cout << "Degregree " << stopien << ": " << "We need to reject it [chi^2]" << endl;
			}
        } 
        cout << "x_" << i << " = " << wsp[i] << " +- " << wsp_sigma[i] << endl;
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	counter++;
}

double polynomials(double *x, double *params){
	//cout << "I'm in polynomial" << endl;
	double value = 0;
	for(int v = 0; v <= params[0]; v++)
	{
		value += params[v+1]*pow(x[0], v);
	}
	return value;

}
void lab11(){
	TCanvas *c1 = new TCanvas(); //frame
	TLegend *leg = new TLegend(0.1, 0.9, 0.4, 0.6); //legend
	vector<double> x, y, uncertanity;
	double coefficients[6], coefficients_sigma[6];
	
	for(int p = 0; p <= 5; p++)
    {
        fitting(p,number_of_measurements, x, y, uncertanity, coefficients, coefficients_sigma);
        if(p == 0)
        {
            TGraphErrors *gr = new TGraphErrors(x.size(),&x[0],&y[0],0,&uncertanity[0]);
            gr -> SetMarkerColor(kBlack); 
			gr -> SetMarkerStyle(22);
            gr -> SetTitle("Results of fitting; t, cos #Theta; y, liczba obserwacji");
            gr -> Draw("ALP");
        }

        TF1 *fun1 = new TF1(" ",polynomials,-1,15,p+2);
        fun1 -> SetParameter(0,p);

        for(int i = 0; i < p+1; i++)
		{
			fun1 -> SetParameter(i+1, coefficients[i]);
		} 

        fun1 -> SetLineColor(p+1); //now colors will be exactly the same as in the task
        string x = "deg "+to_string(p); //
        const char *tab = x.c_str();
        leg -> AddEntry(fun1,tab,"l");
        fun1 -> Draw("SAME");
    }
    leg -> Draw();

}
