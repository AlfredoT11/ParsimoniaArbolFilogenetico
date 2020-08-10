#ifndef ARBOLFILOGENETICO_HPP
#define ARBOLFILOGENETICO_HPP

#include "NodoArbol.hpp"

class ArbolFilogenetico{

    public:
        NodoArbol raiz;
        int maximaParsimoniaPosible;
        string formatoNewick;

        ArbolFilogenetico(int numeroHojas, int &auxPosSecuencias, vector<int> &listaPosicionesGeneradas, vector<string> &secuencias, vector<string> &nombresSecuencias); //Genera un árbol binario inicial con el número indicado de hojas.
        static void leerAlineamientoClustalW(vector<string> &nombreSecuencias, vector<string> &sitiosInformativos, string nombreArchivoEntrada);
        static void filtrarSitiosRepetidos(vector<string> &sitiosInformativosCompletos, vector<string> &sitiosInformativosFiltrados);
        int obtenerParsimonia(NodoArbol &hojaIntercambiada1, NodoArbol &hojaIntercambiada2, int busquedasLocalesMaximas, int &numBusquedasLocalesRealizadas);
        void intercambiarValoresHojas(NodoArbol &direccionHoja1, NodoArbol &direccionHoja2);
        void busquedaLocal(vector<NodoArbol*> &listaHojas, int &posicionHoja1, int &posicionHoja2);
        void perturbarSolucion(vector<vector<NodoArbol*>> &tablaNodosInteriores);

};

#endif