
#include "matrix_booster.hpp"



int main(int argc, char* argv[])
{
    int m,n,o,p,q,r;
    /*switch(argc)
    {
	case 1:
		m=1000;
                n=m;
                o=m;
                p=m;
                q=m;
                r=m;      
		break;
	case 2:
		m=atoi(argv[1]);
                n=m;
                o=m;
                p=m;
                q=m;
                r=m;
		break;
        case 4:
                m=atoi(argv[1]);
                n=atoi(argv[2]);
                p=atoi(argv[3]);
                o=n;
                q=m;
                r=p;
		break;
        case 7:
                m=atoi(argv[1]);
                n=atoi(argv[2]);
                p=atoi(argv[3]);
                o=n;
                q=m;
                r=p;
		break;

        default:
                printf("Nº de argumentos erróneo\n");
                return 1;
                break;
    }*/
    int test_sizes[] = {
        31, 32, 96, 97, 127, 128, 129, 191, 192, 229, 255, 256, 257,
        319, 320, 321, 417, 479, 480, 511, 512, 639, 640, 767, 768, 769, 1000,
    };
    int tamano;
    for(int i=0;i<sizeof(test_sizes)/sizeof(test_sizes[0]);i++)
    {
            tamano=test_sizes[i];   
            prueba_int(tamano);
            prueba_float(tamano);
            prueba_double(tamano);
    }
}


