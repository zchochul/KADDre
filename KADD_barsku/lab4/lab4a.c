void lab4a(){

 Double_t w = 600;
   Double_t h = 600;
   TCanvas *c = new TCanvas("c", "c", w, h);
   c->Divide(3,3);

TF1 *f1 = new TF1("f1", "TMath::Exp(-x/2.)/2.", 0,8);

TH1D *t = new TH1D("t","t",100,0,1);
TH1D *t2 = new TH1D("t2","t2",100,0,1);
TH1D *t3 = new TH1D("t3","t3",100,0,1);
TH1D *t4 = new TH1D("t4","t4",100,0,1);
TH1D *t5 = new TH1D("t5","t5",100,0,8);
TH1D *t6 = new TH1D("t5","t5",20,0,8);
TH1D *t7 = new TH1D("t5","t5",20,0,8);
TH1D *t8 = new TH1D("t5","t5",20,0,8);
TH1D *t9 = new TH1D("t5","t5",20,0,8);

ifstream ifile1,ifile2,ifile3,ifile4;
ifile1.open("losowe1.dat");
ifile2.open("losowe2.dat");
ifile3.open("losowe3.dat");
ifile4.open("losowe4.dat");
double val1,val2,val3,val4;

while(ifile1>>val1 && ifile2>>val2 && ifile3>>val3&& ifile4>>val4)
{
	t5->Fill(-2*log(1-val1));
t6->Fill(-2*log(1-val2));
t7->Fill(-2*log(1-val3));
t8->Fill(-2*log(1-val4));
t9->Fill(-2*log(1-gRandom->Uniform(1)));
  t->Fill(val1);
t2->Fill(val2);
t3->Fill(val3);
t4->Fill(val4);
}

ifile1.close();
ifile2.close();
ifile3.close();
ifile4.close();
c->cd(1);
t->Scale(1./(t->Integral()));
t2->Scale(1./(t2->Integral()));
t3->Scale(1./(t3->Integral()));
t4->Scale(1./(t4->Integral()));
t5->Scale(1./(t5->Integral()));
t6->Scale(1./(t6->Integral()));
t7->Scale(1./(t7->Integral()));
t8->Scale(1./(t8->Integral()));
t9->Scale(1./(t9->Integral()));
t->Draw();
c->cd(2);
t2->Draw();
c->cd(3);
t3->Draw();
c->cd(4);
t4->Draw();
c->cd(5);
t5->Draw();
f1->Draw("same");
c->cd(6);
t6->Draw();
f1->Draw("same");
c->cd(7);
t7->Draw();
f1->Draw("same");
c->cd(8);
t8->Draw();
f1->Draw("same");
c->cd(9);
t9->Draw();
f1->Draw("same");







}
