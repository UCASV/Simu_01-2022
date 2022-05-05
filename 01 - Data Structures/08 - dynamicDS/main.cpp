#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#include "headers/dynamicDS.h"

/*
    La clase Dynamic_Structures se ha definido exclusivamente con
    métodos estáticos, ya que se ha concebido como una clase utilitaria.

    Adicionalmente, dado que Dynamic_Structures es un template, es
    necesario hacer uso de sus métodos establecienco el "meta-parámetro"
    en cada una de sus respectivas llamadas.
*/

int main(void){
    //Conjunto de variables auxiliares que se utilizarán
    //en el proceso ilustrativo.
    int e,r,c;
    bool br;

    /*
        A partir de este momento, toda operación con estructuras
        de datos dinámicas se hará a través de la clase utilitaria
        Dynamic_Structures.

        Para hacer el proceso completamente transparente al "cliente",
        que en este caso es el proceso ilustrativo de main, se trabaja
        haciendo uso de una clase genérica llamada simplemente DS.

        El "cliente" no deberá preocuparse por las diferecias de uso
        e implementación entre listas, árboles y grafos, la clase utilitaria
        se encargará de todo esto.
    */

    /*
        Toda estructura dinámica se maneja mediante un objeto DS,
        que generaliza el concepto, dejando el detalle de diferenciación
        y de implementación a la clase utilitaria Dynamic_Structures.

        Todos los objetos serán creados en Dynamic_Structures mediante
        el operador 'new', el cual devuelve un puntero al objeto creado,
        por ende, todos los DS se manejan por dirección, y se declaran acá
        los respectivos punteros.
    */

    //Se preparan punteros para dos DS de enteros que se manejarán
    //como listas enlazadas simples. El segundo es exclusivo para la prueba
    //del proceso de creación de copia.
    DS<int>* SL; DS<int>* SL2;
    //Se preparan punteros para dos DS de enteros que se manejarán
    //como listas enlazadas dobles. El segundo es exclusivo para la prueba
    //del proceso de creación de copia.
    DS<int>* DL; DS<int>* DL2;
    //Se preparan punteros para dos DS de enteros que se manejarán
    //como árboles binarios de búsqueda. El segundo es exclusivo para la prueba
    //del proceso de creación de copia.
    DS<int>* T; DS<int>* T2;
    //Se preparan punteros para dos DS de enteros que se manejarán
    //como grafos. El segundo es exclusivo para la prueba del proceso de
    //creación de copia.
    DS<int>* G; DS<int>* G2;

    cout << "Probando creación de lista enlazada simple... ";
    /*
        El objeto DS será creado en Dynamic_Structures, pero para poder
        tener acceso a la asignación correspondiente, el puntero local
        debe enviarse **por referencia** usando el operador de dirección
        '&'.
    */
    Dynamic_Structures<int>::create(&SL,SINGLE_LINKED_LIST);
    cout << "OK\n";

    cout << "Probando inserción en lista enlazada simple... ";
    //Insertamos en reversa ya que la inserción se hace por defecto al
    //inicio de la lista, para que los datos queden en forma ascendente
    for(int i = 10; i > 0; i--)
        Dynamic_Structures<int>::insert(SL, i);
    cout << "OK\n";

    cout << "Obteniendo longitud de lista enlazada simple...\n";
    /*
        Para mantener una perspectiva estricta en el uso de la clase
        utilitaria, en el caso de operaciones que proveen un resultado
        también se delega la asignación a Dynamic_Structures, requiriendo
        entonces el envío **por referencia** de la variable en la que queremos
        guardar el resultado.

        Esto aplica a todas las operaciones de Dynamic_Structures que generan
        resultados de algún tipo, y se verá reflejado en todas las instrucciones
        a continuación que utilicen operaciones de esta naturaleza.

        Esto puede ser opcional dependiendo de la implementación,
        permitiendo que la asignación sea local y que la clase utilitaria sí
        retorne datos.
    */
    //Se obtiene la longitud de la lista y se almacena en la variable auxiliar e
    Dynamic_Structures<int>::extension(SL,&e);
    cout << "La longitud de la lista es: " << e << "\n";

    cout << "Mostrando lista...\n";
    Dynamic_Structures<int>::show(SL,false); //false indica que no se necesita modo VERBOSE

    cout << "Probando inserción en posición de lista enlazada simple... ";
    //Insertamos un 50 en la posición 3 de la lista
    Dynamic_Structures<int>::insert(SL, 3, 50);
    cout << "OK\n";

    cout << "Mostrando lista...\n";
    Dynamic_Structures<int>::show(SL,false);

    cout << "Probando extracción de dato de lista enlazada simple...\n";
    //Extraemos el dato almacenado en la posición 5 de la lista y lo almacenamos
    //en la variable auxiliar r
    Dynamic_Structures<int>::extract(SL,5,&r);
    cout << "El dato extraído es: " << r << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    //Se sabe que 7 es un dato que sí está en la lista
    //El resultado se almacena en la variable auxiliar br
    Dynamic_Structures<int>::search(SL,7,&br);
    cout << "Resultado de búsqueda de dato existente: " << ((br)?"TRUE":"FALSE") << "\n";
    //Se sabe que 43 es un dato que no está en la lista
    //El resultado se almacena en la variable auxiliar br
    Dynamic_Structures<int>::search(SL,43,&br);
    cout << "Resultado de búsqueda de dato no existente: " << ((br)?"TRUE":"FALSE") << "\n";

    cout << "Provocando repetición de dato y probando conteo de ocurrencias...\n";
    //Insertamos otro 50 en la posición 7 para hacer el conteo más ilustrativo
    Dynamic_Structures<int>::insert(SL, 7, 50);
    //Contamos las ocurrencias del 50 y almacenamos el resultado en la variable auxiliar c
    Dynamic_Structures<int>::count(SL,50,&c);
    cout << "El resultado del conteo es: " << c << "\n";

    cout << "Probando inversión de lista enlazada simple... ";
    Dynamic_Structures<int>::reverse(SL);
    cout << "OK\n";

    cout << "Mostrando la lista invertida...\n";
    Dynamic_Structures<int>::show(SL,false);

    cout << "Mostrando la lista enlazada simple en modo VERBOSE...\n";
    Dynamic_Structures<int>::show(SL,true); //true indica la ejecución del modo VERBOSE
    
    cout << "Probando creación de copia de la lista enlazada simple... ";
    //SL se envía **por valor**, ya que en Dynamic_Structures sólo se utilizará su contenido
    //SL2 se envía **por referencia**, ya que necesito acceso local a la asignación que
    //Dynamic_Structures ejecutará
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
    /*
        El objeto DS será creado en Dynamic_Structures, pero para poder
        tener acceso a la asignación correspondiente, el puntero local
        debe enviarse **por referencia** usando el operador de dirección
        '&'.
    */
    Dynamic_Structures<int>::create(&DL,DOUBLE_LINKED_LIST);
    cout << "OK\n";

    cout << "Probando inserción en lista enlazada doble... ";
    //Insertamos en reversa ya que la inserción se hace por defecto al
    //inicio de la lista, para que los datos queden en forma ascendente
    for(int i = 10; i > 0; i--)
        Dynamic_Structures<int>::insert(DL, i);
    cout << "OK\n";

    cout << "Obteniendo longitud de lista enlazada doble...\n";
    //Se obtiene la longitud de la lista y se almacena en la variable auxiliar e
    Dynamic_Structures<int>::extension(DL,&e);
    cout << "La longitud de la lista es: " << e << "\n";

    cout << "Mostrando lista...\n";
    Dynamic_Structures<int>::show(DL,false); //false indica que no se necesita modo VERBOSE

    cout << "Probando inserción en posición de lista enlazada doble... ";
    //Insertamos un 50 en la posición 3 de la lista
    Dynamic_Structures<int>::insert(DL, 3, 50);
    cout << "OK\n";

    cout << "Mostrando lista...\n";
    Dynamic_Structures<int>::show(DL,false);

    cout << "Probando extracción de dato de lista enlazada doble...\n";
    //Extraemos el dato almacenado en la posición 5 de la lista y lo almacenamos
    //en la variable auxiliar r
    Dynamic_Structures<int>::extract(DL,5,&r);
    cout << "El dato extraído es: " << r << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    //Se sabe que 7 es un dato que sí está en la lista
    //El resultado se almacena en la variable auxiliar br
    Dynamic_Structures<int>::search(DL,7,&br);
    cout << "Resultado de búsqueda de dato existente: " << ((br)?"TRUE":"FALSE") << "\n";
    //Se sabe que 43 es un dato que no está en la lista
    //El resultado se almacena en la variable auxiliar br
    Dynamic_Structures<int>::search(DL,43,&br);
    cout << "Resultado de búsqueda de dato no existente: " << ((br)?"TRUE":"FALSE") << "\n";

    cout << "Provocando repetición de dato y probando conteo de ocurrencias...\n";
    //Insertamos otro 50 en la posición 7 para hacer el conteo más ilustrativo
    Dynamic_Structures<int>::insert(DL, 7, 50);
    //Contamos las ocurrencias del 50 y almacenamos el resultado en la variable auxiliar c
    Dynamic_Structures<int>::count(DL,50,&c);
    cout << "El resultado del conteo es: " << c << "\n";

    cout << "Probando inversión de lista enlazada doble... ";
    Dynamic_Structures<int>::reverse(DL);
    cout << "OK\n";

    cout << "Mostrando la lista invertida...\n";
    Dynamic_Structures<int>::show(DL,false);

    cout << "Mostrando la lista enlazada doble en modo VERBOSE...\n";
    Dynamic_Structures<int>::show(DL,true); //true indica la ejecución del modo VERBOSE
    
    cout << "Probando creación de copia de la lista enlazada doble... ";
    //DL se envía **por valor**, ya que en Dynamic_Structures sólo se utilizará su contenido
    //DL2 se envía **por referencia**, ya que necesito acceso local a la asignación que
    //Dynamic_Structures ejecutará
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
    /*
        El objeto DS será creado en Dynamic_Structures, pero para poder
        tener acceso a la asignación correspondiente, el puntero local
        debe enviarse **por referencia** usando el operador de dirección
        '&'.
    */
    Dynamic_Structures<int>::create(&T,BINARY_SEARCH_TREE);
    cout << "OK\n";

    cout << "Probando inserción en árbol... ";
    //Por simplicidad, ya que esto es un proceso ilustrativo con énfasis
    //en las estructuras de datos dinámicas, construimos un arreglo de 10
    //enteros con datos a ingresar en el árbol de la forma tradicional
    int datos[10] = {77,84,39,72,56,78,100,72,98,17};
    //Recorremos el arreglo para insertar sus datos en el árbol
    for(int i = 0; i < 10; i++)
        Dynamic_Structures<int>::insert(T, datos[i]);
    cout << "OK\n";

    cout << "Obteniendo altura de árbol...\n";
    //Se obtiene la altura del árbol y se almacena en la variable auxiliar e
    Dynamic_Structures<int>::extension(T,&e);
    cout << "La altura del árbol es: " << e << "\n";

    cout << "Mostrando árbol...\n";
    Dynamic_Structures<int>::show(T,false); //false indica que no se necesita modo VERBOSE

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    //Se sabe que 39 es un dato que sí está en el árbol
    //El resultado se almacena en la variable auxiliar br
    Dynamic_Structures<int>::search(T,39,&br);
    cout << "Resultado de búsqueda de dato existente: " << ((br)?"TRUE":"FALSE") << "\n";
    //Se sabe que 43 es un dato que no está en el árbol
    //El resultado se almacena en la variable auxiliar br
    Dynamic_Structures<int>::search(T,43,&br);
    cout << "Resultado de búsqueda de dato no existente: " << ((br)?"TRUE":"FALSE") << "\n";

    cout << "Probando conteo de ocurrencias...\n";
    //Contamos las ocurrencias del 72 y almacenamos el resultado en la variable auxiliar c
    Dynamic_Structures<int>::count(T,72,&c);
    cout << "El resultado del conteo es: " << c << "\n";

    cout << "Probando conteo de nodos...\n";
    //Contamos la cantidad de nodos en el árbol y almacenamos el resultado en la variable auxiliar c
    Dynamic_Structures<int>::count(T,&c);
    cout << "El número de nodos es: " << c << "\n";

    cout << "Mostrando el árbol en modo VERBOSE...\n";
    Dynamic_Structures<int>::show(T,true); //true indica la ejecución del modo VERBOSE
    
    cout << "Probando creación de copia del árbol... ";
    //T se envía **por valor**, ya que en Dynamic_Structures sólo se utilizará su contenido
    //T2 se envía **por referencia**, ya que necesito acceso local a la asignación que
    //Dynamic_Structures ejecutará
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
    /*
        El objeto DS será creado en Dynamic_Structures, pero para poder
        tener acceso a la asignación correspondiente, el puntero local
        debe enviarse **por referencia** usando el operador de dirección
        '&'.
    */
    Dynamic_Structures<int>::create(&G,GRAPH);
    cout << "OK\n";

    cout << "Probando inserción en grafo... ";
    //Insertamos solamente 5 nodos usando el iterador del 'for' tanto para los
    //identificadores como para los datos almacenados, ya que es únicamente
    //para propósitos ilustrativos
    for(int i = 0; i < 5; i++)
        Dynamic_Structures<int>::insert(G, i+1, i+1);
    cout << "OK\n";

    cout << "Probando extracción de dato del grafo...\n";
    //Extraemos el dato almacenado en el nodo #5 de la lista y lo almacenamos
    //en la variable auxiliar r
    Dynamic_Structures<int>::extract(G,5,&r);
    cout << "El dato extraído es: " << r << "\n";    

    cout << "Mostrando grafo...\n";
    Dynamic_Structures<int>::show(G,false); //false indica que no se necesita modo VERBOSE

    cout << "Probando definición de conexiones para los nodos del grafo...\n";
    //Por simplicidad, ya que esto es un proceso ilustrativo con énfasis
    //en las estructuras de datos dinámicas, construimos un matriz de la forma tradicional
    //para establecer un conjunto de conexiones para cada uno de los nodos del grafo

    /*
        En este ejemplo se trabaja con el siguiente grafo:
        
          1 ------ 4 ------- 5
           \       |         |
             \     |         |
               \   |         |
                 \ |         |
                   3 ------- 2

        Esto se almacena con una estructura que, en principio, es muy similar a una lista
        enlazada simple:

                        Nodo -> Nodo -> ... -> Nodo -> NULL

        Ahora bien, el contenido de cada nodo de este listado es una 3-tupla con la siguiente
        información:

                            ( <id>, <dato>, <conexiones> )
        
            - <id> es el identificador del nodo, un número único que lo diferencia de todos
              los demás nodos del grafo.

            - <dato> es la información de tipo <type> que el nodo almacena.

            - <conexiones> es una lista enlazada simple que contiene punteros a nodos del
              grafo, representando todos los otros nodos del grafo con los que este nodo
              tiene conexión.

        Por simplicidad, asumiremos que todas las condiciones son bidireccionales.

        Las conexiones para el grafo de la ilustración son las siguientes:

            - El Nodo 1 conecta con los Nodos 3 y 4.
            - El Nodo 2 conecta con los Nodos 3 y 5.
            - El Nodo 3 conecta con los Nodos 4, 1 y 2.
            - El Nodo 4 conecta con los Nodos 3, 1 y 5.
            - El Nodo 5 conecta con los Nodos 4 y 2.

        Para simplificar el proceso podemos ubicar estos datos en una simple matriz:

                [ 1 ][ 3 ][ 4 ][ - ]
                [ 2 ][ 3 ][ 5 ][ - ]
                [ 3 ][ 4 ][ 1 ][ 2 ]
                [ 4 ][ 3 ][ 1 ][ 5 ]
                [ 5 ][ 4 ][ 2 ][ - ]

        En cada fila, la primera columna tiene el id de un nodo del grafo, y el resto de
        columnas contienen los id de los nodos a los que está conectado.

        Como los Nodos del grafo no tienen necesariamente la misma cantidad de conexiones, nos
        quedan algunas celdas vacía. Únicamente para facilitar el proceso, representaremos una
        conexión vacía con un -99 :

                [ 1 ][ 3 ][ 4 ][ -99 ]
                [ 2 ][ 3 ][ 5 ][ -99 ]
                [ 3 ][ 4 ][ 1 ][  2  ]
                [ 4 ][ 3 ][ 1 ][  5  ]
                [ 5 ][ 4 ][ 2 ][ -99 ]
    */
    //Se define la matriz con la información del grafo ejemplo
    int M[5][4] = { { 1, 3, 4, -99 }, { 2, 3, 5, -99 }, { 3, 4, 1, 2 }, { 4, 3, 1, 5 }, { 5, 4, 2, -99 } };
    //Pasamos la matriz para que las conexiones puedan ser definidas dentro de nuestro objeto
    //DS para el Grafo
    Dynamic_Structures<int>::define_connections(G, M);

    cout << "Mostrando grafo...\n";
    //Volvemos a mostrar el grafo para visualizar las conexiones definidas
    Dynamic_Structures<int>::show(G,false);

    cout << "Obteniendo cantidad de nodos del grafo...\n";
    //Se obtiene la cantidad de nodos del grafo y se almacena en la variable auxiliar e
    Dynamic_Structures<int>::extension(G,&e);
    cout << "La cantidad de nodos es: " << e << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    //Se sabe que 3 es un dato que sí está en el grafo
    //El resultado se almacena en la variable auxiliar br
    Dynamic_Structures<int>::search(G,3,&br);
    cout << "Resultado de búsqueda de dato existente: " << ((br)?"TRUE":"FALSE") << "\n";
    //Se sabe que 43 es un dato que sí está en el grafo
    //El resultado se almacena en la variable auxiliar br
    Dynamic_Structures<int>::search(G,43,&br);
    cout << "Resultado de búsqueda de dato no existente: " << ((br)?"TRUE":"FALSE") << "\n";

    cout << "Probando conteo de ocurrencias de un dato...\n";
    //Contamos las ocurrencias del 4 y almacenamos el resultado en la variable auxiliar c
    Dynamic_Structures<int>::count(G,4,&c);
    cout << "El resultado del conteo es: " << c << "\n";

    cout << "Mostrando el grafo en modo VERBOSE...\n";
    Dynamic_Structures<int>::show(G,true); //true indica la ejecución del modo VERBOSE
    
    cout << "Probando creación de copia del grafo... ";
    //G se envía **por valor**, ya que en Dynamic_Structures sólo se utilizará su contenido
    //G2 se envía **por referencia**, ya que necesito acceso local a la asignación que
    //Dynamic_Structures ejecutará
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
