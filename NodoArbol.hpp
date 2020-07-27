#ifndef NODOARBOL_HPP
#define NODOARBOL_HPP

#include <vector>

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
    void generarHijoDerecho(const int &alturaMaxima, int nivelHijo, int &sobrantes, int id);
    void generarHijoIzquierdo(const int &alturaMaxima, int nivelHijo, int &sobrantes, int id);
    void generarHijo(const int &alturaMaxima, int nivelHijo, int &sobrantes, int &id, int lado);
    void postorden();

};

#endif