void splot(TF1 **f, int k, TH1D *h, int n) {
	for (int i = 0; i < k; i++) {
		f[i] 
	}
} 

TRandom *r = new TRandom();

void deskaGaltona(TH1D *h, int n, int l, double p) {
	int a;
	double u;
	for (int j = 0; j < n; j++) {
		a = 0;
		for (int i = 0; i < l; i++) {
			u = r -> Uniform(0.0, 1.0);
			if (u <= p) 
				a++;
			else 
				a--;
		}
		h -> Fill(a);
	}
}


void lab18(void) {
	//double u1 = r -> Uniform(0.0, 2.0);
	//double u2 = r -> Uniform(0.0, 2.0);
	
	int N = 1000;
	int l = 10;
	double p = 0.4;
	TH1D *deska = new TH1D ("deska", "deska Galtona", 300, -10, 10);
	deskaGaltona(deska, N, l, p);
	TCanvas *c1 = new TCanvas();
	deska -> Draw();
}

