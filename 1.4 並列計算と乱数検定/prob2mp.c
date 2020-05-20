#include <stdio.h>
#include "MT.h"
#include <omp.h>
#include <math.h>

double fac(double n){
  if (n == 0 || n == 1) return 1;
  else return n * fac(n-1);
}

int main() {
  //再現のためシードを設定
  init_genrand(20200520);

  //乱数列を生成
  //0と1からなる100万ビットの乱数を生成するために
  //32ビットの一様乱数をメルセンヌツイスター法を用いて31250個生成する
  int x[31250] = {0};
  for(int i=0;i<31250;i++){
    x[i] = genrand_int32();
  }

  //各事件の出現回数
  //fk[i]は長さ16の各セットに1がi回出た回数
  int fk[17] = {0};

  double starttimeMulti = omp_get_wtime();

  //100万ビットを16ビットを1セットとして分けて考える
  //count : 各セットに入っている1を数える
  int count = 0;
    #pragma omp parallel for private(count)
    for(int i=0;i<31250;i++)
    {
      count = 0;
      for(int j=0;j<16;j++){
        if(x[i] & 1) count ++;
        x[i] = x[i] >> 1;
      }
      #pragma omp critical
      {
      fk[count]++;
      }

      count = 0;
      for(int j=0;j<16;j++){
        if(x[i] & 1) count ++;
        x[i] = x[i] >> 1;
      }
      #pragma omp critical
      {
      fk[count]++;
      }
    }

  double timespendMulti = omp_get_wtime() - starttimeMulti;

  printf("Multi thread : %lf s spend\n",timespendMulti);
  int sumMulti = 0;
  for(int i=0;i<17;i++){
    printf("fkMulti[%d] = %d\n",i,fk[i]);
    sumMulti += fk[i];
  }
  printf("sum = %d\n",sumMulti);

  double chiobs = 0;
  for(int i=0;i<17;i++){
    double f = fk[i];
    //pk = 16 C i / 2 ^ 16
    double pk = fac(16.0) / (fac((double)i) * fac(16.0 - (double)i) * pow(2,16));
    double npk = 62500.0 * pk;

    printf("i:%d npk = %lf\n",i,npk);

    chiobs += (f - npk) * (f - npk) / npk;
  }

  printf("chiobs = %.10lf\n",chiobs);
    printf("%lf s spend for whole work \n",omp_get_wtime()-starttimeMulti);

  return 0;
}