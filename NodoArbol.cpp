#include "NodoArbol.hpp"
#include <iostream>
#include <vector>
#include <string>

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

    evaluarMutacionHoja();
}

void NodoArbol::evaluarMutacionHoja(){
    if(tipoNodo == 'H'){
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
}

void NodoArbol::evaluarMutaciones(){
    //Implementación del algoritmo de Sankoff para evaluación de máxima parsimonia.

    //Comprobación de que un nodo izquierdo interno aún no ha sido evaluado.
    if(hijoIzquierdo->tipoNodo == 'I' && hijoIzquierdo->evaluacionesMutaciones[-1] && hijoIzquierdo != NULL){
        hijoIzquierdo->evaluarMutaciones();
    }

    //Comprobación de que un nodo izquierdo interno aún no ha sido evaluado.
    if(hijoDerecho->tipoNodo == 'I' && hijoDerecho->evaluacionesMutaciones[-1] && hijoDerecho != NULL){
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
        

        //Generación aleatoria para pruebas----------------------------------------
        char baseAleatoria;
        switch(rand()%4){
            case 0:
            baseAleatoria = 'A';
            break;
            case 1:
            baseAleatoria = 'T';
            break;
            case 2:
            baseAleatoria = 'G';
            break;
            default:
            baseAleatoria = 'C';
            break;                                    
        }
        NodoArbol *auxNuevoHijo = new NodoArbol(baseAleatoria, tempId);
        //-------------------------------------------------------------------------
        
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
        //cout << &auxNuevoHijo << endl;
    }

    if(lado == 0){
        hijoIzquierdo = auxNuevoHijo;
    }else{
        hijoDerecho = auxNuevoHijo;
    }

    auxNuevoHijo->generarHijo(alturaMaxima, nivelHijo+1, sobrantes, id, 1);
    auxNuevoHijo->generarHijo(alturaMaxima, nivelHijo+1, sobrantes, id, 0);
        
}

void NodoArbol::generarTablaNivelesNodosHijos(std::vector<std::vector<NodoArbol *>> &tablaNivelesNodosHijos, 
    std::vector<NodoArbol *> &tablaHojas, NodoArbol *direccionNodo, int nivel){
    
    //cout << "Entrando a un nodo de nivel " << nivel << " Objecto con direccion : " << direccionNodo << endl;

    if(tipoNodo == 'I'){
        if(tablaNivelesNodosHijos.size() < nivel){
            vector<NodoArbol*> auxVectorNivel;
            //cout << "Vector creado. " << endl;
            tablaNivelesNodosHijos.push_back(auxVectorNivel);
            //cout << "Vector agregado a la tabla. " << endl;
        }
        
        //cout << "Mi ID es " << id << endl;
        tablaNivelesNodosHijos[nivel-1].push_back(this);
        //cout << "Direccion del objeto agregada a la tabla. " << endl;
    }else{ 
        tablaHojas.push_back(this);
    }

    if(this->hijoIzquierdo != NULL){
        this->hijoIzquierdo->generarTablaNivelesNodosHijos(tablaNivelesNodosHijos, tablaHojas, hijoIzquierdo, nivel+1);
    }

    if(this->hijoDerecho != NULL){
        this->hijoDerecho->generarTablaNivelesNodosHijos(tablaNivelesNodosHijos, tablaHojas, hijoDerecho, nivel+1);
    }    

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

void NodoArbol::inorden(){
    
    if(hijoIzquierdo != NULL){
        hijoIzquierdo->inorden();
    }

    if(tipoNodo == 'H'){
        cout << id << " " << baseNitrogenada << " ";    
    }else{
        cout << id << " ";
    }

    if(hijoDerecho != NULL){
        hijoDerecho->inorden();
    }
    
}


void NodoArbol::ordenar(int &nuevoID){

    if(hijoIzquierdo != NULL){
        hijoIzquierdo->ordenar(nuevoID);
    }

    //cout << id << " ";
    id = nuevoID;
    nuevoID++;

    if(hijoDerecho != NULL){
        hijoDerecho->ordenar(nuevoID);
    }

}

void NodoArbol::limpiarEvaluacionesMutaciones(){

    if(hijoIzquierdo != NULL){
        hijoIzquierdo->limpiarEvaluacionesMutaciones();
    }

    if(hijoDerecho != NULL){
        hijoDerecho->limpiarEvaluacionesMutaciones();
    }

    for(int i = 0; i < 4; i++){
        //cout << "Antigua : " << evaluacionesMutaciones[i];
        evaluacionesMutaciones[i] = -1; //-1 = Infinito.
        //cout << "Nueva : " << evaluacionesMutaciones[i] << endl;
    }

    evaluarMutacionHoja();

}

NodoArbol* NodoArbol::buscarNodoPorID(int &idAEncontrar){
    
    if(this->id == idAEncontrar){
        //cout << "Encontrado." << endl;
        return this;
    }

    if(hijoIzquierdo != NULL && idAEncontrar < this->id){
        //cout << "Izquierda." << endl;
        return hijoIzquierdo->buscarNodoPorID(idAEncontrar);
    }

    if(hijoDerecho != NULL && idAEncontrar > this->id){
        //cout << "Derecha." << endl;
        return hijoDerecho->buscarNodoPorID(idAEncontrar);
    }

    //cout << "No encontrado " << endl;
    return NULL;

}

void NodoArbol::construirFormatoNewick(string &cadenaNewick){


    if(hijoIzquierdo != NULL && hijoDerecho != NULL){
        cadenaNewick.append("(");
        hijoIzquierdo->construirFormatoNewick(cadenaNewick);
        cadenaNewick.append(",");
        hijoDerecho->construirFormatoNewick(cadenaNewick);
        cadenaNewick.push_back(')');
        return;
    }else if(hijoIzquierdo != NULL && hijoDerecho == NULL){
        cadenaNewick.push_back('(');
        hijoIzquierdo->construirFormatoNewick(cadenaNewick);
        cadenaNewick.push_back(')');
        return;
    }else if(hijoIzquierdo == NULL && hijoDerecho != NULL){
        cadenaNewick.push_back('(');
        hijoDerecho->construirFormatoNewick(cadenaNewick);
        cadenaNewick.push_back(')');
        return;        
    }else{
        //cout << "ID: " << id << endl;
        cadenaNewick.append(to_string(id));
        return;
    }


}

//typedef NodoArbol *apuNodoArbol;