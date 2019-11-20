#include <ilcplex/cplex.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include  <math.h>
#include <time.h>
using namespace std;
#include"variables.h"
#include"delete_var.h"

int m , Integer , Continous , Binary;



float second() { 
	return((float )clock()/(float)CLK_TCK);
}
//void DistanceFunction () {	
//	short int i, j;
//	Distance = new float  *[(N+K) + 1];
//	for (i = 0; i<= (N+K) ; i++)
//		Distance[i] = new float [N + 1];
//
//	for(i=1; i<=(N+K);i++) {
//		for(j=0; j<=N;j++){
//          Distance[i][j]=0;
//		}
//	}
//	
//	for (i = 1; i <= (N+K); i++){
//		for (j = 0; j <=N; j++){
//			
//			Distance[i][j] = sqrt( (Xcoordinate[i] - Xcoordinate[j])*(Xcoordinate[i] - Xcoordinate[j]) + (Ycoordinate[i] - Ycoordinate[j])*(Ycoordinate[i] - Ycoordinate[j]) );
//			
//		}
//	}
//	for(i=1; i<=(N+K);i++) {
//		for(j=0; j<=N;j++){
//          cout<<Distance[i][j]<<"\t";
//		}
//		cout<<endl;
//	}
//}
void ReadData () {
	int i, j, k, t,n;
	
	Input = fopen(FileName, "r");
	if(!Input)
	{
		cout<<"cannt open data!!"<<endl;
		exit(1);
	}
	fscanf(Input,"%d",&N);    //Number of retailer'N'
	fscanf(Input,"%d",&K);    //types of vehicle 'K'
	fscanf(Input,"%lf",&h1);    // holding cost per unit at supplier'HS'
	fscanf(Input,"%lf",&a);    // shortage cost per unit'π'
	fscanf(Input,"%lf",&h);    //holding cost per unit at retailers'HR'
	fscanf(Input,"%d",&T);    //Number of periods
	fscanf(Input,"%lf",&speed); //speed'S'
	fscanf(Input,"%d",&S);    //Number of secnario'Ξ'
	fscanf(Input,"%d",&Q);    //Available quantity at supplier'Q'
	fscanf(Input,"%d",&R);    //Maximal inventory capacity at retailers 'Υ'
	fscanf(Input,"%lf",&fc);   //fuel cost'φF'
	fscanf(Input,"%lf",&Conversion);   //Conversion 'ψ'
	fscanf(Input,"%lf",&Cf);   // capacity of refrigerator at retailers'CR'
	fscanf(Input,"%lf",&CF1);   // capacity of refrigerator at supplier'CS'
	fscanf(Input,"%lf",&fe);   //electricity cost 'φE'
	fscanf(Input,"%lf",&Er);   //energy consumption refrigerantion at retailers'ER'
	fscanf(Input,"%lf",&Er1);   //energy consumption refrigerantion at supplier'ES'
	fscanf(Input,"%lf",&L);   //The amount of carbon emissions for 1kWh 'δ'
	fscanf(Input,"%lf",&Z);   //technical parameter'Γ', Γ = τ /ϕψ
	fscanf(Input,"%lf",&Pc);   //unit emissions price 'µ'
	fscanf(Input,"%lf",&alfa);   // alfa 'α'

	A = new double [K + 1]; //γκ, γκ = 1/(1000ζκω)
	for (i = 1; i<= K ; i++) {
	fscanf(Input,"%lf",&A[i]);
	}

	for(i=1; i<=(K);i++) {
		
          cout<<A[i]<<"\t";
		}
		cout<<endl;


		B = new double [K + 1];//βκ, βκ = 0.5CdκρAκ
	for (i = 1; i<= K ; i++) {
	fscanf(Input,"%lf",&B[i]);   
	}
	Mk = new int [K + 1];// Total number of vehicles available for type κ at the supplier
	for (i = 1; i<= K ; i++) {
	fscanf(Input,"%d",&Mk[i]);    
	}

	C = new int [K + 1];

	for (i = 1; i<= K ; i++) {
	fscanf(Input,"%d",&C[i]);    //Total capacity of vehicle type k
	}

	f = new double [K + 1];
	for (i = 1; i<= K ; i++) {
	fscanf(Input,"%lf",&f[i]);    //fixed cost of vehicle type k
	}

	H = new double [K + 1];
	for (i = 1; i<= K ; i++) {
	fscanf(Input,"%lf",&H[i]);    //Engine fraction vehicle type k
	}

	Nk = new double [K + 1];
	for (i = 1; i<= K ; i++) {
	fscanf(Input,"%lf",&Nk[i]);    //engine speed of vehicle type k
	}

	V = new double [K + 1];
	for (i = 1; i<= K ; i++) {
	fscanf(Input,"%lf",&V[i]);    //engine displacement of vehicle type k
	}

	W = new double [K + 1];
	for (i = 1; i<= K ; i++) {
	fscanf(Input,"%lf",&W[i]);    //Curb weight of vehicle type k
	}



	rate = new double [K + 1];
	for (i = 1; i<= K ; i++) {
	fscanf(Input,"%lf",&rate[i]);    //fixed rate =1.2 for add to fuel consumption beacuse of having refrigeration
	}

	for(i=1; i<=(K);i++) {
		
          cout<<rate[i]<<"\t";
		}
		cout<<endl;
	

	D = new int *[N + 1];
	for (i = 1; i<= N ; i++) {
		D[i]=new int [S + 1];
	}
	for (i=1; i<=S; i++){
	for (j = 1; j<= N ; j++) {
	fscanf(Input,"%d",&D[j][i]);    //Demand retailer
	kole_demand=kole_demand+D[j][i];
	}
	}
	mean_demand=kole_demand/S;
	P = new double [S + 1];
	for (i = 1; i<= S ; i++) {
	fscanf(Input,"%lf",&P[i]);    //Probability of scenario s
	}

	Distance = new double  *[(N+K) + 1];
	for (i = 0; i<= (N+K) ; i++)
		Distance[i] = new double [N + 1];

	for(i=1; i<=(N+K);i++) {// distance retailer
		for(j=0; j<=N;j++){
          Distance[i][j]=0;
		}
	}
	for (i=1; i<=(N+K); i++){
	for (j = 0; j<= N ; j++) {
	fscanf(Input,"%lf",&Distance[i][j]);    
	}
	}
	for(i=1; i<=(N+K);i++) {
		for(j=0; j<=N;j++){
          cout<<Distance[i][j]<<"\t";
		}
		cout<<endl;
	}

	
	
	
	
	//////////////// Memory allocation /////////////////////////////////	
	I=new long  **[N + 1];
	for(i = 0; i <= N; i++) {
		I[i] = new long *[T + 1];
		for(j = 0; j <=T; j++) {
			I[i][j] = new long [S + 1];
		}
	}
	U=new long  **[N + 1];
	for(i = 0; i <= N; i++) {
		U[i] = new long *[T + 1];
		for(j = 0; j <=T; j++) {
			U[i][j] = new long [S + 1];
		}
	}

	I2=new long  [S + 1];
	
	if (I2 == NULL) {
		printf ("could not allocate memory for I2.\n");
		exit (-1);
	}

	U2=new long  [S + 1];
	
	if (U2 == NULL) {
		printf ("could not allocate memory for I2.\n");
		exit (-1);
	}

	G=new long  **[N + 1];
	for(i = 0; i <= N; i++) {
		G[i] = new long *[T + 1];
		for(j = 0; j <=T; j++) {
			G[i][j] = new long [S + 1];
		}
	}
	
	flow_d1=new long  **[(N) + 1];// cost flow
	for(i = 0; i <= (N); i++) {
		flow_d1[i] = new long *[K + 1];
		for (k=1; k<=K; k++) {
			flow_d1[i][k]=new long [Mk[k]+1];
			
		}
	}


	flow_d2=new long  ***[(N) + 1];
	for(i = 0; i <= (N); i++) {
		flow_d2[i] = new long **[K + 1];
		for(k = 1; k <=K; k++) {
			flow_d2[i][k] = new long *[Mk[k] + 1];
			for (j=1; j<=Mk[k]; j++) {
				flow_d2[i][k][j]=new long [S+1];
			
			}
		}
	}


	O1=new long  **[(N) + 1];
	for(i = 0; i <= (N); i++) {
		O1[i] = new long *[K + 1];
		for (k=1; k<=K; k++) {
			O1[i][k]=new long [Mk[k]+1];
			
		}
	}

	O2=new long  ***[(N) + 1];
	for(i = 0; i <= (N); i++) {
		O2[i] = new long **[K + 1];
		for(k = 1; k <=K; k++) {
			O2[i][k] = new long *[Mk[k] + 1];
			for (j=1; j<=Mk[k]; j++) {
				
				O2[i][k][j]=new long [S+1];
			
			}
		}
	}

	q1=new long [N+1];
	
	q=new long  *[N + 1];
	for(i = 0; i <= N; i++) {
			q[i] = new long [S + 1];
		
	}

	qv1=new long  **[N + 1];
	for(i = 0; i <= N; i++) {
		qv1[i] = new long *[K + 1];
		for(k = 1; k <= K; k++) {
			qv1[i][k]=new long [Mk[k] + 1];
		}
	}

	qv=new long  ***[N + 1];
	for(i = 0; i <= N; i++) {
		qv[i] = new long **[K + 1];
		for(k = 1; k <=K; k++) {
			qv[i][k] = new long *[Mk[k] + 1];
			for (j=1; j<=Mk[k]; j++) { 
				
					qv[i][k][j]=new long [S+1];

			}
		}
	}

	x1=new long  ***[(N+K) + 1];
	for(i = 1; i <= (N+K); i++) {
		x1[i] = new long **[N + 1];
		for(j = 0; j <=N; j++) {
			x1[i][j] = new long *[K + 1];
			for(k = 1; k <=K; k++) {
				x1[i][j][k]= new long [Mk[k]+1];
			}
		}
	}


	SV=new long  **[N + 1];
	for(i = 0; i <= N; i++) {
		SV[i] = new long *[T + 1];
		for (t=0; t<=T; t++) {
			SV[i][t]=new long [S+1];
		}
	}


	x2=new long  ****[(N+K) + 1];
	for(i = 1; i <= (N+K); i++) {
		x2[i] = new long ***[N + 1];
		for(j = 0; j <=N; j++) {
			x2[i][j]=new long **[K + 1];
			for(k = 1; k <=K; k++) {
				x2[i][j][k]=new long *[Mk[k] + 1];
				for(n = 1; n <=Mk[k] ; n++){
					
						x2[i][j][k][n]=new long [S + 1];
					

				}
			}
		}
	}

	
	fclose (Input);
	/*DistanceFunction ();*/
}

