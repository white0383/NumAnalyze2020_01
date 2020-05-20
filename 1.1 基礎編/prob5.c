#include <stdio.h>
#include <math.h>

#define DATASIZE 8
#define DATANUM 100
#define DATADIM 2

int main()
{
  //begin=========================================
  //Step 1. Caculate covariance and correlation coef. dat3
    //Get data
    double x3[DATANUM][DATADIM]; //100*2 Array to save dat3

    FILE *fp;
    fp = fopen("dat3_double_100_dim2", "rb");
    fread(&x3[0][0], DATASIZE, DATANUM * DATADIM, fp); 
    fclose(fp);

    //Calculate
    double cov3 = 0, cor3 = 0; //dat3の共分散と相関係数

      //Calculate COVariance = E(XY)-E(X)E(Y)=E( (X-E(X)) * (Y-E(Y))
      double avg30 = 0, avg31 = 0; //avg30:　x3[][0]の平均 avg31: 同様

        //Calculate avg30, avg31
        double avg30_tmp = 0, avg31_tmp = 0;
        for(int i=0;i<DATANUM;i++){
          avg30_tmp += x3[i][0];
          avg31_tmp += x3[i][1];
        }
        avg30 = avg30_tmp / DATANUM;
        avg31 = avg31_tmp / DATANUM;

      double cov3_tmp = 0;
      for(int i=0;i<DATANUM;i++){
        double delta0 = x3[i][0] - avg30;
        double delta1 = x3[i][1] - avg31;
        cov3_tmp += delta0 * delta1;
      }
      cov3 = cov3_tmp / DATANUM;

      //Calculate CORrelation coefficient = cov / (dev(X) * dev(Y))
      double dev30 = 0, dev31 = 0; //dev30: x3[][0]の標準偏差 dev31: 同様

        //Calculate dev0, dev1
        double var30 = 0, var31 = 0; //var0: x[][0]の分散 var1: 同様
        double var30_tmp = 0,var31_tmp = 0;
        for(int i=0;i<DATANUM;i++){
          double delta0 = x3[i][0] - avg30;
          double delta1 = x3[i][1] - avg31;
          var30_tmp += delta0 * delta0;
          var31_tmp += delta1 * delta1;
        }
        var30 = var30_tmp / DATANUM;
        var31 = var31_tmp / DATANUM;
        dev30 = sqrt(var30);
        dev31 = sqrt(var31);

      cor3 = cov3 / (dev30 * dev31);
  //=========================================end

  //begin=========================================
  //Step 2. Caculate covariance and correlation coef. dat4
    //Get data
    double x4[DATANUM][DATADIM]; //100*2 Array to save dat4

    fp = fopen("dat4_double_100_dim2", "rb");
    fread(&x4[0][0], DATASIZE, DATANUM * DATADIM, fp); 
    fclose(fp);

    //Calculate
    double cov4 = 0, cor4 = 0; //dat4の共分散と相関係数

      //Calculate COVariance = E(XY)-E(X)E(Y)=E( (X-E(X)) * (Y-E(Y))
      double avg40 = 0, avg41 = 0; //avg40:　x4[][0]の平均 avg41: 同様

        //Calculate avg40, avg41
        double avg40_tmp = 0, avg41_tmp = 0;
        for(int i=0;i<DATANUM;i++){
          avg40_tmp += x4[i][0];
          avg41_tmp += x4[i][1];
        }
        avg40 = avg40_tmp / DATANUM;
        avg41 = avg41_tmp / DATANUM;

      double cov4_tmp = 0;
      for(int i=0;i<DATANUM;i++){
        double delta0 = x4[i][0] - avg40;
        double delta1 = x4[i][1] - avg41;
        cov4_tmp += delta0 * delta1;
      }
      cov4 = cov4_tmp / DATANUM;

      //Calculate CORrelation coefficient = cov / (dev(X) * dev(Y))
      double dev40 = 0, dev41 = 0; //dev40: x4[][0]の標準偏差 dev41: 同様

        //Calculate dev0, dev1
        double var40 = 0, var41 = 0; //var40: x4[][0]の分散 var41: 同様
        double var0_tmp = 0,var1_tmp = 0;
        for(int i=0;i<DATANUM;i++){
          double delta0 = x4[i][0] - avg40;
          double delta1 = x4[i][1] - avg41;
          var0_tmp += delta0 * delta0;
          var1_tmp += delta1 * delta1;
        }
        var40 = var0_tmp / DATANUM;
        var41 = var1_tmp / DATANUM;
        dev40 = sqrt(var40);
        dev41 = sqrt(var41);

      cor4 = cov4 / (dev40 * dev41);
  //=========================================end

  //begin=========================================
  //Step 3. Fit dat3, 4 into a line by Least Squares
    //資料の式(18),(19)
    double a3 = 0, b3 = 0, b3_cor3 = 0;
    double a4 = 0, b4 = 0, b4_cor4 = 0;

    a3 = cov3 / var30;
    b3 = avg31 - a3 * avg30;
    b3_cor3 = avg31 - cor3 * avg30;

    a4 = cov4 / var40;
    b4 = avg41 - a4 * avg40;
    b4_cor4 = avg41 - cor4 * avg40;

  //=========================================end

  //ファイル入出力機能を使ったらcソースコードから直接データファイルを生成できるが、
  //printfでデータをターミナルに出力し、得られた標準出力をテキストファイルに保存する.
  //出力するファイルの数が多くないため、いらない部分はコメント処理した
  //得られた .dat 形式のファイルをgnuplotを用いてプロットした
  //使ったコマンド（例）
  //$ gcc prob5.c -o app5
  //$ ./app5 > res.dat

  //begin=========================================
  //Print
    printf("# dat3_x\tdat3_y\t\tdat4_x\t\tdat4_y\n");
    for(int i=0;i<DATANUM;i++){
      printf("%f\t%f\t%f\t%f\n",x3[i][0],x3[i][1],x4[i][0],x4[i][1]);
    }

    printf("# cov3 = %f\n", cov3);
    printf("# cor3 = %f\n", cor3);
    printf("# cov4 = %f\n", cov4);
    printf("# cor4 = %f\n", cor4);

    printf("# a3 = %f\n", a3);
    printf("# b3 = %f\n", b3);
    printf("# a4 = %f\n", a4);
    printf("# b4 = %f\n", b4);

    printf("# b3_cor3 = %f\n", b3_cor3);
    printf("# b4_cor4 = %f\n", b4_cor4);

  //=========================================end

  return 0;
}