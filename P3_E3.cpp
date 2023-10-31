//PRACTICA 3: EJERCICIO 3
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
    int rango; // Variable para almacenar el rango del proceso actual 
    int arr_data[3]; // Buffer para almacenar los datos a enviar
    int recv_data[3]; // Buffer para recibir los datos de otro proceso

    MPI_Init(&argc, &argv); // Inicialización del entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rango); // Obtener el rango del proceso actual

    // Inicializa el array con valores de rango + i
    for(int i=0; i<3; ++i){
        arr_data[i] = rango + i;
    }

    if(rango == 0){
        cout << "- Soy proceso: " << rango << endl;
        
        // Recopilar la operación de reducción global (suma) realizada sobre cada uno de los procesos
        MPI_Reduce(&arr_data, &recv_data, 3, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 
        cout << "- Array final:" << endl;
        printArr(recv_data, 3);

    } else {
        // Realiza una operación de reducción global (suma) sobre cada uno de los procesos y se envía al root
        MPI_Reduce(&arr_data, &recv_data, 3, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 
    }

    MPI_Finalize();
    return 0;
}
