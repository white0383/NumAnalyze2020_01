#include <stdio.h>

int main() {
    double z[100][2];
    FILE *fp;

    fp = fopen("dat3_double_100_dim2", "rb");

    fread(&z[0][0],8,200,fp); // 8비트인 더블이 1000개

    fclose(fp);

    for(int i = 0;i<200;i++){
        int a = i%100;
        int b = i/100;
        double d = z[a][b];
        printf("z[%d][%d] = %f\n", a,b,d);
    }

    return 0;
}