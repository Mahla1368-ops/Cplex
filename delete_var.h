void delete_variables()
{
	 
		  if (obj		!= NULL)	delete [] obj;
		  if (rhs		!= NULL)	delete [] rhs;
		  if (sense	!= NULL)	delete [] sense;
		  if (lb		!= NULL)	delete [] lb;
		  if (ub		!= NULL)	delete [] ub;
		  if (coltype != NULL)    delete [] coltype;
		  if (X_Cplex != NULL)    delete [] X_Cplex;
		  if (rmatval	!= NULL)	delete [] rmatval;
		  if (rmatind	!= NULL)	delete [] rmatind;
		  if (rmatbeg	!= NULL)	delete [] rmatbeg;
		  if (A    	!= NULL)	delete [] A;
		  if (B    	!= NULL)	delete [] B;
		 /* if (Mk   	!= NULL)	delete [] Mk;*/
		  if (C    	!= NULL)	delete [] C;
		  if (f    	!= NULL)	delete [] f;
		  if (H    	!= NULL)	delete [] H;
		  if (Nk    != NULL)	delete [] Nk;
		  if (V    	!= NULL)	delete [] V;
		  if (W   	!= NULL)	delete [] W;

		  if (q1  	!= NULL)	delete [] q1;
		  if (q1Ptr  	!= NULL)	delete [] q1Ptr;
		   if (I2  	!= NULL)	delete [] I2;
		  if (I2Ptr  	!= NULL)	delete [] I2Ptr;

		  for (i = 1; i <= N ; ++i)
				 delete [] D[i];
					delete [] D;

	      if (P   	!= NULL)	delete [] P;

		 /* if (Xcoordinate	!= NULL)	delete [] Xcoordinate;
       	  if (Ycoordinate	!= NULL)	delete [] Ycoordinate;*/

	
		  for(i = 0; i <= N; i++) {
			  for(j = 0; j <= T; j++) {
				  delete[] I[i][j];
			  }
			  delete[] I[i];
		  }
		  delete[] I;
		  

		   for(i = 0; i <= N; i++) {
			  for(j = 0; j <= T; j++) {
				  delete[] IPtr[i][j];
			  }
			  delete[] IPtr[i];
		  }
		  delete[] IPtr;


		  for(i = 0; i <= N; i++) {
			  for(j = 0; j <= T; j++) {
				  delete[] U[i][j];
			  }
			  delete[] U[i];
		  }
		  delete[] U;


		   for(i = 0; i <= N; i++) {
			  for(j = 0; j <= T; j++) {
				  delete[] UPtr[i][j];
			  }
			  delete[] UPtr[i];
		  }
		  delete[] UPtr;


		  


		  


		  for(i = 0; i <= N; i++) {
			  for(j = 0; j <= T; j++) {
				  delete[] G[i][j];
			  }
			  delete[] G[i];
		  }
		  delete[] G;


		  for(i = 0; i <= N; i++) {
			  for(j = 0; j <= T; j++) {
				  delete[] GPtr[i][j];
			  }
			  delete[] GPtr[i];
		  }
		  delete[] GPtr;


		   for(i = 0; i <= (N); i++) {
			  for(j = 1; j <= K; j++) {
				  delete[] O1[i][j];
			  }
			  delete[] O1[i];
		  }
		  delete[] O1;


		  for(i = 0; i <= (N); i++) {
			  for(j = 1; j <= K; j++) {
				  delete[] O1Ptr[i][j];
			  }
			  delete[] O1Ptr[i];
		  }
		  delete[] O1Ptr;


		  for(i = 0; i <= (N); i++) {
			  for(j = 1; j <= K; j++) {
				  for (k=1; k<=Mk[j]; k++) {
				  
			  delete[] O2[i][j][k];
		  }
		  delete[] O2[i][j];
			  }
			  delete[] O2[i];
		  }
		   delete[] O2;


		   for(i = 0; i <= (N); i++) {
			  for(j = 1; j <= K; j++) {
				  for (k=1; k<=Mk[j]; k++) {
				 
			  delete[] O2Ptr[i][j][k];
		  }
		  delete[] O2Ptr[i][j];
			  }
			  delete[] O2Ptr[i];
		  }
		   delete[] O2Ptr;


		   for(i = 0; i <= N; i++) {
			  
			  delete[] q[i];
		  }
		  delete[] q;

		   for(i = 0; i <= N; i++) {
			 
			  delete[] qPtr[i];
		  }
		  delete[] qPtr;


		  for (i = 0; i <=N; ++i){
			  for(j = 1; j <= K; j++){
			  delete [] qv1[i][j];
			  }
		  delete [] qv1[i];
		  }

		   delete [] qv1;

		  for (i = 0; i <=N; ++i){
			  for(j = 1; j <= K; j++){
			  delete [] qv1Ptr[i][j];
			  }
		  delete [] qv1Ptr[i];
		  }

		   delete [] qv1Ptr;


		  for(i = 0; i <= N; i++) {
			  for (k=1; k<=K; k++){
			  for(j = 1; j <= Mk[k]; j++) {
				   
			  delete[] qv[i][k][j];
		  }
		  delete[] qv[i][k];
		  }
		   delete[] qv[i];
		  }
		   delete[] qv;

		   for(i = 0; i <= N; i++) {
			  for (k=1; k<=K; k++){
			  for(j = 1; j <= Mk[k]; j++) {
				   
			  delete[] qvPtr[i][k][j];
		  }
		  delete[] qvPtr[i][k];
		  }
		   delete[] qvPtr[i];
		  }
		   delete[] qvPtr;


		   for(i = 1; i <= (N+K); i++) {
			  for(j = 0; j <= N; j++) {
				  for (k=1; k<=K; k++){
				  delete[] x1[i][j][k];
			  }
			  delete[] x1[i][j];
		  }
		  delete[] x1[i];
		   }
		   delete[] x1;


			for(i = 1; i <= (N+K); i++) {
			  for(j = 0; j <= N; j++) {
				  for (k=1; k<=K; k++){
				  delete[] x1Ptr[i][j][k];
			  }
			  delete[] x1Ptr[i][j];
		  }
		  delete[] x1Ptr[i];
		   }
		   delete[] x1Ptr;


		  for(i = 0; i <= N; i++) {
			  for(j = 0; j <= T; j++) {
				  delete[] SV[i][j];
			  }
			  delete[] SV[i];
		  }
		  delete[] SV;


		   for(i = 0; i <= N; i++) {
			  for(j = 0; j <= T; j++) {
				  delete[] SVPtr[i][j];
			  }
			  delete[] SVPtr[i];
		  }
		  delete[] SVPtr;

		   for(i = 1; i <= (N+K); i++) {
			  for(j = 0; j <= N; j++) {
				  for (k=1; k<=K; k++) {
					  for (n=1; n<=Mk[k]; n++){
				 
			  delete[] x2[i][j][k][n];
		  }
		  delete[] x2[i][j][k];
			  }
			  delete[] x2[i][j];
		  }
		   delete[] x2[i];
		   }
		   delete[] x2;


		   for(i = 1; i <= (N+K); i++) {
			  for(j = 0; j <= N; j++) {
				  for (k=1; k<=K; k++) {
					  for (n=1; n<=Mk[k]; n++){
				 
			  delete[] x2Ptr[i][j][k][n];
		  }
		  delete[] x2Ptr[i][j][k];
			  }
			  delete[] x2Ptr[i][j];
		  }
		   delete[] x2Ptr[i];
		   }
		   delete[] x2Ptr;



		   /* for(i = 0; i <= (N); i++) {
			  for(j = 1; j <= K; j++) {
				  delete[] y3[i][j];
			  }
			  delete[] y3[i];
		  }
		  delete[] y3;


		   for(i = 0; i <= (N); i++) {
			  for(j = 1; j <= K; j++) {
				  delete[] y3Ptr[i][j];
			  }
			  delete[] y3Ptr[i];
		  }
		  delete[] y3Ptr;*/


		 /* for(i = 0; i <= (N); i++) {
			  for(k = 1; k <= K; k++) {
				  for (j=1; j<=Mk[k]; j++) {
				  for (t=0; t<=T; t++) {
				  delete[] y2[i][k][j][t];
			  }
			  delete[] y2[i][k][j];
		  }
		  delete[] y2[i][k];
			  }
			  delete[] y2[i];
		  }
		   delete[] y2;
		  
		   for(i = 0; i <= (N); i++) {
			  for(k = 1; k <= K; k++) {
				  for (j=1; j<=Mk[k]; j++) {
				  for (t=0; t<=T; t++) {
				  delete[] y2Ptr[i][k][j][t];
			  }
			  delete[] y2Ptr[i][k][j];
		  }
		  delete[] y2Ptr[i][k];
			  }
			  delete[] y2Ptr[i];
		  }
		   delete[] y2Ptr;*/

		  
		    if (Mk   	!= NULL)	delete [] Mk;

		  for (i = 0; i < (N+1)*(N+1)*(T+1) + 2*(T + 1) + 2*(N+1)*(T+1) + 25000; ++i)
			  delete [] colname[i];
		  delete [] colname;
		  
		  
		  for (i = 1; i <=(N+K); ++i)
			  delete [] Distance[i];
		  delete [] Distance;
}