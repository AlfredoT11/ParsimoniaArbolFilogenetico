#include "NodoArbol.hpp"
#include "ArbolFilogenetico.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <algorithm>    // std::random_shuffle


using namespace std;

enum PosicionBase { //Especifica la posición del posible valor de la mutación en el miembro "evaluacionesMutaciones" de la clase "Nodo_arbol".
    A, T, G, C
};

vector<string> cadenasPrueba = {"ATGCT", "TGGCA", "ATGCC", "GCCTA", "CCTAG", "ATTGC", "TCTAT", "GTACT", "GTAGA", "ACGGA",
                                "GTACA", "TGCGG", "TTAAT", "ATATA", "ATACA", "GCCAT", "CACAT", "CGCGT", "TATAT", "CAGAA"};

int main(){

    srand((unsigned)time(NULL));

    /*int numHojas;
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


    //arbolPrueba.raiz.generarTablaNivelesNodosHijos(tablaPruebaInternos, tablaPruebaHojas, &arbolPrueba.raiz, 1);
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

    /*
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

    /* Pruebas de una sola base nitrogenada --------------------------------------------------------------------------
    int numHojas, busquedasLocales, perturbaciones;
    int id = 1;
    vector<vector<NodoArbol*>> tablaNodosInternos;
    vector<NodoArbol*> listaHojas;

    cout << "Numero de hojas a generar: ";
    cin >> numHojas;
    cout << "Numero de busquedas locales: ";
    cin >> busquedasLocales;
    cout << "Numero de perturbaciones: ";
    cin >> perturbaciones;

    //Se genera el árbol inicial.
    ArbolFilogenetico arbolPrueba = ArbolFilogenetico(numHojas);

    arbolPrueba.raiz.ordenar(id);
    
    //Se evalúa el árbol inicial.
    arbolPrueba.raiz.evaluarMutaciones();

    //Se obtiene la parsimonia del árbol y se obtiene el formato newick inicial.
    arbolPrueba.obtenerParsimonia();

    cout << "Parsimonia máxima inicial: " << arbolPrueba.maximaParsimoniaPosible << endl;
    cout << "Newick: " << arbolPrueba.formatoNewick << endl;
    

    for(int i = 0; i < perturbaciones; i++){
        vector<vector<NodoArbol*>>().swap(tablaNodosInternos);
        vector<NodoArbol*>().swap(listaHojas);
        arbolPrueba.raiz.generarTablaNivelesNodosHijos(tablaNodosInternos, listaHojas, &arbolPrueba.raiz, 1);
        for(int j = 0; j < busquedasLocales; j++){
            //cout << "Busqueda local..." << endl;            
            arbolPrueba.busquedaLocal(listaHojas);
            arbolPrueba.raiz.evaluarMutaciones();
            arbolPrueba.obtenerParsimonia();
            //cout << "\n";
            //arbolPrueba.raiz.inorden();
        }
        cout << "\nPerturbando solución..." << endl;
        arbolPrueba.perturbarSolucion(tablaNodosInternos);
        id = 1;
        arbolPrueba.raiz.ordenar(id);

    }

    cout << "\nMaxima parsimonia final: " << arbolPrueba.maximaParsimoniaPosible << endl;
    cout << "Arbol final: " << arbolPrueba.formatoNewick << endl;

    ofstream archivoNewick;
    archivoNewick.open("prueba.newick");
    archivoNewick << arbolPrueba.formatoNewick << ";";
    archivoNewick.close();
    ------------------------------------------------------------------------------------------------------------------ */

    cout << "Cadenas de prueba: " << endl;
    vector<int> listaElementosPrueba;
    for(int i = 0; i < 20; i++){
        listaElementosPrueba.push_back(i);
        cout << i << " : " << cadenasPrueba[i] << " ";
    }

    std::random_shuffle(listaElementosPrueba.begin(), listaElementosPrueba.end());

    cout << "\nLista mezclada: "<< endl;
    for(int i = 0; i < 20; i++){
        cout << listaElementosPrueba[i] << " : " << cadenasPrueba[listaElementosPrueba[i]] << " ";
    }
    cout << endl;

    int numHojas, busquedasLocales, perturbaciones;
    int id = 1;
    int auxPosSecuencias = 0;
    vector<vector<NodoArbol*>> tablaNodosInternos;
    vector<NodoArbol*> listaHojas;

    cout << "Numero de hojas a generar: ";
    cin >> numHojas;
    cout << "Numero de busquedas locales: ";
    cin >> busquedasLocales;
    cout << "Numero de perturbaciones: ";
    cin >> perturbaciones;

    //cout << "Numero de busquedas locales: ";
    //cin >> busquedasLocales;
    //cout << "Numero de perturbaciones: ";
    //cin >> perturbaciones;

    //Se genera el árbol inicial.
    ArbolFilogenetico arbolPrueba = ArbolFilogenetico(numHojas, auxPosSecuencias, listaElementosPrueba, cadenasPrueba);

    cout << "\nArbol generado." << endl;

    arbolPrueba.raiz.ordenar(id);
    arbolPrueba.raiz.inorden();
    
    //Se evalúa el árbol inicial.
    for(int i = 0; i < arbolPrueba.raiz.evaluacionesMutaciones.size(); i++){
        //cout << "Evaluando mutaciones de " << i << endl;
        arbolPrueba.raiz.evaluarMutaciones(i);
    }

    //Se obtiene la parsimonia del árbol y se obtiene el formato newick inicial.
    arbolPrueba.obtenerParsimonia();

    cout << "Parsimonia máxima inicial: " << arbolPrueba.maximaParsimoniaPosible << endl;
    cout << "Newick: " << arbolPrueba.formatoNewick << endl;

    //Se comienza con la búsqueda local y las perturbaciones.

    for(int i = 0; i < perturbaciones; i++){
        vector<vector<NodoArbol*>>().swap(tablaNodosInternos);
        vector<NodoArbol*>().swap(listaHojas);
        arbolPrueba.raiz.generarTablaNivelesNodosHijos(tablaNodosInternos, listaHojas, &arbolPrueba.raiz, 1);
        for(int j = 0; j < busquedasLocales; j++){
            //cout << "Busqueda local..." << endl;            
            arbolPrueba.busquedaLocal(listaHojas);
            for(int i = 0; i < arbolPrueba.raiz.evaluacionesMutaciones.size(); i++){
                //cout << "Evaluando mutaciones de " << i << endl;
                arbolPrueba.raiz.evaluarMutaciones(i);
            }
            arbolPrueba.obtenerParsimonia();
            //cout << "\n";
            //arbolPrueba.raiz.inorden();
        }
        //cout << "\nPerturbando solución..." << endl;
        arbolPrueba.perturbarSolucion(tablaNodosInternos);
        id = 1;
        arbolPrueba.raiz.ordenar(id);

    }

    cout << "\nMaxima parsimonia final: " << arbolPrueba.maximaParsimoniaPosible << endl;
    cout << "Arbol final: " << arbolPrueba.formatoNewick << endl;

    ofstream archivoNewick;
    archivoNewick.open("prueba.newick");
    archivoNewick << arbolPrueba.formatoNewick << ";";
    archivoNewick.close();    

    return 0;
}