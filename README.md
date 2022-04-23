# KADDre
# Table of contents
1. [Lab1](#Lab1)
2. [Lab2](#Lab2)
3. [Lab3](#Lab3)
4. [Lab4](#Lab4)
5. [Lab5](#Lab5)
7. [Lab6](#Lab6)
8. [TF1](#TF1)
9. [TGraph](#TGraph)
10. [TCanvas](#TCanvas)


## Lab1 <a name="Lab1"></a>
`test.c` - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_1_EN) (28.02.2022) <br>
![image](https://user-images.githubusercontent.com/87480906/164894115-a8760881-77da-45c1-9bba-c993338c5c28.png)
![image](https://user-images.githubusercontent.com/87480906/164894119-3f323396-fbcd-4868-952f-159d75755c0f.png)

## Lab2 <a name="Lab2"></a>
`lab1.c` - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_2_EN) (07.03.2022) <br>
![image](https://user-images.githubusercontent.com/87480906/164894897-324e1326-5bcc-48c0-b9d0-0bb949a2928a.png)
![image](https://user-images.githubusercontent.com/87480906/164894774-4a806203-0761-4073-8e57-2be95a8e2ead.png)
![image](https://user-images.githubusercontent.com/87480906/164894781-e3a34ef5-2273-488d-b424-d4da6b0a377c.png)


## Lab3 <a name="Lab3"></a>
`lab3.c` - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_3_EN) (14.03.2022) <br>

## Lab4 <a name="Lab4"></a>
`lab4.c` - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_4_EN) (21.03.2022) <br>

## Lab5 <a name="Lab5"></a>
`lab5.c` - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_5_EN) (28.03.2022) <br>

## Lab6 <a name="Lab6"></a>
`lab6.c` - [task](http://www.if.pw.edu.pl/~lgraczyk/wiki/index.php/KADD_2022_Laboratorium_6_EN) (04.04.2022) <br>

## TF1 <a name="TF1"></a>
> **Create function using TF1** <br>
>> `TF1 *fun1= new TF1("fun1", "TMath::Sin(x)", 0, 2*TMath::Pi());` <br>

> **Set Parameters**
>> `TF1 *fun1 = new TF1("fun1", "1./[0] * TMath::Exp(-x/[0])", 0, 50);`<br>
>>	`fun1->SetParameter(0, 6);`<br>

> **Style TF1**
>> `fun1->SetLineColor(kBlue);` <br>

> **Draw options**
>> `fun2 -> Draw("same");` <br>

## TGraph <a name="TGraph"></a>
>**Create TGraph** <br>
  >> `TGraph* gr = new TGraph();` <br>

>**Fill TGraph**
>> `gr-> SetPoint(i, throws[i], pips[i]);`

>**Style TGraph**
>> `gr -> SetMarkerSize(2);` <br>
>>	`gr -> SetMarkerStyle(22);` <br>

> **Draw options**
>> `gr -> Draw("AP");` Points without lines between <br>

## TCanvas <a name="TCanvas"></a>
> **Create window** <br>
>> `TCanvas *c1 = new TCanvas("c1", "window 1", 10, 10, 800, 800);` <br>

> **Dividing window 2x2** <br>
>>`c1 -> Divide(2,2);` <br>
  
 > **Drawing in window** <br>
  >> `c1-> cd(1);` <br>

## Probability distribution (more in `lab1.c`)
First you need to normalize given function, for example:<br>
`TF1 *fun1 = new TF1("fun1", "1./[0] * TMath::Exp(-x/[0])", 0, 50);` <br>
by dividing it by: `Double_t a = fun1 -> Integral(0,50);`. <br>
then `fun1->SetParameter(0, a);` <br>
and draw it: `fun1->Draw();` <br>

## Cumulative distribution (more in `lab1.c`)
After all steps from _Probability distribution_: <br>
by dividing it by: `Double_t a = fun1 -> Integral(0,50);`. <br>
then `fun1->SetParameter(0, a);` <br>
and draw it: `fun1->DrawIntegral();` <br>

## Probability  P(5 <= X <= 10) (more in `lab1.c`)
After all steps from _Probability distribution_, do:  `Double_t b = fun1 -> Integral(5,10);` <br>

## Expected value (more in `lab1.c`)
After all steps from _Probability distribution_, do: `Double_t mean = fun1 -> Mean(0,50);` <br>

## Variance (more in `lab1.c`)
After all steps from _Probability distribution_, do: `Double_t variance = fun1 -> Variance(0,50);` <br>

## Mode (more in `lab1.c`)
After all steps from _Probability distribution_, do: `Double_t mode = fun1 -> GetMaximumX(0,50);` <br>

## Quantiles (more in `lab1.c`)
After all steps from _Probability distribution_, do:  <br>
`const Int_t nq = 3;` <br>
	`Double_t xq[nq] = {0.25,0.5,0.75};` <br>
	`Double_t yq[nq];` <br>
	`fun1->GetQuantiles(nq,yq,xq);` <br>

## Useful snipets from documentation!
TF1 - [here](https://root.cern.ch/doc/master/classTF1.html)<br>
TCanvas - [here](https://root.cern.ch/doc/master/classTCanvas.html)<br>
TMath - [here](https://root.cern.ch/root/html524/TMath.html)<br>
TAttMarker - [here](https://root.cern.ch/doc/master/classTAttMarker.html)<br>
TGraph - [here](https://root.cern.ch/doc/master/classTGraph.html)<br>
