#include <stdio.h>
#include <math.h>
#include <memory.h>

#define DATASIZE 8
#define DATANUM 1000
#define PARA_H 10

int main()
{
  //Get data
  double x[DATANUM];

  FILE *fp;
  fp = fopen("dat5_double_1000", "rb");
  fread(&x[0], DATASIZE, DATANUM, fp); 
  fclose(fp);

  double x0[DATANUM - PARA_H], x1[DATANUM - PARA_H];
  memcpy(x0, x, sizeof(x) - PARA_H * sizeof(double)); 
  memcpy(x1, x+PARA_H, sizeof(x) - PARA_H * sizeof(double)); 

  //Calculate
  double cov = 0, cor = 0; //共分散 相関係数=自己相関

    //Calculate COVariance = E(XY)-E(X)E(Y)=E( (X-E(X)) * (Y-E(Y))
    double avg0 = 0, avg1 = 0; //avg0: x0[]の平均 avg1: 同様

      //Calculate avg0, avg1
      double avg0_tmp = 0, avg1_tmp = 0;
      for(int i=0;i<DATANUM-PARA_H;i++){
        avg0_tmp += x0[i];
        avg1_tmp += x1[i];
      }
      avg0 = avg0_tmp / (DATANUM-PARA_H);
      avg1 = avg1_tmp / (DATANUM-PARA_H);
    
    double cov_tmp = 0;
    for(int i=0;i<DATANUM-PARA_H;i++){
      double delta0 = x0[i] - avg0;
      double delta1 = x1[i] - avg1;
      cov_tmp += delta0 * delta1;
    }
    cov = cov_tmp / (DATANUM-PARA_H);

    //Calculate CORrelation coefficient = cov / (dev(X) * dev(Y))
    double dev0 = 0, dev1 = 0; //dev0: x0[]の標準偏差 dev1: 同様

      //Calculate dev0, dev1
      double var0 = 0, var1 = 0; //var0: x0[]の分散 var1: 同様
      double var0_tmp = 0,var1_tmp = 0;
      for(int i=0;i<DATANUM-PARA_H;i++){
        double delta0 = x0[i] - avg0;
        double delta1 = x1[i] - avg1;
        var0_tmp += delta0 * delta0;
        var1_tmp += delta1 * delta1;
      }
      var0 = var0_tmp / (DATANUM-PARA_H);
      var1 = var1_tmp / (DATANUM-PARA_H);
      dev0 = sqrt(var0);
      dev1 = sqrt(var1);

    cor = cov / (dev0 * dev1);

  //Print
  printf("cov = %f\n",cov);
  printf("cor = %f\n",cor);

  return 0;
}