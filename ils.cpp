#include "NodoArbol.hpp"
#include "ArbolFilogenetico.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include <time.h>
#include <algorithm>    // std::random_shuffle


using namespace std;

enum PosicionBase { //Especifica la posición del posible valor de la mutación en el miembro "evaluacionesMutaciones" de la clase "Nodo_arbol".
    A, T, G, C
};

string ils(string nombreArchivoAlineamiento, string nombreArchivoSalida){

    vector<string> nombresSecuencias;
    vector<string> sitiosInformativos;

    ArbolFilogenetico::leerAlineamientoClustalW(nombresSecuencias, sitiosInformativos, nombreArchivoAlineamiento);
    int numeroSecuencias = nombresSecuencias.size();

    //-----------------------------------------------------------------------------------------------------------------
    vector<int> listaElementosMezclados;
    for(int i = 0; i < numeroSecuencias; i++){
        listaElementosMezclados.push_back(i);
        //cout << i << " : " << sitiosInformativos[i] << " ";
    }

    std::random_shuffle(listaElementosMezclados.begin(), listaElementosMezclados.end());

    int numHojas, busquedasLocales, perturbaciones;
    int id = 1;
    int auxPosSecuencias = 0;
    vector<vector<NodoArbol*>> tablaNodosInternos;
    vector<NodoArbol*> listaHojas;

    numHojas = numeroSecuencias;

    cout << "Numero de busquedas locales: ";
    cin >> busquedasLocales;
    cout << "Numero de perturbaciones: ";
    cin >> perturbaciones;

    //cout << "Numero de busquedas locales: ";
    //cin >> busquedasLocales;
    //cout << "Numero de perturbaciones: ";
    //cin >> perturbaciones;

    //Se genera el árbol inicial.
    ArbolFilogenetico arbol = ArbolFilogenetico(numHojas, auxPosSecuencias, listaElementosMezclados, sitiosInformativos, nombresSecuencias);

    //cout << "\nArbol generado." << endl;

    arbol.raiz.ordenar(id);
    //arbolPrueba.raiz.inorden();
    
    //Se evalúa el árbol inicial.
    for(int i = 0; i < arbol.raiz.evaluacionesMutaciones.size(); i++){
        //cout << "Evaluando mutaciones de " << i << endl;
        arbol.raiz.evaluarMutaciones(i);
    }

    //Se obtiene la parsimonia del árbol y se obtiene el formato newick inicial.
    arbol.obtenerParsimonia();

    //cout << "Parsimonia máxima inicial: " << arbolPrueba.maximaParsimoniaPosible << endl;
    //cout << "Newick: " << arbolPrueba.formatoNewick << endl;

    //Se comienza con la búsqueda local y las perturbaciones.

    for(int i = 0; i < perturbaciones; i++){
        vector<vector<NodoArbol*>>().swap(tablaNodosInternos);
        vector<NodoArbol*>().swap(listaHojas);
        arbol.raiz.generarTablaNivelesNodosHijos(tablaNodosInternos, listaHojas, &arbol.raiz, 1);
        for(int j = 0; j < busquedasLocales; j++){
            //cout << "Busqueda local..." << endl;            
            arbol.busquedaLocal(listaHojas);
            for(int i = 0; i < arbol.raiz.evaluacionesMutaciones.size(); i++){
                //cout << "Evaluando mutaciones de " << i << endl;
                arbol.raiz.evaluarMutaciones(i);
            }
            arbol.obtenerParsimonia();
            //cout << "\n";
            //arbolPrueba.raiz.inorden();
        }
        //cout << "\nPerturbando solución..." << endl;
        arbol.perturbarSolucion(tablaNodosInternos);
        id = 1;
        arbol.raiz.ordenar(id);

    }

    cout << "\nMaxima parsimonia final: " << arbol.maximaParsimoniaPosible << endl;
    cout << "Arbol final: " << arbol.formatoNewick << endl;

    ofstream archivoNewick;
    archivoNewick.open(nombreArchivoSalida);
    archivoNewick << arbol.formatoNewick << ";";
    archivoNewick.close();

    return arbol.formatoNewick;    

}

int main(int argc, char **argv){

    cout << "Numero argumentos: " << argc << endl;

    string nombreArchivoAlineamiento;
    string nombreArchivoSalida;

    if(argc < 2){
        cout << "Por favor ingresa al menos nombre del alineamiento (Formato ClustalW). Puedes ingresar tambien el nombre del archivo de salida (Formato Newick)" << endl;
        return 0;
    }else if(argc == 2){
        nombreArchivoAlineamiento = argv[1];
        nombreArchivoSalida = "resultado.newick";
    }else if(argc == 3){
        nombreArchivoAlineamiento = argv[1];
        nombreArchivoSalida = argv[2];        
    }else{
        cout << "Por favor unicamente ingresa el nombre del alineamiento (Formato ClustalW). Puedes ingresar tambien el nombre del archivo de salida (Formato Newick)" << endl;
        return 0;
    }

    srand((unsigned)time(NULL));

    ils(nombreArchivoAlineamiento, nombreArchivoSalida);

    cout << "Terminado." << endl;

    return 0;
}