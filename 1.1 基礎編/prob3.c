#include <stdio.h>
#include <math.h>

#define DATASIZE 8
#define DATANUM 100
#define DATADIM 2

int main()
{
  //Get data
  double x[DATANUM][DATADIM];

  FILE *fp;
  fp = fopen("dat3_double_100_dim2", "rb");
  fread(&x[0][0], DATASIZE, DATANUM * DATADIM, fp); 
  fclose(fp);

  //Calculate
  double cov = 0, cor = 0; //共分散 相関係数

    //Calculate COVariance = E(XY)-E(X)E(Y)=E( (X-E(X)) * (Y-E(Y))
    double avg0 = 0, avg1 = 0; //avg0:　x[][0]の平均 avg1: 同様

      //Calculate avg0, avg1
      double avg0_tmp = 0, avg1_tmp = 0;
      for(int i=0;i<DATANUM;i++){
        avg0_tmp += x[i][0];
        avg1_tmp += x[i][1];
      }
      avg0 = avg0_tmp / DATANUM;
      avg1 = avg1_tmp / DATANUM;
    
    double cov_tmp = 0;
    for(int i=0;i<DATANUM;i++){
      double delta0 = x[i][0] - avg0;
      double delta1 = x[i][1] - avg1;
      cov_tmp += delta0 * delta1;
    }
    cov = cov_tmp / DATANUM;

    //Calculate CORrelation coefficient = cov / (dev(X) * dev(Y))
    double dev0 = 0, dev1 = 0; //dev0: x[][0]の標準偏差 dev1: 同様

      //Calculate dev0, dev1
      double var0 = 0, var1 = 0; //var0: x[][0]の分散 var1: 同様
      double var0_tmp = 0,var1_tmp = 0;
      for(int i=0;i<DATANUM;i++){
        double delta0 = x[i][0] - avg0;
        double delta1 = x[i][1] - avg1;
        var0_tmp += delta0 * delta0;
        var1_tmp += delta1 * delta1;
      }
      var0 = var0_tmp / DATANUM;
      var1 = var1_tmp / DATANUM;
      dev0 = sqrt(var0);
      dev1 = sqrt(var1);

    cor = cov / (dev0 * dev1);

  //Print
  printf("cov = %f\n",cov);
  printf("cor = %f\n",cor);
  return 0;
}