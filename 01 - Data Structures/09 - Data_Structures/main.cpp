#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>

using namespace std;

#include "headers/SDDS.h"

/*
    La clase SDDS se ha definido exclusivamente con
    métodos y atributos estáticos, ya que se ha concebido
    como una clase utilitaria.

    C++ requiere, para los atributos estáticos, que se
    realice, antes del proceso, una asignación para que
    se genere el espacio de memoria correspondiente.

    En este escenario, ref es de tipo Data, que es una struct,
    y es un atributo estático de la clase SDDS, por lo que
    comenzamos por asignarle un struct vacío.

    La sintaxis de esta asignación es:

            <tipo> <Clase>::<atributo> = <valor_nulo>;

    Para el caso:
        - <tipo> es Data.
        - Clase es SDDS.
        - <atributo> es ref.
        - <valor_nulo>, por ser un struct, requiere una
          instanciación vacía de la misma haciendo uso
          de un constructor genérico.

    Por último, dado que SDDS es un template, es necesario
    realizar esta instanciación establecienco el "meta-parámetro";
    sin embargo, ya que el proceso no ha comenzado aún no está
    definido el tipo de dato concreto a utilizar, por lo que
    se "acarrea" el template.
*/
template <typename T>
Data SDDS<T>::ref = Data();

