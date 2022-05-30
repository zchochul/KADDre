double MNK (int st, int n, double *tj, double *yj, double *sigmaj, double *wsp, double *bwsp) {
	TMatrixD *A = new TMatrixD(n, st);
	TMatrixD *H = new TMatrixD(n, n);
	for (int i = 0; i < n; i++) {
		(*H)(i, i) = (double) 1. / sigmaj[i];
		for (int j = 0; j < st; j++) {
			(*A)(i, j) = TMath::Power(tj[i], j);
		}
	}
	TMatrixD *A_prim = new TMatrixD(*H, TMatrixD::kMult, *A);
	
	TMatrixD *ys = new TMatrixD(n, 1);
	ys -> SetMatrixArray(yj); 
	
	TMatrixD *c_prim = new TMatrixD(*H, TMatrixD::kMult, *ys);
	TMatrixD *A_prim_T = new TMatrixD(TMatrixD::kTransposed, *A_prim);
	TMatrixD *A_prim_T_mul_A_prim = new TMatrixD(*A_prim_T, TMatrixD::kMult, *A_prim);
	TMatrixD *A_prim_T_mul_c_prim = new TMatrixD(*A_prim_T, TMatrixD::kMult, *c_prim);
	
	A_prim_T_mul_A_prim -> Invert();
	TMatrixD *x_tilde = new TMatrixD(*A_prim_T_mul_A_prim, TMatrixD::kMult, *A_prim_T_mul_c_prim);
	TMatrixD *eta_tilde = new TMatrixD(*A, TMatrixD::kMult, *x_tilde);
	
	double M = 0;
	for (int k = 0; k < n; k++) {
		M += TMath::Power((yj[k] - (*eta_tilde)(k, 0))/sigmaj[k], 2);
	}
	
	for (int l = 0; l < st; l++) {
		wsp[l] = (*x_tilde)(l, 0);
		bwsp[l] = TMath::Sqrt((*A_prim_T_mul_A_prim)(l, l));
	}
	
	return M;
}

int testchi2(double T, double alpha, int ndf) {
	TF1 *chi = new TF1("chi", "[0] * TMath::Power(x, [1] - 1) * TMath::Exp(-1 * x/2)", 0, 20);
	int k = 1 / (TMath::Gamma(ndf) * TMath::Power(2, ndf));
	chi -> SetParameter(0, k);
	chi -> SetParameter(1, ndf);
	double spr;
	spr = chi -> Integral(0, T);
	if ((1 - alpha) < spr) {
		return 1;
	}
	else 
		return 0;
}


void lab11_J_S(void) {
	ifstream ifile("dane.txt");
	double a, b, alpha = 0.01;
	double tj[15], yj[15], sigmaj[15];
	int n = 0, ndf;
	while(ifile >> a) {
		ifile >> b;
		tj[n] = a;
		yj[n] = b;
		sigmaj[n] = TMath::Sqrt(b);
		n++;
	}
	ifile.close();
	
	TGraphErrors *errgraph = new TGraphErrors(n, tj, yj, NULL, sigmaj);
	TCanvas *window = new TCanvas ("window", "Zadanie 12", 800, 800);
	window -> cd(1);
	errgraph -> Draw("A*");
	
	double wsp[15], bwsp[15];
	double M;
	
	for (int i = 1; i < 6; i++) {
		M = MNK(i, n, tj, yj, sigmaj, wsp, bwsp);
		ndf = n - i - 1;
		cout << "Dopasowanie wielomianem stopnia " << i << endl;
		cout << "M = " << M << endl;
		cout << "Liczba stopni swobody = " << ndf << endl;
		TF1 *fun = new TF1 ("wielomian", Form("pol%d", i), 0, 15);
		for (int j = 0; j < i; j++) {
			cout << "x" << j << " = " << wsp[j] << " +- " << bwsp[j] << endl;
			fun -> SetParameter(j, wsp[j]);
		}
		fun -> SetLineColor(i);
		fun -> Draw("sameC");
		cout << "Poziom istotności = " << alpha << endl;
		if (testchi2(M, alpha, ndf) == 1) {
			cout << "Odrzucamy stopień " << i << endl;
		}
		else {
			cout << "Brak podstaw do odrzucenia stopnia " << i << endl;
		}
	}
}
