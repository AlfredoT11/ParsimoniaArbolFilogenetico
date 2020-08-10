#include "ArbolFilogenetico.hpp"

#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

enum PosicionBase { //Especifica la posición del posible valor de la mutación en el miembro "evaluacionesMutaciones" de la clase "Nodo_arbol".
    A, T, G, C
};




ArbolFilogenetico::ArbolFilogenetico(int numeroHojas, int &auxPosSecuencias, vector<int> &listaPosicionesGeneradas, vector<string> &secuencias, vector<string> &nombresSecuencias){

    char aAcento = 160;    
    /*cout << "Logaritmo: " << log2(numeroHojas) << endl;
    cout << "Ceil: " << ceil(log2(numeroHojas)) << endl;
    cout << "Entero: " << int(ceil(log2(numeroHojas))) << endl;*/

    cout << "Generando "<< aAcento << "rbol..." << endl;

    int alturaMaxima = int(ceil(log2(numeroHojas)));

    int hojasSobrantes = int(pow(2, alturaMaxima)) - numeroHojas;

    /*cout << "Altura maxima: " << alturaMaxima << endl;
    cout << "NumeroHojas: " << numeroHojas << endl;
    cout << "HojasSobrantes: " << hojasSobrantes << endl;*/

    raiz = NodoArbol('N', 1, auxPosSecuencias, listaPosicionesGeneradas, secuencias, nombresSecuencias);
    int contador = 2;
    raiz.generarHijo(alturaMaxima, 2, hojasSobrantes, contador, 1, auxPosSecuencias, listaPosicionesGeneradas, secuencias, nombresSecuencias);
    raiz.generarHijo(alturaMaxima, 2, hojasSobrantes, contador, 0, auxPosSecuencias, listaPosicionesGeneradas, secuencias, nombresSecuencias);
    maximaParsimoniaPosible = -1;

}

void ArbolFilogenetico::leerAlineamientoClustalW(vector<string> &nombresSecuencias, vector<string> &sitiosInformativos, string nombreArchivoEntrada){
//=============================================================================================================
    //Leida de alineamiento en formato Clustal.
    fstream archivoPruebaAlineamiento(nombreArchivoEntrada);
    string lineaAuxiliar;
    string auxInformacionAlineamiento;
    int numeroLinea = 0;
    int numeroSecuencias = 0;
    int secuenciasContadas = 0;
    vector<string> auxSecuenciasTemporales;
    vector<string> sitiosInformativosCompletos;
    char uAcento = 163;

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
    cout << "N" << uAcento <<"mero secuencias: " << numeroSecuencias << endl;

    for(int i = 0; i < numeroSecuencias; i++){
        sitiosInformativosCompletos.push_back("");
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
                            if(auxSecuenciasTemporales[j][i] != 'A' && auxSecuenciasTemporales[j][i] != 'a' && auxSecuenciasTemporales[j][i] != 'T' && auxSecuenciasTemporales[j][i] != 't' &&
                                auxSecuenciasTemporales[j][i] != 'G' && auxSecuenciasTemporales[j][i] != 'g' && auxSecuenciasTemporales[j][i] != 'C' && auxSecuenciasTemporales[j][i] != 'c'){
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
                                sitiosInformativosCompletos[i] += columnaAuxiliar[i];
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

    archivoPruebaAlineamiento.close();

    /*for(int i = 0; i < numeroSecuencias; i++){
        cout << sitiosInformativos[i] << endl;
    }*/

    //Sitios informativos filtrados
    filtrarSitiosRepetidos(sitiosInformativosCompletos, sitiosInformativos);
    //===============================================================================================================    
}

void ArbolFilogenetico::filtrarSitiosRepetidos(vector<string> &sitiosInformativosCompletos, vector<string> &sitiosInformativosFiltrados){

    vector<string> sitiosVolteados;
    vector<string> sitiosVolteadosFiltrados;

    for(int i = 0; i < sitiosInformativosCompletos[0].size(); i++){
        sitiosVolteados.push_back("");
        for(int j = 0; j < sitiosInformativosCompletos.size(); j++){
            sitiosVolteados[i].push_back(sitiosInformativosCompletos[j][i]);
        }
    }

    sort(sitiosVolteados.begin(), sitiosVolteados.end());
    
    for(int i = 0; i < sitiosVolteados.size(); i++){
        bool encontrado = false;
        for(int j = 0; j < sitiosVolteadosFiltrados.size(); j++){
            if(sitiosVolteados[i] == sitiosVolteadosFiltrados[j]){
                encontrado = true;
                break;
            }
        }
        if(!encontrado){
            sitiosVolteadosFiltrados.push_back(sitiosVolteados[i]);
        }
    }

    
    for(int i = 0; i < sitiosVolteadosFiltrados[0].size(); i++){
        sitiosInformativosFiltrados.push_back("");
        for(int j = 0; j < sitiosVolteadosFiltrados.size(); j++){
            sitiosInformativosFiltrados[i].push_back(sitiosVolteadosFiltrados[j][i]);
        }
    }  

    cout << "Registros: " << sitiosInformativosFiltrados.size() << " de tamanio: " << sitiosInformativosFiltrados[0].size() << endl;

}

int ArbolFilogenetico::obtenerParsimonia(NodoArbol &hojaIntercambiada1, NodoArbol &hojaIntercambiada2, int busquedasLocalesMaximas, int &numBusquedasLocalesRealizadas){
    
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
            cout << "Nuevo mínimo encontrado." << endl;
            numBusquedasLocalesRealizadas = 0;
        }else{            
            intercambiarValoresHojas(hojaIntercambiada1, hojaIntercambiada2);
            numBusquedasLocalesRealizadas++;
        }
    }

    if(numBusquedasLocalesRealizadas == busquedasLocalesMaximas){
        return 1;
    }else{
        return 0;
    }

}