int main(void){
    //Conjunto de variables auxiliares que se utilizarán
    //en el proceso ilustrativo.
    int n,m;
    bool b; 
    Data dim;    

    //Se hará uso de la generación de números aleatorios con las
    //herramientas que se encuentran en <stdlib.h>
    //Primero, debe establecerse la "seed" del algoritmo de generación,
    //lo que se realiza mediante la función time()
    srand( time( NULL ) );

    /*
        A partir de este momento, toda operación con estructuras
        de datos se hará a través de la clase utilitaria SDDS.

        Para hacer el proceso completamente transparente al "cliente",
        que en este caso es el proceso ilustrativo de main, se trabaja
        haciendo uso de una clase genérica llamada simplemente DS.

        El "cliente" no deberá preocuparse por las diferecias de uso
        e implementación entre arreglos, matrices, listas, árboles o
        grafos, la clase utilitaria se encargará de todo esto.

        Como SDDS es un template, para su uso deberá especificarse el
        tipo de dato a utilizar mediante un "meta-parámetro".
    */

   /*
        Todos los objetos serán creados en SDDS mediante el operador
        'new', el cual devuelve un puntero al objeto creado, por ende,
        todos los DS se manejan por dirección, y se declaran acá
        los respectivos punteros.
    */

    //Punteros a DS que se utilizarán para las distintas estructuras
    DS<int> *A,*M,*SL,*DL,*T,*G;
    //Un segundo puntero a DS por tipo de estructura que será utilizado
    //en las pruebas de creación de copias
    DS<int> *A2,*M2,*SL2,*DL2,*T2,*G2;

    /*========= Se crean las estructuras =============*/
    cout << "Creando arreglo...";
    SDDS<int>::create(&A,10,ARRAY);
    cout << "OK.\nCreando matriz...";
    SDDS<int>::create(&M,3,3,MATRIX);
    cout << "OK.\nCreando lista enlazada simple...";
    SDDS<int>::create(&SL,SINGLE_LINKED_LIST);
    cout << "OK.\nCreando lista enlazada doble...";
    SDDS<int>::create(&DL,DOUBLE_LINKED_LIST);
    cout << "OK.\nCreando árbol binario de búsqueda...";
    SDDS<int>::create(&T,BINARY_SEARCH_TREE);
    cout << "OK.\nCreando grafo...";
    SDDS<int>::create(&G,GRAPH);
    cout << "OK.\n\n";

    /*========= Se llenan las estructuras con datos ========*/
    cout << "Llenando arreglo +\nLlenando lista enlazada simple +\nLlenando lista enlazada doble +\nLlenando grafo\n............................";
    for(int i = 0; i < 10; i++){
        SDDS<int>::insert(A,i,i);
        SDDS<int>::insert(SL,i);
        SDDS<int>::insert(DL,i);
        SDDS<int>::insert(G,i,i);
    }
    cout << "OK.\nLlenando matriz...";
    for(int k = 0; k < 9; k++) SDDS<int>::insert(M,k/3,k%3,k);
    cout << "OK.\nLlenando árbol binario de búsqueda...";
    for(int i = 0; i < 10; i++){
        //Se coloca en el árbol un dato aleatorio entre 0 y 99
        SDDS<int>::insert( T, rand()%100 );
    }
    cout << "OK.\nGenerando conexiones para el grafo...";
    //Se prepara como variable auxiliar un objeto DS para una
    //lista enlazada simple de enteros
    DS<int>* list;
    SDDS<int>::create(&list,SINGLE_LINKED_LIST);

    //Se recorren los distintos id que se colocaron en el grafo
    for(int g = 0; g < 10; g++){
        //Se genera un número aleatorio entre 1 y 9,
        //esto será la cantidad de conexiones que se le definirán
        //al nodo en el grafo correspondiente al id actual del
        //recorrido
        m = rand()%9+1;

        //Se procede a tantas conexiones como se definión en m
        for(int c = 0; c < m; c++){
            //Se genera un número aleatorio entre 1 y 9, esto será
            //el id del nodo que se conectará el nodo actual del
            //recorrido
            n = rand()%10;

            //Verificamos si ya existe conexión registrada con el
            //nodo generado
            SDDS<int>::search(list,n,&b);

            //Si no existe aún conexión con el nodo generado, y
            //el nodo generado no es el mismo nodo actual (porque
            //no queremos bucles), entonces añadimos el id generado
            //en la lista auxiliar
            if(n!=g && !b) SDDS<int>::insert(list,n);
        }

        //Ya que se tienen construidas las conexiones del nodo actual,
        //se invoca a define_connections() enviando el Grafo, el id
        //del nodo actual, y la lista de id de sus conexiones
        SDDS<int>::define_connections(G,g,list);

        //El contenido de la lista actual ya no es necesario, se procede
        //a eliminarlo
        SDDS<int>::destroy(list);
    }
    //Se elimina el objeto auxiliar
    delete list;
    cout << "OK.\n\n";

    /*========== Se muestra el contenido de las estructuras ========*/
    cout << "Mostrando arreglo en modo simple:\n";
    SDDS<int>::show(A,false);
    cout << "\nMostrando arreglo en modo verbose:\n";
    SDDS<int>::show(A,true);
    cout << "\nMostrando matriz en modo simple:\n";
    SDDS<int>::show(M,false);
    cout << "\nMostrando matriz en modo verbose:\n";
    SDDS<int>::show(M,true);
    cout << "\nMostrando lista enlazada simple en modo simple:\n";
    SDDS<int>::show(SL,false);
    cout << "\nMostrando lista enlazada simple en modo verbose:\n";
    SDDS<int>::show(SL,true);
    cout << "\nMostrando lista enlazada doble en modo simple:\n";
    SDDS<int>::show(DL,false);
    cout << "\nMostrando lista enlazada doble en modo verbose:\n";
    SDDS<int>::show(DL,true);
    cout << "\nMostrando árbol binario de búsqueda en modo simple:\n";
    SDDS<int>::show(T,false);
    cout << "\nMostrando árbol binario de búsqueda en modo verbose:\n";
    SDDS<int>::show(T,true);
    cout << "\nMostrando grafo en modo simple:\n";
    SDDS<int>::show(G,false);
    cout << "\nMostrando grafo en modo verbose:\n";
    SDDS<int>::show(G,true);

    /*========== Se muestran las extensiones de las estructuras ========*/
    SDDS<int>::extension(A,&n);
    cout << "\nLa longitud del arreglo es: " << n << "\n";
    SDDS<int>::extension(M,&n,&m);
    cout << "Las dimensiones de la matriz son: " << n << "x" << m << "\n";
    SDDS<int>::extension(SL,&n);
    cout << "La longitud de la lista enlazada simple es: " << n << "\n";
    SDDS<int>::extension(DL,&n);
    cout << "La longitud de la lista enlazada doble: " << n << "\n";
    SDDS<int>::extension(T,&n);
    cout << "La altura del árbol es: " << n << "\n";
    SDDS<int>::extension(G,&n);
    cout << "La cantidad de nodos en el grafo es: " << n << "\n\n";

    /*========== Se extraen datos de las estructuras ========*/
    SDDS<int>::extract(A,3,&n);
    cout << "El dato extraído del arreglo es: " << n << "\n";
    SDDS<int>::extract(M,1,1,&n);
    cout << "El dato extraído de la matriz es: " << n << "\n";
    SDDS<int>::extract(SL,3,&n);
    cout << "El dato extraído de la lista enlazada simple es: " << n << "\n";
    SDDS<int>::extract(DL,3,&n);
    cout << "El dato extraído de la lista enlazada doble es: " << n << "\n";
    SDDS<int>::extract(G,3,&n);
    cout << "El dato extraído del grafo es: " << n << "\n\n";

    /*========== Se buscan datos en las estructuras ========*/
    SDDS<int>::search(A,3,&b);
    cout << "El resultado de búsqueda en el arreglo resultó: " << ((b)?"TRUE\n":"FALSE\n");
    SDDS<int>::search(M,4,&b);
    cout << "El resultado de búsqueda en la matriz resultó: " << ((b)?"TRUE\n":"FALSE\n");
    SDDS<int>::search(SL,3,&b);
    cout << "El resultado de búsqueda en la lista enlazada simple resultó: " << ((b)?"TRUE\n":"FALSE\n");
    SDDS<int>::search(DL,16,&b);
    cout << "El resultado de búsqueda en la lista enlazada doble resultó: " << ((b)?"TRUE\n":"FALSE\n");
    SDDS<int>::search(T,45,&b);
    cout << "El resultado de búsqueda en el árbol resultó: " << ((b)?"TRUE\n":"FALSE\n");
    SDDS<int>::search(G,6,&b);
    cout << "El resultado de búsqueda en el grafo resultó: " << ((b)?"TRUE\n\n":"FALSE\n\n");

    /*========== Se cuentan los datos de las estructuras ========*/
    SDDS<int>::count(A,3,&n);
    cout << "El resultado del conteo en el arreglo resultó: " << n << "\n";
    SDDS<int>::count(M,4,&n);
    cout << "El resultado del conteo en la matriz resultó: " << n << "\n";
    SDDS<int>::count(SL,3,&n);
    cout << "El resultado del conteo en la lista enlazada simple resultó: " << n << "\n";
    SDDS<int>::count(DL,10,&n);
    cout << "El resultado del conteo en la lista enlazada doble resultó: " << n << "\n";
    SDDS<int>::count(T,33,&n);
    cout << "El resultado del conteo en el árbol resultó: " << n << "\n";
    SDDS<int>::count(G,6,&n);
    cout << "El resultado del conteo en el grafo resultó: " << n << "\n";

    /*========== Se crean copias de las estructuras ========*/
    SDDS<int>::create_copy(A,&A2);
    cout << "Se muestra la copia del arreglo:\n";
    SDDS<int>::show(A2,false);
    SDDS<int>::create_copy(M,&M2);
    cout << "Se muestra la copia de la matriz:\n";
    SDDS<int>::show(M2,false);
    SDDS<int>::create_copy(SL,&SL2);
    cout << "Se muestra la copia de la lista enlazada simple:\n";
    SDDS<int>::show(SL2,false);
    SDDS<int>::create_copy(DL,&DL2);
    cout << "Se muestra la copia de la lista enlazada doble:\n";
    SDDS<int>::show(DL2,false);
    SDDS<int>::create_copy(T,&T2);
    cout << "Se muestra la copia del árbol:\n";
    SDDS<int>::show(T2,false);
    SDDS<int>::create_copy(G,&G2);
    cout << "Se muestra la copia del grafo:\n";
    SDDS<int>::show(G2,false);

    /*========== Se invierten las estructuras ========*/
    SDDS<int>::reverse(A2);
    cout << "\nSe muestra la copia del arreglo copia invertida:\n";
    SDDS<int>::show(A2,false);
    SDDS<int>::reverse(SL2);
    cout << "Se muestra la copia de la lista enlazada simple invertida:\n";
    SDDS<int>::show(SL2,false);
    SDDS<int>::reverse(DL2);
    cout << "Se muestra la copia de la lista enlazada doble invertida:\n";
    SDDS<int>::show(DL2,false);

    /*========== Se procede a hacer la limpieza de la memoria ==========*/
    SDDS<int>::destroy(A);      SDDS<int>::destroy(A2);
    SDDS<int>::destroy(M);      SDDS<int>::destroy(M2);
    SDDS<int>::destroy(SL);     SDDS<int>::destroy(SL2);
    SDDS<int>::destroy(DL);     SDDS<int>::destroy(DL2);
    SDDS<int>::destroy(T);      SDDS<int>::destroy(T2);
    SDDS<int>::destroy(G);      SDDS<int>::destroy(G2);

    delete A;    delete A2;
    delete M;    delete M2;
    delete SL;   delete SL2;
    delete DL;   delete DL2;
    delete T;    delete T2;
    delete G;    delete G2;

    return 0;
}
