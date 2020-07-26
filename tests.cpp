#include "NodoArbol.hpp"
#include <iostream>


using namespace std;

enum PosicionBase { //Especifica la posición del posible valor de la mutación en el miembro "evaluacionesMutaciones" de la clase "Nodo_arbol".
    A, T, G, C
};

int main(){

    NodoArbol raiz('I', 'N');
    NodoArbol izquierdoRaiz('I', 'N');
    NodoArbol derechoRaiz('I', 'N');
    NodoArbol derechoNivel2('I', 'N');
    NodoArbol hijo1('H', 'T');
    NodoArbol hijo2('H', 'C');
    NodoArbol hijo3('H', 'A');
    NodoArbol hijo4('H', 'G');
    NodoArbol hijo5('H', 'A');

    raiz.hijoIzquierdo = &izquierdoRaiz;
    raiz.hijoDerecho = &derechoRaiz;

    izquierdoRaiz.hijoIzquierdo = &hijo1;
    izquierdoRaiz.hijoDerecho = &hijo2;

    derechoRaiz.hijoIzquierdo = &hijo3;
    derechoRaiz.hijoDerecho = &derechoNivel2;

    derechoNivel2.hijoIzquierdo = &hijo4;
    derechoNivel2.hijoDerecho = &hijo5;

    //cout << "Soy la raiz con base: " << raiz.baseNitrogenada << endl;
    //cout << "Soy el hijo izquierdo a traves de la raiz con base: " << raiz.hijoIzquierdo->baseNitrogenada << endl;
    //cout << "Soy el hijo derecho a traves de la raiz con base: " << raiz.hijoDerecho->baseNitrogenada << endl;
    NodoArbol *aux = &raiz;
    aux->evaluarMutaciones();

    cout << "Valores mutaciones: " << endl;
    cout << "A: " << aux->evaluacionesMutaciones[PosicionBase::A] << endl;
    cout << "T: " << aux->evaluacionesMutaciones[PosicionBase::T] << endl;
    cout << "G: " << aux->evaluacionesMutaciones[PosicionBase::G] << endl;
    cout << "C: " << aux->evaluacionesMutaciones[PosicionBase::C] << endl;

    return 0;
}