#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Los parámetros al ejecutar el programa son:\n 1- nombre del archivo \n 2- rango de cantidad de números primos \n ");
        return -1;
    }

    int n = atoi(argv[1]);
    int i, j, prime, total = 0;
    // Establecer cantidad de hilos
    omp_set_num_threads(8);

#pragma omp parallel for private(i, j, prime) reduction(+ : total)
    for (i = 2; i <= n; i++)
    {
        prime = 1;
        for (j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
                prime = 0;
                break;
            }
        }
        total = total + prime;
    }

    printf("La cantidad de números primos hasta %d es: %d \n", n, total);
    return 0;
}