void ModelPopulate(int x1, int x2 ) 
{
	
	// Allocate temporary CPLEX data structures
	rhs	= new double [2];
	if (rhs == NULL) {
		printf ("could not allocate memory for obj.\n");
		exit (-1);
	}
	
	rmatval	= new double [(N+1)*(N+1)*(T+1) + 1];
	if (rmatval == NULL) {
		printf ("could not allocate memory for obj.\n");
		exit (-1);
	}
	
	rmatind	  = new int [(N+1)*(N+1)*(T+1) + 1];
	if (rmatind == NULL) {
		printf ("could not allocate memory for obj.\n");
		exit (-1);
	}
	
	rmatbeg	  = new int [2];
	if (rmatbeg == NULL) {
		printf ("could not allocate memory for obj.\n");
		exit (-1);
	}
	
    sense	  = new char [2];
	if (sense == NULL) {
		printf ("could not allocate memory for obj.\n");
		exit (-1);
	}
	
	obj	  = new double [(N+1)*(N+1)*(T+1) + 2*(T + 1) + 2*(N+1)*(T+1) + 50000];
	if (obj == NULL) {
		printf ("could not allocate memory for obj.\n");
		exit (-1);
	}
	
	lb	  = new double [(N+1)*(N+1)*(T+1) + 2*(T + 1) + 2*(N+1)*(T+1) + 50000];
	if (lb == NULL) {
		printf ("could not allocate memory for lb.\n");
		exit (-1);
	}
	
	ub	  = new double [(N+1)*(N+1)*(T+1) + 2*(T + 1) + 2*(N+1)*(T+1) + 50000];
	if (ub == NULL) {
		printf ("could not allocate memory for ub.\n");
		exit (-1);
	}
	
	coltype = new char   [(N+1)*(N+1)*(T+1) + 2*(T + 1) + 2*(N+1)*(T+1) + 50000];
	if (coltype == NULL) { 
		printf ("could not allocate memory for coltype.\n");
		exit (-1);
	}
	
	colname = new char  *[(N+1)*(N+1)*(T+1) + 2*(T + 1) + 2*(N+1)*(T+1) + 50000];
	for (i = 0; i< (N+1)*(N+1)*(T+1) + 2*(T + 1) + 2*(N+1)*(T+1) + 50000; i++)
		colname[i] = new char [100];
	if (colname == NULL) {
		printf ("could not allocate memory for colname.\n");
		exit (-1);
	}
	
	
	IPtr=new long  **[N + 1];
	for(i = 0; i <= N; i++) {
		IPtr[i] = new long *[T + 1];
		for(j = 0; j <=T; j++) {
			IPtr[i][j] = new long [S + 1];
		}
	}

	UPtr=new long  **[N + 1];
	for(i = 0; i <= N; i++) {
		UPtr[i] = new long *[T + 1];
		for(j = 0; j <=T; j++) {
			UPtr[i][j] = new long [S + 1];
		}
	}

	I2Ptr=new long  [S + 1];
	
	

	U2Ptr=new long  [S + 1];
	

	GPtr=new long  **[N + 1];
	for(i = 0; i <= N; i++) {
		GPtr[i] = new long *[T + 1];
		for(j = 0; j <=T; j++) {
			GPtr[i][j] = new long [S + 1];
		}
	}
	flow_d1Ptr=new long  **[(N) + 1];
	for(i = 0; i <= (N); i++) {
		flow_d1Ptr[i] = new long *[K + 1];
		for (k=1; k<=K; k++) {
			flow_d1Ptr[i][k]=new long [Mk[k]+1];
			
		}
	}

	flow_d2Ptr=new long  ***[(N) + 1];
	for(i = 0; i <= (N); i++) {
		flow_d2Ptr[i] = new long **[K + 1];
		for(k = 1; k <=K; k++) {
			flow_d2Ptr[i][k] = new long *[Mk[k] + 1];
			for (j=1; j<=Mk[k]; j++) {
				
				flow_d2Ptr[i][k][j]=new long [S+1];
			
			}
		}
	}



	O1Ptr=new long  **[(N) + 1];
	for(i = 0; i <= (N); i++) {
		O1Ptr[i] = new long *[K + 1];
		for (k=1; k<=K; k++) {
			O1Ptr[i][k]=new long [Mk[k]+1];
			
		}
	}

	O2Ptr=new long  ***[(N) + 1];
	for(i = 0; i <= (N); i++) {
		O2Ptr[i] = new long **[K + 1];
		for(k = 1; k <=K; k++) {
			O2Ptr[i][k] = new long *[Mk[k] + 1];
			for (j=1; j<=Mk[k]; j++) {
				
				O2Ptr[i][k][j]=new long [S+1];
			
			}
		}
	}

	


	q1Ptr= new long [N+1];


	qPtr=new long  *[N + 1];
	for(i = 0; i <= N; i++) {
		
			qPtr[i] = new long [S + 1];
		
	}



	qv1Ptr=new long  **[N + 1];
	for(i = 0; i <= N; i++) {
		qv1Ptr[i] = new long *[K + 1];
		for(k = 1; k <= K; k++) {
			qv1Ptr[i][k]=new long [Mk[k] + 1];
		}
	}

	qvPtr=new long ***[N + 1];
	for(i = 0; i <= N; i++) {
		qvPtr[i] = new long **[K + 1];
		for(k = 1; k <=K; k++) {
			qvPtr[i][k] = new long *[Mk[k] + 1];
			for (j=1; j<=Mk[k]; j++) { 
				
					qvPtr[i][k][j]=new long [S+1];
				
			}
		}
	}


	x1Ptr=new long  ***[(N+K) + 1];
	for(i = 1; i <= (N+K); i++) {
		x1Ptr[i] = new long **[N + 1];
		for(j = 0; j <=N; j++) {
			x1Ptr[i][j] = new long *[K + 1];
			for(k = 1; k <=K; k++) {
				x1Ptr[i][j][k]=new long [Mk[k]+1];
			}
		}
	}

	SVPtr=new long  **[N + 1];
	for(i = 0; i <= N; i++) {
		SVPtr[i] = new long *[T + 1];
		for (t=0; t<=T; t++) {
			SVPtr[i][t]=new long [S+1];
		}
	}

	x2Ptr=new long  ****[(N+K) + 1];
	for(i = 1; i <= (N+K); i++) {
		x2Ptr[i] = new long ***[N + 1];
		for(j = 0; j <=N; j++) {
			x2Ptr[i][j]=new long **[K + 1];
			for(k = 1; k <=K; k++) {
				x2Ptr[i][j][k]=new long *[Mk[k] + 1];
				for(n = 1; n <=Mk[k] ; n++){
					
						x2Ptr[i][j][k][n]=new long [S + 1];
					
				}
			}
		}
	}



	
	printf("Here 1\n");
	numcols = 0;
	numrows = 0;
	
	///////////////// Initialize ptr-vectors /////////////////
	for (i = 0; i <= N; i++) {
		for (t = 0; t <= T; t++) { 
			for (s = 0; s <= S; s++) {
				IPtr[i][t][s] = -1;
				UPtr[i][t][s] = -1;
				GPtr[i][t][s] = -1;
				
				
			}
		}
	}	

	for (i = 0; i <= N; i++) {
		
			for (s = 0; s <= S; s++) {
	qPtr[i][s] = -1;
			}
	}
	for (i = 1; i <= (N+K); i++) {
		for (j = 0; j <= N; j++) { 
			for (k = 1; k <= K; k++) {
				for (n=1; n<=Mk[k]; n++) {
					
						for (s=1; s<=S; s++) {
							x2Ptr[i][j][k][n][s]=-1;
						
						
					}
				}
				
			}
		}
	}	

	for (i = 1; i <= (N+K); i++) {
		for (j = 0; j <= N; j++) { 
			for (k = 1; k <= K; k++) {
				for (n = 1; n <= Mk[k]; n++) {
					x1Ptr[i][j][k][n] = -1;
				}
			}
		}
	}


	for (i = 0; i <= (N); i++) {
		
			for (k = 1; k <= K; k++) {
				for (j = 1; j <= Mk[k]; j++) { 
				
		O1Ptr[i][k][j]=-1;
		flow_d1Ptr[i][k][j]=-1;
				
				
			}
		}
	}	


	for (i = 0; i <= (N); i++) {
		
			for (k =1; k <= K; k++) {
				for (j = 1; j <= Mk[k]; j++) { 
				
					for (s=1; s<=S; s++) {
						
						O2Ptr[i][k][j][s] = -1;
						flow_d2Ptr[i][k][j][s] = -1;
					
				}
				
			}
		}
	}	
	

	
	printf("Here 11\n");
	
	for (i = 0; i <= N; i++) {
		q1Ptr[i] = -1;
	}
		
	


		for (s = 0; s <= S; s++) {
			I2Ptr[s]=-1;
			U2Ptr[s]=-1;
		
	}

	for (i = 0; i <= N; i++) {
	for (t = 0; t <= T; t++) {
		for (s = 0; s <= S; s++) {
		
			SVPtr[i][t][s]=-1;
		}
			
		}
	}
	for (i = 0; i <= N; i++) {
	for (k = 1; k <= K; k++) {
		for (j=1; j<=Mk[k]; j++){
		
			qv1Ptr[i][k][j]=-1;
			
				for (s=1; s<=S; s++) {
					qvPtr [i][k][j][s]=-1;
				
				}
			}

		}
			
	}
	



	printf("Here 12\n");
	Integer = 0;
	Continous = 0;
	Binary = 0;
	//////////////	 Define variables	 ///////////////////////////////////////////////(I,I1,I2)////////////////////////////
	counter = 0;
	m = counter;
	for (i = 1; i <= N; i++) {
		for (t = 1; t <= T; t++) {
			for (s=1; s<=S; s++) {
				sprintf(colname[counter],"I%3d_%3d_%3d", i, t,s);
			
				lb[counter]			= 0;
				ub[counter]			= R;
				obj[counter]		= P[s]*h;
				coltype[counter++]	= 'I';//c
				IPtr[i][t][s]   	= numcols++;
		}
	}
	}

	/*Continous += counter - m;
	m = counter;*/
	Integer += counter - m;
	m = counter;
	sprintf(colname[counter],"I1");
			
				lb[counter]			= 0;
				ub[counter]			= T*Q;
				obj[counter]		= h1;
				coltype[counter++]	= 'I';//C
				I1Ptr   	= numcols++;


	/*Continous += counter - m;
	m = counter;*/
	Integer += counter - m;
	m = counter;
		
			for (s=1; s<=S; s++) {
				sprintf(colname[counter],"I2%3d",s);
			
				lb[counter]			= 0;
				ub[counter]			= T*Q;
				obj[counter]		= P[s]*h1;
				coltype[counter++]	= 'I';//C
				I2Ptr[s]   	= numcols++;
		
	}

	/*Continous += counter - m;
	m = counter;*/

	Integer += counter - m;
	m = counter;
	 printf("Here 13\n");
	 /////////////////////////////////////////////////////(G[i][t][s]////////////////////////////////////////////
	 for (i = 1; i <= N; i++) {
		for (t = 1; t <= T; t++) {
			for (s=1; s<=S; s++) {
				sprintf(colname[counter],"G%3d_%3d_%3d", i, t,s);
			
				lb[counter]			= 0;
				ub[counter]			= D[i][s];
				obj[counter]		= P[s]*a;
				coltype[counter++]	= 'I';//C
				GPtr[i][t][s]   	= numcols++;
		}
	}
	}

	/*Continous += counter - m;
	m = counter;*/

	 Integer += counter - m;
	m = counter;


	 printf("Here 14\n");
/////////////////////////////////////////////////////////////////////(O1[i], O2[i][t][s]/////////////
	
	 Max=0;
	 for (i=1; i<=K; i++) { 
		 if (Max < C[i])
		 {
			 /*Max=0;*/
			 Max=C[i];
		 }
		 
	 }
	 max1=0;
for (i=1; i<=(N+K); i++){
	for (j=0; j<=N; j++){
		if (max1< Distance [i][j]){
			max1= Distance [i][j];
		}
	}
}
/////////////////////////////////////////////////////////////flow_d1, flow_d2///////////////////////////////////////


		  for (j=1; j<=N; j++) {
			  

			  for (k=1; k<=K; k++) {
				  for (i=1; i<=Mk[k]; i++) {
				  
		
				sprintf(colname[counter],"flow_d1%3d_%3d_%3d", j,k,i);
			
				lb[counter]			= 0;
				ub[counter]			= 1000000000;
				obj[counter]		= kilo*(rate[k]*Z*A[k]*alfa*Unit_w*(fc+Pc*Conversion));
				coltype[counter++]	= 'C';
				flow_d1Ptr[j][k][i]        	= numcols++;
			  }
		}
	  }
	
	
	Continous += counter - m;
	m = counter;


		   for (j=1; j<=N; j++) {
			  
			    for (k=1; k<=K; k++) {
					 for (n=1; n<=Mk[k]; n++) {
					
						for (s=1; s<=S; s++) {
							sprintf(colname[counter],"flow_d2%3d_%3d_%3d_%3d", j,k,n,s);
			
							lb[counter]			= 0;
							ub[counter]			= 1000000000;
							obj[counter]		= P[s]*kilo*(rate[k]*Z*A[k]*alfa*Unit_w*(fc+Pc*Conversion));
							coltype[counter++]	= 'C';
							flow_d2Ptr[j][k][n][s]   	= numcols++;
						}
		
	}
	}
	   }
	   

	Continous += counter - m;
	m = counter;


/////////////////////////////////////////////////////////////////////////////////////////////////
	 
		  for (j=0; j<=N; j++) {
			 

			  for (k=1; k<=K; k++) {
				  for (s=1; s<=Mk[k]; s++) {
				  
		
				sprintf(colname[counter],"O1%3d_%3d_%3d", j,k,s);
			
				lb[counter]			= 0;
				ub[counter]			= Max;
				obj[counter]		= 0;
				coltype[counter++]	= 'I';//C
				O1Ptr[j][k][s]        	= numcols++;
			  }
		}
	  }
	  

	/*Continous += counter - m;
	m = counter;*/
	Integer += counter - m;
	m = counter;




	 
		   for (j=0; j<=N; j++) {
			  
			    for (k=1; k<=K; k++) {
					 for (n=1; n<=Mk[k]; n++) {
					
						for (s=1; s<=S; s++) {
							sprintf(colname[counter],"O2%3d_%3d_%3d_%3d", j,k,n,s);
			
							lb[counter]			= 0;
							ub[counter]			= Max;
							obj[counter]		= 0;
							coltype[counter++]	= 'I';//C
							O2Ptr[j][k][n][s]   	= numcols++;
						
		}
	}
	}
	   }
	   

	/*Continous += counter - m;
	m = counter;*/

	Integer += counter - m;
	m = counter;

  for (i = 1; i <= N; i++) {
		
				sprintf(colname[counter],"q1%3d", i);
			
				lb[counter]			= 0;
				ub[counter]			= Max;
				obj[counter]		= 0;
				coltype[counter++]	= 'I';//C
				q1Ptr[i]        	= numcols++;
		}


	/*Continous += counter - m;
	m = counter;*/
  Integer += counter - m;
	m = counter;

  for (i = 1; i <= N; i++) {
		
			for (s=1; s<=S; s++) {
				sprintf(colname[counter],"q%3d_%3d", i,s);
			
				lb[counter]			= 0;
				ub[counter]			= Max;
				obj[counter]		= 0;
				coltype[counter++]	= 'I';//C
				qPtr[i][s]   	= numcols++;
		
	}
	}
	
	/*Continous += counter - m;
	m = counter;*/
  Integer += counter - m;
	m = counter;


	printf("Here 15\n");

	////////////////////////////////////////////////////////////x1[i][j][k], x2[i][j][k][t][s]//////////////////////////////////////////////
	for (i = 1; i <= (N+K); i++) {
		for (j = 0; j <= N; j++) {
			if (i==j || (i>N &&j==0) ) 
			{
				
				continue; 
			}
				
			for (k = 1; k <= K; k++) {
				if (i>N && (i-N) != k) 
					continue;
				for (n=1;n<=Mk[k]; n++){
				sprintf(colname[counter],"x1%3d_%3d_%3d_%3d", i, j, k,n);
				
				lb[counter]			= 0;
				ub[counter]			= 1;
				if(i==(N+k)&&j!=0){
					obj[counter]		= f[k]+(fc*rate[k]*Z+Pc*rate[k]*Z*Conversion)*(H[k]*Nk[k]*V[k]*Distance [i][j]*kilo*rate_speed/speed+W[k]*A[k]*alfa*Distance [i][j]*kilo+B[k]*A[k]*Distance [i][j]*kilo*(speed/rate_speed)*(speed/rate_speed));
				}
				else{
					
					

				obj[counter]		= (fc*rate[k]*Z+Pc*Z*rate[k]*Conversion)*(H[k]*Nk[k]*V[k]*Distance [i][j]*kilo*rate_speed/speed+W[k]*A[k]*alfa*Distance [i][j]*kilo+B[k]*A[k]*Distance [i][j]*kilo*(speed/rate_speed)*(speed/rate_speed));
				}//end else
				
				coltype[counter++]	= 'B';
				x1Ptr[i][j][k][n]   	= numcols++;
				}
			}
		}
	}

	Binary += counter - m;
	m = counter;

	for (i = 1; i <= (N+K); i++) {
		for (j = 0; j <= N; j++) {
			if (i==j || (i>N &&j==0) ) 
			{
				
				continue; 
			}
			for (k = 1; k <= K; k++) {
				if (i>N && (i-N) != k) 
					continue;
				for (n=1;n<=Mk[k]; n++){
				
					for (s=1; s<=S; s++) {
						sprintf(colname[counter],"x2%3d_%3d_%3d_%3d", i, j, k,n,s);
				
						lb[counter]			= 0;
						ub[counter]			= 1;
						if(i==(N+k)&&j!=0){
							obj[counter]		= P[s]*(f[k]+(fc*rate[k]*Z+Pc*rate[k]*Z*Conversion)*(H[k]*Nk[k]*V[k]*Distance [i][j]*kilo*rate_speed/speed+W[k]*A[k]*alfa*Distance [i][j]*kilo+B[k]*A[k]*Distance [i][j]*kilo*(speed/rate_speed)*(speed/rate_speed)));
						}
						else {
							

						obj[counter]		= P[s]*(fc*rate[k]*Z+Pc*rate[k]*Z*Conversion)*(H[k]*Nk[k]*V[k]*Distance [i][j]*kilo*rate_speed/speed+W[k]*A[k]*alfa*Distance [i][j]*kilo+B[k]*A[k]*Distance [i][j]*kilo*(speed/rate_speed)*(speed/rate_speed));
						}
						
						coltype[counter++]	= 'B';
						x2Ptr[i][j][k][n][s]  	= numcols++;
					
				}
			}
			}
		}
	}

	Binary += counter - m;
	m = counter;

	printf("Here 16\n");

	/////////////////////////////////////////////////////////////////////////////y3[i][k][j],y2[i][k][j][t][s]//////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////SV//////////////////////////////////////////////////
	for (i = 1; i <= N; i++) {
		for (t=1; t<=T;t++) {
			for (s = 1; s <= S; s++) {
		
						sprintf(colname[counter],"SV%3d_%3d_%3d", i, t,s );
				
						lb[counter]			= 0;
						ub[counter]			= 1;
						obj[counter]		= 0;
						coltype[counter++]	= 'B';
						SVPtr[i][t][s]   	= numcols++;
			
				}
			}
	}

	Binary += counter - m;
	m = counter;

	/////////////////////////////////////////////////////////////U1, U2[t][s], U[i][t][s]//////////////////////////////////////////////////////
					sprintf(colname[counter],"U1");
				
						lb[counter]			= 0;
						ub[counter]			= (T*Q)/CF1;
						obj[counter]		= (fe*Er1)+(Pc*Er1*L);
						coltype[counter++]	= 'I';
						U1Ptr			   	= numcols++;

	Integer += counter - m;
	m = counter;
		
				for (s = 1; s <= S; s++) {
		
						sprintf(colname[counter],"U2%3d_%3d", s );
				
						lb[counter]			= 0;
						ub[counter]			= (T*Q)/CF1;
						obj[counter]		= P[s]*((fe*Er1)+(Pc*Er1*L));
						coltype[counter++]	= 'I';
						U2Ptr[s]   	= numcols++;
			
				
			}


	Integer += counter - m;
	m = counter;


			for (i=1; i<=N; i++) {
			for (t = 1; t <= T; t++) {
				for (s = 1; s <= S; s++) {
		
						sprintf(colname[counter],"U%3d_%3d_%3d", i,  t,s );
				
						lb[counter]			= 0;
						ub[counter]			= (T*Q)/Cf;
						obj[counter]		= P[s]*((fe*Er)+(Pc*Er*L));
						coltype[counter++]	= 'I';
						UPtr[i][t][s]   	= numcols++;
				}
			
				}
			}

	Integer += counter - m;
	m = counter;

			printf("Here 18\n");
///////////////////////////////////////////////////////////////////qv1, qv/////////////////////////////////////////////////////////////
			for (i=1; i<=N; i++) {
			for (k = 1; k <= K; k++) {
				for (j = 1; j <= Mk[k]; j++) {
				
		
						sprintf(colname[counter],"qv1%3d_%3d_%3d", i,  k,j);
				
						lb[counter]			= 0;
						ub[counter]			= Max;
						obj[counter]		= 0;
						coltype[counter++]	= 'I';//C
						qv1Ptr[i][k][j]   	= numcols++;
						
				}
				
			}
				}
			
	/*Continous += counter - m;
	m = counter;*/
	Integer += counter - m;
	m = counter;


			for (i=1; i<=N; i++) {
			for (k = 1; k <= K; k++) {
				for (j = 1; j <= Mk[k]; j++) {
				
				for (s = 1; s <= S; s++) {
		
						sprintf(colname[counter],"qv%3d_%3d_%3d_%3d", i,  k,j,s );
				
						lb[counter]			= 0;
						ub[counter]			= Max;
						obj[counter]		= 0;
						coltype[counter++]	= 'I';//C
						qvPtr[i][k][j][s]   	= numcols++;
				
				}
				}
				}
			}

	/*Continous += counter - m;
	m = counter;*/
	Integer += counter - m;
	m = counter;

	//////////////////////////////////////////////////////////////////////////////////

	printf("Here 2\n");
	status = CPXnewcols(env,lp,counter,obj,lb,ub,coltype,colname);
	if (status)	{
		CPXgeterrorstring (env, status, errmsg);
		printf("%s", errmsg);
		exit(-1);
	}
	
	printf("Here 3\n");
/////////////////////////////////////////////constraints////////////////////////////////////////////////////
////////////////////////////////////////////////////(2)//////////////////////////////////////////////////////////////////////
	constraints = 0;

	constraints = constraints + 1;
		nzcnt		= 0;
		rhs[0]		= Q;                                 
		sense[0]	= 'E';
		rmatbeg[0]	= 0;
		for (i = 1; i <= N ; i++) {
			if (q1Ptr [i] >= 0){
				rmatind[nzcnt] =q1Ptr [i];
				rmatval[nzcnt++] = 1;
			}
		}

		if (I1Ptr >= 0){
				rmatind[nzcnt] =I1Ptr;
				rmatval[nzcnt++] = 1;
		}

		rmatbeg[1] = nzcnt;
		if (nzcnt > 0) {
			status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
			if (status)	{
				CPXgeterrorstring (env, status, errmsg);
				printf("%s", errmsg);
				exit(-1);
			}
		}
//////////////////////////////////////////////////////////////////(3*)///////////////////////////////////////////////
		
	
		for (s=1; s<= S; s++){
			constraints = constraints + 1;
			nzcnt		= 0;
			rhs[0]		= Q;                                 
			sense[0]	= 'E';
			rmatbeg[0]	= 0;

			if (I2Ptr[s] >= 0){
				rmatind[nzcnt] =I2Ptr [s];
				rmatval[nzcnt++] = 1;
		}
			if (I1Ptr >= 0){
				rmatind[nzcnt] =I1Ptr;
				rmatval[nzcnt++] = -1;
		}

			for (i=1; i<=N; i++){
				if (qPtr [i][s] >= 0){
					rmatind[nzcnt] =qPtr [i][s];
					rmatval[nzcnt++] = 1;
				}
			}
	
	
		rmatbeg[1] = nzcnt;
		if (nzcnt > 0) {
			status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
			if (status)	{
				CPXgeterrorstring (env, status, errmsg);
				printf("%s", errmsg);
				exit(-1);
			}
		}
		

}
///////////////////////////////////////////////////////////////////////(4)//////////////////////////////
for(i=1; i<=N; i++) {
	//for (t=1; t<= 1; t++){	
		for (s=1; s<= S; s++){
			constraints = constraints + 1;
			nzcnt		= 0;
			rhs[0]		= -D[i][s];                                 
			sense[0]	= 'E';
			rmatbeg[0]	= 0;

			if (IPtr[i][1][s] >= 0){
				rmatind[nzcnt] =IPtr [i][1][s];
				rmatval[nzcnt++] = 1;
		}


			if (q1Ptr [i] >= 0){
				rmatind[nzcnt] =q1Ptr [i];
				rmatval[nzcnt++] = -1;
			}
	
			if (GPtr [i][1][s] >= 0){
				rmatind[nzcnt] = GPtr [i][1][s] ;
				rmatval[nzcnt++] = -1;
				}
	
		rmatbeg[1] = nzcnt;
		if (nzcnt > 0) {
			status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
			if (status)	{
				CPXgeterrorstring (env, status, errmsg);
				printf("%s", errmsg);
				exit(-1);
			}
		}
		}
	
}
/////////////////////////////////////////////////////////////////(5)/////////////////////////////////////////////
for(i=1; i<=N; i++) {
	for (t=2; t<= T; t++){	
		for (s=1; s<= S; s++){
			constraints = constraints + 1;
			nzcnt		= 0;
			rhs[0]		= -D[i][s];                                 
			sense[0]	= 'E';
			rmatbeg[0]	= 0;

			if (IPtr[i][t][s] >= 0){
				rmatind[nzcnt] =IPtr [i][t][s];
				rmatval[nzcnt++] = 1;
		}

			if (IPtr[i][(t-1)][s] >= 0){
				rmatind[nzcnt] =IPtr[i][(t-1)][s];
				rmatval[nzcnt++] = -1;
		}

			if (qPtr [i][s] >= 0){
				rmatind[nzcnt] =qPtr [i][s];
				rmatval[nzcnt++] = -1;
			}
	
			if (GPtr [i][t][s] >= 0){
				rmatind[nzcnt] = GPtr [i][t][s] ;
				rmatval[nzcnt++] = -1;
				}
	
		rmatbeg[1] = nzcnt;
		if (nzcnt > 0) {
			status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
			if (status)	{
				CPXgeterrorstring (env, status, errmsg);
				printf("%s", errmsg);
				exit(-1);
			}
		}
		}
	}
	
}

//////////////////////////////////////////////////////////////////(6)/////////////////////////////////////
for(i=1; i<=N; i++) {
	for (t=1; t<=T; t++){	//t
		for (s=1; s<= S; s++){
			constraints = constraints + 1;
			nzcnt		= 0;
			rhs[0]		= R;                                 
			sense[0]	= 'L';
			rmatbeg[0]	= 0;

			if (IPtr[i][t][s] >= 0){
				rmatind[nzcnt] =IPtr [i][t][s];
				rmatval[nzcnt++] = 1;
		}

		rmatbeg[1] = nzcnt;
		if (nzcnt > 0) {
			status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
			if (status)	{
				CPXgeterrorstring (env, status, errmsg);
				printf("%s", errmsg);
				exit(-1);
			}
		}
		}
	}
}

///////////////////////////////////////////////////////////////(7)/////////////////////////////////////////
		for(i=1; i<=N; i++) {
			constraints = constraints + 1;
			nzcnt		= 0;
			rhs[0]		= 0;                                 
			sense[0]	= 'L';
			rmatbeg[0]	= 0;

			if (q1Ptr[i] >= 0){
				rmatind[nzcnt] =q1Ptr [i];
				rmatval[nzcnt++] = 1;
		}

		
		for (j = 1; j <= (N+K) ; j++) {
			
			for (k=1; k<=K; k++) {
				for (n=1; n<=Mk[k]; n++) {
				if (x1Ptr [j][i][k][n] >= 0){
				rmatind[nzcnt] =x1Ptr [j][i][k][n];
				rmatval[nzcnt++] = -R;
				}
			}
		}
		}
		
		rmatbeg[1] = nzcnt;
		if (nzcnt > 0) {
			status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
			if (status)	{
				CPXgeterrorstring (env, status, errmsg);
				printf("%s", errmsg);
				exit(-1);
			}
		}
	}
///////////////////////////////////////////////////////(8)///////////////////////////
		for(i=1; i<=N; i++) {
			
				for(s=1; s<=S; s++) {
					constraints = constraints + 1;
					nzcnt		= 0;
					rhs[0]		= 0;                                 
					sense[0]	= 'L';
					rmatbeg[0]	= 0;

					if (qPtr[i][s] >= 0){
						rmatind[nzcnt] =qPtr[i][s];
						rmatval[nzcnt++] = 1;
				}

		
				for (j = 1; j <= (N+K) ; j++) {
			
					for (k=1; k<=K; k++) {
						for (n=1; n<=Mk[k]; n++) {
						if (x2Ptr [j][i][k][n][s] >= 0){
						rmatind[nzcnt] =x2Ptr [j][i][k][n][s];
						rmatval[nzcnt++] = -R-D[i][s];
						}
					}
				}
				}
		
				rmatbeg[1] = nzcnt;
				if (nzcnt > 0) {
					status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
					if (status)	{
						CPXgeterrorstring (env, status, errmsg);
						printf("%s", errmsg);
						exit(-1);
					}
				
			}
		}
	}
////////////////////////////////////////////////////////////////////////////(9)
		for(i=1; i<=N; i++) {
			for(t=2; t<=T; t++) {
				for(s=1; s<=S; s++) {
					constraints = constraints + 1;
					nzcnt		= 0;
					rhs[0]		= D[i][s]+R;                                 
					sense[0]	= 'L';
					rmatbeg[0]	= 0;

					if (qPtr[i][s] >= 0){
						rmatind[nzcnt] =qPtr[i][s];
						rmatval[nzcnt++] = 1;
				}

					if (IPtr[i][(t-1)][s] >= 0){
						rmatind[nzcnt] =IPtr[i][(t-1)][s];
						rmatval[nzcnt++] = 1;
				}
				
		
				rmatbeg[1] = nzcnt;
				if (nzcnt > 0) {
					status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
					if (status)	{
						CPXgeterrorstring (env, status, errmsg);
						printf("%s", errmsg);
						exit(-1);
					}
				}
			}
		}
	}


/////////////////////////////////////////////////////(10)////////////////////////////////////

	
	for (k=1; k<= K; k++){
		for (n=1; n<=Mk[k]; n++) {
			constraints = constraints + 1;
			nzcnt		= 0;
			rhs[0]		= 1;                                 
			sense[0]	= 'L';
			rmatbeg[0]	= 0;


			for (j=1; j<=N; j++) {
				
				if (x1Ptr[(N+k)][j][k][n] >= 0){
				rmatind[nzcnt] =x1Ptr[(N+k)][j][k][n];
				rmatval[nzcnt++] = 1;
			
				}
			}

			rmatbeg[1] = nzcnt;
			if (nzcnt > 0) {
				status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
				if (status)	{
					CPXgeterrorstring (env, status, errmsg);
					printf("%s", errmsg);
					exit(-1);
				}
		
			}
		}

	}

/////////////////////////////////////////////////////(11)///////////////////////////////////////
	for (k=1; k<= K; k++){
		for (n=1; n<=Mk[k]; n++) {
			
				for (s=1; s<=S; s++) {
			constraints = constraints + 1;
			nzcnt		= 0;
			rhs[0]		= 1;                                 
			sense[0]	= 'L';
			rmatbeg[0]	= 0;


			for (j=1; j<=N; j++) {
				
				if (x2Ptr[(N+k)][j][k][n][s] >= 0){
				rmatind[nzcnt] =x2Ptr[(N+k)][j][k][n][s] ;
				rmatval[nzcnt++] = 1;
			
				}
			}

			rmatbeg[1] = nzcnt;
			if (nzcnt > 0) {
				status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
				if (status)	{
					CPXgeterrorstring (env, status, errmsg);
					printf("%s", errmsg);
					exit(-1);
				}
		
			}
		}
			
		}

	}

/////////////////////////////////////////////////////(12)///////////////////////////////////////
		
			for (j=1; j<=N; j++) {
				
			for (k=1; k<=K; k++) {
				for (n=1; n<=Mk[k]; n++) {
				
					constraints = constraints + 1;
					nzcnt		= 0;
					rhs[0]		= 0;                                 
					sense[0]	= 'L';
					rmatbeg[0]	= 0;

					if (O1Ptr[j][k][n] >= 0){
						rmatind[nzcnt] =O1Ptr[j][k][n];
						rmatval[nzcnt++] = 1;
					}

					for (i=1; i<=(N+K); i++) {
						if (x1Ptr[i][j][k][n] >= 0){
						rmatind[nzcnt] =x1Ptr[i][j][k][n];
						rmatval[nzcnt++] = -C[k];
					
				}
					}

				rmatbeg[1] = nzcnt;
				if (nzcnt > 0) {
					status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
					if (status)	{
						CPXgeterrorstring (env, status, errmsg);
						printf("%s", errmsg);
						exit(-1);
					}
				}
				}
			}
		}
		
///////////////////////////////////////////////////////////////(13)///////////////////////////////////////////////////
			for (j=1; j<=N; j++) {
				
			for (k=1; k<=K; k++) {
				for (n=1; n<=Mk[k]; n++) {
					
						for (s=1; s<=S; s++) {
				
							constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 0;                                 
							sense[0]	= 'L';
							rmatbeg[0]	= 0;

							if (O2Ptr[j][k][n][s] >= 0){
								rmatind[nzcnt] =O2Ptr[j][k][n][s] ;
								rmatval[nzcnt++] = 1;
							}

							for (i=1; i<=(N+K); i++) {
								if (x2Ptr[i][j][k][n][s] >= 0){
								rmatind[nzcnt] =x2Ptr[i][j][k][n][s];
								rmatval[nzcnt++] = -C[k];
					
						}
							}

						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
								}
							}
						}
					}
				}
			
		}