void ArbolFilogenetico::intercambiarValoresHojas(NodoArbol &direccionHoja1, NodoArbol &direccionHoja2){

    string auxiliarCambios;
    string auxiliarNombreSecuencia;

    direccionHoja1.baseNitrogenada = direccionHoja1.baseNitrogenada ^ direccionHoja2.baseNitrogenada;
    direccionHoja2.baseNitrogenada = direccionHoja1.baseNitrogenada ^ direccionHoja2.baseNitrogenada;
    direccionHoja1.baseNitrogenada = direccionHoja1.baseNitrogenada ^ direccionHoja2.baseNitrogenada;    

    auxiliarCambios = direccionHoja1.secuencia;
    direccionHoja1.secuencia = direccionHoja2.secuencia;
    direccionHoja2.secuencia = auxiliarCambios;

    auxiliarNombreSecuencia = direccionHoja1.nombreSecuencia;
    direccionHoja1.nombreSecuencia = direccionHoja2.nombreSecuencia;
    direccionHoja2.nombreSecuencia = auxiliarNombreSecuencia;    

    direccionHoja1.evaluarMutacionHoja();
    direccionHoja2.evaluarMutacionHoja();


}

void ArbolFilogenetico::busquedaLocal(vector<NodoArbol*> &listaHojas, int &posicionHoja1, int &posicionHoja2){
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

    int posHoja1 = rand() % listaHojas.size();
    int posHoja2;
    do{
        posHoja2 = rand() % listaHojas.size();
    }while(posHoja1 == posHoja2);


    direccionHoja1 = listaHojas[posHoja1];
    direccionHoja2 = listaHojas[posHoja2];

    posicionHoja1 = posHoja1;
    posicionHoja2 = posHoja2;

    //Se intercambian las bases entre los nodos seleccionados.
    intercambiarValoresHojas(*direccionHoja1, *direccionHoja2);

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
