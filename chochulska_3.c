//Zuzanna Chochulska kol 3

TRandom *r = new TRandom();

double losujVonNeumann (TF1 *g, double min, double max) {
	double u, y;
	do {
		u = r -> Uniform(0, g -> GetMaximum(min, max));
		y = r -> Uniform(min, max);
	} while ((g -> Eval(y)) < u);
	return y; 
}

double wydajnoscVonNeumanna (TF1 *g, double min, double max, int n) {
	int w = 0;
	double u, y;
	for (int i = 0; i < n; i++) {
		u = r -> Uniform(0, g -> GetMaximum(min, max));
		y = r -> Uniform(min, max);
		if ((g -> Eval(y)) > u ) 
			w++;
	}
	return (double) w / n;
}

double calkaVonNeumann (TF1 *g, double min, double max, int n) {
	double d = g -> GetMaximum(min, max);
	return wydajnoscVonNeumanna(g, min, max, n) * (max - min) * d ;
}

void chochulska_3(void) {
	double min = (TMath::Pi())/4;
	double max = (TMath::Pi())/2;
	double wydajnosc;
	int N = 100000;
	
	TF1 *g = new TF1 ("g", "TMath::Sin(TMath::Cos(x))", min, max);
	
	//Results
	cout << "\nCałka metodą Integral: " << g -> Integral(min, max);
	cout << "\nCalka von Neumanna: " << calkaVonNeumann(g, min, max, N);
	cout << "\n Blad wzgledny = " << TMath::Abs(calkaVonNeumann(g, min, max, N) - g -> Integral(min, max))/(g -> Integral(min, max)) << endl;
	
}

