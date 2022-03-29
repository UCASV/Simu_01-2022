#include <iostream>
#include <stdlib.h>

using namespace std;

/*  La librería hace uso de template, para que cada función
    quede independiente del tipo de dato a utilizar.

    Cuando las funciones sean utilizadas se deberá
    establecer el tipo de dato mediante un "meta-parámetro".

    En el proceso de compilación, cada template se copiará
    y se establecerá con un tipo de dato concreto por cada
    "meta-parámetro" utilizado.
*/

/*
    Función para crear espacio en memoria para un
    arreglo bidimensional de tipo <type>, con <nrows>
    filas y <ncols> columnas.
    Se retorna la dirección del espacio en memoria
    creado.
*/
template <typename type>
type** create(int nrows, int ncols){
    /*
        La estructura a construir en memoria corresponde a un arreglo
        principal de punteros simples, donde cada uno apunta a un arreglo
        que corresponde a una de las filas de la matriz:

        int** matriz -->  [ int* ]-[ int* ]-[ int* ]     //Arreglo principal
                             |        |        |
                             v        v        v
                          [ int ]  [ int ]  [ int ]
                          [ int ]  [ int ]  [ int ]
                          [ int ]  [ int ]  [ int ]
    */
   
    //Se construye primero el arreglo principal:

    //Casting a (type**) ya que el bloque de memoria
    //se provee "crudo" ( void* ), el doble puntero responde
    //a que se almacenarán punteros simples a tipo <type>.
    //sizeof(type*) ya que se almacenarán datos de tipo <type*>.
    //sizeof(type*)*nrows para generar tantos espacios
    //como los indicados por el número de filas de la matriz.
    type** matrix = (type**) malloc(sizeof(type*)*nrows);

    //Se recorre el arreglo principal:
    for(int i = 0; i < nrows; i++)
        //Por cada espacio, que es equivalente a decir, por
        //cada fila, se construye un arreglo:

        //Casting a (type*) ya que el bloque de memoria
        //se provee "crudo" ( void* ).
        //sizeof(type) ya que se almacenarán datos de tipo <type>.
        //sizeof(type)*ncols para generar tantos espacios
        //como los indicados por el número de columnas de la matriz.
        *(matrix+i) = (type*) malloc(sizeof(type)*ncols);
    return matrix;
}

/*
    Función para insertar un valor <value> de tipo <type>
    en la celda ( <row>, <col> ) de una matriz de datos de tipo <type>.
*/
template <typename type>
void insert(type** matrix, int row, int col, type value){
    matrix[row][col] = value;
    //*(*(matrix+row)+col) = value; //También funciona
}

/*
    Función para liberar todo el espacio en memoria
    utilizado por una matriz de datos tipo <type>.
*/
template <typename type>
void destroy(type** matrix, int nrows){
    //Es necesario liberar primero todas las filas
    //antes de liberar el arreglo principal, a fin
    //de no perder la referencia.

    //Se recorre el arreglo principal:
    for(int i = 0; i < nrows; i++)
        //Se libera cada fila, utilizando el contenido
        //de cada celda del arreglo principal, el cual
        //corresponde a los punteros a cada una de las
        //filas.
        free(*(matrix+i));

    //Por último, se libera el arreglo principal usando
    //la dirección de memoria inicial de toda la matriz.
    free(matrix);
}

/*
    Función que determina si un valor <value> de tipo <type>
    se encuentra o no dentro de una matriz de datos de tipo <type>.
    Se retorna true si se encuentra, false en caso
    contrario.
    <nrows> y <ncols> determinan la cantidad de filas y la
    cantidad de columnas de la matriz, respectivamente, y se
    usan para controlar los límites de los procesos de recorrido.
*/
template <typename type>
bool search(type** matrix, int nrows, int ncols, type value){
    //Respuesta por defecto: "No se encuentra."
    bool ans = false;

    //Se recorre la matriz:
    for(int i = 0; i < nrows; i++)
        for(int j = 0; j < ncols; j++)
            //Verifico en la celda actual si se ha
            //encontrado el dato buscado.
            if(matrix[i][j] == value){
                //Si se encontró, se actualiza la respuesta.
                ans = true;
                //Basta una ocurrencia, no es necesario
                //continuar el recorrido.
                break;
            }
    return ans;
}

/*
    Función que determina la cantidad de ocurrencias
    de un valor <value> de tipo <type> en una matriz
    de datos de tipo <type>.
    <nrows> y <ncols> determinan la cantidad de filas y la
    cantidad de columnas de la matriz, respectivamente, y se
    usan para controlar los límites de los procesos de recorrido.
*/
template <typename type>
int count(type** matrix, int nrows, int ncols, type value){
    //Se inicializa un contador de suma
    int cont = 0;

    //Se recorre la matriz:
    for(int i = 0; i < nrows; i++)
        for(int j = 0; j < ncols; j++)
            //Verifico si hay ocurrencia en la celda
            //actual del arreglo
            if(matrix[i][j] == value)
                //Si hay ocurrencia, actualizo el contador.
                //No hay break, ya que me interesa saber
                //el total de ocurrencias, sigo buscando.
                cont++;
    //Retorno el resultado
    return cont;
}

/*
    Función que, dada una matriz de datos de tipo <type,
    crea una nueva matriz de datos de tipo <type> como
    copia exacta de la original.
    <nrows> y <ncols> determinan la cantidad de filas y la
    cantidad de columnas de la matriz, respectivamente, y se
    usan para controlar los límites de los procesos de recorrido.
*/
template <typename type>
type** create_copy(type** original, int nrows, int ncols){
    //Se crea una nueva matriz de datos de tipo <type> del
    //mismo tamaño que la original:

    //Primero, se crea un nuevo arreglo principal del mismo
    //tamaño que el arreglo principal de la matriz original.
    type** new_one = (type**) malloc(sizeof(type*)*nrows);

    //Luego, se recorre el arreglo principal de la matriz original.
    for(int i = 0; i < nrows; i++){
        //Por cada fila de la matriz original, se crea una fila
        //para la nueva matriz, del mismo tamaño.
        *(new_one+i) = (type*) malloc(sizeof(type)*ncols);
        //Se recorre la fila de la matriz original
        for(int j = 0; j < ncols; j++)
            //Cada dato de la fila original se copia en la fila
            //correspondiente de la nueva matriz, quedando entonces
            //en la misma posición, en la misma celda.
            new_one[i][j] = original[i][j];
    }
    //Se retorna la dirección del bloque de memoria
    //correspondiente a la nueva matriz.
    return new_one;
}
