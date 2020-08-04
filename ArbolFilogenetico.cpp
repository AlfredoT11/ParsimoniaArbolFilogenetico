#include "ArbolFilogenetico.hpp"

#include <iostream>
#include <math.h>

using namespace std;

ArbolFilogenetico::ArbolFilogenetico(int numeroHojas, int &auxPosSecuencias, vector<int> &listaPosicionesGeneradas, vector<string> &secuencias, vector<string> &nombresSecuencias){
    
    /*cout << "Logaritmo: " << log2(numeroHojas) << endl;
    cout << "Ceil: " << ceil(log2(numeroHojas)) << endl;
    cout << "Entero: " << int(ceil(log2(numeroHojas))) << endl;*/

    cout << "Generando arbol..." << endl;

    int alturaMaxima = int(ceil(log2(numeroHojas)));

    int hojasSobrantes = int(pow(2, alturaMaxima)) - numeroHojas;

    /*cout << "Altura maxima: " << alturaMaxima << endl;
    cout << "NumeroHojas: " << numeroHojas << endl;
    cout << "HojasSobrantes: " << hojasSobrantes << endl;*/

    raiz = NodoArbol('N', 1, auxPosSecuencias, listaPosicionesGeneradas, secuencias, nombresSecuencias);
    cout << "Raiz generada." << endl;
    int contador = 2;
    raiz.generarHijo(alturaMaxima, 2, hojasSobrantes, contador, 1, auxPosSecuencias, listaPosicionesGeneradas, secuencias, nombresSecuencias);
    cout << "Hijos izquierdos generados" << endl;
    raiz.generarHijo(alturaMaxima, 2, hojasSobrantes, contador, 0, auxPosSecuencias, listaPosicionesGeneradas, secuencias, nombresSecuencias);
    cout << "Hijos izquierdos generados" << endl;
    maximaParsimoniaPosible = -1;

}

void ArbolFilogenetico::obtenerParsimonia(){
    
    if(maximaParsimoniaPosible == -1){
        
        for(int i = 0; i < raiz.evaluacionesMutaciones.size(); i++){
            int auxiliarMaximaParsimoniaSitio = raiz.evaluacionesMutaciones[i][0];
            for(int j = 1; j < 3; j++){
                if(raiz.evaluacionesMutaciones[i][j] < auxiliarMaximaParsimoniaSitio){
                    auxiliarMaximaParsimoniaSitio = raiz.evaluacionesMutaciones[i][j];
                }
            }
            maximaParsimoniaPosible += auxiliarMaximaParsimoniaSitio;
        }
        formatoNewick = "";
        raiz.construirFormatoNewick(formatoNewick);
        
    }else{

        int auxMaximaParsimoniaTotal = 0;
        for(int i = 0; i < raiz.evaluacionesMutaciones.size(); i++){
            int auxiliarMaximaParsimoniaSitio = raiz.evaluacionesMutaciones[i][0];
            for(int j = 1; j < 3; j++){
                if(raiz.evaluacionesMutaciones[i][j] < auxiliarMaximaParsimoniaSitio){
                    auxiliarMaximaParsimoniaSitio = raiz.evaluacionesMutaciones[i][j];
                }
            }
            auxMaximaParsimoniaTotal += auxiliarMaximaParsimoniaSitio;
        }

        //cout << "\nNueva calculada: " << auxMaximaParsimoniaTotal;

        if(auxMaximaParsimoniaTotal < maximaParsimoniaPosible){
            maximaParsimoniaPosible = auxMaximaParsimoniaTotal;
            formatoNewick = "";
            raiz.construirFormatoNewick(formatoNewick);
            cout << "\nNuevo mínimo encontrado." << endl;
        }    
    }
}

void ArbolFilogenetico::busquedaLocal(vector<NodoArbol*> &listaHojas){
    //Intercambia 2 hojas al azar.

    /*cout << "\nAnteriores: ";
    for(int i = 0; i < 4; i++){
        cout << raiz.evaluacionesMutaciones[i] << " ";
    }*/

    raiz.limpiarEvaluacionesMutaciones();

    /*cout << "\nNuevas: ";
    for(int i = 0; i < 4; i++){
        cout << raiz.evaluacionesMutaciones[i] << " ";
    }

    cout << "\n" << endl;*/

    NodoArbol* direccionHoja1;
    NodoArbol* direccionHoja2;

    string auxiliarCambios;
    string auxiliarNombreSecuencia;

    int posHoja1 = rand() % listaHojas.size();
    int posHoja2;
    do{
        posHoja2 = rand() % listaHojas.size();
    }while(posHoja1 == posHoja2);


    direccionHoja1 = listaHojas[posHoja1];
    direccionHoja2 = listaHojas[posHoja2];

    //cout << "\nBase hoja 1: " << direccionHoja1->baseNitrogenada << " Base hoja 2: " << direccionHoja2->baseNitrogenada << endl;

    //Se intercambian las bases entre los nodos seleccionados.

    direccionHoja1->baseNitrogenada = direccionHoja1->baseNitrogenada ^ direccionHoja2->baseNitrogenada;
    direccionHoja2->baseNitrogenada = direccionHoja1->baseNitrogenada ^ direccionHoja2->baseNitrogenada;
    direccionHoja1->baseNitrogenada = direccionHoja1->baseNitrogenada ^ direccionHoja2->baseNitrogenada;    

    auxiliarCambios = direccionHoja1->secuencia;
    direccionHoja1->secuencia = direccionHoja2->secuencia;
    direccionHoja2->secuencia = auxiliarCambios;
    
    auxiliarNombreSecuencia = direccionHoja1->nombreSecuencia;
    direccionHoja1->nombreSecuencia = direccionHoja2->nombreSecuencia;
    direccionHoja2->nombreSecuencia = auxiliarNombreSecuencia;    

    //cout << "Base hoja 1: " << direccionHoja1->baseNitrogenada << " Base hoja 2: " << direccionHoja2->baseNitrogenada << endl;

    direccionHoja1->evaluarMutacionHoja();
    direccionHoja2->evaluarMutacionHoja();

}

