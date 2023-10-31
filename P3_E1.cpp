//PRACTICA 3: EJERCICIO 1
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
    int rango, res_data; // Variable para almacenar el rango del proceso actual y mensaje de respuesta
    int recv_data[1]; // Buffer para recibir un dato de otro proceso
    int recv_buf[5]; // Buffer para recopilar resultados de otros procesos
    
    MPI_Init(&argc, &argv); // Inicialización del entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rango); // Obtener el rango del proceso actual

    if(rango == 0){
        cout << "- Soy proceso: " << rango << endl;
        // Inicialización del array con valores arbitrarios
        int arr_data[5] = {4,5,6,7,8};

        // Distribución del array a los otros procesos
        MPI_Scatter(&arr_data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        cout << "- Array inicial:" << endl;
        printArr(arr_data, 5);

        res_data = recv_data[0] + rango;

        // Recopilar los resultados de los otros procesos
        MPI_Gather(&res_data, 1, MPI_INT, &recv_buf, 1, MPI_INT, 0, MPI_COMM_WORLD);
        cout << "- Array final:" << endl;
        printArr(recv_buf, 5);

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