//	///////////////////////////////////////////////////////////////(14)///////////////////////////////////////

		for (i=1; i<= (N); i++){
				
					
					constraints = constraints + 1;
					nzcnt		= 0;
					rhs[0]		= 1;                                 
					sense[0]	= 'L';
					rmatbeg[0]	= 0;

				for (j=1; j<=(N+K); j++) {
					for (k=1; k<=K; k++) {
						for (n=1; n<=Mk[k]; n++) {
							if (x1Ptr[j][i][k][n]>= 0){
							rmatind[nzcnt] =x1Ptr[j][i][k][n];
							rmatval[nzcnt++] = 1;
							}
						}
					}
				}
				rmatbeg[1] = nzcnt;
				if (nzcnt > 0) {
					status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
					if (status)	{
						CPXgeterrorstring (env, status, errmsg);
						printf("%s", errmsg);
						exit(-1);
					}
				}
					
			}
///////////////////////////////////////////////////////(15)///////////////////////////////////////////
		for (i=1; i<= (N); i++){
			
				for (s=1; s<= S; s++){
				
					constraints = constraints + 1;
					nzcnt		= 0;
					rhs[0]		= 1;                                 
					sense[0]	= 'L';
					rmatbeg[0]	= 0;

				for (j=1; j<=(N+K); j++) {
					for (k=1; k<=K; k++) {
						for (n=1; n<=Mk[k]; n++) {
							if (x2Ptr[j][i][k][n][s]>= 0){
							rmatind[nzcnt] =x2Ptr[j][i][k][n][s];
							rmatval[nzcnt++] = 1;
							}
						}
					}
				}
				rmatbeg[1] = nzcnt;
				if (nzcnt > 0) {
					status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
					if (status)	{
						CPXgeterrorstring (env, status, errmsg);
						printf("%s", errmsg);
						exit(-1);
						}
					}
				}
			}
					
		

