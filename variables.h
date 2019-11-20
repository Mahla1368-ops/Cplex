long   ****x1, *****x2,***y3,*****y2, ***SV;
float  *Xcoordinate,*Ycoordinate;
long ***I, I1, *I2, ***G, ***O1,****O2, *q1,**q, ***qv1, ****qv,U1, *U2, ***U,***flow_d1, ****flow_d2;
int    T, S,Q, K, N, R, Max, mean_demand=0,kole_demand=0,n,max1; 
int **D,*Mk, *C;
double Cf, CF1;
long M=1000000;
double   h1, a, h, speed, **Distance, fc, *f, Conversion, Em, fe, Er, Er1, L, Z, *H, *Nk, *V, *W, Pc, *P, e=0.0001, *A, *B, alfa, *CV, Unit_w=10, kilo=1000, rate_speed=3.6, *rate;

long   ****x1Ptr,*****x2Ptr, ***y3Ptr,*****y2Ptr, ***IPtr,I1Ptr, *I2Ptr, ***GPtr, ***O1Ptr,****O2Ptr, *q1Ptr, **qPtr,***qv1Ptr, ****qvPtr, U1Ptr,*U2Ptr, ***UPtr,***SVPtr, ***flow_d1Ptr,****flow_d2Ptr;
double inventory_cost=0,shortage_cost=0,inventory_emissions_cost=0, emissions_cost=0,transportation_cost=0,total_cost=0, emissions_net=0, tedade_shortage=0;
int    CounterRows = 0;
int    CPXEnv=0;
float  StartTime, EndTime;
double objval, gap_p ,slack[1];
bool key_create=false;

FILE *Input, *Output;
char FileName[100000], FileNameOut[100000];


CPXENVptr env = NULL;
CPXLPptr  lp  = NULL;
CPXFILEptr logfile;

	int	    i, j, t,k,s, z ,status, status1, counter;
	char    errmsg[1024];
	
	int		*rmatind, *rmatbeg;
	char	*sense, *coltype, **colname;
	long	constraints, nzcnt, numcols, numrows;

	double	*rhs, *rmatval, *obj, *lb, *ub, *X_Cplex;	