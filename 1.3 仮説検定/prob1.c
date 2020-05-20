#include <stdio.h>
#include <math.h>
#include "CALCPARA.h"
#include "NORMDIST.h"

#define DATANUM 10000
#define DATASIZE 8
#define MU 3.4
#define SIGMA2 5.0
#define ALPHA 0.01

int main() {
  //Get data
  double x[DATANUM];

  FILE *fp;
  fp = fopen("dat8_double_10000", "rb");
  fread(&x[0], DATASIZE, DATANUM, fp); //8バイトのDouble型データが10000個
  fclose(fp);

  //Calculate parameters
  double mu_bar = cal_avg(x,DATANUM);
  double test = fabs((mu_bar - MU)/(sqrt(SIGMA2 / DATANUM)));
  double z_halfAlpha = FindZvalue(ALPHA / 2.0);

  //Print
  printf("mu_bar = %lf\n",mu_bar);
  printf("test = %lf\n",test);
  printf("Z_halfAlpha = %lf\n", z_halfAlpha);
  printf("z_0.005 from https://keisan.casio.jp/exec/system/1161228880 \n = 2.575829 \n");

  return 0;
}