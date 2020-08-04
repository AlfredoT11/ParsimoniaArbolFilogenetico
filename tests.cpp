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

    //=============================================================================================================
    //Leida de alineamiento en formato Clustal.
    fstream archivoPruebaAlineamiento("alineamiento11secuencias.clw");
    string lineaAuxiliar;
    string auxInformacionAlineamiento;
    int numeroLinea = 0;
    int numeroSecuencias = 0;
    int secuenciasContadas = 0;
    vector<string> nombresSecuencias;
    vector<string> sitiosInformativos;
    vector<string> auxSecuenciasTemporales;

    while(getline(archivoPruebaAlineamiento, lineaAuxiliar)){
        
        if(lineaAuxiliar.size() != 0 && numeroLinea != 0){
            std::istringstream iss(lineaAuxiliar);
            string nombre;
            iss >> nombre;
            numeroSecuencias++;
            nombresSecuencias.push_back(nombre);
        }else if(lineaAuxiliar.size() == 0 && numeroSecuencias > 0){
            break;
        }
        numeroLinea++;
        //cout << "size: " << lineaAuxiliar.size() << " Ultimo caracter: " << lineaAuxiliar[lineaAuxiliar.size() - 1] << endl;
    }

    numeroSecuencias--;
    nombresSecuencias.pop_back();
    cout << "Numero secuencias: " << numeroSecuencias << endl;

    for(int i = 0; i < numeroSecuencias; i++){
        sitiosInformativos.push_back("");
    }

    archivoPruebaAlineamiento.seekg (0, ios::beg);
    numeroLinea = 0;
    getline(archivoPruebaAlineamiento, lineaAuxiliar);
    //cout << "Primera linea de nuevo: " << lineaAuxiliar << endl;

    //cout << "Secuencias encontradas: " << endl;
    for(int i = 0; i < nombresSecuencias.size(); i++){
        cout << nombresSecuencias[i] << endl;
    }

    secuenciasContadas = 0;
    int parte = 0;
    string columnaAuxiliar;
    vector<int> contadorBasesSitio = {0, 0, 0, 0};
    int contadorCambiosNecesarios;

    while(getline(archivoPruebaAlineamiento, lineaAuxiliar)){
        if(lineaAuxiliar.size() != 0 && numeroLinea != 0){
            if(secuenciasContadas == numeroSecuencias){
                secuenciasContadas = 0;
                auxInformacionAlineamiento = "";
                auxInformacionAlineamiento = lineaAuxiliar.substr(lineaAuxiliar.size()-auxSecuenciasTemporales[0].size(), auxSecuenciasTemporales[0].size());
                for(int i = 0; i < auxInformacionAlineamiento.size(); i++){
                    columnaAuxiliar = "";

                    if(auxInformacionAlineamiento[i] != '*'){
                        for(int j = 0; j < numeroSecuencias; j++){
                            if(auxSecuenciasTemporales[j][i] == 'N' || auxSecuenciasTemporales[j][i] == '-'){
                                break;
                            }
                            columnaAuxiliar += auxSecuenciasTemporales[j][i];
                        }
                    }
                    if(columnaAuxiliar.size() == numeroSecuencias){                        
                        contadorCambiosNecesarios = 0;
                        for(int i = 0; i < numeroSecuencias; i++){
                            switch(columnaAuxiliar.at(i)){
                                case 'A':
                                case 'a':
                                    contadorBasesSitio[PosicionBase::A]++;
                                    break;
                                case 'T':
                                case 't':
                                    contadorBasesSitio[PosicionBase::T]++;
                                    break;
                                case 'G':
                                case 'g':
                                    contadorBasesSitio[PosicionBase::G]++;
                                    break;                            
                                case 'C':
                                case 'c':
                                    contadorBasesSitio[PosicionBase::C]++;
                                    break;                        
                            }                            
                        }
                        for(int i = 0; i < 4; i++){
                            if(contadorBasesSitio[i] >= 2){
                                contadorCambiosNecesarios++;
                            }
                            contadorBasesSitio[i] = 0;
                        }
                        if(contadorCambiosNecesarios >= 2){
                            //cout << "Sition informativo encontrado." << endl;
                            //cout << columnaAuxiliar << endl;
                            for(int i = 0; i < numeroSecuencias; i++){
                                sitiosInformativos[i] += columnaAuxiliar[i];
                            }
                        }                                                
                    }

                }
                vector<string>().swap(auxSecuenciasTemporales);
                parte++;
            }else{
                std::istringstream iss(lineaAuxiliar);
                string nombre, secuencia;
                iss >> nombre >> secuencia;
                secuenciasContadas++;
                auxSecuenciasTemporales.push_back(secuencia);
            }

        }
        numeroLinea++;
        //cout << "size: " << lineaAuxiliar.size() << " Ultimo caracter: " << lineaAuxiliar[lineaAuxiliar.size() - 1] << endl;
    }

    /*for(int i = 0; i < numeroSecuencias; i++){
        cout << sitiosInformativos[i] << endl;
    }*/

    //Sitios informativos filtrados
    //===============================================================================================================


    //-----------------------------------------------------------------------------------------------------------------
    //Ejemplo del algoritmo en funcionamiento con 20 cadenas de prueba
    cout << "Cadenas de prueba: " << endl;
    vector<int> listaElementosPrueba;
    for(int i = 0; i < numeroSecuencias; i++){
        listaElementosPrueba.push_back(i);
        cout << i << " : " << sitiosInformativos[i] << " ";
    }

    std::random_shuffle(listaElementosPrueba.begin(), listaElementosPrueba.end());

    cout << "\nLista mezclada: "<< endl;
    for(int i = 0; i < numeroSecuencias; i++){
        cout << listaElementosPrueba[i] << " : " << sitiosInformativos[listaElementosPrueba[i]] << " ";
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
    ArbolFilogenetico arbolPrueba = ArbolFilogenetico(numHojas, auxPosSecuencias, listaElementosPrueba, sitiosInformativos, nombresSecuencias);

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
    //Fin del ejemplo del algoritmo con 20 cadenas de pruebas.
    // ============================================================================================================

    cout << "Terminado." << endl;

    return 0;
}