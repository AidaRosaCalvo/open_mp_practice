#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

/* Código secuencial que implementa el producto de una matriz B de dimensión
   N x N por un vector c de dimension N */
void prodmv(double *a, double *c, double **B, int N)
{
    int i, j;
    double sum;
    for (i = 0; i < N; i++)
    {
        sum = 0;
        for (j = 0; j < N; j++)
            sum += B[i][j] * c[j];
        a[i] = sum;
    }
}

/* Función que imprime una matriz m de tamaño N */
void print_matrix(double **m, int N)
{
    printf("Matriz:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%.1f\t", m[i][j]);
        }
        printf("\n");
    }
}

/* Función que imprime un vector v de tamaño N */
void print_vector(double *v, int N)
{
    printf("Vector:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%.1f\t", v[i]);
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Los parámetros al ejecutar el programa son:\n 1- nombre del archivo \n 2- tamaño de la matriz cuadrada \n ");
        return -1;
    }

    int i, j, N;
    double sum;
    N = atoi(argv[1]);
    // Reservar memoria de forma dinámica para los vectores
    double *a = malloc(sizeof(double) * N);
    double *c = malloc(sizeof(double) * N);
    double **B = malloc(sizeof(double *) * N);
    for (i = 0; i < N; i++)
    {
        B[i] = (double *)malloc(sizeof(double) * N);
    }
    double parallel_start_time, parallel_end_time, parallel_time = 0.0, serial_time = 0.0;
    clock_t serial_start_time, serial_end_time;
    // Establecer la cantidad de hilos
    omp_set_num_threads(8);
    // Inicializar el vector c y la matriz B con valores aleatorios entre 0 y 10
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        c[i] = rand() % 10;
        for (int j = 0; j < N; j++)
        {
            B[i][j] = rand() % 10;
        }
    }
    // print_matrix(B,N);
    // print_vector(c,N);

    // Ejecución en paralelo
    parallel_start_time = omp_get_wtime();
#pragma omp parallel for private(i, j, sum)
    for (i = 0; i < N; i++)
    {
        sum = 0;
        for (j = 0; j < N; j++)
        {
            sum += B[i][j] * c[j];
        }
        a[i] = sum;
    }
    parallel_end_time = omp_get_wtime();
    parallel_time = parallel_end_time - parallel_start_time;
    printf("Tiempo de ejecución en paralelo: %.4f\n", parallel_time);
    // print_vector(a,N);

    // Ejecución en serie
    double *as = malloc(sizeof(double) * N);
    serial_start_time = clock();
    prodmv(as, c, B, N);
    serial_end_time = clock();
    serial_time += (double)(serial_end_time - serial_start_time) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución en serie: %.4f\n", serial_time);
    // print_vector(as,N);
    double speedup = serial_time/parallel_time;
    printf("speedup: %.4f\n", speedup);

    free(a);
    free(as);
    free(B);
    free(c);
    return 0;
}