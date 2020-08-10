# Iterated local search para la construcción de árboles filogenéticos
_Implementación de método de máxima parsimonia para la generación de árboles filogenético a partir de alineamientos múltiples de secuencias de ADN._
_Utiliza el algoritmo de Sankoff para la evaluación de parsimonia de los árboles generados, además utiliza metaheurística ILS (Iterated Local Search) para la búsqueda de soluciones óptimas dentro del espacio total de soluciones_

## Cómo utilizar
Para poder generar un árbol filogenético con este proyecto es necesario contar con alineamientos de secuencias de ADN. Estos alineamientos deben estar en formato **ClustalW (.clw)**. La salida generada será un archivo en formato **Newick (.newick)**.

Durante la ejecución del proyecto el usuario deberá introducir 2 parámetros:
- **Número de búsquedas locales** : Modifica la posición de las secuencias dentro de un árbol generado permitiendo evaluar diferentes soluciones para saber si se obtiene un nuevo valor óptimo.
- **Número de perturbaciones** : Es el número de cambios de estructura de árbol que se generarán para buscar soluciones óptimas.

A mayor número de búsquedas locales y perturbaciones el tiempo de procesamiento será mayor, sin embargo, podrían obtenerse mejores resultados finales.


### Windows
1. Abrir una nueva terminal de línea de comandos en la ubicación donde se encuentra el ejecutable (.exe) de este proyecto.
2. Ejecutar alguno de los siguientes 2 comandos: 

Lee el alineamiento _<nombreDelAlineamiento>.clw_ y genera como salida el archivo _resultado.newick_ en la misma carpeta.
```
ils.exe <nombreDelAlineamiento>.clw
```

Permite especificar el nombre del archivo de salida en formato newick.

```
ils.exe <nombreDelAlineamiento>.clw <nombreDelArchivoDeSalida>.newick
```

### Ubuntu
1. Abrir una nueva terminal de línea de comandos en la ubicación donde se encuentra el archivo compilado de este proyecto.
2. Ejecutar alguno de los siguientes 2 comandos: 

Lee el alineamiento _<nombreDelAlineamiento>.clw_ y genera como salida el archivo _resultado.newick_ en la misma carpeta.
```
./ils <nombreDelAlineamiento>.clw
```

Permite especificar el nombre del archivo de salida en formato newick.

```
./ils <nombreDelAlineamiento>.clw <nombreDelArchivoDeSalida>.newick
```

⌨️ con ❤️ por [AlfredoT11](https://github.com/AlfredoT11) 🙂
