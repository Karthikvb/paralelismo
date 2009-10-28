
#include "matrix_booster.h"

int main(int argc, char* argv[])
{
    matrix A,B,C;
    double tiempo;
    int n=atoi(argv[1]);
    fill(&A,n);
    fill(&B,n);
    fill(&C,n);
    start_clock();
    for (int j=0;j<1;j++)
    {
        naive_multiplymatrix(&A,&B,&C);
    }
    tiempo=end_clock();
    printf ("La prueba del benchmar naive ha tardado %lf segundos\n",tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        naive_multiplymatrix_openmp (&A,&B,&C);
    }
    tiempo=end_clock();
    printf ("La prueba del benchmar naive openmp ha tardado %lf segundos\n",tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        blocked_multiplymatrix(&A,&B,&C);
    }
    tiempo=end_clock();
    printf ("La prueba del benchmar blocked openmp ha tardado %lf segundos\n",tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        blocked_multiplymatrix_openmp(&A,&B,&C);
    }
    tiempo=end_clock();
    printf ("La prueba del benchmar blocked openmp ha tardado %lf segundos\n",tiempo);
}