//////////////////////////////////////////////////////(16)//////////////////////////////////////////////////
		for (j=1; j<= N; j++){
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++) {
						constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 0;                                 
							sense[0]	= 'E';
							rmatbeg[0]	= 0;


					for (i = 1; i <= (N+K) ; i++) {
						if(i==j)  continue;
						if (x1Ptr [i][j][k][n] >= 0){
							rmatind[nzcnt] =x1Ptr [i][j][k][n];
							rmatval[nzcnt++] = 1;
					}}



					for (i = 0; i <= N ; i++) {
						if(i==j)  continue;
						if (x1Ptr [j][i][k][n] >= 0){
							rmatind[nzcnt] =x1Ptr [j][i][k][n];
							rmatval[nzcnt++] = -1;
					}}

						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
					}
				}
		}
//	///////////////////////////////////////////////////////////////////////////////(17)////////////////////////////////////////
		for (j=1; j<= N; j++){
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++) {
						
							for (s=1; s<=S; s++) {
									constraints = constraints + 1;
									nzcnt		= 0;
									rhs[0]		= 0;                                 
									sense[0]	= 'E';
									rmatbeg[0]	= 0;


							for (i = 1; i <= (N+K) ; i++) {
								if(i==j)  continue;
								if (x2Ptr [i][j][k][n][s] >= 0){
									rmatind[nzcnt] =x2Ptr [i][j][k][n][s];
									rmatval[nzcnt++] = 1;
							}}



							for (i = 0; i <= N ; i++) {
								if(i==j)  continue;
								if (x2Ptr [j][i][k][n][s] >= 0){
									rmatind[nzcnt] =x2Ptr [j][i][k][n][s];
									rmatval[nzcnt++] = -1;
							}}

								rmatbeg[1] = nzcnt;
								if (nzcnt > 0) {
									status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
									if (status)	{
										CPXgeterrorstring (env, status, errmsg);
										printf("%s", errmsg);
										exit(-1);
									}
								}
							}
						}
					}
				
			}
		///////////////////////////////////////////////(jadid)(20)/////////////////////////////////////

		for (k=1; k<= K; k++){
			for (n=1; n<=Mk[k]; n++){
			constraints = constraints + 1;
			nzcnt		= 0;
			rhs[0]		= 0;                                 
			sense[0]	= 'G';
			rmatbeg[0]	= 0;


			for (j=1; j<=N; j++) {
				if (x1Ptr[(N+k)][j][k][n] >= 0){
					rmatind[nzcnt] =x1Ptr[(N+k)][j][k][n];
					rmatval[nzcnt++] = M;
				}
			}

			
			for (i=1; i<=N; i++) {
				for (m=0; m<=N; m++) {
					if (i==m) continue;
					if (x1Ptr[i][m][k][n] >= 0){
						rmatind[nzcnt] =x1Ptr[i][m][k][n];
						rmatval[nzcnt++] = -1;
					}
				}
			}


		rmatbeg[1] = nzcnt;
		if (nzcnt > 0) {
			status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
			if (status)	{
				CPXgeterrorstring (env, status, errmsg);
				printf("%s", errmsg);
				exit(-1);
			}
		}
		}
		}
//////////////////////////////////////////////////////(21)/////////////////////////////////////////
		for (k=1; k<= K; k++){
			for (n=1; n<=Mk[k]; n++){
				
					for (s=1; s<=S; s++){
					constraints = constraints + 1;
					nzcnt		= 0;
					rhs[0]		= 0;                                 
					sense[0]	= 'G';
					rmatbeg[0]	= 0;


					for (j=1; j<=N; j++) {
						if (x2Ptr[(N+k)][j][k][n][s] >= 0){
							rmatind[nzcnt] =x2Ptr[(N+k)][j][k][n][s];
							rmatval[nzcnt++] = M;
						}
					}

			
					for (i=1; i<=N; i++) {
						for (m=0; m<=N; m++) {
							if (i==m) continue;
							if (x2Ptr[i][m][k][n][s] >= 0){
								rmatind[nzcnt] =x2Ptr[i][m][k][n][s];
								rmatval[nzcnt++] = -1;
							}
						}
					}


				rmatbeg[1] = nzcnt;
				if (nzcnt > 0) {
					status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
					if (status)	{
						CPXgeterrorstring (env, status, errmsg);
						printf("%s", errmsg);
						exit(-1);
							}
						}
					}
				}
			
		}
////////////////////////////////////////////////(22)//////////////////////////////////////////
					
							constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 0;                                 
							sense[0]	= 'E';
							rmatbeg[0]	= 0;

						
							for (k=1; k<=K; k++) {
								for(i=1; i<=Mk[k]; i++) {
									if (O1Ptr [0][k][i] >= 0){
										rmatind[nzcnt] =O1Ptr [0][k][i];
										rmatval[nzcnt++] = 1;
									}
								}
							}
						

						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
					
				
