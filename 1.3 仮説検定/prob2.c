#include <stdio.h>
#include <math.h>
#include "CALCPARA.h"
#include "TSTUDENT.h"

#define DATANUM 101
#define DATASIZE 8
#define MU -2.8
#define ALPHA 0.01

int main() {
  //Get data
  double x[DATANUM];

  FILE *fp;
  fp = fopen("dat9_double_101", "rb");
  fread(&x[0], DATASIZE, DATANUM, fp); //8バイトのDouble型データが101個
  fclose(fp);

  //Calculate parameters
  double mu_bar = cal_avg(x,DATANUM);
  double s2 = cal_var_unbiased(x, DATANUM);
  double t_100_halfAlpha = FindTvalue(DATANUM-1, ALPHA /2);
  double test = (mu_bar - MU)/(sqrt(s2 / DATANUM));

  //Print
  printf("mu_bar = %lf\n",mu_bar);
  printf("test = %lf\n",test);
  printf("t_100_halfAlpha = %lf\n", t_100_halfAlpha);
  printf("t_0.005(100) from https://keisan.casio.jp/exec/system/1161228824 \n = 2.625890 \n");

  return 0;
}