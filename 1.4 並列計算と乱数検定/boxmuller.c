#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "MT.h"

#define DATANUM 100000
#define XMIN -5
#define XMAX 5
#define STEP 0.1

/**
 * Make standard normal distribution using Box-Muller transform
 */

int main(void){
  init_genrand((unsigned)time(NULL)); //現在時間をシードにする

  //Generate random number
  double z1[DATANUM], z2[DATANUM]; //Box-Muller法を用いた標準正規分布に従う乱数

  for (int i = 0; i < DATANUM; i++){
    double x = genrand_real1(); //メルセンヌ・ツイスタを使って一応乱数を生成する
    double y = genrand_real1();
    z1[i] = sqrt(-2 * log(x)) * cos(2 * M_PI * y);
    z2[i] = sqrt(-2 * log(x)) * sin(2 * M_PI * y);
  }

  //Make frequency array h1, h2
  //h1[]にはz1の度数を記録し, h2[]ににはz2の度数を記録する
  //XMINからXMAXまでをSTEPの間隔で数え上げる
  //標準正規分布N(0,1)の場合、絶対値がXMIN(ここでは5)以上の値が出る確率が非常に低い(6.0 * 10^-6)ため、
  //絶対値が5以上の場合は-5か5で扱う

  int *h1, *h2; 
  int steps = (XMAX - XMIN) / STEP;

    //Allocate memory of array Initiate it 0
    if (((h1 = malloc(sizeof(int) * steps)) == NULL) || ((h2 = malloc(sizeof(int) * steps)) == NULL)){
      printf("メモリが確保できませんでした(h1 or h2)\n");
      exit(1);
    }
    for (int i = 0; i<steps;i++) {
      h1[i] = 0;
      h2[i] = 0;
    }
  
  for (int i = 0; i < DATANUM; i++){
    //judge Z1
    int h_step = z1[i] * (XMAX - XMIN) + (XMAX - XMIN) / STEP / 2;
    if (z1[i] < XMIN) h1[0]++ ;
    else if (z1[i] >= XMAX) h1[steps-1]++ ;
    else h1[h_step]++;
    //judge Z2
    h_step = z2[i] * 10 + 50;
    if (z2[i] < XMIN) h2[0]++ ;
    else if (z2[i] >= XMAX) h2[steps-1]++ ;
    else h2[h_step]++;
  }

  //Make Cumlative frequency array ch1, ch2
  int *ch1, *ch2; 

    //Allocate memory of array and Initiate it 0
    if (((ch1 = malloc(sizeof(int) * steps)) == NULL) || ((ch2 = malloc(sizeof(int) * steps)) == NULL)){
      printf("メモリが確保できませんでした(h1 or h2)\n");
      exit(1);
    }
    for (int i = 0; i<steps;i++) {
      ch1[i] = 0;
      ch2[i] = 0;
    }
  
  ch1[0] = h1[0];
  ch2[0] = h2[0];

  for(int i=1;i<steps;i++){
    ch1[i] = ch1[i-1] + h1[i];
    ch2[i] = ch2[i-1] + h2[i];
  }

  //Print
  printf("#range\tz1\tz2\tz1cu\tz2cu\n");
  for (int i = 0; i < steps; i++){
    double d = (i / 10.0) - 5.0;
    double h1i_rela = (double)h1[i] / DATANUM / STEP;
    double h2i_rela = (double)h2[i] / DATANUM / STEP;
    double ch1i_rela = (double)ch1[i] / DATANUM;
    double ch2i_rela = (double)ch2[i] / DATANUM;
    printf("%.1lf\t%lf\t%lf\t%lf\t%lf\n",d,h1i_rela,h2i_rela,ch1i_rela,ch2i_rela);
  }

  //Free histogram array
  free(h1);
  free(h2);
  free(ch1);
  free(ch2);

  return 0;
}