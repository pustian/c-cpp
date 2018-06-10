#include<stdio.h>
void matrix_add(double a[][3], size_t a_row, double b[][3], size_t b_row) {
    int i=0;
    for(i =0; i<2; i++) {
        int j= 0;
        for(j=0; j<3; j++) {
            // double tmp = a[i][j] + b[i][j];
            // printf("%4.2f %4.2f %4.2f\t", a[i][j], b[i][j], tmp);
            a[i][j] += b[i][j];
        }
        putchar('\n');
    }
}
int main() {
    double maxtix_a[2][3] ={
        {1.0, 2.0, 3.0},
        {11.1, 12.3, 13.4},
        };
    double maxtix_b[2][3] ={
        {6.0, 5.0, 9.0},
        {61.1, 32.3, 43.4},
        };
    puts("matrix_a");
    int i=0;
    for(i =0; i<2; i++) {
        int j= 0;
        for(j=0; j<3; j++) {
            printf("%6.2f ", maxtix_a[i][j]);
        }
        putchar('\n');
    }
    puts("matrix_b");
    for(i =0; i<2; i++) {
        int j= 0;
        for(j=0; j<3; j++) {
            printf("%6.2f ", maxtix_b[i][j]);
        }
        putchar('\n');
    }
    matrix_add(maxtix_a, 2, maxtix_b, 2);
    puts("matrix_a after add");
    for(i =0; i<2; i++) {
        int j= 0;
        for(j=0; j<3; j++) {
            printf("%6.2f ", maxtix_a[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
    return 0;
}
