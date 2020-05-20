#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <memory.h>
#include "MT.h"
#include "CALCPARA.h"

#define DATANUM 1000000
#define BOT 2
#define TOP 4

int main(void){
  init_genrand((unsigned)time(NULL)); //現在時間をシードにする

  //Generate random number (Only use x)
  
  static double x[DATANUM];

  for (int i = 0; i < DATANUM; i++){
    //Make X ~ U[2,4]
    double u = genrand_real1(); //メルセンヌ・ツイスタを使って一応乱数を生成する
    x[i] = u * (TOP - BOT) + BOT;
  }

  //Calculate average and variance of x(population)
  double mu = cal_avg(x, DATANUM);
  double sigma2 = cal_var(x, DATANUM);

  //Calculate average, variance, unbiased variance of each set 
  //and Save them in array sized 100,000
  static double x_avg[DATANUM/10], x_var[DATANUM/10], x_var_unbiased[DATANUM/10];

  for (int i=0; i<DATANUM / 10;i++){
    double set[10];
    memcpy(set, x+i*10, sizeof(double) * 10); //x[i*10]からx[i*10 + 10]までをset[]にコピー
    x_avg[i] = cal_avg(set, 10);
    x_var[i] = cal_var(set, 10);
    x_var_unbiased[i] = cal_var_unbiased(set, 10);
  }

  //Calculate average of each of 3 arrays that has statistics value
  double mu_tilda = cal_avg(x_avg, DATANUM / 10);
  double sigma2_tilda = cal_avg(x_var, DATANUM / 10);
  double sigma2_unbiased_tilda = cal_avg(x_var_unbiased, DATANUM / 10);

  //Print
  printf("mu\t: %lf\n",mu);
  printf("sgm2\t: %lf\n\n",sigma2);
  printf("mu_t\t: %lf\n",mu_tilda);
  printf("sgm2_t\t: %lf\n",sigma2_tilda);
  printf("sgm2_u_t\t: %lf\n",sigma2_unbiased_tilda);

  return 0;
}