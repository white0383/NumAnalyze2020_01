#include <stdio.h>
#include <math.h>
#include "CALCPARA.h"

#define DATANUM 10000
#define DATASIZE 8
#define LOWER 0.0
#define UPPER 1.0
#define ALPHA 0.01
#define PK = 0.1

int main() {
  //Get data
  double x[DATANUM];

  FILE *fp;
  fp = fopen("dat10_double_10000", "rb");
  fread(&x[0], DATASIZE, DATANUM, fp); //8バイトのDouble型データが10000個
  fclose(fp);

  //Calculate parameters
  double chi_obs = 0;
  int fk[10] = {0,};
  for(int i=0;i<DATANUM;i++){
    int whereIsX = x[i] * 10;
    fk[whereIsX]++;
  }

  for(int i=0;i<10;i++){
    double Npk = 1000.0;
    chi_obs += (fk[i] - Npk)*(fk[i]-Npk)/Npk;
  }

  //Print
  for(int i=0;i<10;i++){
    printf("fk[%d] = %d\n",i,fk[i]);
  }
  printf("chi_obs = %lf \n",chi_obs);
  printf("chi2_0.01 from https://keisan.casio.jp/exec/system/1161228834\n = 23.209251\n");

  return 0;
}