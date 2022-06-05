TRandom *r = new TRandom(0);

double pi_mc () {
	int n = 0;
	int nn = 0;
	int N = 10000;
	TGraph *accepted = new TGraph ();
	TGraph *naccepted = new TGraph ();
	for (int i = 0; i < N; i++) {
		double x = r -> Uniform(1);
		double y = r -> Uniform(1);
		if (x*x + y*y <= 1) {
			n++;
			accepted -> SetPoint(n, x, y);
		}
		else {
			nn++;
			naccepted -> SetPoint(nn, x, y);
		}
	}
	TCanvas *window = new TCanvas ("window", "Zadanie 6", 800, 800);
	naccepted -> Draw("AP");
	accepted -> Draw("SameP");
	naccepted -> SetMarkerColor(kRed);
	accepted -> SetMarkerColor(kBlue);
	return 4.0 * n / N;
}

double losujVonNeumann (TF1 *g, double min, double max) {
	double u = 0, y = 0;
	do {
		u = r -> Uniform(0.0, g -> GetMaximum(min, max));
		y = r -> Uniform(min, max);
	} while ((g -> Eval(y)) > u);
	return y; 
}

double wydajnoscVonNeumanna (TF1 *g, double min, double max, int n) {
	int w = 0;
	double u = 0, y = 0;
	TH1D *h1 = new TH1D ("calkaN", "Neumann", 100, min, max);
	for (int i = 0; i < n; i++) {
		u = r -> Uniform(0.0, g -> GetMaximum(min, max));
		y = r -> Uniform(min, max);
		if ((g -> Eval(y)) > u ) {
			w++;
			h1 -> Fill(y);
		}
	}
	TCanvas *window1 = new TCanvas ("window1", "Zadanie 6.1", 800, 800);
	h1 -> Scale(g -> Integral(min, max)/(h1 -> Integral("width")));
	h1 -> Draw();
	g -> Draw("Same");
	return (double) w / n;
}

double calkaVonNeumann (TF1 *g, double min, double max, int n) {
	double d = g -> GetMaximum(min, max);
	return wydajnoscVonNeumanna(g, min, max, n) * (max - min) * d ;
}

double calkaFL (double x, double a, double b) {
	return a * x * x / 2 + b * x;
}

double odwrDys (double x, double a, double b) {
	return - b / a - TMath::Sqrt((2 * x) / a + (b * b) / (a * a));
}

double calkaVonNeumannZPomoc (TF1 *g, TF1 *s, double min, double max, int n, double &wydajnosc) {
	int wyd = 0;
	double a = s -> GetParameter(0);
	double b = s -> GetParameter(1);
	double u = 0, y = 0, x = 0;
	TH1D *h2 = new TH1D ("calkaNzP", "Neumann z pomocnicza", 100, min, max);
	for (int i = 0; i < n; i++) {
		u = gRandom -> Uniform(0, 1);
		x = gRandom -> Uniform(calkaFL(min, a, b), calkaFL(max, a, b));
		y = odwrDys(x, a, b);
		if ((g -> Eval(y) / s -> Eval(y)) > u ) {
			wyd++;
			h2 -> Fill(y);
		}
	} 
	TCanvas *window2 = new TCanvas ("window2", "Zadanie 6.2", 800, 800);
	h2 -> Scale(g -> Integral(min, max) / (h2 -> Integral("width")));
	h2 -> Draw();
	g -> Draw("Same"); 
	s -> SetLineColor(kGreen);
	s -> Draw("same");
	wydajnosc = (double) wyd / n;
	return wydajnosc * (max - min) * (s -> Eval(min) + s -> Eval(max)) / 2;
}

void lab16(void) {
	//cout << "Policzone PI = " << pi_mc();
	double min = 0.0;
	double max = 1.0;
	double wydajnosc;
	int N = 100000;
	TF1 *s = new TF1 ("s", "[0] * x + [1]", min, max);
	//TF1 *g = new TF1 ("g", "0.4 + (TMath::Sin(TMath::Pi() * (x + 1.2))) / (TMath::Pi() * (x + 1.2) + 1)", min, max);
	TF1 *g = new TF1 ("g", "TMath::Exp(-5 * x)", min, max);
	double c = g -> Eval(min);
	double d = g -> Eval(max);
	s -> SetParameter(0, (d - c)/(max - min));
	s -> SetParameter(1, c - min * s -> GetParameter(0));
	//cout << "c :" << c << "d : " << d << endl;
	cout << "a : " << s -> GetParameter(0) << " b: " << s -> GetParameter(1) << endl;
	cout << "\nCałka metodą Integral: " << g -> Integral(min, max);
	cout << "\nCalka von Neumanna: " << calkaVonNeumann(g, min, max, N);
	cout << "\nWydajnosc: " << wydajnoscVonNeumanna(g, min, max, N);
	cout << "\nCalka von Neumanna pomocnicza: " << calkaVonNeumannZPomoc(g, s, min, max, N, wydajnosc);
	cout << "\nWydajnosc: " << wydajnosc << "\n";
}
