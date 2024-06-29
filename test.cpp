#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "DeBlock.cpp"
using namespace std;
/*****
 * int main
 * ******
 * Funcion main la cual lee un archivo con las operaciones a realizar en la estructura de datos DeBlock y realizarlas dependiendo de los inputs
 * ******
 * Input:
 * Un archivo con la operaones a tratar
 * .......
 * ******
 * Returns:
 * int 0
 * ******
 * */

int main() {
    fstream file;
    file.open("pruebas.txt", ios::in);
    if( !file.is_open() ){
        cout << "Error al abrir el archivo\n";
        exit(1);
    }
    int n,b;
    file >> n; 
    file >> b; 
    tElem elems[n];
    for (int i = 0; i < n; i++) {
        file >> elems[i];
    }
    DeBlock deblock(elems,n,b);
    int nOperaciones;
    file>> nOperaciones;
    char operaciones[nOperaciones];
    int I, V;
    for (int i = 1; i <= nOperaciones  ; i) {
        file >> operaciones[i];
        if(operaciones[i] == 'I'){ //corresponde a insertar el elemento v en la posición i.
            file >> I;
            file >> V;
            cout << deblock.insert(I, V) <<endl ;
            i++;
        }
        else if(operaciones[i] == 'G'){ // corresponde a mostrar por pantalla el elemento en la posición i.
            file >> I;
            cout << deblock.get_value(I) <<endl;
            i++;
        }
        else if(operaciones[i] == 'L'){ // corresponde a que se debe mostrar por pantalla la cantidad de elementos en la estructura
            int s;
            s = deblock.length();
            cout << s << endl;
            i++;
        }
    }
    file.close();
    deblock.clear();
    return 0;
}

