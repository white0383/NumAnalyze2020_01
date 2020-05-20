#include <stdio.h>

double cal_avg(double *arr, int arr_size){
  double sum = 0;
  for (int i=0;i<arr_size;i++){
    sum += arr[i];
  }
  return sum / arr_size;
}

double cal_var(double *arr, int arr_size){
  double avg = cal_avg(arr, arr_size);
  double sum = 0;
  for (int i=0;i<arr_size;i++){
    sum += (arr[i]-avg) * (arr[i]-avg);
  }
  return sum / arr_size;
}

double cal_var_unbiased(double *arr, int arr_size){
  double avg = cal_avg(arr, arr_size);
  double sum = 0;
  for (int i=0;i<arr_size;i++){
    sum += (arr[i]-avg) * (arr[i]-avg);
  }
  return sum / (arr_size - 1);
}