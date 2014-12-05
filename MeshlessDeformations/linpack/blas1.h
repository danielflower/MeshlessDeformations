double d_abs ( double x );
double d_max ( double x, double y );
double d_sign ( double x );
double dasum ( int n, double x[], int incx );
void daxpy ( int n, double da, double dx[], int incx, double dy[], int incy );
void dcopy ( int n, double dx[], int incx, double dy[], int incy );
double ddot ( int n, double dx[], int incx, double dy[], int incy );
double dmach ( int job );
double dnrm2 ( int n, double x[], int incx );
void drot ( int n, double x[], int incx, double y[], int incy, double c, 
  double s );
void drotg ( double *sa, double *sb, double *c, double *s );
void dscal ( int n, double sa, double x[], int incx );
void dswap ( int n, double x[], int incx, double y[], int incy );
int i_max ( int i1, int i2 );
int i_min ( int i1, int i2 );
int idamax ( int n, double dx[], int incx );
bool lsame ( char ca, char cb );
void xerbla ( char *srname, int info );