///////////////////////////////////////////////////////////////(25)//////////////////////////////////////////////
		
		for (j=1; j<= N; j++){
			
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++) {
							constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 0;                                 
							sense[0]	= 'L';
							rmatbeg[0]	= 0;

							
							if (O1Ptr [j][k][n] >= 0){
								rmatind[nzcnt] =O1Ptr [j][k][n];
								rmatval[nzcnt++] = 1;
						}

					for (i=1; i<=(N+K); i++) {

							if (x1Ptr [i][j][k][n] >= 0){
								rmatind[nzcnt] =x1Ptr [i][j][k][n];
								rmatval[nzcnt++] = -M;
							}
						}
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
					}
				}
		}
	
		/////////////////////////////////////////////26 (a)///////////////////////////////////////////////////////////////////
		for (i=1; i<=N; i++) {
				for (j=0; j<=N; j++) {
					if (i==j) continue; 
					for (k=1; k<=K; k++){
						for  (n=1; n<=Mk[k]; n++){
						
						
							constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= -M;  //-2*M                               
							sense[0]	= 'G';
							rmatbeg[0]	= 0;

						
								
								if (O1Ptr [i][k][n]>= 0){
									rmatind[nzcnt] =O1Ptr [i][k][n];
									rmatval[nzcnt++] = 1;
							}
							
								
								if (O1Ptr [j][k][n]>= 0){
									rmatind[nzcnt] =O1Ptr [j][k][n];
									rmatval[nzcnt++] = -1;
							}
							
							
							if (q1Ptr [i]>= 0){
									rmatind[nzcnt] =q1Ptr [i];
									rmatval[nzcnt++] = -1;
							}

							if (x1Ptr [i][j][k][n]>= 0){
									rmatind[nzcnt] =x1Ptr [i][j][k][n];
									rmatval[nzcnt++] = -M;
							}

						
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
					}
					}
				}
		}

///////////////////////////////////////////////////////////26(b)/////////////////////////////////////////////
		for (i=1; i<=N; i++) {
				for (j=0; j<=N; j++) {
					if (i==j) continue; 
					for (k=1; k<=K; k++){
						for  (n=1; n<=Mk[k]; n++){
						
						
							constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= M;                                 
							sense[0]	= 'L';
							rmatbeg[0]	= 0;

						
								
								if (O1Ptr [i][k][n]>= 0){
									rmatind[nzcnt] =O1Ptr [i][k][n];
									rmatval[nzcnt++] = 1;
							}
							
								
								if (O1Ptr [j][k][n]>= 0){
									rmatind[nzcnt] =O1Ptr [j][k][n];
									rmatval[nzcnt++] = -1;
							}
							
							
							if (q1Ptr [i]>= 0){
									rmatind[nzcnt] =q1Ptr [i];
									rmatval[nzcnt++] = -1;
							}

							if (x1Ptr [i][j][k][n]>= 0){
									rmatind[nzcnt] =x1Ptr [i][j][k][n];
									rmatval[nzcnt++] = M;
							}


							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
					}
					}
				}
		}

//////////////////////////////////////////////////(27)/////////////////////////////////////
				
					for (s=1; s<=S; s++){
						constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 0;                                 
							sense[0]	= 'E';
							rmatbeg[0]	= 0;

						
							for (k=1; k<=K; k++) {
								for(i=1; i<=Mk[k]; i++) {
									if (O2Ptr [0][k][i][s] >= 0){
										rmatind[nzcnt] =O2Ptr [0][k][i][s];
										rmatval[nzcnt++] = 1;
									}
								}
							}
						

						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
					}
				
					
//////////////////////////////////////////////////////////////////////////(30)////////////////////////////////////////////////////////
			for (j=1; j<= N; j++){
			
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++) {
						
							for (s=1; s<=S; s++) {

							constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 0;                                 
							sense[0]	= 'L';
							rmatbeg[0]	= 0;

							
							if (O2Ptr [j][k][n][s] >= 0){
								rmatind[nzcnt] =O2Ptr [j][k][n][s];
								rmatval[nzcnt++] = 1;
						}

					for (i=1; i<=(N+K); i++) {

							if (x2Ptr [i][j][k][n][s] >= 0){
								rmatind[nzcnt] =x2Ptr [i][j][k][n][s];
								rmatval[nzcnt++] = -M;
							}
						}
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
									}
								}
							}
						
					}
				}
			}

////	//////////////////////////////////////////////////////////////////(31)////////////////////////////////////////////////////////////
			for (i=1; i<=N; i++) {
				for (j=0; j<=N; j++) {
					if (i==j) continue; 
					for (k=1; k<=K; k++){
						for  (n=1; n<=Mk[k]; n++){
							
								for  (s=1; s<=S; s++){
						
									constraints = constraints + 1;
									nzcnt		= 0;
									rhs[0]		= -M;  //-2*M                               
									sense[0]	= 'G';
									rmatbeg[0]	= 0;

						
								
										if (O2Ptr [i][k][n][s]>= 0){
											rmatind[nzcnt] =O2Ptr [i][k][n][s];
											rmatval[nzcnt++] = 1;
									}
							
								
										if (O2Ptr [j][k][n][s]>= 0){
											rmatind[nzcnt] =O2Ptr [j][k][n][s];
											rmatval[nzcnt++] = -1;
									}
							
							
									if (qPtr [i][s]>= 0){
											rmatind[nzcnt] =qPtr [i][s];
											rmatval[nzcnt++] = -1;
									}

									if (x2Ptr [i][j][k][n][s]>= 0){
											rmatind[nzcnt] =x2Ptr [i][j][k][n][s];
											rmatval[nzcnt++] = -M;
									}

						
								rmatbeg[1] = nzcnt;
								if (nzcnt > 0) {
									status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
									if (status)	{
										CPXgeterrorstring (env, status, errmsg);
										printf("%s", errmsg);
										exit(-1);
										}
									}
								}
							}
						}
					}
				}
			
/////////////////////////////////////////////////////////////////////////////(32)////////////////////////////////////////////
		for (i=1; i<=N; i++) {
				for (j=0; j<=N; j++) {
					if (i==j) continue; 
					for (k=1; k<=K; k++){
						for  (n=1; n<=Mk[k]; n++){
							
								for  (s=1; s<=S;s++){
						
						
									constraints = constraints + 1;
									nzcnt		= 0;
									rhs[0]		= M;                                 
									sense[0]	= 'L';
									rmatbeg[0]	= 0;

						
								
										if (O2Ptr [i][k][n][s]>= 0){
											rmatind[nzcnt] =O2Ptr [i][k][n][s];
											rmatval[nzcnt++] = 1;
									}
							
								
										if (O2Ptr [j][k][n][s]>= 0){
											rmatind[nzcnt] =O2Ptr [j][k][n][s];
											rmatval[nzcnt++] = -1;
									}
							
							
									if (qPtr [i][s]>= 0){
											rmatind[nzcnt] =qPtr [i][s];
											rmatval[nzcnt++] = -1;
									}

									if (x2Ptr [i][j][k][n][s]>= 0){
											rmatind[nzcnt] =x2Ptr [i][j][k][n][s];
											rmatval[nzcnt++] = M;
									}


							
								rmatbeg[1] = nzcnt;
								if (nzcnt > 0) {
									status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
									if (status)	{
										CPXgeterrorstring (env, status, errmsg);
										printf("%s", errmsg);
										exit(-1);
										}
									}
								}
							}
						}
					
				}
			}

////////////////////////////////////////////////////////////Symmetry breaking constraints (add shode (37) )////////////////////////////////////
			for (k=1; k<=K; k++) {
						for (n=2; n<=Mk[k]; n++) {
						
								constraints = constraints + 1;
									nzcnt		= 0;
									rhs[0]		= 0;                                 
									sense[0]	= 'L';
									rmatbeg[0]	= 0;

								for (j=1; j<=N; j++) {
									if (x1Ptr [((N+k))][j][k][n] >= 0){
										rmatind[nzcnt] =x1Ptr [((N+k))][j][k][n];
										rmatval[nzcnt++] = 1;
									}
								}

								for (s=1; s<=N; s++) {
									if (x1Ptr [((N+k))][s][k][(n-1)] >= 0){
										rmatind[nzcnt] =x1Ptr [((N+k))][s][k][(n-1)];
										rmatval[nzcnt++] = -1;
								}
								}

						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
					}
					}
/////////////////////////////////////////////////////////////////////////////////(38)//////////////////////////////////////////////////		
					for (k=1; k<=K; k++) {
						for (n=2; n<=Mk[k]; n++) {
							
								for (s=1; s<=S; s++) {
						
								constraints = constraints + 1;
									nzcnt		= 0;
									rhs[0]		= 0;                                 
									sense[0]	= 'L';
									rmatbeg[0]	= 0;

								for (j=1; j<=N; j++) {
									if (x2Ptr [((N+k))][j][k][n][s] >= 0){
										rmatind[nzcnt] =x2Ptr [((N+k))][j][k][n][s];
										rmatval[nzcnt++] = 1;
									}
								}

								for (j=1; j<=N; j++) {
									if (x2Ptr [((N+k))][j][k][(n-1)][s] >= 0){
										rmatind[nzcnt] =x2Ptr [((N+k))][j][k][(n-1)][s];
										rmatval[nzcnt++] = -1;
								}
								}

						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
										}
									}
								}
							}
						}
					
				
////////////////////////////////////////////////////(39 add shode)/////////////////////////////////////////////
					for (i=1; i<=N; i++) {	
						for (k=1; k<=K; k++) {
						for (n=2; n<=Mk[k]; n++) {
						
								constraints = constraints + 1;
									nzcnt		= 0;
									rhs[0]		= 0;                                 
									sense[0]	= 'L';
									rmatbeg[0]	= 0;

							
									for (j=1; j<=N; j++) {
										if (i==j) continue;
									if (x1Ptr [(j)][i][k][n] >= 0){
										rmatind[nzcnt] =x1Ptr [(j)][i][k][n];
										rmatval[nzcnt++] = 1;
									}
								} 
									for (j=1; j<=N; j++) {
									for (z=1; z<i; z++) {
									if (x1Ptr [j][z][k][(n-1)] >= 0){
										rmatind[nzcnt] =x1Ptr [j][z][k][(n-1)];
										rmatval[nzcnt++] = -1;
								}
									}
									}

						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
					}
						}
					}
///////////////////////////////////////////////////////////(40)/////////////////////////////////////////////
					for (i=1; i<=N; i++) {	
						for (k=1; k<=K; k++) {
							for (n=2; n<=Mk[k]; n++) {
								
									for (s=1; s<=S; s++) {
						
											constraints = constraints + 1;
											nzcnt		= 0;
											rhs[0]		= 0;                                 
											sense[0]	= 'L';
											rmatbeg[0]	= 0;

							
											for (j=1; j<=N; j++) {
												if (i==j) continue;
											if (x2Ptr [(j)][i][k][n][s] >= 0){
												rmatind[nzcnt] =x2Ptr [(j)][i][k][n][s];
												rmatval[nzcnt++] = 1;
											}
										} 
											for (j=1; j<=N; j++) {
											for (z=1; z<i; z++) {
											if (x2Ptr [j][z][k][(n-1)][s] >= 0){
												rmatind[nzcnt] =x2Ptr [j][z][k][(n-1)][s];
												rmatval[nzcnt++] = -1;
										}
											}
											}

								rmatbeg[1] = nzcnt;
								if (nzcnt > 0) {
									status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
									if (status)	{
										CPXgeterrorstring (env, status, errmsg);
										printf("%s", errmsg);
										exit(-1);
											}
										}
									}
								}
							}
						
					}
//////////////////////////////////////////////////////////////linearization objective/////////////////////////////////////(42)
					for (i=1; i<=N; i++) {	////////sv constraints
						for (t=1; t<=T; t++) {//t
						for (s=1; s<=S; s++) {
						
								constraints = constraints + 1;
									nzcnt		= 0;
									rhs[0]		= 0;                                 
									sense[0]	= 'L';
									rmatbeg[0]	= 0;

							
									if (GPtr [i][t][s] >= 0){
										rmatind[nzcnt] =GPtr [i][t][s];
										rmatval[nzcnt++] = 1;
								}
									
									if (SVPtr [i][t][s] >= 0){
										rmatind[nzcnt] =SVPtr [i][t][s];
										rmatval[nzcnt++] = -M;
								}
									

						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
					}
						}
					}

////////////////////////////////////////////////////////////////////////(43)////////////////////////////////////////

					for (i=1; i<=N; i++) {	//////////////////sv constraints
						for (t=1; t<=T; t++) {////t
						for (s=1; s<=S; s++) {
						
								constraints = constraints + 1;
									nzcnt		= 0;
									rhs[0]		= M;                                 
									sense[0]	= 'L';
									rmatbeg[0]	= 0;

							
									if (IPtr [i][t][s] >= 0){
										rmatind[nzcnt] =IPtr [i][t][s];
										rmatval[nzcnt++] = 1;
								}
									
									if (SVPtr [i][t][s] >= 0){
										rmatind[nzcnt] =SVPtr [i][t][s];
										rmatval[nzcnt++] = M;
								}
									

						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
					}
						}
					}


