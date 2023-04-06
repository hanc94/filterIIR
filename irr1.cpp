#include "mex.h"
//Implementación de la estructura directa de filtros IIR
double iir1(double xn,double *x,double *y,double *b,double *a,int p){

	int i;
	double yn;
	yn=0.0;

	x[0]=xn;
//Ciclo de la parte no recursiva
	for(i=(p-1);i>=0;i--)
	{
		yn+=b[i]*x[i];
		x[i]=x[i-1];
	}

//Ciclo de la parte recursiva
	for(i=(p-1);i>=1;i--)
	{
		yn-=a[i]*y[i];
		y[i]=y[i-1];
	}

	yn=yn/a[0];

	y[1]=yn;

	return yn;

}

void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]){
	double *xn,*y,*b,*a;
	int p,nx;
	if(nrhs!=3) {
		mexErrMsgIdAndTxt("irr1:nrhs","Se requieren dos entradas.");
	}
/*Verifica que haya un argumento de salida*/
	if(nlhs!=1) {
		mexErrMsgIdAndTxt("irr1:nlhs","Se requiere una salida");
	}
	p=mxGetN(prhs[0]);
	xn=mxGetPr(prhs[2]);
	nx=mxGetM(prhs[2]);
	b=mxGetPr(prhs[0]);
	a=mxGetPr(prhs[1]);
/* Crea la matriz de salida */
	plhs[0] = mxCreateDoubleMatrix((mwSize)nx,1,mxREAL);
/* Puntero a la matriz de salida */
	y = mxGetPr(plhs[0]);
	double x[nx];
	double yn[nx]={0};
	
	for (int i=0;i<nx;i++){
		y[i]=iir1(xn[i],x,yn,b,a,p);
	}
}
