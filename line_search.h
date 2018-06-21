#ifndef __LINE_SEARCH__
#define __LINE_SEARCH__

//beta 在(0,1)
#define ARMIJO_BEAT 0.9
//sigma 在(0,0.5)
#define ARMIJO_SIGMA 0.3

//sigma 在(0,0.5)
#define ARMIJO_MAX_TEST_M 20


//采用Armijo线搜索确定步长 ak
double armijo_func(double *x,double *dk,double beta,double sigma);


#endif