//////////////////////////////////////////////////////////////////////(45)///////////////////////////////////////////////////
					constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 0;                                 
							sense[0]	= 'G';
							rmatbeg[0]	= 0;

							
							if (U1Ptr  >= 0){
								rmatind[nzcnt] =U1Ptr ;
								rmatval[nzcnt++] = 1;
						}
							if (I1Ptr  >= 0){
								rmatind[nzcnt] =I1Ptr ;
								rmatval[nzcnt++] = -(1/CF1);
						}
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}

/////////////////////////////////////////////////////////////(46)//////////////////////////////////////////////
						constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 1-e;                                 
							sense[0]	= 'L';
							rmatbeg[0]	= 0;

							
							if (U1Ptr  >= 0){
								rmatind[nzcnt] =U1Ptr ;
								rmatval[nzcnt++] = 1;
						}
							if (I1Ptr  >= 0){
								rmatind[nzcnt] =I1Ptr ;
								rmatval[nzcnt++] = -(1/CF1);
						}
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
//////////////////////////////////(48)////////////////////////////////////////////////////////
						
							for (s=1; s<=S; s++){
					   constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 0;                                 
							sense[0]	= 'G';
							rmatbeg[0]	= 0;

							
							if (U2Ptr[s]  >= 0){
								rmatind[nzcnt] =U2Ptr[s] ;
								rmatval[nzcnt++] = 1;
						}
							if (I2Ptr[s]  >= 0){
								rmatind[nzcnt] =I2Ptr[s] ;
								rmatval[nzcnt++] = -(1/CF1);
						}
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
							
						}
//////////////////////////////////////////////////(49)////////////////////////////////////////////////////////////
					
						for (s=1; s<=S; s++){

							constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 1-e;                                 
							sense[0]	= 'L';
							rmatbeg[0]	= 0;

							
							if (U2Ptr[s]  >= 0){
								rmatind[nzcnt] =U2Ptr[s] ;
								rmatval[nzcnt++] = 1;
						}
							if (I2Ptr[s]  >= 0){
								rmatind[nzcnt] =I2Ptr[s] ;
								rmatval[nzcnt++] = -(1/CF1);
						}
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
								}
							}
						
					}
////////////////////////////////////////////////////(51)///////////////////////////////////////////
			for(i=1; i<=N; i++) {	
				for (t=1; t<=T; t++) {///t
					for (s=1; s<=S; s++) {
						constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 0;                                 
							sense[0]	= 'G';
							rmatbeg[0]	= 0;

							
							if (UPtr[i][t][s]  >= 0){
								rmatind[nzcnt] =UPtr[i][t][s];
								rmatval[nzcnt++] = 1;
						}
							if (IPtr[i][t][s]  >= 0){
								rmatind[nzcnt] =IPtr[i][t][s] ;
								rmatval[nzcnt++] = -(1/Cf);
						}
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
					}
				}
			}
//////////////////////////////////////////////(52)////////////////////////////////////////////////////////////
			for(i=1; i<=N; i++) {	
				for (t=1; t<=T; t++) {//t
					for (s=1; s<=S; s++) {
						constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 1-e;                                 
							sense[0]	= 'L';
							rmatbeg[0]	= 0;

							
							if (UPtr[i][t][s]  >= 0){
								rmatind[nzcnt] =UPtr[i][t][s];
								rmatval[nzcnt++] = 1;
						}
							if (IPtr[i][t][s]  >= 0){
								rmatind[nzcnt] =IPtr[i][t][s] ;
								rmatval[nzcnt++] = -(1/Cf);
						}
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
					}
				}
			}
/////////////////////////////////////////////////////53/////////////////////////////////////////
			for (i=1; i<=N; i++) {
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++){
					
					constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= M;                                 
							sense[0]	= 'L';
							rmatbeg[0]	= 0;


							if (qv1Ptr[i][k][n] >= 0){
								rmatind[nzcnt] =qv1Ptr[i][k][n];
								rmatval[nzcnt++] = 1;
						}
							
							if (q1Ptr[i] >= 0){
								rmatind[nzcnt] =q1Ptr[i];
								rmatval[nzcnt++] = -1;
						}
							for (j=1; j<=(N+K); j++){
							if (x1Ptr[j][i][k][n]  >= 0){
								rmatind[nzcnt] =x1Ptr[j][i][k][n] ;
								rmatval[nzcnt++] = M;
						}
							}
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
				}
			}
			}
			
//////////////////////////////////////////////////54////////////////////////////////////////////////////////////
	for (i=1; i<=N; i++) {
		for (k=1; k<=K; k++) {
			for (n=1; n<=Mk[k]; n++){
					
				constraints = constraints + 1;
				nzcnt		= 0;
				rhs[0]		= -M;                                 
				sense[0]	= 'G';
				rmatbeg[0]	= 0;


				if (qv1Ptr[i][k][n] >= 0){
					rmatind[nzcnt] =qv1Ptr[i][k][n];
					rmatval[nzcnt++] = 1;
				}
							
				if (q1Ptr[i] >= 0){
					rmatind[nzcnt] =q1Ptr[i];
					rmatval[nzcnt++] = -1;
				}
				for (j=1; j<=(N+K); j++){
					if (x1Ptr[j][i][k][n]  >= 0){
						rmatind[nzcnt] =x1Ptr[j][i][k][n] ;
						rmatval[nzcnt++] = -M;
					}
				}
							
							
							
				rmatbeg[1] = nzcnt;
				if (nzcnt > 0) {
					status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
					if (status)	{
						CPXgeterrorstring (env, status, errmsg);
						printf("%s", errmsg);
						exit(-1);
					}
				}
			}
		}
	}

	//////////////////////////////////////////////////(54a)////////////////////////////////////////////////////////////
	for (i=1; i<=N; i++) {
		for (k=1; k<=K; k++) {
			for (n=1; n<=Mk[k]; n++){
					
				constraints = constraints + 1;
				nzcnt		= 0;
				rhs[0]		= 0;                                 
				sense[0]	= 'L';
				rmatbeg[0]	= 0;


				if (qv1Ptr[i][k][n] >= 0){
					rmatind[nzcnt] =qv1Ptr[i][k][n];
					rmatval[nzcnt++] = 1;
				}
							
				
				for (j=1; j<=(N+K); j++){
					if (x1Ptr[j][i][k][n]  >= 0){
						rmatind[nzcnt] =x1Ptr[j][i][k][n] ;
						rmatval[nzcnt++] = -M;
					}
				}
							
							
							
				rmatbeg[1] = nzcnt;
				if (nzcnt > 0) {
					status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
					if (status)	{
						CPXgeterrorstring (env, status, errmsg);
						printf("%s", errmsg);
						exit(-1);
					}
				}
			}
		}
	}
			
		///////////////////////////////////////////////////////////55/////////////////////////////////////////////
			for (j=1; j<=N; j++) {
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++){
					
					constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= -M;                                 
							sense[0]	= 'G';
							rmatbeg[0]	= 0;


							if (O1Ptr[j][k][n] >= 0){
								rmatind[nzcnt] =O1Ptr[j][k][n];
								rmatval[nzcnt++] = 1;
						}

							for (i=1; i<=N; i++) {
							if (qv1Ptr[i][k][n] >= 0){
								rmatind[nzcnt] =qv1Ptr[i][k][n];
								rmatval[nzcnt++] = -1;
						}
							}


							
							if (x1Ptr[(N+k)][j][k][n]  >= 0){
								rmatind[nzcnt] =x1Ptr[(N+k)][j][k][n] ;
								rmatval[nzcnt++] = -M;
						}
							
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
				}
			}
				}

	/////////////////////////////////////////////////////////////////56//////////////////////////////////////////////////////
			for (j=1; j<=N; j++) {
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++){
					
					constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= M;                                 
							sense[0]	= 'L';
							rmatbeg[0]	= 0;


							if (O1Ptr[j][k][n] >= 0){
								rmatind[nzcnt] =O1Ptr[j][k][n];
								rmatval[nzcnt++] = 1;
						}

							for (i=1; i<=N; i++) {
							if (qv1Ptr[i][k][n] >= 0){
								rmatind[nzcnt] =qv1Ptr[i][k][n];
								rmatval[nzcnt++] = -1;
						}
							}


							
							if (x1Ptr[(N+k)][j][k][n]  >= 0){
								rmatind[nzcnt] =x1Ptr[(N+k)][j][k][n] ;
								rmatval[nzcnt++] = M;
						}
							
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
				}
			}
				}
/////////////////////////////////////////////////////////(57)/////////////////////////////////
			for (i=1; i<=N; i++) {
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++){
						
							for (s=1; s<=S; s++){
	
							constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= M;                                 
							sense[0]	= 'L';
							rmatbeg[0]	= 0;


							if (qvPtr[i][k][n][s] >= 0){
								rmatind[nzcnt] =qvPtr[i][k][n][s];
								rmatval[nzcnt++] = 1;
								}
							
							if (qPtr[i][s] >= 0){
								rmatind[nzcnt] =qPtr[i][s];
								rmatval[nzcnt++] = -1;
								}
							for (j=1; j<=(N+K); j++){
							if (x2Ptr[j][i][k][n][s]  >= 0){
								rmatind[nzcnt] =x2Ptr[j][i][k][n][s] ;
								rmatval[nzcnt++] = M;
								}
							}
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
									}
								}
							}
						}
					}
				
			}
/////////////////////////////////////////////////////////////(58)////////////////////////////////////////////
			for (i=1; i<=N; i++) {
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++){
						
							for (s=1; s<=S; s++){
					
							constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= -M;                                 
							sense[0]	= 'G';
							rmatbeg[0]	= 0;


							if (qvPtr[i][k][n][s] >= 0){
								rmatind[nzcnt] =qvPtr[i][k][n][s];
								rmatval[nzcnt++] = 1;
							}
							
							if (qPtr[i][s] >= 0){
								rmatind[nzcnt] =qPtr[i][s];
								rmatval[nzcnt++] = -1;
							}
							for (j=1; j<=(N+K); j++){
								if (x2Ptr[j][i][k][n][s]  >= 0){
									rmatind[nzcnt] =x2Ptr[j][i][k][n][s] ;
									rmatval[nzcnt++] = -M;
								}
							}
							
							
							
							rmatbeg[1] = nzcnt;
							if (nzcnt > 0) {
								status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
								if (status)	{
									CPXgeterrorstring (env, status, errmsg);
									printf("%s", errmsg);
									exit(-1);
									}
								}
							}
						}
					
				}
			}
//////////////////////////////////////////////////////////////////(58a)/////////////////////////////////////////////
		for (i=1; i<=N; i++) {
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++){
						
							for (s=1; s<=S; s++){
					
							constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= 0;                                 
							sense[0]	= 'L';
							rmatbeg[0]	= 0;


							if (qvPtr[i][k][n][s] >= 0){
								rmatind[nzcnt] =qvPtr[i][k][n][s];
								rmatval[nzcnt++] = 1;
							}
							
				
							for (j=1; j<=(N+K); j++){
								if (x2Ptr[j][i][k][n][s]  >= 0){
									rmatind[nzcnt] =x2Ptr[j][i][k][n][s];
									rmatval[nzcnt++] = -M;
								}
							}
							
							
							
							rmatbeg[1] = nzcnt;
							if (nzcnt > 0) {
								status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
								if (status)	{
									CPXgeterrorstring (env, status, errmsg);
									printf("%s", errmsg);
									exit(-1);
									}
								}
							}
						}
					
				}
			}
			
/////////////////////////////////////////////////////////////////////////(59)////////////////////////////////////////////////////////
			for (j=1; j<=N; j++) {
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++){
						
							for (s=1; s<=S; s++){
					constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= -M;                                 
							sense[0]	= 'G';
							rmatbeg[0]	= 0;


							if (O2Ptr[j][k][n][s] >= 0){
								rmatind[nzcnt] =O2Ptr[j][k][n][s];
								rmatval[nzcnt++] = 1;
						}

							for (i=1; i<=N; i++) {
							if (qvPtr[i][k][n][s] >= 0){
								rmatind[nzcnt] =qvPtr[i][k][n][s];
								rmatval[nzcnt++] = -1;
						}
							}


							
							if (x2Ptr[(N+k)][j][k][n][s]  >= 0){
								rmatind[nzcnt] =x2Ptr[(N+k)][j][k][n][s] ;
								rmatval[nzcnt++] = -M;
						}
							
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
									}
								}
							}
						}
					}
				
			}
////////////////////////////////////////////////////(60)//////////////////////////////////////////

			for (j=1; j<=N; j++) {
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++){
						
							for (s=1; s<=S; s++){
					
							constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= M;                                 
							sense[0]	= 'L';
							rmatbeg[0]	= 0;


							if (O2Ptr[j][k][n][s] >= 0){
								rmatind[nzcnt] =O2Ptr[j][k][n][s];
								rmatval[nzcnt++] = 1;
						}

							for (i=1; i<=N; i++) {
							if (qvPtr[i][k][n][s] >= 0){
								rmatind[nzcnt] =qvPtr[i][k][n][s];
								rmatval[nzcnt++] = -1;
						}
							}


							
							if (x2Ptr[(N+k)][j][k][n][s]  >= 0){
								rmatind[nzcnt] =x2Ptr[(N+k)][j][k][n][s] ;
								rmatval[nzcnt++] = M;
						}
							
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
									}
								}
							}
						}
					}
				
			}
