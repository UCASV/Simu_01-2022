#include <iostream>
#include <stdlib.h>

using namespace std;

/*
    Esta versión trabaja el recorrido de la matriz
    con un solo iterador 'for' utilizando un sólo índice k.

    La equivalencia entre los índices del esquema con dos
    iteradores (i,j) y el índice del esquema con un iterador
    (k) es el siguiente:

        i = k \ ncols
        j = k % ncols

    Donde el operador '\' hace referencia a la "División Entera".

    Estas equivalencias surgen del análisis siguiente:

              Usando (i,j)                          Usando k

          0        1        2                  0        1        2
    0 [ (0,0) ][ (0,1) ][ (0,2) ]        0 [   0   ][   1   ][   2   ]
    1 [ (1,0) ][ (1,1) ][ (1,2) ]  <-->  1 [   3   ][   4   ][   5   ]
    2 [ (2,0) ][ (2,1) ][ (2,2) ]        2 [   6   ][   7   ][   8   ]

    Observando las columnas:

          0        1        2                  0        1        2
    0 [ (_,0) ][ (_,1) ][ (_,2) ]        0 [   0   ][   1   ][   2   ]
    1 [ (_,0) ][ (_,1) ][ (_,2) ]  <-->  1 [   3   ][   4   ][   5   ]
    2 [ (_,0) ][ (_,1) ][ (_,2) ]        2 [   6   ][   7   ][   8   ]

    Puede observarse que para cada fila se repite el ciclo {0,1,2}

    Como ya sabemos, usando la propiedad de la operación módulo podemos
    generar ciclos:
                        n mod m --> dato en [0...m-1]

    Por lo que, para tener un dato en {0,1,2}, hacemos módulo 3, que es
    lo mismo que decir, hacemos módulo <ncols>.

    Usando el iterador k como input del proceso, obtenemos la equivalencia
    para el iterador j:
                                j = k % ncols

    Ahora, observemos las filas:

          0        1        2                  0        1        2
    0 [ (0,_) ][ (0,_) ][ (0,_) ]        0 [   0   ][   1   ][   2   ]
    1 [ (1,_) ][ (1,_) ][ (1,_) ]  <-->  1 [   3   ][   4   ][   5   ]
    2 [ (2,_) ][ (2,_) ][ (2,_) ]        2 [   6   ][   7   ][   8   ]

    El patrón esta vez corresponde a mantener el número de la fila como
    el índice i.

    Observando los valores de k, podemos ver lo siguiente:

          0        1        2                   0          1          2
    0 [ (0,_) ][ (0,_) ][ (0,_) ]        0 [    0    ][    1    ][    2    ]
    1 [ (1,_) ][ (1,_) ][ (1,_) ]  <-->  1 [   0+3   ][   1+3   ][   2+3   ]
    2 [ (2,_) ][ (2,_) ][ (2,_) ]        2 [   0+6   ][   1+6   ][   2+6   ]

    Trabajándolo un poco más:

          0        1        2                   0            1            2
    0 [ (0,_) ][ (0,_) ][ (0,_) ]        0 [   0+3*0   ][   1+3*0   ][   2+3*0   ]
    1 [ (1,_) ][ (1,_) ][ (1,_) ]  <-->  1 [   0+3*1   ][   1+3*1   ][   2+3*1   ]
    2 [ (2,_) ][ (2,_) ][ (2,_) ]        2 [   0+3*2   ][   1+3*2   ][   2+3*2   ]

    El patrón que necesitamos ha aparecido a la derecha como el factor del 3,
    generalizando de la forma:
                                    n+3*n
    
    Para extraer la n de la expresión anterior, aplicamos división entera entre 3:

                                (n + 3*n) \ 3 = n
            { (n + 3*n) \ 3 = floor( (n + 3*n) / 3 ) = floor( n/3 + n ) = n }

    Como la expresión n+3*n viene de la k, y como el 3 corresponde a <ncols>, 
    podemos definir la equivalencia con el índice i como:
                                
                                i = k \ ncols

    Por último, se observa que la k en el ejemplo varía desde o hasta un valor de 8,
    este valor de 8 se puede reescribir como 9 -1 , el cual a su vez se puede reescribir
    como 3*3 - 1, lo que, generalizando, es equivalente a decir <nrows>*<ncols> - 1.

    Por lo que la variación de la k se generaliza como:

                    k pertenece al intervalo [ 0 ... nrows*ncols-1 ]
*/

/* ========================================================= */

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
    for(int i = 0; i < nrows*ncols; i++)
        //Verifico en la celda actual si se ha
        //encontrado el dato buscado.
        if(matrix[i/ncols][i%ncols] == value){
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
    for(int i = 0; i < nrows*ncols; i++)
        //Verifico si hay ocurrencia en la celda
        //actual de la matriz
        if(matrix[i/ncols][i%ncols] == value)
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

    //Por cada fila de la matriz original, se crea una fila
    //para la nueva matriz, del mismo tamaño.
    for(int i = 0; i < nrows; i++)
        *(new_one+i) = (type*) malloc(sizeof(type)*ncols);
    
    //Luego, se recorre el arreglo principal de la matriz original.
    for(int i = 0; i < nrows*ncols; i++)
        //Cada dato de la fila original se copia en la fila
        //correspondiente de la nueva matriz, quedando entonces
        //en la misma posición, en la misma celda.
        new_one[i/ncols][i%ncols] = original[i/ncols][i%ncols];
    //Se retorna la dirección del bloque de memoria
    //correspondiente a la nueva matriz.
    return new_one;
}
