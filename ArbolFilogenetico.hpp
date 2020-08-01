#ifndef ARBOLFILOGENETICO_HPP
#define ARBOLFILOGENETICO_HPP

#include "NodoArbol.hpp"

class ArbolFilogenetico{

    public:
        NodoArbol raiz;
        int maximaParsimoniaPosible;
        string formatoNewick;

        ArbolFilogenetico(int numeroHojas, int &auxPosSecuencias, vector<int> &listaPosicionesGeneradas, vector<string> &secuencias); //Genera un árbol binario inicial con el número indicado de hojas.
        void obtenerParsimonia();
        void busquedaLocal(vector<NodoArbol*> &listaHojas);
        void perturbarSolucion(vector<vector<NodoArbol*>> &tablaNodosInteriores);

};

#endif