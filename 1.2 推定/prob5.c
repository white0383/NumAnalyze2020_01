#include <stdio.h>
#include <math.h>
#include "NORMDIST.h"
#include "CALCPARA.h"

#define DATANUM 200
#define DATASIZE 8
#define ALPHA 0.05
#define SIGMA2 3.2

int main(int argc, char* argv[]) {

  //Get data
  double x[DATANUM];

  FILE *fp;
  fp = fopen("dat7_double_200", "rb");
  fread(&x[0], DATASIZE, DATANUM, fp); //8バイトのDouble型データが1000個
  fclose(fp);

  //Calculate confidence interval
  double mu_tilda = cal_avg(x, DATANUM); //標本平均
  double z_halfalpha = FindZvalue(ALPHA/2);
  double confidence_gap = sqrt(SIGMA2 / DATANUM) * z_halfalpha;

  double confidence_interval_upper = mu_tilda + confidence_gap;
  double confidence_interval_lower = mu_tilda - confidence_gap;

  //Print
  printf("mu_tilda = %lf\n",mu_tilda);
  printf("z_halfalpha = %lf\n",z_halfalpha);
  printf("confidence_gap = %lf\n",confidence_gap);
  printf("信頼区間 = [%lf, %lf]\n",confidence_interval_lower,confidence_interval_upper);

  return 0;
}