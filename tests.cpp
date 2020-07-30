#include "NodoArbol.hpp"
#include "ArbolFilogenetico.hpp"
#include <iostream>
#include <string>
#include <time.h>


using namespace std;

enum PosicionBase { //Especifica la posición del posible valor de la mutación en el miembro "evaluacionesMutaciones" de la clase "Nodo_arbol".
    A, T, G, C
};

int main(){

    srand((unsigned)time(NULL));

    int numHojas;
    vector<vector<NodoArbol*>> tablaPruebaInternos;
    vector<NodoArbol*> tablaPruebaHojas;
    std::string cadenaPrueba = ""; 

    cin >> numHojas;

    ArbolFilogenetico arbolPrueba = ArbolFilogenetico(numHojas);

    int id = 1;
    arbolPrueba.raiz.ordenar(id);

    arbolPrueba.raiz.evaluarMutaciones();
    cout << "Valor A: " << arbolPrueba.raiz.evaluacionesMutaciones[0] <<endl;
    cout << "Valor T: " << arbolPrueba.raiz.evaluacionesMutaciones[1] <<endl;
    cout << "Valor G: " << arbolPrueba.raiz.evaluacionesMutaciones[2] <<endl;
    cout << "Valor C: " << arbolPrueba.raiz.evaluacionesMutaciones[3] <<endl;

    //cout << "Direccion de raiz: " << &arbolPrueba.raiz << endl;
    //cout << "Direccion hijo izquierdo: " << arbolPrueba.raiz.hijoIzquierdo << endl;
    //cout << "Direccion hijo derecho: " << arbolPrueba.raiz.hijoDerecho << endl;

    //arbolPrueba.raiz.postorden();
    /*cout << "\nIndorden: ";
    arbolPrueba.raiz.inorden();*/


    arbolPrueba.raiz.generarTablaNivelesNodosHijos(tablaPruebaInternos, tablaPruebaHojas, &arbolPrueba.raiz, 1);
    //cout << "\nTabla generada. " << endl;

    /*for(int i = 0; i < tablaPruebaInternos.size(); i++){
        cout << "Nivel " << i << ": ";
        for(int j = 0; j < tablaPruebaInternos[i].size(); j++){
            cout << tablaPruebaInternos[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Hojas: " ;
    for(int i = 0; i < tablaPruebaHojas.size(); i++){
        cout << tablaPruebaHojas[i] << " ";
    }*/

    /*cout << "\nIndorden: ";
    arbolPrueba.raiz.inorden();

    cout << "\nPostorden: ";
    arbolPrueba.raiz.postorden();

    arbolPrueba.raiz.construirFormatoNewick(cadenaPrueba);

    cout << "\n" << cadenaPrueba << endl;*/

    arbolPrueba.raiz.construirFormatoNewick(cadenaPrueba);
    //cout << "\nNewick: " << cadenaPrueba << endl;
    cadenaPrueba = "";
    //arbolPrueba.raiz.inorden();
    arbolPrueba.busquedaLocal(tablaPruebaHojas);
    //arbolPrueba.raiz.inorden();
    arbolPrueba.raiz.construirFormatoNewick(cadenaPrueba);
    //cout << "\nNewick después de búsqueda local: " << cadenaPrueba << endl;
    cadenaPrueba = "";
    
    arbolPrueba.raiz.evaluarMutaciones();
    cout << "\nValor A: " << arbolPrueba.raiz.evaluacionesMutaciones[0] <<endl;
    cout << "Valor T: " << arbolPrueba.raiz.evaluacionesMutaciones[1] <<endl;
    cout << "Valor G: " << arbolPrueba.raiz.evaluacionesMutaciones[2] <<endl;
    cout << "Valor C: " << arbolPrueba.raiz.evaluacionesMutaciones[3] <<endl;    

    for(int i = 0; i < 100; i++){    

        cout << "Iteracion " << i << endl;

        //arbolPrueba.raiz.inorden();

        vector<vector<NodoArbol*>>().swap(tablaPruebaInternos);
        //cout << "\nMemoria de tabla interna liberada. " << tablaPruebaInternos.size() <<endl;
        vector<NodoArbol*>().swap(tablaPruebaHojas);
        //cout << "Memoria de tabla hojas liberada. " << tablaPruebaHojas.size() <<endl;

        //arbolPrueba.raiz.inorden();        

        arbolPrueba.raiz.generarTablaNivelesNodosHijos(tablaPruebaInternos, tablaPruebaHojas, &arbolPrueba.raiz, 1);
        
        cout << "\nTabla generada: " << endl;

        for(int i = 0; i < tablaPruebaInternos.size(); i++){
            cout << "Nivel " << i << ": ";
            for(int j = 0; j < tablaPruebaInternos[i].size(); j++){
               //cout << tablaPruebaInternos[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Hojas: " ;
        for(int i = 0; i < tablaPruebaHojas.size(); i++){
            //cout << tablaPruebaHojas[i] << " ";
        }        

        arbolPrueba.perturbarSolucion(tablaPruebaInternos);
        id = 1;
        arbolPrueba.raiz.ordenar(id);
        arbolPrueba.raiz.construirFormatoNewick(cadenaPrueba);
        //cout << "\nNewick después de perturbación: " << cadenaPrueba << endl;
        cadenaPrueba = "";

        arbolPrueba.raiz.evaluarMutaciones();
        cout << "\nValor A: " << arbolPrueba.raiz.evaluacionesMutaciones[0] <<endl;
        cout << "Valor T: " << arbolPrueba.raiz.evaluacionesMutaciones[1] <<endl;
        cout << "Valor G: " << arbolPrueba.raiz.evaluacionesMutaciones[2] <<endl;
        cout << "Valor C: " << arbolPrueba.raiz.evaluacionesMutaciones[3] <<endl;


    }

    cout << "Terminado." << endl;

    /*NodoArbol raizNueva = NodoArbol('N', 1);
    NodoArbol izquierdo = NodoArbol('N', 2);
    NodoArbol derecho = NodoArbol('N', 3);
    NodoArbol izquierdo1 = NodoArbol('G', 4);
    NodoArbol izquierdo2 = NodoArbol('T', 5);
    NodoArbol derecho1 = NodoArbol('A', 6);
    NodoArbol derecho2 = NodoArbol('C', 7);

    raizNueva.hijoIzquierdo = &izquierdo;
    raizNueva.hijoDerecho = &derecho;
    izquierdo.hijoIzquierdo = &izquierdo1;
    izquierdo.hijoDerecho = &izquierdo2;
    derecho.hijoIzquierdo = &derecho1;
    derecho.hijoDerecho = &derecho2;

    cout << "Pruebas: " << endl;
    raizNueva.evaluarMutaciones();
    cout << "\nValor A: " << raizNueva.evaluacionesMutaciones[0] <<endl;
    cout << "Valor T: " << raizNueva.evaluacionesMutaciones[1] <<endl;
    cout << "Valor G: " << raizNueva.evaluacionesMutaciones[2] <<endl;
    cout << "Valor C: " << raizNueva.evaluacionesMutaciones[3] <<endl;     

    NodoArbol raizNueva3 = NodoArbol('N', 1);
    NodoArbol izquierdo3 = NodoArbol('N', 2);
    NodoArbol derecho3 = NodoArbol('N', 3);
    NodoArbol izquierdo13 = NodoArbol('C', 4);
    NodoArbol izquierdo23 = NodoArbol('T', 5);
    NodoArbol derecho13 = NodoArbol('G', 6);
    NodoArbol derecho23 = NodoArbol('A', 7);

    raizNueva3.hijoIzquierdo = &izquierdo3;
    raizNueva3.hijoDerecho = &derecho3;
    izquierdo3.hijoIzquierdo = &izquierdo13;
    izquierdo3.hijoDerecho = &izquierdo23;
    derecho3.hijoIzquierdo = &derecho13;
    derecho3.hijoDerecho = &derecho23;

    cout << "Pruebas: " << endl;
    raizNueva3.evaluarMutaciones();
    cout << "\nValor A: " << raizNueva3.evaluacionesMutaciones[0] <<endl;
    cout << "Valor T: " << raizNueva3.evaluacionesMutaciones[1] <<endl;
    cout << "Valor G: " << raizNueva3.evaluacionesMutaciones[2] <<endl;
    cout << "Valor C: " << raizNueva3.evaluacionesMutaciones[3] <<endl; */    

    return 0;
}