//PRACTICA 3: EJERCICIO 2
//Renato Agustin Montenegro Palma
#include <iostream>
#include <mpi.h>
using namespace std;

// Imprimir por pantalla elementos de un array
void printArr(const int arr[], int size){
    for(int i=0; i<size; ++i){
        cout << arr[i] << endl;
    }
}

int main(int argc, char** argv) {
    int rango, size; // Variable para almacenar el rango del proceso actual y el número total de procesos
    int recv_data[1]; // Buffer para recibir un dato de otro proceso
    int res_data; // Variable para almacenar el dato respuesta de un mensaje

    MPI_Init(&argc, &argv); // Inicialización del entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rango); // Obtener el rango del proceso actual
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener el número total de procesos

    int recv_buf[size]; // Buffer para recopilar resultados de otros procesos

    if(rango == 0){
        cout << "- Soy proceso: " << rango << endl;
        int arr[size]; // Variable para almacenar los datos a enviar

        for(int i=0; i<size; ++i){
            arr[i] = i; // Inicializa el array con valores de 0 a n-1
        }

        // Distribución del array a los otros procesos
        MPI_Scatter(&arr, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        cout << "- Array inicial:" << endl;
        printArr(arr, size);

        res_data = recv_data[0] + rango;

        // Recopilar los resultados de los otros procesos
        MPI_Gather(&res_data, 1, MPI_INT, &recv_buf, 1, MPI_INT, 0, MPI_COMM_WORLD);
        cout << "- Array final:" << endl;
        printArr(recv_buf, size);

    } else {
        int data[1]; // Varabiable para almacenar el dato recibido
        
        // Recibir un dato del proceso root
        MPI_Scatter(&data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        
        res_data = recv_data[0] + rango;
        
        // Enviar el resultado al proceso root
        MPI_Gather(&res_data, 1, MPI_INT, &recv_buf, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}