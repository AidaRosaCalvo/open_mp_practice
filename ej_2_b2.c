#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

void randInit(int array[], const int n, const int bound)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        array[i] = rand() % bound;
}

double mean(int array[], const int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += array[i];
    return (double)sum / n;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Los parámetros al ejecutar el programa son:\n 1- nombre del archivo \n 2- tamaño del arreglo \n 3- cantidad de hilos \n");
        return -1;
    }

    double sum = 0.0;
    double parallel_mean = 0.0, serial_mean = 0.0;
    int i;
    double parallel_start_time, parallel_end_time, parallel_time = 0.0, serial_time = 0.0;
    clock_t serial_start_time, serial_end_time;

    int n = atoi(argv[1]);
    int nthreads = atoi(argv[2]);
    omp_set_num_threads(nthreads);
    int *array = (int *)malloc(sizeof(int) * n);
    randInit(array, n, 10);

    // Ejecución en paralelo
    parallel_start_time = omp_get_wtime();

    #pragma omp parallel for private(i) shared(array, n) schedule(static,1000) reduction(+ : sum)
    for (i = 0; i < n; i++)
    {
        sum += array[i];
    }

    parallel_mean = sum / n;

    parallel_end_time = omp_get_wtime();
    parallel_time = parallel_end_time - parallel_start_time;
    printf("Tiempo de ejecución en paralelo: %.4f\n", parallel_time);
    printf("Media en paralelo: %.2f\n", parallel_mean);

    // Ejecución en serie
    serial_start_time = clock();

    serial_mean = mean(array, n);

    serial_end_time = clock();
    serial_time += (double)(serial_end_time - serial_start_time) / CLOCKS_PER_SEC;

    printf("Tiempo de ejecución en serie: %.4f\n", serial_time);
    printf("Media en serie: %.2f\n", serial_mean);
    double speedup = serial_time/parallel_time;
    printf("speedup: %.4f\n", speedup);
    return 0;
}