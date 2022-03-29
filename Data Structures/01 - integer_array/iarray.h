#include <iostream>
#include <stdlib.h>

using namespace std;

/*
    Función para crear espacio en memoria para un
    arreglo unidimensional de enteros de longitud
    <size>.
    Se retorna la dirección del espacio en memoria
    creado.
*/
int* create(int size){
    //Casting a (int*) ya que el bloque de memoria
    //se provee "crudo" ( void* ).
    //sizeof(int) ya que se almacenarán enteros.
    //sizeof(int)*size para generar tantos espacios
    //como los indicados por el tamaño del arreglo.
    int* array = (int*) malloc(sizeof(int)*size);
    return array;
}

/*
    Función para insertar un valor entero <value>
    en la posición <pos> de un arreglo de enteros.
*/
void insert(int* array, int pos, int value){
    array[pos] = value;
    //*(array + pos) = value; //También funciona
}

/*
    Función para liberar todo el espacio en memoria
    utilizado por un arreglo de enteros.
*/
void destroy(int* array){
    //Se indica la dirección inicial del bloque de
    //memoria a liberar.
    free(array);
}

/*
    Función que determina si un valor entero <value>
    se encuentra o no dentro de un arreglo de enteros.
    Se retorna true si se encuentra, false en caso
    contrario.
    <size> determina la longitud del arreglo, para
    controlar el límite del proceso de recorrido.
*/
bool search(int* array, int size, int value){
    //Respuesta por defecto: "No se encuentra."
    bool ans = false;
    //Se recorre el arreglo de enteros.
    for(int i = 0; i < size; i++)
        //Verifico en la posición actual si se ha
        //encontrado el entero buscado.
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
    de un valor entero <value> en un arreglo de enteros.
    <size> determina la longitud del arreglo, para
    controlar el límite del proceso de recorrido.
*/
int count(int* array, int size, int value){
    //Se inicializa un contador de suma
    int cont = 0;
    //Recorro el arreglo de entero
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
    Función que, dado un arreglo de enteros, crea
    un nuevo arreglo de enteros como copia exacta
    del original.
    <size> determina la longitud del arreglo original.
*/
int* create_copy(int* original, int size){
    //Se crea un nuevo arreglo de enteros del mismo tamaño
    //que el original.
    int* new_one = (int*) malloc(sizeof(int)*size);
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
    Función que, dado un arreglo de enteros, invierte
    su contenido, es decir, el último dato se vuelve el
    primero, el penúltimo se vuelve el segundo, y así
    sucesivamente.
    <size> determina la longitud del arreglo.
*/
int* reverse(int* array, int size){
    //Se crea un nuevo arreglo de enteros del mismo
    //tamaño del original.
    int* array2 = (int*) malloc(sizeof(int)*size);
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
        a 5, y con estose obtiene la posición requerida en
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
