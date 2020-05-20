#include <stdio.h>

int main() {
    double x[1000];
    FILE *fp;

    fp = fopen("dat1_double_1000", "rb");

    fread(&x[0],8,1000,fp); // 8비트인 더블이 1000개

    fclose(fp);

    for(int i =0;i<1000;i++){
        printf("x[%d] = %f\n", i,x[i]);
    }

    return 0;
}