#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

//z_alpha(n)の値を小数点の下6桁まで数値計算を用いて計算する
//TSTUDENT.h の確率密度関数だけ正規分布にした

//標準正規分布の確率密度関数p(x)を返す
//xはパーセント点である
double CalcNormalDensity(double x){
  double numerator = exp(-(x*x)/2);
  double denominator = sqrt(M_PI * 2);
  return numerator / denominator;
}

//xから+無限大までp(t)を定積分した値を数値計算で計算して返す。
//台形法を利用して定積分の値を近似する。
//ステップサイズは要求される精度(下6桁)を考えて1e-6とする
//t分布の確率密度関数はnによらずtが正の時単調減少するため,
//p(t)<epsだったらそれ以上は足しても結果に与える影響が少ないため計算を停止する。 
//epsは1e-9とする。
double CalcNormalIntegral(double x){
  double stepSize = 0.000001;
  double eps = 0.000000001;
  double sum = 0; //積分の結果
  double y_prev = CalcNormalDensity(x);
  double y_now = 0;
  double x_prev = x;
  double x_now = 0;

  while(y_prev > eps){
    x_now = x_prev + stepSize;
    y_now = CalcNormalDensity(x_now);
    double area = stepSize * (y_prev + y_now) / 2;
    sum += area;
    y_prev = y_now;
    x_prev = x_now;
  }

  return sum;
}

//標準正規分布の確率密度関数をxから+無限大まで定積分した値が
//alphaとなるxを見つける関数.
//バイナリツリーを利用したらより高速に計算できるが、
//そうするとコードが読みにくくなる。
//という訳で、結果を10進数で考える。
//以下はFindZvalueのアルゴリズムである。
//Step1.  0から1ずつxを大きくし、CalcNormalIntegral(n,x)が
//        alphaを超えるとx-1を次のステップに渡す。
//        前のステップから渡されたx-1をx_0とする。
//        * x_iの’i’は「下i桁まで計算済み」という意味である。
//        * 下0桁という言葉は使わないが、ここでは上1桁を意味する。
//Step2.  x_0を0.1ずつ大きくし, CalcNormalIntegral(n,x_0が)
//        alphaを超えるとx_0-1をx_1として次のステップに渡す。
//Step3.  Step2.　をx_7が分かるまで繰り返す.
//Output. x_7
//最悪の場合80回(上1桁〜下7桁 * 0~9)CalcNormalntegralを実行する。
//結果を下7桁で四捨五入して下6桁までを使用する

double FindZvalue(double alpha){
  //確率密度関数の性質より
  if(alpha > 0.5) return -1 * FindZvalue(1-alpha);

  double x[8] = {0};

  for(int i=0;i<8;i++){
    bool isFinished = false;
    double stepSize = pow(10,-i);

    do{
      if(CalcNormalIntegral(x[i]) > alpha) {
        x[i] += stepSize;
      } else {
        x[i] -= stepSize;
        if(i != 7) x[i+1] = x[i];
        isFinished = true;
      }
    } while(!isFinished);
  }

  return x[7];
}