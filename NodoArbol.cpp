#include "NodoArbol.hpp"
#include <iostream>
#include <vector>

using namespace std;

enum PosicionBase { //Especifica la posición del posible valor de la mutación en el miembro "evaluacionesMutaciones" de la clase "Nodo_arbol".
    A, T, G, C
};

vector <vector<int>> matrizValoresMutaciones{ 
    //A  T  G  C
    { 0, 5, 2, 8 }, // A 
    { 5, 0, 9, 3 }, // T
    { 2, 9, 0, 6 }, // G
    { 8, 3, 6, 0 }  // C
};


NodoArbol::NodoArbol(char nuevoTipoNodo, char nuevaBaseNitrogenada){
    //Constructor de la clase.
    tipoNodo = nuevoTipoNodo;
    hijoIzquierdo = NULL;
    hijoDerecho = NULL;

    for(int i = 0; i < 4; i++){
        evaluacionesMutaciones.push_back(-1); //-1 = Infinito.
    }
    if(tipoNodo == 'H'){ 
        baseNitrogenada = nuevaBaseNitrogenada;

        switch(baseNitrogenada){
            case 'A':
            case 'a':
                evaluacionesMutaciones[PosicionBase::A] = 0;
                break;
            case 'T':
            case 't':
                evaluacionesMutaciones[PosicionBase::T] = 0;
                break;
            case 'G':
            case 'g':
                evaluacionesMutaciones[PosicionBase::G] = 0;
                break;                            
            case 'C':
            case 'c':
                evaluacionesMutaciones[PosicionBase::C] = 0;
                break;                        
        }
    }else{
        baseNitrogenada = 'N';
    }
}

void NodoArbol::evaluarMutaciones(){

    //Comprobación de que un nodo izquierdo interno aún no ha sido evaluado.
    if(hijoIzquierdo->tipoNodo == 'I' && hijoIzquierdo->evaluacionesMutaciones[-1] && hijoIzquierdo != NULL){
        hijoIzquierdo->evaluarMutaciones();
    }

    //Comprobación de que un nodo izquierdo interno aún no ha sido evaluado.
    if(hijoDerecho->tipoNodo == 'I' && hijoDerecho->evaluacionesMutaciones[-1] && hijoIzquierdo != NULL){
        hijoDerecho->evaluarMutaciones();
    }            

    for(int i = 0; i < 4; i++){
        int uMin = 2147483647, wMin = 2147483647; //u = Hijo izquierdo, w = Hijo derecho.

        for(int j = 0; j < 4; j++){
            if(hijoIzquierdo->evaluacionesMutaciones[j] == -1){
                continue;
            }
            if(hijoIzquierdo->evaluacionesMutaciones[j] + matrizValoresMutaciones[i][j] <= uMin){
                //printf("%d %d \n.", hijoIzquierdo->evaluacionesMutaciones[j], matrizValoresMutaciones[i][j]);
                uMin = hijoIzquierdo->evaluacionesMutaciones[j] + matrizValoresMutaciones[i][j];
            }
        }

        for(int j = 0; j < 4; j++){
            if(hijoDerecho->evaluacionesMutaciones[j] == -1){                        
                continue;
            }
            if(hijoDerecho->evaluacionesMutaciones[j] + matrizValoresMutaciones[i][j] <= wMin){
                //printf("%d %d \n.", hijoDerecho->evaluacionesMutaciones[j], matrizValoresMutaciones[i][j]);
                wMin = hijoDerecho->evaluacionesMutaciones[j] + matrizValoresMutaciones[i][j];
            }
        }                
        evaluacionesMutaciones[i] = uMin + wMin;
        //printf("Total: %d\n", evaluacionesMutaciones[i]);
    } 
}

//typedef NodoArbol *apuNodoArbol;