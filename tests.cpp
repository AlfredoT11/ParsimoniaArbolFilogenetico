//#include "NodoArbol.hpp"
#include "ArbolFilogenetico.hpp"
#include <iostream>


using namespace std;

enum PosicionBase { //Especifica la posición del posible valor de la mutación en el miembro "evaluacionesMutaciones" de la clase "Nodo_arbol".
    A, T, G, C
};

int main(){

    int numHojas;
    cin >> numHojas;

    ArbolFilogenetico arbolPrueba = ArbolFilogenetico(numHojas);

    arbolPrueba.raiz.evaluarMutaciones();
    cout << "Valor A: " << arbolPrueba.raiz.evaluacionesMutaciones[0] <<endl;
    cout << "Valor T: " << arbolPrueba.raiz.evaluacionesMutaciones[1] <<endl;
    cout << "Valor G: " << arbolPrueba.raiz.evaluacionesMutaciones[2] <<endl;
    cout << "Valor C: " << arbolPrueba.raiz.evaluacionesMutaciones[3] <<endl;

    cout << "Direccion hijo izquierdo: " << arbolPrueba.raiz.hijoIzquierdo << endl;
    cout << "Direccion hijo derecho: " << arbolPrueba.raiz.hijoDerecho << endl;

    arbolPrueba.raiz.postorden();

    return 0;
}