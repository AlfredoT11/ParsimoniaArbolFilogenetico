#include <vector>

class NodoArbol{

    public:
        NodoArbol *hijoIzquierdo;
        NodoArbol *hijoDerecho;
        char baseNitrogenada;
        char tipoNodo; //Interno = I |Hoja (Secuencia) = H
        std::vector<int> evaluacionesMutaciones; //Posiciones: [ A=0 | T=1 | G=2 | C=3 ]

        NodoArbol(char nuevoTipoNodo, char nuevaBaseNitrogenada);
        void evaluarMutaciones();

};