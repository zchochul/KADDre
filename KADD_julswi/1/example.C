/******************************************************************|
|W środowisku ROOT piszemy makra, które zawierają kod w języku C++ |
|interpretowany linijka po linijce. Makra mają rozszerzenie .c, .C,|
|.cpp lub .cxx. Nie trzeba załączać bibliotek (w większości        |
|przypadków) co pozwala na efektywniejszą pracę. Wewnątrz makra    |
|można tworzyć wiele funkcji. Makro można uruchomić na dwa sposoby:|
|1) bezpośrednio w terminalu:                                      |
|  root makro.C                                                    |
|2) wewnątrz interpretera po uruchumieniu komendą root:            |
|  .x makro.C                                                      |
|W obu przypadkach zostanie zostanie wywołana funkcja makro(),     |
|dlatego jeśli chcemy skorzystać z takiej opcji, należy nazwać     |
|główną funkcję tak samo jak makro (można o tym myśleć jak main w  |
|programie c++).                                                   |
|Jeśli chcemy mieć dostęp do napisanych funkcji w interpreterze,   |
|bez uruchamiania głównej funkcji, można załadować makro komendą:  |
|  .L makro.C                                                      |
|Aby zamknąć interpreter należy wykonać komendę:                   |
|  .q                                                              |
*******************************************************************/


//główna funkcja przykładowego makra
void example(){
  //typy zmiennych tak samo jak w c++
  float a1 = 1.564; // zmienna typu 
  int b1 = 2;
  double c1 = a1 * b1;
  
  //Wypisywanie na terminal analogicznie do c++
  std::cout << "Zmienna c1=" << c1 << std::endl;

  // dodatkowo są też zmienne środowiska ROOT: Double_t, Int_t, Float_t, ...
  Float_t a2 = 2.432;
  Int_t b2 = 4;
  Double_t c2 = a2 / b2;
  std::cout << "Zmienna c2=" << c2 << std::endl;
  // Te typy są zoptymalizowane pod względem zużycia pamięci
  // (na zajęciach można ograniczyć się do standardowych).

  // Klasa TMath pozwala na wykorzystanie różnych funkcji i stałych matematycznych
  std::cout << "Klasa TMath" << std::endl;
  std::cout << "PI=" << TMath::Pi() << std::endl
	    << "sin(PI/2)=" << TMath::Sin(TMath::Pi()/2) << std::endl
	    << "exp(2)=" << TMath::Exp(2) << std::endl;

  // Można też stworzyć obiekt funkcji wykorzystująć TF1
  TF1* f1 = new TF1("f1","[0] * TMath::Exp([1]*x)",0,5); // podajemy nazwe obiektu, funkcję matematyczną, liczbę parametrów i zakrez dla x.
  f1->SetParameters(-1,2); // ustawienie parametru [0] = 1, [1] = 2
  f1->SetLineColor(kBlue); // ustawienie koloru wykresu (więcej szczegółów w klasie TAttMarker i TF1)

  // aby narysować funkcję należy stworzyć obiekty TCanvas
  Int_t width = 600;
  Int_t height = 800;
  TCanvas* canva1 = new TCanvas("canva1","Canvas 1", width, height);
  f1->Draw(); 
  

}
