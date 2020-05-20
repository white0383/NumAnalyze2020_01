#include <stdio.h>
#include <math.h>
#include "CALCPARA.h"

#define DATANUM 1000
#define DATASIZE 8
#define ALPHA 0.01

//標準正規分布の累積分布関数cumuNormDist(x) cumulative normal distribution
double CumuNormDist(double x){
  return 0.5 * (1 + erf(x / sqrt(2)));
}

//標本の経験累積分布関数
double FN(double* arr, int size, double x){
  double count =0.0;

  for(int i=0;i<size;i++){
    if(arr[i] < x) count += 1.0;
  }

  return count / size;
}

double ProdTestD_func(double i, double x){
  double res = pow(-1,i-1) * exp(-2 * i * i * x * x);
  return res;
}

int main() {
  //Get data
  double x[DATANUM];

  FILE *fp;
  fp = fopen("dat11_double_1000", "rb");
  fread(&x[0], DATASIZE, DATANUM, fp); //8バイトのDouble型データが1000個
  fclose(fp);

  //Calculate parameters
  double testD = 0.0;
  for(double xd = -5.0;xd <= 5.0; xd += 0.01){
    double test = fabs(CumuNormDist(xd) - FN(x,DATANUM,xd));
    if(testD < test) testD = test;
  }
  testD = testD * sqrt(DATANUM);

  double prodTestD = 1.0;
  double prodTestD_i = 1;
  double prodTestD_step = 0;
  double eps = 1.0e-30;

  do{
    prodTestD_step = ProdTestD_func(prodTestD_i,testD);
    prodTestD_i += 1.0;
    prodTestD -= 2*prodTestD_step;
  }while(prodTestD_step > eps);

  //Print
  printf("testD = %lf\n",testD);
  printf("prodTestD = %.15lf\n",prodTestD);

  return 0;
}