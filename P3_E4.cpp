//PRACTICA 3: EJERCICIO 4
//Renato Agustin Montenegro Palma
#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char** argv) {
    int rango; // Variable para almacenar el rango del proceso actual 
    int data, min, max; // Variables para almacenar el número secreto y las reducciones globales (max) y (min)
    int recv_data; // Buffer para recibir los datos de otro proceso

    MPI_Init(&argc, &argv); // Inicialización del entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rango); // Obtener el rango del proceso actual

    if(rango == 0){
        int data = 2; // Inicialización del número secreto
        cout << "- Soy proceso: " << rango << ", y el numero secreto es: " << data << endl; 
        
        // Enviar número secreto a todos los procesos
        MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        
        // Recopilar la operación de reducción global (min) realizada sobre cada uno de los procesos
        MPI_Reduce(&data, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD); 
        cout << "- Dato min recibido: " << min << endl;
        
        // Recopilar la operación de reducción global (max) realizada sobre cada uno de los procesos
        MPI_Reduce(&data, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
        cout << "- Dato max recibido: " << max << endl;        

    } else {
        // Recibir número secreto del proceso root
        MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

        data += rango;
        
        // Realiza una operación de reducción global (min) sobre cada uno de los procesos y se envía al root
        MPI_Reduce(&data, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD); 
        
        // Realiza una operación de reducción global (max) sobre cada uno de los procesos y se envía al root
        MPI_Reduce(&data, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
