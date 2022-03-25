#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#include "headers/dynamicDS.h"

int main(void){
    int e,r,c;
    bool br;
    DS<int>* SL; DS<int>* SL2;
    DS<int>* DL; DS<int>* DL2;
    DS<int>* T; DS<int>* T2;
    DS<int>* G; DS<int>* G2;

    cout << "Probando creación de lista enlazada simple... ";
    Dynamic_Structures<int>::create(&SL,SINGLE_LINKED_LIST);
    cout << "OK\n";

    cout << "Probando inserción en lista enlazada simple... ";
    for(int i = 10; i > 0; i--)
        Dynamic_Structures<int>::insert(SL, i);
    cout << "OK\n";

    cout << "Obteniendo longitud de lista enlazada simple...\n";
    Dynamic_Structures<int>::extension(SL,&e);
    cout << "La longitud de la lista es: " << e << "\n";

    cout << "Mostrando lista...\n";
    Dynamic_Structures<int>::show(SL,false);

    cout << "Probando inserción en posición de lista enlazada simple... ";
    Dynamic_Structures<int>::insert(SL, 3, 50);
    cout << "OK\n";

    cout << "Mostrando lista...\n";
    Dynamic_Structures<int>::show(SL,false);

    cout << "Probando extracción de dato de lista enlazada simple...\n";
    Dynamic_Structures<int>::extract(SL,5,&r);
    cout << "El dato extraído es: " << r << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    Dynamic_Structures<int>::search(SL,7,&br);
    cout << "Resultado de búsqueda de dato existente: " << ((br)?"TRUE":"FALSE") << "\n";
    Dynamic_Structures<int>::search(SL,43,&br);
    cout << "Resultado de búsqueda de dato no existente: " << ((br)?"TRUE":"FALSE") << "\n";

    cout << "Provocando repetición de dato y probando conteo de ocurrencias...\n";
    Dynamic_Structures<int>::insert(SL, 7, 50);
    Dynamic_Structures<int>::count(SL,50,&c);
    cout << "El resultado del conteo es: " << c << "\n";

    cout << "Probando inversión de lista enlazada simple... ";
    Dynamic_Structures<int>::reverse(SL);
    cout << "OK\n";

    cout << "Mostrando la lista invertida...\n";
    Dynamic_Structures<int>::show(SL,false);

    cout << "Mostrando la lista enlazada simple en modo VERBOSE...\n";
    Dynamic_Structures<int>::show(SL,true);
    
    cout << "Probando creación de copia de la lista enlazada simple... ";
    Dynamic_Structures<int>::create_copy(SL,&SL2);
    cout << "OK\n";

    cout << "Mostrando la copia de la lista enlazada simple...\n";
    Dynamic_Structures<int>::show(SL2,false);

    cout << "Probando eliminación de lista enlazada simple... ";
    Dynamic_Structures<int>::destroy(SL);
    Dynamic_Structures<int>::destroy(SL2);
    cout << "OK\n";

    cout << "\n\n=============================================================\n\n";

    cout << "Probando creación de lista enlazada doble... ";
    Dynamic_Structures<int>::create(&DL,DOUBLE_LINKED_LIST);
    cout << "OK\n";

    cout << "Probando inserción en lista enlazada doble... ";
    for(int i = 10; i > 0; i--)
        Dynamic_Structures<int>::insert(DL, i);
    cout << "OK\n";

    cout << "Obteniendo longitud de lista enlazada doble...\n";
    Dynamic_Structures<int>::extension(DL,&e);
    cout << "La longitud de la lista es: " << e << "\n";

    cout << "Mostrando lista...\n";
    Dynamic_Structures<int>::show(DL,false);

    cout << "Probando inserción en posición de lista enlazada doble... ";
    Dynamic_Structures<int>::insert(DL, 3, 50);
    cout << "OK\n";

    cout << "Mostrando lista...\n";
    Dynamic_Structures<int>::show(DL,false);

    cout << "Probando extracción de dato de lista enlazada doble...\n";
    Dynamic_Structures<int>::extract(DL,5,&r);
    cout << "El dato extraído es: " << r << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    Dynamic_Structures<int>::search(DL,7,&br);
    cout << "Resultado de búsqueda de dato existente: " << ((br)?"TRUE":"FALSE") << "\n";
    Dynamic_Structures<int>::search(DL,43,&br);
    cout << "Resultado de búsqueda de dato no existente: " << ((br)?"TRUE":"FALSE") << "\n";

    cout << "Provocando repetición de dato y probando conteo de ocurrencias...\n";
    Dynamic_Structures<int>::insert(DL, 7, 50);
    Dynamic_Structures<int>::count(DL,50,&c);
    cout << "El resultado del conteo es: " << c << "\n";

    cout << "Probando inversión de lista enlazada doble... ";
    Dynamic_Structures<int>::reverse(DL);
    cout << "OK\n";

    cout << "Mostrando la lista invertida...\n";
    Dynamic_Structures<int>::show(DL,false);

    cout << "Mostrando la lista enlazada doble en modo VERBOSE...\n";
    Dynamic_Structures<int>::show(DL,true);
    
    cout << "Probando creación de copia de la lista enlazada doble... ";
    Dynamic_Structures<int>::create_copy(DL,&DL2);
    cout << "OK\n";

    cout << "Mostrando la copia de la lista enlazada doble...\n";
    Dynamic_Structures<int>::show(DL2,false);

    cout << "Probando eliminación de lista enlazada doble... ";
    Dynamic_Structures<int>::destroy(DL);
    Dynamic_Structures<int>::destroy(DL2);
    cout << "OK\n";

    cout << "\n\n=============================================================\n\n";

    cout << "Probando creación de árbol... ";
    Dynamic_Structures<int>::create(&T,BINARY_SEARCH_TREE);
    cout << "OK\n";

    cout << "Probando inserción en árbol... ";
    int datos[10] = {77,84,39,72,56,78,100,72,98,17};
    for(int i = 0; i < 10; i++)
        Dynamic_Structures<int>::insert(T, datos[i]);
    cout << "OK\n";

    cout << "Obteniendo altura de árbol...\n";
    Dynamic_Structures<int>::extension(T,&e);
    cout << "La altura del árbol es: " << e << "\n";

    cout << "Mostrando árbol...\n";
    Dynamic_Structures<int>::show(T,false);

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    Dynamic_Structures<int>::search(T,39,&br);
    cout << "Resultado de búsqueda de dato existente: " << ((br)?"TRUE":"FALSE") << "\n";
    Dynamic_Structures<int>::search(T,43,&br);
    cout << "Resultado de búsqueda de dato no existente: " << ((br)?"TRUE":"FALSE") << "\n";

    cout << "Probando conteo de ocurrencias...\n";
    Dynamic_Structures<int>::count(T,72,&c);
    cout << "El resultado del conteo es: " << c << "\n";

    cout << "Probando conteo de nodos...\n";
    Dynamic_Structures<int>::count(T,&c);
    cout << "El número de nodos es: " << c << "\n";

    cout << "Mostrando el árbol en modo VERBOSE...\n";
    Dynamic_Structures<int>::show(T,true);
    
    cout << "Probando creación de copia del árbol... ";
    Dynamic_Structures<int>::create_copy(T,&T2);
    cout << "OK\n";

    cout << "Mostrando la copia del árbol...\n";
    Dynamic_Structures<int>::show(T2,false);

    cout << "Probando eliminación de árbol... ";
    Dynamic_Structures<int>::destroy(T);
    Dynamic_Structures<int>::destroy(T2);
    cout << "OK\n";

    cout << "\n\n=============================================================\n\n";

    cout << "Probando creación de grafo... ";
    Dynamic_Structures<int>::create(&G,GRAPH);
    cout << "OK\n";

    cout << "Probando inserción en grafo... ";
    for(int i = 0; i < 5; i++)
        Dynamic_Structures<int>::insert(G, i+1, i+1);
    cout << "OK\n";

    cout << "Probando extracción de dato del grafo...\n";
    Dynamic_Structures<int>::extract(G,5,&r);
    cout << "El dato extraído es: " << r << "\n";    

    cout << "Mostrando grafo...\n";
    Dynamic_Structures<int>::show(G,false);

    cout << "Probando definición de conexiones para los nodos del grafo...\n";
    //De momento está quemado, luego se hará uso de Array2D
    int M[5][4] = { { 1, 3, 4, -99 }, { 2, 3, 5, -99 }, { 3, 4, 1, 2 }, { 4, 3, 1, 5 }, { 5, 4, 2, -99 } };
    Dynamic_Structures<int>::define_connections(G, M);

    cout << "Mostrando grafo...\n";
    Dynamic_Structures<int>::show(G,false);

    cout << "Obteniendo cantidad de nodos del grafo...\n";
    Dynamic_Structures<int>::extension(G,&e);
    cout << "La cantidad de nodos es: " << e << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    Dynamic_Structures<int>::search(G,3,&br);
    cout << "Resultado de búsqueda de dato existente: " << ((br)?"TRUE":"FALSE") << "\n";
    Dynamic_Structures<int>::search(G,43,&br);
    cout << "Resultado de búsqueda de dato no existente: " << ((br)?"TRUE":"FALSE") << "\n";

    cout << "Mostrando el grafo en modo VERBOSE...\n";
    Dynamic_Structures<int>::show(G,true);
    
    cout << "Probando creación de copia del grafo... ";
    Dynamic_Structures<int>::create_copy(G,&G2);
    cout << "OK\n";

    cout << "Mostrando la copia del grafo...\n";
    Dynamic_Structures<int>::show(G2,false);

    cout << "Probando eliminación de grafo... ";
    Dynamic_Structures<int>::destroy(G);
    Dynamic_Structures<int>::destroy(G2);
    cout << "OK\n";

    delete SL; delete SL2;
    delete DL; delete DL2;
    delete T; delete T2;
    delete G; delete G2;

    return 0;
}