void ArbolFilogenetico::perturbarSolucion(vector<vector<NodoArbol*>> &tablaNodosInteriores){

    NodoArbol* auxiliarAleatorio1;
    NodoArbol* auxiliarAleatorio2;
    NodoArbol* auxiliarCambio;

    int nivelAuxiliar1, posicionAuxiliar1, ladoAux1; //Lado : 0 = izq | 1 =der.
    int nivelAuxiliar2, posicionAuxiliar2, ladoAux2;

    nivelAuxiliar1 = 1 + (rand() % (tablaNodosInteriores.size() - 1));
    posicionAuxiliar1 = rand() % tablaNodosInteriores[nivelAuxiliar1].size();
    ladoAux1 = rand() % 2;

    auxiliarAleatorio1 = tablaNodosInteriores[nivelAuxiliar1][posicionAuxiliar1];

    do{
        //cout << "\nProbando de nuevo..." << endl;
        nivelAuxiliar2 = rand() % tablaNodosInteriores.size();
        posicionAuxiliar2 = rand() % tablaNodosInteriores[nivelAuxiliar2].size();
        ladoAux2 = rand() % 2;
        auxiliarAleatorio2 = tablaNodosInteriores[nivelAuxiliar2][posicionAuxiliar2];
        //cout << "Nodo 1: " << auxiliarAleatorio1 << " Nodo 2: " << auxiliarAleatorio2 << endl;
        if(auxiliarAleatorio1->buscarNodoPorID(auxiliarAleatorio2->id) != NULL){
            //cout << "Nodo 2 es hijo de 1" << endl;
        }else if(auxiliarAleatorio2->buscarNodoPorID(auxiliarAleatorio1->id)){
            //cout << "Nodo 1 es hijo de 2" << endl;
        }

    }while(auxiliarAleatorio2 == auxiliarAleatorio1 || 
        auxiliarAleatorio1->buscarNodoPorID(auxiliarAleatorio2->id) != NULL || auxiliarAleatorio1 == auxiliarAleatorio2
        || auxiliarAleatorio2->buscarNodoPorID(auxiliarAleatorio1->id) != NULL);
    

    /*cout << "\nNodo 1 :" << auxiliarAleatorio1->id << " Nodo 2: " << auxiliarAleatorio2->id << endl;
    cout << "\nNodo 1 :" << auxiliarAleatorio1 << " Nodo 2: " << auxiliarAleatorio2 << endl;

    cout << "Nodo 1: Izquierdo" << auxiliarAleatorio1->hijoIzquierdo->id << " Derecho: " << auxiliarAleatorio1->hijoDerecho->id << endl;
    cout << "Nodo 2: Izquierdo" << auxiliarAleatorio2->hijoIzquierdo->id << " Derecho: " << auxiliarAleatorio2->hijoDerecho->id << endl;

    if(auxiliarAleatorio1->hijoDerecho == NULL || auxiliarAleatorio1->hijoIzquierdo == NULL){
        cout << "Hay un nulo con el auxiliar 1";
    }

    if(auxiliarAleatorio2->hijoDerecho == NULL || auxiliarAleatorio2->hijoIzquierdo == NULL){
        cout << "Hay un nulo con el auxiliar 2";
    }*/

    if(ladoAux1 == 0){
        //cout << "Obteniendo el auxiliar" << endl;
        auxiliarCambio = auxiliarAleatorio1->hijoIzquierdo;
        //cout << "Auxiliar obtenido" << endl;
        if(ladoAux2 == 0){
            auxiliarAleatorio1->hijoIzquierdo = auxiliarAleatorio2->hijoIzquierdo;
            auxiliarAleatorio2->hijoIzquierdo = auxiliarCambio;
        }else{
            auxiliarAleatorio1->hijoIzquierdo = auxiliarAleatorio2->hijoDerecho;
            auxiliarAleatorio2->hijoDerecho = auxiliarCambio;            
        }
    }else{
        //cout << "Obteniendo el auxiliar" << endl;
        auxiliarCambio = auxiliarAleatorio1->hijoDerecho;
        //cout << "Auxiliar obtenido" << endl;
        if(ladoAux2 == 0){
            auxiliarAleatorio1->hijoDerecho = auxiliarAleatorio2->hijoIzquierdo;
            auxiliarAleatorio2->hijoIzquierdo = auxiliarCambio;
        }else{
            auxiliarAleatorio1->hijoDerecho = auxiliarAleatorio2->hijoDerecho;
            auxiliarAleatorio2->hijoDerecho = auxiliarCambio;            
        }        
    }

    /*cout << "Nuevos: " << endl;
    cout << "Nodo 1: Izquierdo" << auxiliarAleatorio1->hijoIzquierdo->id << " Derecho: " << auxiliarAleatorio1->hijoDerecho->id << endl;
    cout << "Nodo 2: Izquierdo" << auxiliarAleatorio2->hijoIzquierdo->id << " Derecho: " << auxiliarAleatorio2->hijoDerecho->id << endl;    
    */

}
