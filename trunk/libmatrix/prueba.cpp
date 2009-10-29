
#include "matrix_booster.h"

int main(int argc, char* argv[])
{
    matrix A,B,C;
    double tiempo;
    int m,n,o;
    switch(argc)
    {
	case 1:
		m=1000;
    		fill(&A,m);
    		fill(&B,m);
    		fill(&C,m);
		break;
	case 2:
		m=atoi(argv[1]);
    		fill(&A,m);
    		fill(&B,m);
    		fill(&C,m);
		break;
        case 4:
                m=atoi(argv[1]);
                n=atoi(argv[2]);
                o=atoi(argv[3]);
    		fill(&A,m,n);
    		fill(&B,n,o);
    		fill(&C,m,o);
		break;
        default:
                printf("Nº de argumentos erróneo\n");
                return 1;
                break;
    }
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
    printf ("La prueba del benchmar blocked ha tardado %lf segundos\n",tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        blocked_multiplymatrix_openmp(&A,&B,&C);
    }
    tiempo=end_clock();
    printf ("La prueba del benchmar blocked openmp ha tardado %lf segundos\n",tiempo);
}


