#include <stdio.h>
#include <math.h>

double normdist(double x, double sigma, double mu){
    double twopi = 8.0 * atan(1.0);
    return (1.0 / (sigma * sqrt(twopi))) *
    exp(-(x - mu)*(x - mu) / (2.0 * sigma * sigma));
}
int main(){
    double nd[100], ndcum[100];
    double start = -5.0;
    double step = 0.1;

    double sigma = 1.0;
    double mu = 0.0;

    for(int i=0;i<100;i++){
        nd[i] = normdist(start + step * i, sigma, mu);
        if (i == 0){
            ndcum[i] = nd[0] / 10.0;
        } else {
            ndcum[i] = ndcum[i-1] + nd[i] / 10.0;
        }
    }

    printf("# x \t norm \t cumu\n");
    for(int i = 0;i<100;i++){
        double d = start + step * i;
        printf("%.1lf\t%lf\t%lf\n",d,nd[i],ndcum[i]);
    }

    return 0;
}