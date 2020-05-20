#include <stdio.h>
#include <math.h>
#include "TSTUDENT.h"
#include "CALCPARA.h"

#define DATANUM 101
#define DATASIZE 8
#define ALPHA 0.05

int main() {
  //Get data
  double x[DATANUM];

  FILE *fp;
  fp = fopen("dat6_double_101", "rb");
  fread(&x[0], DATASIZE, DATANUM, fp); //8バイトのDouble型データが1000個
  fclose(fp);

  //Calculate confidence interval
  double mu_tilda = cal_avg(x, DATANUM); //標本平均
  double sigma2_tilda = cal_var_unbiased(x, DATANUM); //不偏分散
  double t_halfalpha_n = FindTvalue(DATANUM-1, ALPHA/2);
  double confidence_gap = sqrt(sigma2_tilda / DATANUM) * t_halfalpha_n;

  double confidence_interval_upper = mu_tilda + confidence_gap;
  double confidence_interval_lower = mu_tilda - confidence_gap;

  //Print
  printf("mu_tilda = %lf\n",mu_tilda);
  printf("sigma2_tilda = %lf\n",sigma2_tilda);
  printf("t_halfalpha_n = %lf\n",t_halfalpha_n);
  printf("confidence_gap = %lf\n",confidence_gap);
  printf("信頼区間 = [%lf, %lf]\n",confidence_interval_lower,confidence_interval_upper);

  return 0;
}