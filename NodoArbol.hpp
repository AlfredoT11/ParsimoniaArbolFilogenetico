#ifndef NODOARBOL_HPP
#define NODOARBOL_HPP

#include <vector>
#include <string>

using namespace std;

class NodoArbol{

    public:
    NodoArbol *hijoIzquierdo;
    NodoArbol *hijoDerecho;
    char baseNitrogenada;
    char tipoNodo; //Interno = I |Hoja (Secuencia) = H
    std::vector<int> evaluacionesMutaciones; //Posiciones: [ A=0 | T=1 | G=2 | C=3 ]
    int id;

    NodoArbol(void);
    NodoArbol(char nuevaBaseNitrogenada, int id);
    void evaluarMutaciones();
    void setHijoIzquierdo();
    void generarHijo(const int &alturaMaxima, int nivelHijo, int &sobrantes, int &id, int lado);
    void generarTablaNivelesNodosHijos(std::vector<std::vector<NodoArbol*>> &tablaNivelesNodosHijos, NodoArbol *direccionNodo, int nivel);
    void inorden();
    void postorden();
    void ordenar(int &nuevoID);
    void construirFormatoNewick(string &cadenaNewick);

};

#endif