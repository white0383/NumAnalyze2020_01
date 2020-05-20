#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#define DATASIZE 4
#define DATANUM 1000

int compare (const void *a, const void *b){
  double num1 = *(double *)a;
  double num2 = *(double *)b;

  if (num1 < num2) return -1;

  if (num1 > num2) return 1;

  return 0;
}

int main()
{
  //Get data
  int x[DATANUM];

  FILE *fp;
  fp = fopen("dat2_int_1000", "rb");
  fread(&x[0], DATASIZE, DATANUM, fp); //8バイトのDouble型データが1000個
  fclose(fp);

  //Copy int array into double array
  double xd[DATANUM];
  for(int i=0;i<DATANUM;i++){
    xd[i] = (double)x[i];
  }

  //Calculate
  double avg = 0, med = 0, var = 0, dev = 0; //平均 中央値 分散 標準偏差

    //Calculate AVerGe
    double avg_tmp = 0;
    for (int i = 0; i < DATANUM; i++) {
      avg_tmp += xd[i];
    }
    avg = avg_tmp / DATANUM;

    //Calculate MEDian
    double xd_copy[DATANUM]; //Make copy of x[]
    memcpy(xd_copy, xd, sizeof(xd)); 
    qsort(xd_copy, sizeof(xd_copy) / sizeof(double), sizeof(double), compare); // sort x[]
    med = (xd_copy[499] + xd_copy[500])/2.0;

    //Calculate VARiance
    double var_tmp = 0;
    for (int i = 0; i < DATANUM; i++) {
      var_tmp += pow(xd[i]-avg,2);
    }
    var = var_tmp / DATANUM;

    //Calculate standard DEViation
    dev = sqrt(var);

  //Print

  printf("avg = %f\n",avg);
  printf("med = %f\n",med);
  printf("var = %f\n",var);
  printf("dev = %f\n",dev);
  return 0;
}