# KADDre
This repository is based on the laboratories for the subject Komputerowa Analiza Danych Doświadczalnych (KADD) taught at WUT. For more info open [dr Łukasz Graczykowski's website](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2021/2022).
# Laboratories
1. [Lab1](#Lab1)
2. [Lab2](#Lab2)
3. [Lab3](#Lab3)
4. [Lab4](#Lab4)
5. [Lab5](#Lab5)
6. [Lab6](#Lab6)
7. [Lab7](#Lab7)
8. [Lab8](#Lab8)
# Root help ;)
1. [TF1](#TF1)
2. [TGraph](#TGraph)
3. [TF2](#TF2)
4. [TH1D](#TH1D)
5. [TH2D](#TH2D)
6. [TGraph](#TGraph)
7. [TGraph2D](#TGraph2D)
8. [TCanvas](#TCanvas)
# Math help ;)
1. [Probability distribution](#PDF)
2. [Cumulative distribution](#cumulativ)
3. [Marginal distribution](#Marginal)
4. [Probability  P(5 <= X <= 10)](#PDF)
5. [Expected value](#expect)
6. [Variance](#variance)
7. [Standard deviation](#std)
8. [Covariance](#covariance)
9. [Covariance matrix](#covariance_matrix)
10. [Correlation coefficient rho(X,Y)](#cor_coef_rho)
11. [Mode](#Mode)
12. [Quantiles](#Quantiles)
13. [Linear congruent generator of pseudorandom numbers](#LCG)
14. [ Spectral test](#spectral_test)
15. [Estimation of Pi](#pi)

## Lab1 <a name="Lab1"></a>
[`test.c`](https://github.com/zchochul/KADDre/blob/main/test.C) - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_1_EN) (28.02.2022) <br>
![image](https://user-images.githubusercontent.com/87480906/164894115-a8760881-77da-45c1-9bba-c993338c5c28.png)
![image](https://user-images.githubusercontent.com/87480906/164894119-3f323396-fbcd-4868-952f-159d75755c0f.png)

## Lab2 <a name="Lab2"></a>
[`lab1.c`](https://github.com/zchochul/KADDre/blob/main/lab1.C) - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_2_EN) (07.03.2022) <br>
![image](https://user-images.githubusercontent.com/87480906/164894897-324e1326-5bcc-48c0-b9d0-0bb949a2928a.png)
![image](https://user-images.githubusercontent.com/87480906/164894774-4a806203-0761-4073-8e57-2be95a8e2ead.png)
![image](https://user-images.githubusercontent.com/87480906/164894781-e3a34ef5-2273-488d-b424-d4da6b0a377c.png)


## Lab3 <a name="Lab3"></a>
[`lab3.c`](https://github.com/zchochul/KADDre/blob/main/lab3.c) - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_3_EN) (14.03.2022) <br>
![image](https://user-images.githubusercontent.com/87480906/164895932-e5ea2389-2bdb-4ad6-b4f6-10878bdca759.png)
```c
double fcn(double *x, double *params)
	{
		if(x[0]>=0 && x[0] <= 1 && x[1]>=0 && x[0] <= 1 )
			return params[0]*TMath::Power(x[0], params[1])*TMath::Power(x[1], params[2]);
		return 0;
	}
```
![image](https://user-images.githubusercontent.com/87480906/164895944-9d971d97-18cf-43a9-88ed-3b3a41e59792.png)

## Lab4 <a name="Lab4"></a>
[`lab4.c`](https://github.com/zchochul/KADDre/blob/main/lab4.c) - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_4_EN) (21.03.2022) <br>
![image](https://user-images.githubusercontent.com/87480906/164905937-3de4698c-5994-4d66-87f6-698bc6b8462b.png)
```c
double fcn(double *x, double *params)
	{
		if((0 <= x[0]*x[1]) &&  (x[0]*x[1]<= TMath::Pi()))
			return params[0]*TMath::Sin(x[0]*x[1]);
		return 0;
	}
```
![image](https://user-images.githubusercontent.com/87480906/164906289-2276233a-97c6-4a52-93e6-fa16c91b3cef.png)
![image](https://user-images.githubusercontent.com/87480906/164906467-d6e839f0-59d6-4cfd-872b-50f38bcc8d0e.png)
randomly select from the probability distribution a pair of numbers (x,y) and then fill with the a histogram of the probability distribution f(x,y): <br>
```c
	double px, py;
	for (Int_t i = 0; i < 50000; i++) {
		fun1->GetRandom2(px,py); // fun1 determines values
		fun2->Fill(px,py); //fun2 is TH2D histogram 
	}
```
## Lab5 <a name="Lab5"></a>
[`lab5.c`](https://github.com/zchochul/KADDre/blob/main/lab5.c) - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_5_EN) (28.03.2022) <br>
![image](https://user-images.githubusercontent.com/87480906/164974297-d00fb8f7-f434-4760-b473-931d0e78eb11.png)<br>
![image](https://user-images.githubusercontent.com/87480906/164974306-762886b7-b19d-4cf9-851a-10730a1151e2.png)<br>
Read data from file (the same as in C++):<br>
```c
	ifstream ifile;
	ifile.open("dane.dat");
	double val;
	while(ifile>>val)
	{
 		cout<<val<<endl;
	}
	ifile.close();
```


## Lab6 <a name="Lab6"></a>
[`lab6.c`](https://github.com/zchochul/KADDre/blob/main/lab6.c) - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_6_EN) (04.04.2022) <br>
![image](https://user-images.githubusercontent.com/87480906/164976280-28f80e4f-e35c-4260-bcc8-ee6c119dbd01.png)<br>
![image](https://user-images.githubusercontent.com/87480906/164976293-4f0f1ff8-030d-46e3-b3f4-a8e2d1c19946.png)<br>


## Lab7 <a name="Lab7"></a>
[`lab16.c`](https://github.com/zchochul/KADDre/blob/main/lab16.c)  - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_7_EN) (11.04.2022)

## Lab8 <a name="Lab8"></a>
[`lab8.c`](https://github.com/zchochul/KADDre/blob/main/lab8.c)  - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_8) (18.04.2022)
![image](https://user-images.githubusercontent.com/87480906/164978627-80d33f71-de3c-4357-a8a4-a289f4064941.png)<br>
![image](https://user-images.githubusercontent.com/87480906/164978634-d52f9ece-7cff-48c8-acef-19135dac004d.png)<br>
Rot Gaussian distribution you can use:
```c
	TF1 *fa1n = new TF1("fa1n","ROOT::Math::gaussian_pdf(x, 0.2, 1.0)",-10,10);
```


## TF1 <a name="TF1"></a>
> **Create function using TF1** <br>
>> `TF1 *fun1= new TF1("fun1", "TMath::Sin(x)", 0, 2*TMath::Pi());` <br>

> **Set Parameter**
>> `TF1 *fun1 = new TF1("fun1", "1./[0] * TMath::Exp(-x/[0])", 0, 50);`<br>
>>	`fun1->SetParameter(0, 6);`<br>

> **Style TF1**
>> `fun1->SetLineColor(kBlue);` <br>

> **Draw options**
>> `fun2 -> Draw("same");` <br>

## TF2 <a name="TF2"></a>
> **Create function using TF2** <br>
>> `TF2 *fun1 = new TF2("fun1",fcn,xmin,xmax,ymin,ymax,nparams);` <br>
>> where `nparams` is number of parameters <br>

> **Set Parameters**
>> `fun1->SetParameters(1,1,2);` <br>

> **Set Parameter** <br>
>> `fun1->SetParameter(0,1/c);` (that's for TF2 in [`lab3.c`](https://github.com/zchochul/KADDre/blob/main/lab3.c))<br>

> **Style TF2**
>> `fun1->SetTitle("Gestosc");` <br>
>> `fun1->GetXaxis()->SetTitle("x");`<br>
>> `fun1->GetYaxis()->SetTitle("y");`<br>
>> `fun1->GetZaxis()->SetTitle("f(x,y)");`<br>

> **Draw options**
>> `fun1->Draw("Surf1");`<br>

## TH1D <a name="TH1D"></a>
> **Create** <br>
>> `TH1D *hist = new TH1D("h", ";;Y Axis", 6, 0, 6);` (like in [`test.c`](https://github.com/zchochul/KADDre/blob/main/test.C)) <br>

> **Fill histogram**<br>
>> `hist -> SetBinContent(pips[i], throws[i]);`<br>

> **Draw options** <br>
>> `hist -> Draw();` <br>

> **Projection of TH2D on TH1D** <br> (like in [`lab4.c`](https://github.com/zchochul/KADDre/blob/main/lab4.c))
>> Creating: `TH1D * projh2Y = fun2->ProjectionY();` <br>

## TH2D <a name="TH2D"></a>
>**Create TH2D** <br>
>> `TH2D *fun2 = new TH2D("fun2", "gestosc", 20, xmin, xmax, 20, ymin, ymax);`<br> (like in [`lab4.c`](https://github.com/zchochul/KADDre/blob/main/lab4.c))

> **Filling with data** <br>
>> `fun2->Fill(px,py);`<br> (like in [`lab4.c`](https://github.com/zchochul/KADDre/blob/main/lab4.c))
>>  `fun3->SetBinContent(xs, ys, fun2->Integral(0,xs, 0, ys));` (like in [`lab4.c`](https://github.com/zchochul/KADDre/blob/main/lab4.c))

> **Draw options** <br>
>> `fun2->Draw("lego1");` <br> (like in [`lab4.c`](https://github.com/zchochul/KADDre/blob/main/lab4.c))
>> ![image](https://user-images.githubusercontent.com/87480906/164973419-23b222f4-cda7-4aa9-b06c-4630c5e0f0d7.png)<br>
>>  `h12->Draw("colz");`<br>
>>  ![image](https://user-images.githubusercontent.com/87480906/164974734-98abb162-175b-4abd-89f9-1265733ec066.png)<br>

## TGraph <a name="TGraph"></a>
>**Create TGraph** <br>
  >> `TGraph* gr = new TGraph();` <br>

>**Fill TGraph**
>> `gr-> SetPoint(i, throws[i], pips[i]);`

>**Style TGraph**
>> `gr -> SetMarkerSize(2);` <br>
>> `gr -> SetMarkerStyle(22);` <br>

> **Draw options** <br>
>> `gr -> Draw("AP");` Only points <br>
>> ![image](https://user-images.githubusercontent.com/87480906/164972950-6a208f4c-4955-4657-8d14-101bf93cadf9.png)<br>
>> `gr -> Draw("APL");` Connect points with a line <br>
>> ![image](https://user-images.githubusercontent.com/87480906/164972933-04a95cd3-21e2-4f09-856d-69217eb131b8.png) <br>
>> `accepted -> Draw("SameP");`<br>
>> ![image](https://user-images.githubusercontent.com/87480906/164978562-d99c9809-1ca7-4320-8456-e7dbc5417d0b.png)


## TGraph2D <a name="TGraph2D"></a>
>**Create TGraph2D** <br>
  >> `TGraph2D *g = new TGraph2D();` <br>
  
> **Normalize TH2D**
>> `fun2->Scale(1./fun2->Integral());` <br>

> **Draw options** <br>
>> `g->Draw("surf1");`<br>
![image](https://user-images.githubusercontent.com/87480906/164972733-482da830-526f-47cc-8a9a-1af501beb8f4.png)<br>
>> `fun3->Draw("lego1");` <br>

## TMatrixD (used in [`lab5.c`](https://github.com/zchochul/KADDre/blob/main/lab5.c))<br>
> **Create**<br>
>> `TMatrixD matrix(row, column);`<br>

> **Fill**<br>
>> `matrix(row, column) = value` <br>

> **Multiplying two matrixes**<br>
>> `TMatrix matrix3 = matrix1 * matrix2`<br>

> **Transpose a matrix**<br>
>> `matrix.Transpose(matrix2)`<br>

> **Printing**<br>
>> `matrix.Print();`<br>

## TCanvas <a name="TCanvas"></a>
> **Create window** <br>
>> `TCanvas *c1 = new TCanvas("c1", "window 1", 10, 10, 800, 800);` <br>

> **Dividing window 2x2** <br>
>>`c1 -> Divide(2,2);` <br>
  
 > **Drawing in window** <br>
  >> `c1-> cd(1);` <br>

## Probability distribution (more in [`lab1.c`](https://github.com/zchochul/KADDre/blob/main/lab1.C)) <a name="PDF"></a>
First you need to normalize given function, for example:<br>
`TF1 *fun1 = new TF1("fun1", "1./[0] * TMath::Exp(-x/[0])", 0, 50);` <br>
by dividing it by: `Double_t a = fun1 -> Integral(0,50);`. <br>
then `fun1->SetParameter(0, 1/a);` <br>
and draw it: `fun1->Draw();` <br> <br>

Or you can use `Scale` function: ` fun2->Scale(1./fun2->Integral());` (like in [`lab4.c`](https://github.com/zchochul/KADDre/blob/main/lab4.c))<br> 

## Cumulative distribution (more in  [`lab1.c`](https://github.com/zchochul/KADDre/blob/main/lab1.C)) <a name="cumulativ"></a>
After all steps from _Probability distribution_: <br>
by dividing it by: `Double_t a = fun1 -> Integral(0,50);`. <br>
then `fun1->SetParameter(0, a);` <br>
and draw it: `fun1->DrawIntegral();` <br> <br>
For 2D: <br>
```c
TGraph2D *g = new TGraph2D();
	int count = 0;
	for(Double_t xs = 0; xs <=1 ; xs+= 1./30){
		for(Double_t ys=0; ys <=1 ; ys+= 1./30 )
		{
			g->SetPoint(count, xs, ys, fun1->Integral(0,xs, 0, ys));
			count++;
		}
	}
```

## Marginal distribution (more in  [`lab3.c`](https://github.com/zchochul/KADDre/blob/main/lab3.c)) <a name="Marginal"></a>
![image](https://user-images.githubusercontent.com/87480906/164903038-cee06d37-d5a1-4ba5-b276-9c8850a2e2bc.png)
### g(x)
```c
TGraph *fung = new TGraph();
	int count1 = 0;
	for(Double_t xs = 0; xs <=1 ; xs+= 1./30){
		fung -> SetPoint(count1, xs, fun1->Integral(xs-1./100,xs,0,1));
		count1++;
	}
```
### h(y)
```c
TGraph *funh = new TGraph();
	int count2 = 0;
	for(Double_t ys = 0; ys <=1 ; ys+= 1./30){
		funh -> SetPoint(count2, ys, fun1->Integral(0,1, ys-1./100,ys));
		count2++;
	}
```
## Probability  P(5 <= X <= 10) (more in [`lab1.c`](https://github.com/zchochul/KADDre/blob/main/lab1.C)) <a name="Prob"></a>
After all steps from _Probability distribution_, do:  `Double_t b = fun1 -> Integral(5,10);` <br>

## Expected value (more in [`lab1.c`](https://github.com/zchochul/KADDre/blob/main/lab1.C)) <a name="expect"></a>
After all steps from _Probability distribution_, do: `Double_t mean = fun1 -> Mean(0,50);` <br><br>

If you use TH2D and you want to obtain E(X) and E(Y) (like in [`lab4.c`](https://github.com/zchochul/KADDre/blob/main/lab4.c)) use: <br>
```c
	double Ex = fun2 -> GetMean(1);
	double Ey = fun2 -> GetMean(2);
```

## Variance (more in [`lab1.c`](https://github.com/zchochul/KADDre/blob/main/lab1.C)) <a name="variance"></a>
After all steps from _Probability distribution_, do: `Double_t variance = fun1 -> Variance(0,50);` <br>

## Standard deviation <a name="std"></a>
Standard deviation is the square root of the variance. When you want to use it on **TH2D** (like in [`lab4.c`](https://github.com/zchochul/KADDre/blob/main/lab4.c)) use `GetRMS(<number of axis>)`, for example: <br>
```c
	double sigmax = fun2 -> GetRMS(1);
	double sigmay = fun2 -> GetRMS(2);
```
## Covariance (like in [`lab4.c`](https://github.com/zchochul/KADDre/blob/main/lab4.c)) <a name="covariance"></a>
To obtain covariance use: `double covxy = fun2 -> GetCovariance(1,2);`<br>

##  Covariance matrix (like in [`lab5.c`](https://github.com/zchochul/KADDre/blob/main/lab5.c) <a name="covariance_matrix"></a>
More on that here [lecture](http://www.if.pw.edu.pl/~lgraczyk/KADD2022/Wyklad5-2022.pdf). Long story short on diagonal we have sigma xi (so GetRMS but squared) and in other cases we have cov xixj (GetCovariance). For examples in code open  [`lab5.c`](https://github.com/zchochul/KADDre/blob/main/lab5.c).<br>
If you have covariance function you can obtain correlation function easily: `double corfac =  result(0,1)/sqrt(result(0,0) * result(1,1));` (like in  [`lab5.c`](https://github.com/zchochul/KADDre/blob/main/lab5.c)).<br>
And you can also calculate errors: `double errory2 = sqrt(result(1,1));`<br>

## Correlation coefficient rho(X,Y)  (like in [`lab4.c`](https://github.com/zchochul/KADDre/blob/main/lab4.c)) <a name="cor_coef_rho"></a>
To obtain correlation coefficient use: `double corfac = fun2 -> GetCorrelationFactor(1,2);`<br>
If you have covariance function you can use: `double corfac =  result(0,1)/sqrt(result(0,0) * result(1,1));` (like in  [`lab5.c`](https://github.com/zchochul/KADDre/blob/main/lab5.c)).<br>

## Mode (more in [`lab1.c`](https://github.com/zchochul/KADDre/blob/main/lab1.C)) <a name="Mode"></a>
After all steps from _Probability distribution_, do: `Double_t mode = fun1 -> GetMaximumX(0,50);` <br>

## Quantiles (more in [`lab1.c`](https://github.com/zchochul/KADDre/blob/main/lab1.C)) <a name="Quantiles"></a>
After all steps from _Probability distribution_, do:  <br>
```c
	const Int_t nq = 3;
	Double_t xq[nq] = {0.25,0.5,0.75};
	Double_t yq[nq];
	fun1->GetQuantiles(nq,yq,xq);
```
## Linear congruent generator of pseudorandom numbers (more in [`lab6.c`](https://github.com/zchochul/KADDre/blob/main/lab6.c) <a name="LCG"></a>
Generator based on formula: `x[j+1] = (g*x[j] + c) mod m.`. By providing first value `x[0]` defines whole series. There are few conditions:
1. c and m do not have joint divisors,
2. b = g-1 is a multiply of every prime number p, which is a divisor of a number m,
3. b is a multiply of 4 if n is also a multiply of 4.

When `c=0` then we get multiplicative generator (MLCG).

## Spectral test (more in [`lab6.c`](https://github.com/zchochul/KADDre/blob/main/lab6.c)) <a name="spectral_test"></a>
Plot `(x[n], x[n+1])` to see the quality of the generator.  The obtained graph will show a spectral pattern of the generator - hence the name of the test. If the points are distributed uniformly, the test can be judged good.

## Estimation of PI <a name="pi"></a>
Using von Neuman (Monte Carlo) method it is possible to calculate estimation of PI. In order to calculate the Pi, we randomly generate two numbers x and y from the uniform distribution [0,1] and we check whether the pair falls within the circle of the radius equal to 1. Next, by calculating the ratio of accepted pairs to all of them, you approximate the ratio of areas of the circle to the rectangle.

## Useful snipets from documentation!
TF1 - [here](https://root.cern.ch/doc/master/classTF1.html)<br>
TCanvas - [here](https://root.cern.ch/doc/master/classTCanvas.html)<br>
TMath - [here](https://root.cern.ch/root/html524/TMath.html)<br>
TAttMarker - [here](https://root.cern.ch/doc/master/classTAttMarker.html)<br>
TGraph - [here](https://root.cern.ch/doc/master/classTGraph.html)<br>
