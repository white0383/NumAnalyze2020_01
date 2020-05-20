#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <memory.h>
#include "MT.h"
#include "CALCPARA.h"

#define DATANUM 1000000
#define MU 3.7
#define SIGMA2 2.5

int main(void){
  init_genrand((unsigned)time(NULL)); //現在時間をシードにする

  //Generate random number (Only use z1)
  //Box-Muller法を用いた標準正規分布N(0,1)を作り,
  //N(0,1) * sigma + mu = N(mu,sigma^2)の変換を利用して
  //N(3.7, 2.5)に従う乱数を生成する
  static double z1[DATANUM];

  for (int i = 0; i < DATANUM; i++){
    //Make Z1 ~ N(0,1)
    double x = genrand_real1(); //メルセンヌ・ツイスタを使って一応乱数を生成する
    double y = genrand_real1();
    z1[i] = sqrt(-2 * log(x)) * cos(2 * M_PI * y);

    //Transform Z1 to N(3.7,2.5)   
    z1[i] = z1[i] * sqrt(SIGMA2) + MU;
  }

  //Calculate average and variance of z1(population)
  double mu = cal_avg(z1, DATANUM);
  double sigma2 = cal_var(z1, DATANUM);

  //Calculate average, variance, unbiased variance of each set 
  //and Save them in array sized 100,000
  static double z1_avg[DATANUM/10], z1_var[DATANUM/10], z1_var_unbiased[DATANUM/10];

  for (int i=0; i<DATANUM / 10;i++){
    double set[10];
    memcpy(set, z1+i*10, sizeof(double) * 10); //z1[i*10]からz1[i*10 + 10]までをset[]にコピー
    z1_avg[i] = cal_avg(set, 10);
    z1_var[i] = cal_var(set, 10);
    z1_var_unbiased[i] = cal_var_unbiased(set, 10);
  }

  //Calculate average of each of 3 arrays that has statistics value
  double mu_tilda = cal_avg(z1_avg, DATANUM / 10);
  double sigma2_tilda = cal_avg(z1_var, DATANUM / 10);
  double sigma2_unbiased_tilda = cal_avg(z1_var_unbiased, DATANUM / 10);

  //Print
  printf("mu\t: %lf\n",mu);
  printf("sgm2\t: %lf\n\n",sigma2);
  printf("mu_t\t: %lf\n",mu_tilda);
  printf("sgm2_t\t: %lf\n",sigma2_tilda);
  printf("sgm2_u_t\t: %lf\n",sigma2_unbiased_tilda);

  return 0;
}