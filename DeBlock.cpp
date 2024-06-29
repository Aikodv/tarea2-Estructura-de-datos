#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

typedef int tElem;
typedef tElem tListadeLista; // lo trate como un puntero doble

class DeBlock {
private:
    int cant_elems;
    tListadeLista** l;
    int* block_sizes;
    int block_count;
    int block_size;

public:
    /*****
    * Deblock
    * ******
    * Funcion que inicializa la estructura de datos deblock
    * ******
    * Input:
    * Resive un array de los elemenetos para crear la lista, la cantidad de numeros y en cuanto quiere particionar los bloques  
    * .......
    * ******
    * Returns:
    * No retorna nada
    * ******
    * */
    DeBlock(tElem* elems, int n, int b) {
        cant_elems = n;
        block_size = b;
        block_count = (n + b - 1) / b; 
        l = new tElem*[block_count];
        block_sizes = new int[block_count];
        
        int current_block = 0;
        for (int i = 0; i < n; i++) {
            if (i % b == 0) {
                l[current_block] = new tElem[b];
                block_sizes[current_block] = 0;
                current_block++;
            }
            l[current_block - 1][block_sizes[current_block - 1]] = elems[i];
            block_sizes[current_block - 1]++;
        }
    }
    /*****
     * insert
     * ******
     * Funcion que inserta un elemento en la posicion indicada
     * ******
     * Input:
     * Resive la posicion donde se quiere insertar el elemento y el elemento a insertar
     * .......
     * ******
     * Returns:
     * Retorna 1 si se inserto correctamente y 0 si no se pudo insertar
     * ******
     * */
    int insert(int pos, tElem elem) {
        if (pos < 0 || pos > cant_elems)
            return 0;

        int block_idx = pos / block_size;
        int block_pos = pos % block_size;

        if (block_sizes[block_idx] >= block_size) {
            int new_block_count = block_count + 1;
            tElem** new_l = new tElem*[new_block_count];
            int* new_block_sizes = new int[new_block_count];

            for (int i = 0; i < block_count; i++) {
                new_l[i] = l[i];
                new_block_sizes[i] = block_sizes[i];
            }

            new_l[block_count] = new tElem[block_size];
            new_block_sizes[block_count] = 0;

            block_count = new_block_count;
            delete[] l;
            delete[] block_sizes;
            l = new_l;
            block_sizes = new_block_sizes;
        }

        for (int i = block_sizes[block_idx]; i > block_pos; i--) {
            l[block_idx][i] = l[block_idx][i - 1];
        }
        l[block_idx][block_pos] = elem;
        block_sizes[block_idx]++;
        cant_elems++;
        return 1;
    }
    /*****
     * get_value
     * ******
     * Funcion que retorna el elemento en la posicion indicada
     * ******
     * Input:
     * Resive la posicion donde se quiere obtener el elemento
     * .......
     * ******
     * Returns:
     * Retorna el elemento en la posicion indicada
     * ******
     * */
    tElem get_value(int pos) {
        if (pos < 0 || pos >= cant_elems) {
            exit(1);
        }
        int block_idx = pos / block_size;
        int block_pos = pos % block_size;
        return l[block_idx][block_pos];
    }
    /*****
     * length
     * ******
     * Funcion que retorna la cantidad de elementos en la estructura
     * ******
     * Input:
     * No recibe nada
     * .......
     * ******
     * Returns:
     * Retorna la cantidad de elementos en la estructura
     * ******
     * */
    int length() {
        return cant_elems;
    }
    /*****
     * clear
     * ******
     * Funcion que libera la memoria de la estructura
     * ******
     * Input:
     * No recibe nada
     * .......
     * ******
     * Returns:
     * No retorna nada
     * ******
     * */
    void clear() {
        for (int i = 0; i < block_count; i++) {
            delete[] l[i];
        }
        delete[] l;
        delete[] block_sizes;
    }
};
