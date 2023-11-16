#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

/* Función que imprime una matriz m de rows filas y cols columnas */
void print_matrix(int **m, int rows, int cols)
{
    printf("Matriz:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
}

/* Función que genera un número double aleatorio entre min y max */
int aleatorioInt(int min, int max)
{
    int numeroAleatorio = rand() % (max - min + 1) + min;
    return numeroAleatorio;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Los parámetros al ejecutar el programa son:\n 1- nombre del archivo \n 2- cantidad de filas de la matriz \n 3- cantidad de columnas de la matriz \n");
        return -1;
    }

    int smallest, largest;
    int i, j;
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int **matrix = malloc(sizeof(int *) * rows);
    for (i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * cols);
    }
    // Inicializar matriz con núemros enteros aleatorios
    srand(time(NULL));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = aleatorioInt(1, 100);
        }
    }
    print_matrix(matrix, rows, cols);

    // Establecer la cantidad de hilos
    omp_set_num_threads(8);
    // Establecer como mínimo y máximo inicial al primer elemento de la matriz
    smallest = matrix[0][0];
    largest = matrix[0][0];

#pragma omp parallel for private(i, j) reduction(min : smallest) reduction(max : largest)
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (matrix[i][j] < smallest)
            {
                smallest = matrix[i][j];
            }
            if (matrix[i][j] > largest)
            {
                largest = matrix[i][j];
            }
        }
    }
    printf("Menor elemento de la matriz: %d\n", smallest);
    printf("Mayor elemento de la matriz: %d\n", largest);

    free(matrix);
    return 0;
}