#include "ArbolFilogenetico.hpp"

#include <iostream>
#include <math.h>

using namespace std;

ArbolFilogenetico::ArbolFilogenetico(int numeroHojas){
    
    /*cout << "Logaritmo: " << log2(numeroHojas) << endl;
    cout << "Ceil: " << ceil(log2(numeroHojas)) << endl;
    cout << "Entero: " << int(ceil(log2(numeroHojas))) << endl;*/

    int alturaMaxima = int(ceil(log2(numeroHojas)));

    int hojasSobrantes = int(pow(2, alturaMaxima)) - numeroHojas;

    /*cout << "Altura maxima: " << alturaMaxima << endl;
    cout << "NumeroHojas: " << numeroHojas << endl;
    cout << "HojasSobrantes: " << hojasSobrantes << endl;*/

    raiz = NodoArbol('N', 1);
    int contador = 2;
    raiz.generarHijo(alturaMaxima, 2, hojasSobrantes, contador, 1);
    raiz.generarHijo(alturaMaxima, 2, hojasSobrantes, contador, 0);

}