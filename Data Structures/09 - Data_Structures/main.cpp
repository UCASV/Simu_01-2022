#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>

using namespace std;

#include "headers/SDDS.h"

template <typename T>
Data SDDS<T>::ref = Data();

int main(void){
    int n,m;
    bool b; 
    Data dim;    
    DS<int> *A,*M,*SL,*DL,*T,*G;
    DS<int> *A2,*M2,*SL2,*DL2,*T2,*G2;

    srand( time( NULL ) );

    SDDS<int>::create(&A,10,ARRAY);
    SDDS<int>::create(&M,3,3,MATRIX);
    SDDS<int>::create(&SL,SINGLE_LINKED_LIST);
    SDDS<int>::create(&DL,DOUBLE_LINKED_LIST);
    SDDS<int>::create(&T,BINARY_SEARCH_TREE);
    SDDS<int>::create(&G,GRAPH);

    for(int i = 0; i < 10; i++){
        SDDS<int>::insert(A,i,i);
        SDDS<int>::insert(SL,i);
        SDDS<int>::insert(DL,i);
        SDDS<int>::insert(G,i,i);
    }
    for(int k = 0; k < 9; k++) SDDS<int>::insert(M,k/3,k%3,k);
    for(int i = 0; i < 10; i++){
        SDDS<int>::insert( T, rand()%100 );
    }
    DS<int>* list;
    for(int g = 0; g < 10; g++){
        SDDS<int>::create(&list,SINGLE_LINKED_LIST);

        m = rand()%9+1;
        for(int c = 0; c < m; c++){
            n = rand()%10;
            SDDS<int>::search(list,n,&b);
            if(n!=g && !b) SDDS<int>::insert(list,n);
        }
        SDDS<int>::define_connections(G,g,list);

        SDDS<int>::destroy(list);
    }
    delete list;

    SDDS<int>::show(A,false);
    SDDS<int>::show(A,true);
    SDDS<int>::show(M,false);
    SDDS<int>::show(M,true);
    SDDS<int>::show(SL,false);
    SDDS<int>::show(SL,true);
    SDDS<int>::show(DL,false);
    SDDS<int>::show(DL,true);
    SDDS<int>::show(T,false);
    SDDS<int>::show(T,true);
    SDDS<int>::show(G,false);
    SDDS<int>::show(G,true);

    SDDS<int>::extension(A,&n);
    cout << "La longitud del arreglo es: " << n << "\n";
    SDDS<int>::extension(M,&n,&m);
    cout << "Las dimensiones de la matriz son: " << n << "x" << m << "\n";
    SDDS<int>::extension(SL,&n);
    cout << "La longitud de la lista enlazada simple es: " << n << "\n";
    SDDS<int>::extension(DL,&n);
    cout << "La longitud de la lista enlazada doble: " << n << "\n";
    SDDS<int>::extension(T,&n);
    cout << "La altura del árbol es: " << n << "\n";
    SDDS<int>::extension(G,&n);
    cout << "La cantidad de nodos en el grafo es: " << n << "\n";

    SDDS<int>::extract(A,3,&n);
    cout << "El dato extraído del arreglo es: " << n << "\n";
    SDDS<int>::extract(M,1,1,&n);
    cout << "El dato extraído de la matriz es: " << n << "\n";
    SDDS<int>::extract(SL,3,&n);
    cout << "El dato extraído de la lista enlazada simple es: " << n << "\n";
    SDDS<int>::extract(DL,3,&n);
    cout << "El dato extraído de la lista enlazada doble es: " << n << "\n";
    SDDS<int>::extract(G,3,&n);
    cout << "El dato extraído del grafo es: " << n << "\n";

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
    cout << "El resultado de búsqueda en el grafo resultó: " << ((b)?"TRUE\n":"FALSE\n");

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

    SDDS<int>::reverse(A2);
    cout << "Se muestra la copia del arreglo copia invertida:\n";
    SDDS<int>::show(A2,false);
    SDDS<int>::reverse(SL2);
    cout << "Se muestra la copia de la lista enlazada simple invertida:\n";
    SDDS<int>::show(SL2,false);
    SDDS<int>::reverse(DL2);
    cout << "Se muestra la copia de la lista enlazada doble invertida:\n";
    SDDS<int>::show(DL2,false);

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
