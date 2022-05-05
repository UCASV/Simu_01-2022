#include <iostream>
#include <stdlib.h>

using namespace std;

/*
    Función para crear espacio en memoria para un
    arreglo unidimensional de caracteres de longitud
    <size>.
    Se retorna la dirección del espacio en memoria
    creado.
*/
char* create(int size){
    //Casting a (char*) ya que el bloque de memoria
    //se provee "crudo" ( void* ).
    //sizeof(char) ya que se almacenarán caracteres.
    //sizeof(char)*size para generar tantos espacios
    //como los indicados por el tamaño del arreglo.
    char* array = (char*) malloc(sizeof(char)*size);
    return array;
}

/*
    Función para insertar un caracter <value>
    en la posición <pos> de un arreglo de caracteres.
*/
void insert(char* array, int pos, char value){
    array[pos] = value;
    //*(array + pos) = value; //También funciona
}

/*
    Función para liberar todo el espacio en memoria
    utilizado por un arreglo de caracteres.
*/
void destroy(char* array){
    //Se indica la dirección inicial del bloque de
    //memoria a liberar.
    free(array);
}

/*
    Función que determina si un caracter <value>
    se encuentra o no dentro de un arreglo de caracteres.
    Se retorna true si se encuentra, false en caso
    contrario.
    <size> determina la longitud del arreglo, para
    controlar el límite del proceso de recorrido.
*/
bool search(char* array, int size, char value){
    //Respuesta por defecto: "No se encuentra."
    bool ans = false;
    //Se recorre el arreglo de caracteres.
    for(int i = 0; i < size; i++)
        //Verifico en la posición actual si se ha
        //encontrado el caracter buscado.
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
    de un caracter <value> en un arreglo de caracteres.
    <size> determina la longitud del arreglo, para
    controlar el límite del proceso de recorrido.
*/
int count(char* array, int size, char value){
    //Se inicializa un contador de suma
    int cont = 0;
    //Recorro el arreglo de caracteres
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
    Función que, dado un arreglo de caracteres, crea
    un nuevo arreglo de caracteres como copia exacta
    del original.
    <size> determina la longitud del arreglo original.
*/
char* create_copy(char* original, int size){
    //Se crea un nuevo arreglo de caracteres del mismo tamaño
    //que el original.
    char* new_one = (char*) malloc(sizeof(char)*size);
    //Se recorre el arreglo original
    for(int i = 0; i < size; i++)
        //Por cada posición, se coloca en el nuevo arreglo
        //el dato encontrado en el arreglo original.
        new_one[i] = original[i];
    //Se retorna la dirección del bloque de memoria
    //correspondiente al nuevo arreglo de caracteres.
    return new_one;
}

/*
    Función que, dado un arreglo de caracteres, invierte
    su contenido, es decir, el último dato se vuelve el
    primero, el penúltimo se vuelve el segundo, y así
    sucesivamente.
    <size> determina la longitud del arreglo.
*/
char* reverse(char* array, int size){
    //Se crea un nuevo arreglo de caracteres del mismo
    //tamaño del original.
    char* array2 = (char*) malloc(sizeof(char)*size);
    //Se recorre el arreglo original en reversa desde
    //la última posición.
    for (int i = size-1; i >= 0; i--){
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
    }
    //El arreglo original será sustituido por el nuevo arreglo,
    //por lo que dicho contenido ya no será utilizado y se puede
    //liberar.
    destroy(array);
    //Se retorna la dirección del nuevo bloque en memoria que
    //contiene la información invertida.
    return array2;
}
