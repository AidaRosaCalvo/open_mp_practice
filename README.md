# OpenMP_practice
# Ejercicios de Programación Paralela y Distribuida con OpenMP

Este repositorio contiene varios ejercicios en el lenguaje C que utilizan la librería OpenMP. Estos ejercicios forman parte de las evaluaciones de la asignatura "Programación Paralela y Distribuida". Además, el repositorio incluye scripts para ejecutar los ejercicios en el clúster de computadoras de la Universidad Central Martha Abreus de las Villas.

## Contenidos

- **Ejercicios en C**: Implementaciones de diferentes algoritmos y problemas utilizando OpenMP para programación paralela.
- **Scripts de Ejecución**: Scripts para compilar y ejecutar los ejercicios en el clúster de la universidad.
- **Instrucciones de Uso**: Detalles sobre cómo ejecutar los ejercicios tanto en entornos locales como en el clúster.

## Requisitos Previos

- Compilador de C compatible con OpenMP (gcc recomendado).
- Acceso al clúster de computadoras de la universidad (para aquellos que deseen ejecutarlos en un mejor entorno).
- Bash para la ejecución de scripts.

## Uso

### Ejecución Local

1. Clona el repositorio:
    ```sh
    git clone https://github.com/AidaRosaCalvo/open_mp_practice.git
    cd open_mp_practice
    ```

2. Compila el ejercicio deseado:
    ```sh
    gcc -fopenmp ej_3.c -o ej_3
    ```

3. Ejecuta el ejercicio:
    ```sh
    ./ej_3
    ```
## Contribuciones

Las contribuciones son bienvenidas. Si deseas contribuir, por favor sigue los siguientes pasos:

1. Haz un fork del repositorio.
2. Crea una rama para tu característica (`git checkout -b feature/nueva-caracteristica`).
3. Realiza tus cambios (`git commit -m 'Añadir nueva característica'`).
4. Sube tus cambios a tu fork (`git push origin feature/nueva-caracteristica`).
5. Abre un pull request.
