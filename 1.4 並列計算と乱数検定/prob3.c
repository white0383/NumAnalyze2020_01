#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "CALCPARA.h"
#include "MT.h"

#define DATANUM 100000
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
  double starttime = omp_get_wtime();
  //再現性のためシード設定
  init_genrand(20200520); 

  //Generate random number
  double z1[DATANUM], z2[DATANUM]; //Box-Muller法を用いた標準正規分布に従う乱数

  for (int i = 0; i < DATANUM; i++){
    double x = genrand_real1(); //メルセンヌ・ツイスタを使って一応乱数を生成する
    double y = genrand_real1();
    z1[i] = sqrt(-2 * log(x)) * cos(2 * M_PI * y);
    z2[i] = sqrt(-2 * log(x)) * sin(2 * M_PI * y);
  }

  //Calculate parameters
  double testD = 0.0;
  double loopStartTime = omp_get_wtime();
  for(double xd = -5.0;xd <= 5.0; xd += 0.01){
    double test = fabs(CumuNormDist(xd) - FN(z1,DATANUM,xd));
    if(testD < test) testD = test;
  }
  printf("for Loop with single threading : %lf\n",omp_get_wtime() - loopStartTime);
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
  printf("time spend = %lf\n",omp_get_wtime() - starttime);

  return 0;
}