//////////////////////////////////////////////////////////////////mahdodiate add shode flow (61)////////////////////////////////
			for (j=1; j<=N; j++) {
				for (i=1; i<=(N+K); i++){
					
				for (k=1; k<=K; k++) {
					for (n=1; n<=Mk[k]; n++){
					
						

					constraints = constraints + 1;
							nzcnt		= 0;
							rhs[0]		= -M;                                 
							sense[0]	= 'G';
							rmatbeg[0]	= 0;

							if (flow_d1Ptr[j][k][n] >= 0){
								rmatind[nzcnt] =flow_d1Ptr[j][k][n];
								rmatval[nzcnt++] = 1;
						}
							if (O1Ptr[j][k][n] >= 0){
								rmatind[nzcnt] =O1Ptr[j][k][n];
								rmatval[nzcnt++] = -(Distance[i][j]);
						}

							


							
							if (x1Ptr[i][j][k][n]  >= 0){
								rmatind[nzcnt] =x1Ptr[i][j][k][n] ;
								rmatval[nzcnt++] = -M;
						}
							
							
							
						rmatbeg[1] = nzcnt;
						if (nzcnt > 0) {
							status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
							if (status)	{
								CPXgeterrorstring (env, status, errmsg);
								printf("%s", errmsg);
								exit(-1);
							}
						}
				}
			}
				}
			}
//	//////////////////////////////////////////////////////////////mahdodiate add shode flow (62)//////////////////////
			for (j=1; j<=N; j++) {
				for (i=1; i<=(N+K); i++){
					
					for (k=1; k<=K; k++) {
						for (n=1; n<=Mk[k]; n++){
							
								for (s=1; s<=S; s++){
					
									constraints = constraints + 1;
									nzcnt		= 0;
									rhs[0]		= -M;                                 
									sense[0]	= 'G';
									rmatbeg[0]	= 0;

									if (flow_d2Ptr[j][k][n][s] >= 0){
										rmatind[nzcnt] =flow_d2Ptr[j][k][n][s];
										rmatval[nzcnt++] = 1;
								}
									if (O2Ptr[j][k][n][s] >= 0){
										rmatind[nzcnt] =O2Ptr[j][k][n][s];
										rmatval[nzcnt++] = -(Distance[i][j]);
								}

							


							
									if (x2Ptr[i][j][k][n][s]  >= 0){
										rmatind[nzcnt] =x2Ptr[i][j][k][n][s] ;
										rmatval[nzcnt++] = -M;
								}
							
							
							
								rmatbeg[1] = nzcnt;
								if (nzcnt > 0) {
									status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
									if (status)	{
										CPXgeterrorstring (env, status, errmsg);
										printf("%s", errmsg);
										exit(-1);
										}
									}
								}
							}
						}
					}
				}
//////////////////////////////////////////////////////////////////valid inequalities//////////////////////////////////////////////
			/*				for (j=1; j<=N; j++) {
					
								for (s=1; s<=S; s++){
					
									constraints = constraints + 1;
									nzcnt		= 0;
									rhs[0]		= 1;                                 
									sense[0]	= 'G';
									rmatbeg[0]	= 0;

								
									for (i=1; i<=(N+K); i++){
										for (k=1; k<=K; k++) {
											for (n=1; n<=Mk[k]; n++){
												if (x2Ptr[i][j][k][n][s]  >= 0){
													rmatind[nzcnt] =x2Ptr[i][j][k][n][s] ;
													rmatval[nzcnt++] = 1;
												}
											}
										}
									}
							
									if (IPtr[j][1][s]  >= 0){
										rmatind[nzcnt] =IPtr[j][1][s] ;
										rmatval[nzcnt++] = (1/ D[j][s]);
									}
							
							
								rmatbeg[1] = nzcnt;
								if (nzcnt > 0) {
									status = CPXaddrows(env,lp,0,1,nzcnt,rhs,sense,rmatbeg,rmatind,rmatval,NULL,NULL);
									if (status)	{
										CPXgeterrorstring (env, status, errmsg);
										printf("%s", errmsg);
										exit(-1);
										}
									}
								}
				}*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
		  numcols = CPXgetnumcols(env,lp);
		  numrows = CPXgetnumrows(env,lp);

		  
		
          cout<<  numcols<<"\t";
		cout<<endl;
		  cout<<   numrows<<"\t";
		cout<<endl;
		  
		  
		  
		  X_Cplex = new double [numcols];
		  
		  CPXcopyctype (env, lp, coltype);
		  
		  
		   sprintf(FileName, "%s", "C:\\cplex\\jadid\\test2\\output\\Log");
		  strcat (FileName, ".txt");
		  logfile = CPXfopen (FileName, "w");
		  status = CPXsetlogfile (env, logfile);
		  
		  status = CPXwriteprob (env, lp, "lpex1.lp", NULL);
		 
	CPXsetintparam(env, CPX_PARAM_MEMORYEMPHASIS, 1);
	CPXsetdblparam(env, CPX_PARAM_WORKMEM, 1);
	CPXsetintparam(env, CPX_PARAM_NODEFILEIND, 2);

	status = CPXsetdblparam(env, CPX_PARAM_TILIM, 100);
	/*status= CPXsetintparam(env, CPX_PARAM_BNDSTRENIND,0.08);*/
	status= CPXsetintparam(env, CPX_PARAM_BNDSTRENIND,1);
	status= CPXsetintparam(env, CPX_PARAM_BNDSTRENIND,0.01);
	
	cout<<"Solving.."<<endl;
	StartTime = second();
	status = CPXmipopt(env, lp);
	EndTime = second();

	if (status) 
	{
		printf ("\nFailed to optimize LP.\n");
		EndTime = second();
		exit(-11);
	}

	status = CPXgetmipx (env, lp, X_Cplex, 0, numcols - 1);
	if ( status )
	{
		printf ("\nFailed to obtain solution.\n");
		EndTime = second();
		exit(-12);
	}

		status = CPXsolwrite(env, lp, "Solution.sol");

		  
		  CPXgetslack (env, lp, slack, 0, 0);
		  
		  status = CPXgetmiprelgap(env, lp, &gap_p);
		  
		  char OutName[500];
		  FILE *Out;

		  status1 = CPXgetmipobjval (env, lp, &objval);
		  if ( status1 ) 
		  {
			  printf ("Failed to get the MIP objective value.\n");
			  exit(1);
		  }

		  if(key_create==false)
		  {

			   sprintf(OutName, "C:\\cplex\\jadid\\test2\\output\\TotalR.txt");
			  Output=fopen(OutName,"w");
			  key_create=true;
		  }


		 

		  fprintf(Output, "%d_%d	%f	%f	%f\n",x1,x2,objval,gap_p,EndTime- StartTime );
		  fflush(Output);
		  
		  
		   sprintf(OutName, "C:\\cplex\\jadid\\test2\\output\\Result%d_%d",x1,x2);
		  strcat (OutName, ".txt");
		  
		  Out = fopen(OutName,"w");

		  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		  	counter = 0;
			
			/////////////////////////////////print I//////////////////////////////////////////
			fprintf(Out, "%s","I:\n");
			for (i = 1; i <= N ; i++) {	
					for (t=1; t<= T; t++){
						for (s=1; s<= S; s++){
						if (X_Cplex[counter] >=0) {
							fprintf(Out, "I[%d][%d][%d]= %f\n",i,t,s, X_Cplex[counter] );
							inventory_cost=inventory_cost+(X_Cplex[counter]*P[s]*h);
						}
						
						counter = counter + 1;
					}
				}
				
			}
			fprintf(Out, "\n");
			fflush(Out);
		///////////////////////////////////////////////////I1/////////////////////////////////////	
			fprintf(Out, "%s","I1:\n");
				if (X_Cplex[counter] >0) {
					fprintf(Out, "I1= %f\n", X_Cplex[counter]);
					inventory_cost=inventory_cost+(X_Cplex[counter]*h1);
				}
				
				counter = counter + 1;
			
			fprintf(Out, "\n");
			///////////////////////////////////////I2///////////////////////////////////
			fprintf(Out, "%s","I2:\n");
			
					
						for (s=1; s<= S; s++){
						if (X_Cplex[counter] >0) {
							fprintf(Out, "I2[%d]= %f\n",s, X_Cplex[counter] );
							inventory_cost=inventory_cost+(X_Cplex[counter]*P[s]*h1);
						}
						
						counter = counter + 1;
					}
				
				
			fprintf(Out, "\n");
////////////////////////////////////////////////////////////////////////////////////////////////////
			fprintf(Out, "%s","G:\n");
			for (i = 1; i <= N ; i++) {	
					for (t=1; t<= T; t++){
						for (s=1; s<= S; s++){
						if (X_Cplex[counter] >0 ) {
							fprintf(Out, "G[%d][%d][%d]= %f\n",i,t,s, X_Cplex[counter] );
							shortage_cost=shortage_cost+(X_Cplex[counter]*P[s]*a);
							tedade_shortage=tedade_shortage+X_Cplex[counter];
						}
						counter = counter + 1;
					}
				}
				
			}
			fprintf(Out, "\n");
/////////////////////////////////////////////flow-d1/////////////////////////////////////////////
			fprintf(Out, "%s","flow_d1:\n");
			
					for (i=1; i<= (N); i++){
						
							
							for (k=1; k<=K; k++) {
							for (j=1; j<=Mk[k]; j++) {	
						
						if (X_Cplex[counter] >0) {
							fprintf(Out, "flow_d1[%d][%d][%d]= %f\n",i,k, j, X_Cplex[counter] );
							
							emissions_cost=emissions_cost+X_Cplex[counter]*Z*rate[k]*A[k]*alfa*kilo*Unit_w*Pc*Conversion;
							emissions_net=emissions_net+X_Cplex[counter]*Z*rate[k]*A[k]*alfa*kilo*Unit_w*Conversion;
							transportation_cost=transportation_cost+(X_Cplex[counter]*Z*rate[k]*A[k]*alfa*kilo*Unit_w*fc);
						}
						counter = counter + 1;
					}
					}
					}
					
		
			fprintf(Out, "\n");
			fflush(Out);
///////////////////////////////////////////////////flow_d2///////////////////////////////////////////////
			fprintf(Out, "%s","flow_d2:\n");
			for (i = 1; i <= (N) ; i++) {	
				
					
					for (k=1; k<=K; k++) {
						for (j=1; j<=Mk[k]; j++) {	

					
						for (s=1; s<= S; s++){
						if (X_Cplex[counter] >0 ) {
							fprintf(Out, "flow_d2[%d][%d][%d][%d]= %f\n",i,k, j,s, X_Cplex[counter] );
							
							emissions_cost=emissions_cost+(X_Cplex[counter]*P[s]*(Z*rate[k]*A[k]*alfa*kilo*Unit_w*Pc*Conversion));
							emissions_net=emissions_net+(X_Cplex[counter]*P[s]*(Z*rate[k]*A[k]*alfa*kilo*Unit_w*Conversion));
							transportation_cost=transportation_cost+(X_Cplex[counter]*P[s]*Z*rate[k]*A[k]*alfa*kilo*Unit_w*fc);
						}
						counter = counter + 1;
					}
				}
					
				}
			}
			fprintf(Out, "\n");
///////////////////////////////////////////////////O1////////////////////////////////////////////
			fprintf(Out, "%s","O1:\n");
			
					for (i=0; i<= N; i++){
						
							
							for (k=1; k<=K; k++) {
								for (j=1; j<=Mk[k]; j++) {	
								
						
						if (X_Cplex[counter] >0) {
							fprintf(Out, "O1[%d][%d][%d]= %f\n",i,k,j, X_Cplex[counter] );
							
							/*emissions_cost=emissions_cost+X_Cplex[counter]*Z*rate*A[k]*alfa*Distance [i][j]*kilo*Unit_w*Pc*Conversion;
							transportation_cost=transportation_cost+(X_Cplex[counter]*Z*rate*A[k]*alfa*Distance [i][j]*kilo*Unit_w*fc);*/
						}
						counter = counter + 1;
					}
					}
					}
					
		
			fprintf(Out, "\n");
			fflush(Out);
/////////////////////////////////////////////////////////O2///////////////////////////////////////////////
			fprintf(Out, "%s","O2:\n");
			for (i = 0; i <= N ; i++) {	
				
					for (k=1; k<=K; k++) {
						for (j=1; j<=Mk[k]; j++) {	
					
						for (s=1; s<= S; s++){
						if (X_Cplex[counter] >0 ) {
							fprintf(Out, "O2[%d][%d][%d][%d]= %f\n",i,k,j,s, X_Cplex[counter] );
							
							/*emissions_cost=emissions_cost+(X_Cplex[counter]*P[s]*(Z*rate*A[k]*alfa*Distance [i][j]*kilo*Unit_w*Pc*Conversion));
							transportation_cost=transportation_cost+(X_Cplex[counter]*P[s]*Z*rate*A[k]*alfa*Distance [i][j]*kilo*Unit_w*fc);*/
						}
						counter = counter + 1;
					}
				}
					}
				
			}
			
			fprintf(Out, "\n");
