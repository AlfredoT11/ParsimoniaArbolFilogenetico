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

NodoArbol::NodoArbol(){
    return;
}


NodoArbol::NodoArbol(char nuevaBaseNitrogenada, int nuevoID){
    //Constructor de la clase.
    hijoIzquierdo = NULL;
    hijoDerecho = NULL;
    id = nuevoID;

    for(int i = 0; i < 4; i++){
        evaluacionesMutaciones.push_back(-1); //-1 = Infinito.
    }
    baseNitrogenada = nuevaBaseNitrogenada;

    if(nuevaBaseNitrogenada == 'N'){
        tipoNodo = 'I';
    }else{
        tipoNodo = 'H';
    }

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
}

void NodoArbol::evaluarMutaciones(){
    //Implementación del algoritmo de Sankoff para evaluación de máxima parsimonia.

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

void NodoArbol::generarHijo(const int &alturaMaxima, int nivelHijo, int &sobrantes, int &id, int lado){
    //lado 0 = izquierdo, 1 = derecho

    int tempId = id;

    if((nivelHijo == alturaMaxima && sobrantes > 0) || nivelHijo > alturaMaxima){
        NodoArbol *auxNuevoHijo = new NodoArbol('A', tempId);
        id++;
        if(lado == 0){
            hijoIzquierdo = auxNuevoHijo;
        }else{
            hijoDerecho = auxNuevoHijo;
        }
        sobrantes--;
        return;
    }

    NodoArbol *auxNuevoHijo = new NodoArbol('N', tempId);
    id++;

    if(tempId == 9 || tempId == 2){
        cout << &auxNuevoHijo << endl;
    }

    if(lado == 0){
        hijoIzquierdo = auxNuevoHijo;
    }else{
        hijoDerecho = auxNuevoHijo;
    }

    auxNuevoHijo->generarHijo(alturaMaxima, nivelHijo+1, sobrantes, id, 1);
    auxNuevoHijo->generarHijo(alturaMaxima, nivelHijo+1, sobrantes, id, 0);
        
}

void NodoArbol::postorden(){

    //cout << "Entrando a nodo: " << this->id << endl;

    if(hijoIzquierdo != NULL){
        hijoIzquierdo->postorden();
    }
    if(hijoDerecho != NULL){
        hijoDerecho->postorden();
    }
    cout << id << " ";
}

//typedef NodoArbol *apuNodoArbol;