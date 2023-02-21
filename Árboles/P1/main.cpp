#include <iostream> 
#include <fstream> 
#include "Abin.hpp" 
#include "abin_E_S.hpp"

using namespace std;

typedef char tElto;
const tElto fin = '#'; // Fin de lectura.

int main () 
{
    Abin<tElto> A;

    cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
    ifstream fe("abin.dat"); // Abrir fichero de entrada. 
    rellenarAbin(fe, A); // Desde fichero.
    fe.close();

    cout << "\n*** Mostrar árbol binario B ***\n";
    imprimirAbin(A); // En std::cout 
}