////////////////////////////////////////////////////////////////q1///////////////////////////////////////////
			fprintf(Out, "%s","q1:\n");
			
					for (i=1; i<= N; i++){
						
						if (X_Cplex[counter] >0 ) {
							fprintf(Out, "q1[%d]= %f\n",i, X_Cplex[counter] );
						}
						counter = counter + 1;
					}
		
			fprintf(Out, "\n");
///////////////////////////////////////////////////////q///////////////////////////////////////////
			fprintf(Out, "%s","q:\n");
			
			for (i = 1; i <= N ; i++) {	
					
						for (s=1; s<= S; s++){
						if (X_Cplex[counter] >0 ) {
							fprintf(Out, "q[%d][%d]= %f\n",i,s, X_Cplex[counter] );
						}
						counter = counter + 1;
					}
				}
				
			
			fprintf(Out, "\n");
//////////////////////////////////////////////////////////////////X1/////////////////////////////////////////
			fprintf(Out, "%s","x1:\n");
			for (i = 1; i <= (N+K) ; i++) {	
					for (j=0; j<= N; j++){
						if (i==j || (i>N &&j==0) ) 
							continue; 
						
						for (k=1; k<= K; k++){
							if (i>N && (i-N)!=k) continue;
							for (n=1; n<=Mk[k]; n++){
						if (X_Cplex[counter] >0 ) {
							fprintf(Out, "x1[%d][%d][%d][%d]= %f\n",i,j,k,n, X_Cplex[counter] );
							emissions_cost=emissions_cost+ (X_Cplex[counter]*Pc*Z*rate[k]*Conversion*(H[k]*Nk[k]*V[k]*Distance [i][j]*kilo*rate_speed/speed+W[k]*A[k]*alfa*Distance [i][j]*kilo+B[k]*A[k]*Distance [i][j]*kilo*(speed/rate_speed)*(speed/rate_speed)));
							emissions_net=emissions_net+ (X_Cplex[counter]*Z*rate[k]*Conversion*(H[k]*Nk[k]*V[k]*Distance [i][j]*kilo*rate_speed/speed+W[k]*A[k]*alfa*Distance [i][j]*kilo+B[k]*A[k]*Distance [i][j]*kilo*(speed/rate_speed)*(speed/rate_speed)));
							
							if(i==(N+k) && j!=0){
								
								transportation_cost=transportation_cost+(X_Cplex[counter]*f[k])+X_Cplex[counter]*(fc*Z*rate[k])*(H[k]*Nk[k]*V[k]*Distance [i][j]*kilo*rate_speed/speed+W[k]*A[k]*alfa*Distance [i][j]*kilo+B[k]*A[k]*Distance [i][j]*kilo*(speed/rate_speed)*(speed/rate_speed));
							}
							else {
								
								transportation_cost=transportation_cost+(X_Cplex[counter]*fc*Z*rate[k]*(H[k]*Nk[k]*V[k]*Distance [i][j]*kilo*rate_speed/speed+W[k]*A[k]*alfa*Distance [i][j]*kilo+B[k]*A[k]*Distance [i][j]*kilo*(speed/rate_speed)*(speed/rate_speed)));
								
							}
						}
						counter = counter + 1;
					}
						}
				}
				
			}
			fprintf(Out, "\n");
////////////////////////////////////////////////////////x2/////////////////////////////////////////////////
			fprintf(Out, "%s","x2:\n");
			for (i = 1; i <= (N+K) ; i++) {	
					for (j=0; j<= N; j++){
						if (i==j || (i>N &&j==0) ) 
						continue; 
			
						for (k=1; k<= K; k++){
							if (i>N && (i-N)!=k) continue;
							for (n=1; n<=Mk[k]; n++){
							
								for (s=1; s<=S; s++) {
									if (X_Cplex[counter] >0 ) {
										fprintf(Out, "x2[%d][%d][%d][%d][%d]= %f\n",i,j,k,n, s, X_Cplex[counter] );
										emissions_cost=emissions_cost+ (X_Cplex[counter]*P[s]*(Pc*Z*rate[k]*Conversion)*(H[k]*Nk[k]*V[k]*Distance [i][j]*kilo*rate_speed/speed+W[k]*A[k]*alfa*Distance [i][j]*kilo+B[k]*A[k]*Distance [i][j]*kilo*(speed/rate_speed)*(speed/rate_speed)));
										emissions_net=emissions_net+ (X_Cplex[counter]*P[s]*(Z*rate[k]*Conversion)*(H[k]*Nk[k]*V[k]*Distance [i][j]*kilo*rate_speed/speed+W[k]*A[k]*alfa*Distance [i][j]*kilo+B[k]*A[k]*Distance [i][j]*kilo*(speed/rate_speed)*(speed/rate_speed)));
										
										if(i==(N+k) && j!=0){
										
								transportation_cost=transportation_cost+(X_Cplex[counter]*P[s]*f[k])+(X_Cplex[counter]*P[s]*(fc*Z*rate[k])*(H[k]*Nk[k]*V[k]*Distance [i][j]*kilo*rate_speed/speed+W[k]*A[k]*alfa*Distance [i][j]*kilo+B[k]*A[k]*Distance [i][j]*kilo*(speed/rate_speed)*(speed/rate_speed)));
							}
							else {

								

								transportation_cost=transportation_cost+(X_Cplex[counter]*P[s]*(fc*Z*rate[k])*(H[k]*Nk[k]*V[k]*Distance [i][j]*kilo*rate_speed/speed+W[k]*A[k]*alfa*Distance [i][j]*kilo+B[k]*A[k]*Distance [i][j]*kilo*(speed/rate_speed)*(speed/rate_speed)));
							
							}
									}
									counter = counter + 1;
								}
							}
							}
					
				}
				
			}
			fprintf(Out, "\n");
//////////////////////////////////////////////////////////y3/////////////////////////////////////
			
//////////////////////////////////////////////////////y2//////////////////////////////////////////////////////////////////////////////////////////
			
/////////////////////////////////////////////////////////SV///////////////////////////
			fprintf(Out, "%s","SV:\n");
			for (i = 1; i <= N ; i++) {	
					for (t=1; t<= T; t++){
						for (s=1; s<= S; s++){
						if (X_Cplex[counter] >0) {
							fprintf(Out, "SV[%d][%d][%d]= %f\n",i,t,s, X_Cplex[counter] );
						}
						counter = counter + 1;
					}
				}
				
			}
			fprintf(Out, "\n");
////////////////////////////////////////////////////////U1///////////////////////////////////
			fprintf(Out, "%s","U1:\n");
				if (X_Cplex[counter] >0) {
					fprintf(Out, "U1= %f\n", X_Cplex[counter]);
					
					inventory_cost=inventory_cost+(X_Cplex[counter]*fe*Er1);
					emissions_cost=emissions_cost+(X_Cplex[counter]*Pc*Er1*L);
					emissions_net=emissions_net+(X_Cplex[counter]*Er1*L);
				}
				
				counter = counter + 1;
			
			fprintf(Out, "\n");
			fflush(Out);
////////////////////////////////////////////////////////U2/////////////////////////////////////////
			fprintf(Out, "%s","U2:\n");	
				
					for (s=1; s<= S; s++){
						if (X_Cplex[counter] >0) {
							fprintf(Out, "U2[%d]= %f\n",s, X_Cplex[counter] );
							inventory_cost=inventory_cost+(X_Cplex[counter]*fe*Er1*P[s]);
							emissions_cost=emissions_cost+(X_Cplex[counter]*Pc*Er1*L*P[s]);
							emissions_net=emissions_net+(X_Cplex[counter]*Er1*L*P[s]);
						}

						counter = counter + 1;
					}
				
				
			fprintf(Out, "\n");

//////////////////////////////////////////////////U///////////////////////////////////////////
			fprintf(Out, "%s","U:\n");
			for (i = 1; i <= N ; i++) {	
					for (t=1; t<= T; t++){
						for (s=1; s<= S; s++){
						if (X_Cplex[counter] >0) {
							fprintf(Out, "U[%d][%d][%d]= %f\n",i,t,s, X_Cplex[counter] );
							inventory_cost=inventory_cost+(X_Cplex[counter]*fe*Er*P[s]);
							emissions_cost=emissions_cost+(X_Cplex[counter]*Pc*Er*L*P[s]);
							emissions_net=emissions_net+(X_Cplex[counter]*Er*L*P[s]);
						}
						counter = counter + 1;
					}
				}
				
			}
			fprintf(Out, "\n");
//////////////////////////////////////////////////////////////qv1//////////////////////////////////////////////////////
			fprintf(Out, "%s","qv1:\n");
			for (i = 1; i <= N ; i++) {	
					for (k=1; k<= K; k++){
						for (j=1; j<=Mk[k]; j++) {	
						
						
						if (X_Cplex[counter] >0) {
							fprintf(Out, "qv1[%d][%d][%d]= %f\n",i,k,j, X_Cplex[counter] );
						}
						counter = counter + 1;
					}
					}
			}
			
			fprintf(Out, "\n");
///////////////////////////////////////////////////////////qv///////////////////////////////////////
			fprintf(Out, "%s","qv:\n");
			for (i = 1; i <= N ; i++) {	
					for (k=1; k<= K; k++){
						for (j=1; j<=Mk[k]; j++) {	
						
						for (s=1; s<= S; s++){
						if (X_Cplex[counter] >0) {
							fprintf(Out, "qv[%d][%d][%d][%d]= %f\n",i,k,j,s, X_Cplex[counter] );
						}
						counter = counter + 1;
					}
						}
					}
					
				
			}
			fprintf(Out, "\n");
			///////////////////////////////////////
			fflush(Out);
		  
		  
		  status1 = CPXgetmipobjval (env, lp, &objval);
		  if ( status1 ) 
		  {
			  printf ("Failed to get the MIP objective value.\n");
			  exit(1);
		  }

		  	//////////////////////////////
		  
			
					//	for (t=1; t<= T; t++){
					//	/*for (s=1; s<= S; s++){*/
					//	
					//		fprintf(Out, "tedade_shortage[%d][%d]= %f\n",t );
					//	
					///*}*/
					//	}
					
			
		  total_cost=inventory_cost+shortage_cost+emissions_cost+transportation_cost;
		  fprintf(Out, "Objective 1: %f\n",objval );

	      fprintf(Out, "Objective 2: %f\n",objval  );
		  fprintf(Out, "Time: %f\n",EndTime- StartTime );
		  fprintf(Out, "inventory_cost: %f\n",inventory_cost);
		  fprintf(Out, "shortage_cost: %f\n",shortage_cost);
		   fprintf(Out, "tedade_shortage: %f\n",tedade_shortage);
		  /*fprintf(Out, "inventory_emissions_cost: %f\n",inventory_emissions_cost);*/
		  fprintf(Out, "emissions_cost: %f\n",emissions_cost);
		   fprintf(Out, "emissions_net: %f\n",emissions_net);
		   fprintf(Out, "transportation_cost: %f\n",transportation_cost);
		   fprintf(Out, "total_cost: %f\n",total_cost);
		    fprintf(Out, "gap_p: %f\n",gap_p);
		  fclose(Out);
		  delete_variables();
		 
}

void CreatProblem() {
	int fstatus, status;
	
	
	if ( !CPXEnv ) {
		env = CPXopenCPLEX (&status);
		if ( env == NULL ) {
			printf ("Could not open CPLEX environment.\n");
			exit(0);
		}
		CPXEnv = 1;
	}
	
	if (lp != NULL) {
		fstatus = CPXfreeprob (env, &lp);
		if ( fstatus )
			printf("CPXfreeprob fail, error code %d \n", fstatus);
		//	CPXcloseCPLEX (&env);
		
		//	env = CPXopenCPLEX (&status);
		//	if ( env == NULL ) {
		//		printf ("Could not open CPLEX environment.\n");
		//		exit(0);
		//	}
	}
	
	lp = CPXcreateprob (env, &status, "example");
	CPXchgobjsen (env, lp, CPX_MIN); 
}

void main (void) {
	
	getchar(); // waiting for key input (press ENTER twice)
	
	for(int x1=65; x1<66 ; x1++) {
		for(int x2=6; x2<7; x2++)
		{
			inventory_cost=0;
			shortage_cost=0;
			inventory_emissions_cost=0;
			emissions_cost=0;
			transportation_cost=0;
			total_cost=0;
			emissions_net=0;
			tedade_shortage=0;
	
			sprintf(FileName, "C:\\cplex\\jadid\\test2\\input\\%d_%d.txt",x1 , x2);

			printf("Loc 1\n");
			ReadData();
			printf("Loc 2\n");
	
			CreatProblem();
			printf("Loc 3\n");
	
			ModelPopulate(x1,x2);
			printf("Loc 4\n");

		}
	}
}