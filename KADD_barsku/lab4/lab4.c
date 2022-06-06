void lab4(){
	
	unsigned long int m,g,c;	
	g = 1664525;
	m=4294967296;
	c=1013904223;

	
	unsigned long int x[100000];
	double y[100000];
	x[0] = time(NULL)%(m-1);

	for(int i = 0; i < 99999; i++){
		x[i+1]  = (g*x[i]+c)%m;
	

	}


	for(int i = 0; i < 100000; i++){
		y[i] =(double)x[i]/(double)m;

	}
	
	ofstream myfile;
  	myfile.open ("losowe4.dat");
	for(int i = 0; i < 100000; i++){
		myfile << y[i]<<endl;

	}
	
  	
  	myfile.close();
	
	




}
