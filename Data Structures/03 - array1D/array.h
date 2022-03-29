#include <iostream>
#include <stdlib.h>

using namespace std;

/*  Ahora la librería hace uso de template,
    para que cada función quede independiente
    del tipo de dato a utilizar.

    Cuando las funciones sean utilizadas se deberá
    establecer el tipo de dato mediante un "meta-parámetro".

    En el proceso de compilación, cada template se copiará
    y se establecerá con un tipo de dato concreto por cada
    "meta-parámetro" utilizado.
*/

/*
    Función para crear espacio en memoria para un
    arreglo unidimensional de tipo <type> de longitud
    <size>.
    Se retorna la dirección del espacio en memoria
    creado.
*/
template <typename type>
type* create(int size){
    //Casting a (type*) ya que el bloque de memoria
    //se provee "crudo" ( void* ).
    //sizeof(type) ya que se almacenarán datos de tipo <type>.
    //sizeof(type)*size para generar tantos espacios
    //como los indicados por el tamaño del arreglo.
    type* array = (type*) malloc(sizeof(type)*size);
    return array;
}

/*
    Función para insertar un valor <value> de tipo <type>
    en la posición <pos> de un arreglo de datos de tipo <type>.
*/
template <typename type>
void insert(type* array, int pos, type value){
    array[pos] = value;
    //*(array + pos) = value; //También funciona
}

/*
    Función para liberar todo el espacio en memoria
    utilizado por un arreglo de datos tipo <type>.
*/
template <typename type>
void destroy(type* array){
    //Se indica la dirección inicial del bloque de
    //memoria a liberar.
    free(array);
}

/*
    Función que determina si un valor <value> de tipo <type>
    se encuentra o no dentro de un arreglo de datos de tipo <type>.
    Se retorna true si se encuentra, false en caso
    contrario.
    <size> determina la longitud del arreglo, para
    controlar el límite del proceso de recorrido.
*/
template <typename type>
bool search(type* array, int size, type value){
    //Respuesta por defecto: "No se encuentra."
    bool ans = false;
    //Se recorre el arreglo
    for(int i = 0; i < size; i++)
        //Verifico en la posición actual si se ha
        //encontrado el dato buscado.
        if(array[i] == value){
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
    de un valor <value> de tipo <type> en un arreglo
    de datos de tipo <type>.
    <size> determina la longitud del arreglo, para
    controlar el límite del proceso de recorrido.
*/
template <typename type>
int count(type* array, int size, type value){
    //Se inicializa un contador de suma
    int cont = 0;
    //Recorro el arreglo
    for(int i = 0; i < size; i++)
        //Verifico si hay ocurrencia en la posición
        //actual del arreglo
        if(array[i] == value)
            //Si hay ocurrencia, actualizo el contador.
            //No hay break, ya que me interesa saber
            //el total de ocurrencias, sigo buscando.
            cont++;
    //Retorno el resultado
    return cont;
}

/*
    Función que, dado un arreglo de datos de tipo <type,
    crea un nuevo arreglo de datos de tipo <type> como
    copia exacta del original.
    <size> determina la longitud del arreglo original.
*/
template <typename type>
type* create_copy(type* original, int size){
    //Se crea un nuevo arreglo de datos de tipo <type> del
    //mismo tamaño que el original.
    type* new_one = (type*) malloc(sizeof(type)*size);
    //Se recorre el arreglo original
    for(int i = 0; i < size; i++)
        //Por cada posición, se coloca en el nuevo arreglo
        //el dato encontrado en el arreglo original.
        new_one[i] = original[i];
    //Se retorna la dirección del bloque de memoria
    //correspondiente al nuevo arreglo de enteros.
    return new_one;
}

/*
    Función que, dado un arreglo de datos de tipo <type>,
    invierte su contenido, es decir, el último dato se vuelve
    el primero, el penúltimo se vuelve el segundo, y así
    sucesivamente.
    <size> determina la longitud del arreglo.
*/
template <typename type>
type* reverse(type* array, int size){
    //Se crea un nuevo arreglo de datos de tipo <type>
    //del mismo tamaño del original.
    type* array2 = (type*) malloc(sizeof(type)*size);
    //Se recorre el arreglo original en reversa desde
    //la última posición.
    for (int i = size-1; i >= 0; i--)
        /*
        Para determinar el índice en el nuevo arreglo
        donde se insertará el dato en la posición actual
        del recorrido del arreglo original, se toma en
        cuenta lo siguiente:

        Si el arreglo original tiene 5 posiciones,
        size es 5
        Posiciones: 0 1 2 3 4
        Queremos:
            - Guardar el dato de la posición 4 del
              original en la posición 0 del nuevo arreglo.
            - Guardar el dato de la posición 3 del
              original en la posición 1 del nuevo arreglo.
        
        Observando:
        4 -> 0 --> 5 - (4 + 1) = 0
        3 -> 1 --> 5 - (3 + 1) = 1
        2 -> 2 --> 5 - (2 + 1) = 2
        1 -> 3 --> 5 - (1 + 1) = 3
        0 -> 4 --> 5 - (0 + 1) = 4

        Es decir, a partir de la posición del arreglo
        original, se le suma 1 y el resultado se le resta
        a 5, y con esto se obtiene la posición requerida en
        el nuevo arreglo.

        Generalizando:

        indice_nuevo_arreglo = size - (indice_arreglo_original + 1)

        */
        array2[ size - (i + 1) ] = array[i];
    //El arreglo original será sustituido por el nuevo arreglo,
    //por lo que dicho contenido ya no será utilizado y se puede
    //liberar.
    destroy(array);
    //Se retorna la dirección del nuevo bloque en memoria que
    //contiene la información invertida.
    return array2;
}
