// f - tablica wskaznikow do obiektow TF1, rozklady skladowe
// k - wymiar tablicy f
// h - histogram do ktorego wrzucamy wynik splotu
// n - liczba losowan
void splot(TF1 **f, int k, TH1D *h, int n){
	double z=0;
	
	for (int i=0; i < n; i++){
		for (int j=0; j< k; j++){
			z += f[j]->GetRandom();
		}	
		h->Fill(z);
		z=0;
	}
	
	
}
//     n - liczba prób (kul)
//    l - liczba rzędów
//    p - prawdopodobieństwo ruchu kuli w prawo (sukcesu) 
void deskaGaltona(TH1D * h, int n, int l, double p){
	TRandom *r = new TRandom();
	
	for (int i=0; i<n; i++){
		double z = 0;
		for(int j = 0; j<l; j++){
			if(r -> Uniform(0,1) < p)
				z--;
			else 
				z++;
		}
		h->Fill(z);
	}
}

void lab8(){
	TCanvas *c1 = new TCanvas();
	c1 -> Divide(2,2);
	TF1 *fa1 = new TF1("fa1","0*x+1",0,2);
	TF1 *fa2 = new TF1("fa2","0*x+1",0,2);
	TF1 *fa[2];
	fa[0] = fa1;
	fa[1] = fa2;
	
	TF1 *fu1 = new TF1("fu1","0*x+1",0,2);
	TF1 *fu2 = new TF1("fu2","0*x+1",0,2);
	TF1 *fu3 = new TF1("fu3","0*x+1",0,2);
	TF1 *fu[3];
	fu[0] = fu1;
	fu[1] = fu2;
	fu[2] = fu3;
	
	double xmin = 0.0, xmax = 2.0;
	c1->cd(1);
	TH1D *efekt = new TH1D("h1", "h1 title", 100, 0, 4);
	splot(fa, 2, efekt, 100000);
	efekt->Draw();
	
	c1->cd(2);
	TH1D *efekt2 = new TH1D("h2", "h1 title", 100, 0, 6);
	splot(fu, 3, efekt2, 100000);
	efekt2->Draw();
	
	//ROOT::Math::gaussian_pdf 	
	//Gaussian
	TF1 *fa1n = new TF1("fa1n","ROOT::Math::gaussian_pdf(x, 0.2, 1.0)",-10,10);
	TF1 *fa2n = new TF1("fa2n","ROOT::Math::gaussian_pdf(x,  0.5, 3.0)",-10,10);
	TF1 *fan[2];
	fan[0] = fa1n;
	fan[1] = fa2n;
	TH1D *efekt3 = new TH1D("h3", "h1 title", 100, -10, 6);
	splot(fan, 2, efekt3, 100000);
	c1->cd(3);
	efekt3->Draw();
	
	c1->cd(4);
	TH1D *efekt4 = new TH1D("h4", "h1 title", 100, -10, 10);
	deskaGaltona(efekt4, 1000, 10, 0.4);
	efekt4->Draw();
	
}
