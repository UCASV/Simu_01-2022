/*
    Enumeración utilizada para determinar la categoría de una
    estructura de datos:
        - ARRAY para arreglos.
        - MATRIX para matrices.
        - SINGLE_LINKED_LIST para listas enlazadas simples.
        - DOUBLE_LINKED_LIST para listas enlazadas dobles.
        - BINARY_SEARCH_TREE para árboles binarios de búsqueda.
        - GRAPH para grafos.
*/
enum category {ARRAY,MATRIX,SINGLE_LINKED_LIST,DOUBLE_LINKED_LIST,BINARY_SEARCH_TREE,GRAPH};

/*
    Estructura Data utilizada en la manipulación de
    estructuras de datos estáticas.

    Contiene dos datos enteros, los arreglos utilizan uno
    de ellos su longitud, y las matrices usan ambos para su
    número de filas y número de columnas respectivamente.

    La estructura posee además un constructor genérico
    para poder realizar inicializaciones nulas.
*/
typedef struct Data{
    int n;
    int m;
    Data(){}
} Data;

/*
    Estructura Node utilizada para la creación de nodos para
    una estructura de datos dinámicas.

    Se define como template para hacerla independiente del tipo de
    dato a almacenar.

    Node es la estructura base, que contiene únicamente un dato
    de tipo <type>.
*/
template <typename type>
struct Node{
    type data;
};

/*
    Estructura NodeSL utilizada para la creación de nodos para
    una lista enlazada simple.

    La estructura extienda a la estructura Node, añadieno un
    puntero al siguiente nodo de la lista.

    Dado que Node es un template, y que acá aún no se ha determinado
    el tipo de dato a utilizar, NodeSL se define también como
    template y se establece el "meta-parámetro" al mencionar a
    Node.
*/
template <typename type>
struct NodeSL: Node<type>{
    NodeSL<type>* next;
};

/*
    Estructura NodeDL utilizada para la creación de nodos para
    una lista enlazada doble.

    La estructura extienda a la estructura Node, añadieno un
    puntero al nodo anterior en la lista y un puntero al siguiente
    nodo en la lista.

    Dado que Node es un template, y que acá aún no se ha determinado
    el tipo de dato a utilizar, NodeDL se define también como
    template y se establece el "meta-parámetro" al mencionar a
    Node.
*/
template <typename type>
struct NodeDL: Node<type>{
    NodeDL<type>* prev;
    NodeDL<type>* next;
};

/*
    Estructura NodeT utilizada para la creación de nodos para
    un árbol binario de búsqueda.

    La estructura extienda a la estructura Node, añadieno un
    puntero al nodo padre en el árbol, un puntero al hijo izquierdo
    en el árbol, y un puntero al hijo derecho en el árbol.

    Dado que Node es un template, y que acá aún no se ha determinado
    el tipo de dato a utilizar, NodeT se define también como
    template y se establece el "meta-parámetro" al mencionar a
    Node.
*/
template <typename type>
struct NodeT: Node<type>{
    NodeT<type>* parent;
    NodeT<type>* left;
    NodeT<type>* right;
};

/*
    Estructura NodeG utilizada para la creación de nodos para
    un grafo.

    La estructura extienda a la estructura Node, añadieno un
    booleano para indicar cuál es el nodo de entrada del grafo,
    un entero para almacenar el identificador del grafo, un puntero
    a una lista enlazada simple de punteros a nodo de grafo, la cual
    representa las conexiones del nodo en el grafo, y un puntero al
    nodo siguiente en el grafo.

    Dado que Node es un template, y que acá aún no se ha determinado
    el tipo de dato a utilizar, NodeG se define también como
    template y se establece el "meta-parámetro" al mencionar a
    Node.
*/
template <typename type>
struct NodeG: Node<type>{
    bool entry;
    int id;
    NodeSL<NodeG<type>*>* connections;
    NodeG<type>* next;
};

#include "DS.h"
#include "static/DSA.h"
#include "static/DSM.h"
#include "dynamic/DSSL.h"
#include "dynamic/DSDL.h"
#include "dynamic/DST.h"
#include "dynamic/DSG.h"

/*
    Clase utilitaria para la manipulación y administración
    de estructuras de datos, tanto estáticas como dinámicas.

    La clase se encarga de la lógica de diferenciación entre
    arreglos, matrices, listas enlazadas, árboles y grafos,
    a fin de que el "cliente" no se preocupe por ello.

    La clase hace uso de DSA, DSM, DSSL, DSDL, DST, o de DSG
    según sea el caso, recibiendo de parte del "cliente" objetos DS,
    clase base en todos los casos, para aprovechar el polimorfismo
    en la transparencia de las operaciones.

    Al utilizar DS, DSA, DSM, DSSL, DSDL, DST, y/o DSG, dado que las
    siete clases son templates, es necesario colocar el "meta-parámetro"
    que especifique el tipo de dato. Sin embargo, el tipo de dato
    aún no ha sido definido, ya que SDDS también es un template, por
    lo que el "meta-parámetro" es del tipo de dato genérico local
    <type>.
*/
template <typename type>
class SDDS{
    /*
        Funciones internas de uso exclusivo de la clase utilitaria misma.
    */
    private:
        /*
            Como atributo privado local se maneja una variable auxiliar
            de tipo "struct Data", para poder facilitar los procesos
            de manejo de las estructuras de datos estáticas.
        */
        static Data ref;

        /*========== Funciones para manejo de interfaces ===========*/

        /*
            Función que recibe un objeto insertable de tipo <type>
            para ejecutar su método insert(), enviando el <value>
            proporcionado.
        */
        static void insert_aux(insertable<type>* var, type value){
            var->insert(value);
        }

        /*
            Función que recibe un objeto positionable de tipo <type>
            para ejecutar su método insert(), enviando la posición
            <pos> y el valor <value> proporcionados.
        */
        static void insert_pos_aux(positionable<type>* var, int n, type value){
            var->insert(n, value);
        }

        /*
            Función que recibe un objeto positionable de tipo <type>
            para ejecutar su método extract(), enviando la posición
            <pos> proporcionada, y almacenando el resultado en <res>.
        */
        static void extract_aux(positionable<type>* var, int pos, type* res){
            *res = var->extract(pos);
        }

        /*
            Función que recibe un objeto measurable para ejecutar
            su método extension(), almacenando el resultado en <n>.
        */
        static void extension_aux(measurable* var, int* n){
            *n = var->extension();
        }

        /*
            Función que recibe un objeto reversible para ejecutar
            su método reverse().
        */
        static void reverse_aux(reversible* var){
            var->reverse();
        }

        /*====== Funciones para manejo de árboles ===============*/

        /*
            Función que, dado un árbol binario de búsqueda de tipo <type>, y un
            objeto DS, enviado **por referencia**, que contiene un árbol binario
            de búsqueda, también de tipo <type>, copia el contenido del árbol
            original en el árbol del objeto DS.

            Se recibe <O> como el árbol binario de búsqueda original, y se
            recibe <clone> como la dirección del puntero al objeto DS en cuyo
            árbol se copiará el contenido del árbol original.
        */
        static void copy_tree(NodeT<type>* O, DST<type>** clone){
            //Si el árbol original está vacío, no hay nada que copiar
            if(O == NULL) return;

            //El dato en el nodo actual del árbol original se inserta en el
            //árbol del objeto DS
            (*clone)->insert(O->data);

            //Se procede a copiar el contenido del sub-árbol izquierdo del
            //nodo actual del árbol original
            copy_tree(O->left, clone);
            //Se procede a copiar el contenido del sub-árbol derecho del
            //nodo actual del árbol original
            copy_tree(O->right, clone);
        }

        /*========= Funciones para manejo de grafos ===============*/

        /*
            Función que, dado un objeto DS que contiene un grafo de datos tipo
            <type>, el identificador de un nodo en dicho grago, y un puntero a
            nodo de grafo de datos tipo <type> **por referencia**, extrae la
            dirección del nodo al que corresponde el identificador y la almacena
            en el puntero.

            Se recibe <G> como el objeto DS que contiene el grafo de datos tipo
            <type>, se recibe <id> como el identificador del nodo cuya dirección
            se desea extraer, y se recibe <node> **por referencia** como el puntero
            donde se almacenará la dirección extraída.
        */
        static void extractNode(DS<type>* G, int id, NodeG<type>** node){
            /*
                Se copia la referencia al primer nodo del listado de
                nodos del grafo del objeto DS para no perderla
                durante el recorrido.
                
                Para obtener la dirección del primer nodo del listado de
                nodos del grafo del objeto DS invocamos el método
                getRoot().
                
                Como getRoot() retorna la dirección de un Nodo genérico
                para estructuras de datos dinámicas, hacemos casting a la
                dirección de un Nodo de una grafo de datos tipo <type>.
            */
            NodeG<type>* graph = (NodeG<type>*) ( (DSG<type>*) G )->getRoot();

            //Se recorre el listado de nodos del grafo hasta el final
            while(graph != NULL){
                //Terminamos el proceso cuando nos encontremos en el nodo
                //cuyo identificador es igual al proporcionado
                if(graph->id == id) break;

                //Se avanza al siguiente nodo del grafo
                graph = graph->next;
            }

            //Se almacena la dirección del nodo solicitado en <node>
            *node = graph;
        }

        /*
            Función que, dado un objeto DS que contiene un grafo de datos tipo
            <type>, el identificador de un nodo en dicho grafo, y una lista
            enlazada simple que contiene punteros a nodos en el grafo, define la
            lista dada como el listado de conexiones del nodo al que corresponde
            el identificador.

            Se recibe <G> como el objeto DS que contiene el grafo de datos tipo
            <type>, se recibe <id> como el identificador del nodo cuyas conexiones
            se desean definir, y se recibe <C> como el listado de direcciones de nodos
            del grafo que se convertirá en las conexiones del nodo con el identificador
            dado.
        */
        static void insert_connections(DS<type>* G, int id, NodeSL<NodeG<type>*>* C){
            /*
                Se copia la referencia al primer nodo del listado de
                nodos del grafo del objeto DS para no perderla
                durante el recorrido.
                
                Para obtener la dirección del primer nodo del listado de
                nodos del grafo del objeto DS invocamos el método
                getRoot().
                
                Como getRoot() retorna la dirección de un Nodo genérico
                para estructuras de datos dinámicas, hacemos casting a la
                dirección de un Nodo de una grafo de datos tipo <type>.
            */
            NodeG<type>* graph = (NodeG<type>*) ( (DSG<type>*) G )->getRoot();

            //Se recorre el listado de nodos del grafo hasta el final
            while(graph != NULL){
                //Verificamos si nos encontramos en el nodo indicado por
                //el identificador dado
                if(graph->id == id){
                    //Se coloca como conexiones del nodo indicado la lista
                    //proporcionada
                    graph->connections = C;
                    //No es necesario continuar con el recorrido
                    break;
                }

                //Se avanza al siguiente nodo del grafo
                graph = graph->next;
            }
        }

    /*Se definen los métodos para cada una de las operaciones que el
      "cliente" podrá realizar.                                      */
    public:
        /*=== Funciones básicas para uso de estructuras de datos ===*/

        /*
            Función para liberar todo el espacio en memoria
            utilizado por una estructura de datos de un objeto DS de
            tipo <type>.
        */
        static void destroy(DS<type>* var){
            //Se invoca el método destroy() del objeto var
            var->destroy();
        }

        /*
            Función que determina si un valor <value> de tipo <type>
            se encuentra o no dentro de una estructura de datos
            de un objeto DS de tipo <type>.

            Se retorna true si se encuentra, false en caso
            contrario.
        */
        static void search(DS<type>* var, type value, bool* res){
            //Se invoca el método search() del objeto var enviando el valor <value>
            //a buscar, el resultado se almacena en <res>
            *res = var->search(value);
        }

        /*
            Función que determina la cantidad de ocurrencias de un valor
            <value> de tipo <type> en una estructura de datos 
            de un objeto DS de tipo <type>.
        */
        static void count(DS<type>* var, type value, int* res){
            //Se invoca el método count() del objeto var enviando el valor <value>
            //cuyas ocurrencias se contarán, el resultado se almacena en <res>
            *res = var->count(value);
        }

        /*
            Función que muestra el contenido de una estructura de datos
            de un objeto DS de tipo <type>.

            <verbose> indica el nivel de detalle a mostrar:
                - Si es false, solo se muestra la estructura de datos como tal.

                - Si es true, se detalla posición por posición, y nivel por nivel,
                  el contenido de la estructura de datos.
        */
        static void show(DS<type>* var, bool verbose){
            //Se invoca el método show() del objeto var
            var->show(verbose);
        }

        /*==== Funciones para creación de estructuras de datos ====*/

        /*
            Función que instancia un puntero a objeto DS de tipo
            <type> enviado por referencia creando un objeto DSA.

            Se recibe <n> como el tamaño del arreglo a crear en el
            objeto DSA.
        */
        static void create(DS<type>** var, int n, category cat){
            //Se crea un objeto DSA, ya que se ha solicitado
            //un arreglo
            DSA<type>* array = new DSA<type>();
            
            //Una vez creado el objeto, invocamos su método create()
            //pasando por valor el valor <n> proporcionado
            array->create(n);

            //Instanciamos el objeto <var> con el nuevo objeto
            *var = array;
        }

        /*
            Función que instancia un puntero a objeto DS de tipo <type>
            enviado por referencia creando un objeto DSM.

            Se reciben <nrows> como el número de filas y <ncols> como el
            número de columnas de la matriz a crear en el objeto DSM.
        */
        static void create(DS<type>** var, int nrows, int ncols, category cat){
            //Se crea un objeto DSM, ya que se ha solicitado
            //una matriz
            DSM<type>* matrix = new DSM<type>();

            //Se utiliza la variable auxiliar para empaquetar
            //el número de filas y el número de columnas de la matriz
            //solicitada
            ref.n = nrows;
            ref.m = ncols;

            //Una vez creado el objeto, invocamos su método create()
            //pasando por valor la variable auxiliar
            matrix->create(ref);

            //Instanciamos el objeto <var> con el nuevo objeto
            *var = matrix;
        }

        /*
            Función que instancia un puntero a objeto DS de tipo
            <type> enviado por referencia creando un objeto dependiendo
            de la categoría especificada en <cat>:
                - Si <cat> es SINGLE_LINKED_LIST, se crea un objeto DSSL.
                - Si <cat> es DOUBLE_LINKED_LIST, se crea un objeto DSDL.
                - Si <cat> es BINARY_SEARCH_TREE, se crea un objeto DST.
                - Si <cat> es GRAPH, se crea un objeto DSG.
        */
        static void create(DS<type>** var, category cat){
            switch(cat){
                /*
                    En cada caso:
                        - Se crea el nuevo objeto.
                        - Se invoca su método create().
                        - Se instancia el objeto <var> con el
                          nuevo objeto.
                */

                case SINGLE_LINKED_LIST: {
                    DSSL<type>* SL = new DSSL<type>();
                    SL->create();
                    *var = SL;
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    DSDL<type>* DL = new DSDL<type>();
                    DL->create();
                    *var = DL;
                    break;
                }
                case BINARY_SEARCH_TREE: {
                    DST<type>* T = new DST<type>();
                    T->create();
                    *var = T;
                    break;
                }
                case GRAPH: {
                    DSG<type>* G = new DSG<type>();
                    G->create();
                    *var = G;
                    break;
                }
            }
        }

        /*==== Funciones para medición de estructuras de datos ====*/

        /*
            Función que retorna las dimensiones de la matriz de un objeto
            DS de tipo <type>.

            Se reciben por referencia una variable <rows> donde se almacenará
            el número de filas de la matriz y una variable <columns> donde
            se almacenará el número de columnas de la matriz.
        */
        static void extension(DS<type>* matrix, int* rows, int* columns){
            //Se invoca el método extension() del objeto matrix y el
            //resultado se almacena en la variable auxiliar
            //Dado que matrix es un DS genérico, se hace casting del
            //objeto a DSM antes de invocar a extension()
            ref = ( ( DSM<type>* ) matrix )->extension();

            //Se extraen el número de filas y el número de columnas,
            //el primer dato se almacena en <rows> y el segundo se almacena
            //en <columns>, en ambos caso haciendo uso del operador de
            //contenido
            *rows = ref.n;
            *columns = ref.m;
        }

        /*
            Función que retorna la extensión de la estructura
            de datos de un objeto DS de tipo <type>.

            El concepto de extensión depende de la estructura de datos:
                - Si la estructura es un árbol, su extensión es
                  su altura.
                - Si la estructura es un grafo, su extensión es
                  su cantidad de nodos.
                - En cualquier otro caso, la extensión será la
                  longitud de la estructura.
        */
        static void extension(DS<type>* var, int* n){
            //Se invoca getCategory() para determinar el tipo de
            //estructura de datos con la que se cuenta
            category cat = var->getCategory();

            switch(cat){
                /*
                    En cada caso:
                        - Se hace casting de <var> al objeto
                          correspondiente a la estructura de datos
                          en cuestión.
                        - Se envía el objeto casteado junto con <n>
                          a extension_aux().
                */

                case ARRAY: {
                    extension_aux( ((DSA<type>*) var), n);
                    break;
                }
                case SINGLE_LINKED_LIST: {
                    extension_aux( ((DSSL<type>*) var), n);
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    extension_aux( ((DSDL<type>*) var), n);
                    break;
                }
                case BINARY_SEARCH_TREE: {
                    extension_aux( ((DST<type>*) var), n);
                    break;
                }
                case GRAPH: {
                    extension_aux( ((DSG<type>*) var), n);
                    break;
                }
            }
        }

        /*==== Funciones para inserción en estructuras de datos ====*/

        /*
            Función que inserta un valor <value> de tipo <type> en la
            matriz de un objeto DS de tipo <type>.

            Se reciben <row> y <column> como el número de fila y el 
            número de columna, respectivamente, que corresponden a la
            celda de la matriz en la que se desea insertar <value>.
        */
        static void insert(DS<type>* matrix, int row, int column, type value){
            //Se colocan el número de fila y el número de columna en la
            //variable auxiliar
            ref.n = row; ref.m = column;

            //Se invoca el método insert() del objeto matrix
            //Como matrix se recibe como objeto genérico DS, primero se
            //le hace casting a objeto DSM.
            ( ( DSM<type>* ) matrix )->insert(ref,value);
        }

        /*
            Función para insertar un valor <value> de tipo <type>
            en la estructura de datos de un objeto DS de tipo <type>.
        */
        static void insert(DS<type>* var, type value){
            //Se invoca getCategory() para determinar el tipo de
            //estructura de datos con la que se cuenta
            category cat = var->getCategory();

            switch(cat){
                /*
                    En cada caso:
                        - Se hace casting de <var> al objeto
                          correspondiente a la estructura de datos
                          en cuestión.
                        - Se envía el objeto casteado junto con <value>
                          a insert_aux().
                */

                case SINGLE_LINKED_LIST: {
                    insert_aux( ((DSSL<type>*) var), value);
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    insert_aux( ((DSDL<type>*) var), value);
                    break;
                }
                case BINARY_SEARCH_TREE: {
                    insert_aux( ((DST<type>*) var), value);
                    break;
                }
            }
        }

        /*
            Función para insertar un valor <value> de tipo <type>
            en la posición indicada por <n> de la estructura de datos
            de un objeto DS de tipo <type>.
        */
        static void insert(DS<type>* var, int n, type value){
            //Se invoca getCategory() para determinar el tipo de
            //estructura de datos con la que se cuenta
            category cat = var->getCategory();

            switch(cat){
                /*
                    En cada caso:
                        - Se hace casting de <var> al objeto
                          correspondiente a la estructura de datos
                          en cuestión.
                        - Se envía el objeto casteado junto con <n>
                          y con <value> a insert_pos_aux().
                */

                case ARRAY: {
                    insert_pos_aux( ((DSA<type>*) var), n, value);
                    break;
                }
                case SINGLE_LINKED_LIST: {
                    insert_pos_aux( ((DSSL<type>*) var), n, value);
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    insert_pos_aux( ((DSDL<type>*) var), n, value);
                    break;
                }
                case GRAPH: {
                    insert_pos_aux( ((DSG<type>*) var), n, value);
                    break;
                }
            }
        }

        /*==== Funciones para extracción en estructuras de datos ====*/

        /*
            Función que extra un dato de tipo <type> de la matriz de un
            objeto DS de tipo <type>.

            Se reciben <row> y <column> como el número de fila y el 
            número de columna, respectivamente, que corresponden a la
            celda de la matriz en la que se desea extraer el dato.

            Se recibe <result> por referencia como la variable de tipo
            <type> donde se desea almacenar el dato extraído.
        */
        static void extract(DS<type>* matrix, int row, int column, type* result){
            //Se colocan el número de fila y el número de columna en la
            //variable auxiliar
            ref.n = row; ref.m = column;

            //Se invoca el método extract() del objeto matrix
            //Como matrix se recibe como objeto genérico DS, primero se
            //le hace casting a objeto DSM.
            *result = ( ( DSM<type>* ) matrix )->extract(ref);
        }

        /*
            Función para extraer un dato de tipo <type> de la
            posición indicada por <pos> en la estructura de datos
            de un objeto DS de tipo <type>.
        */
        static void extract(DS<type>* var, int pos, type* res){
            //Se invoca getCategory() para determinar el tipo de
            //estructura de datos con la que se cuenta
            category cat = var->getCategory();

            switch(cat){
                /*
                    En cada caso:
                        - Se hace casting de <var> al objeto
                          correspondiente a la estructura de datos
                          en cuestión.
                        - Se envía el objeto casteado junto con <pos>
                          y con <res> a extract_aux().
                */

                case ARRAY: {
                    extract_aux( ((DSA<type>*) var), pos, res);
                    break;
                }
                case SINGLE_LINKED_LIST: {
                    extract_aux( ((DSSL<type>*) var), pos, res);
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    extract_aux( ((DSDL<type>*) var), pos, res);
                    break;
                }
                case GRAPH: {
                    extract_aux( ((DSG<type>*) var), pos, res);
                    break;
                }
            }
        }

        /*==== Funciones para inversión de estructuras de datos ====*/

        /*
            Función que invierte el contenido de una estructura de datos
            de un objeto DS de tipo <type>.
        */
        static void reverse(DS<type>* var){
            //Se invoca getCategory() para determinar el tipo de
            //estructura de datos con la que se cuenta
            category cat = var->getCategory();

            switch(cat){
                /*
                    En cada caso:
                        - Se hace casting de <var> al objeto
                          correspondiente a la estructura de datos
                          en cuestión.
                        - Se envía el objeto casteado a reverse_aux().
                */

                case ARRAY: {
                    reverse_aux( ((DSA<type>*) var) );
                    break;
                }
                case SINGLE_LINKED_LIST: {
                    reverse_aux( ((DSSL<type>*) var) );
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    reverse_aux( ((DSDL<type>*) var) );
                    break;
                }
            }
        }

        /*==== Utilidades externas a la familia de clases 'DS' =====*/

        /*
            Función que, dado un objeto DS que contiene un grafo de datos tipo
            <type>, el identificador de un nodo en dicho grafo, y una lista
            enlazada simple que contiene identificadores de nodos que se definirán
            como conexiones del nodo cuyo id sea igual al proporcionado.

            Se recibe <G> como el objeto DS que contiene el grafo de datos tipo
            <type>, se recibe <id> como el identificador del nodo cuyas conexiones
            se desean definir, y se recibe <C> como el listado de identificadores
            que definirán el listado de conexiones del nodo con el identificador
            dado.
        */
        static void define_connections(DS<type>* G, int id, DS<int>* C){
            //Se construye un objeto DSSL que contendrá una lista enlazada simple
            //de punteros a Nodos de Grafo con datos de tipo <type>
            DSSL<NodeG<type>*>* graph_nodes = new DSSL<NodeG<type>*>();
            //Se define temp como una variable auxiliar puntero a Nodo de Grafo con
            //dato de tipo <type>
            NodeG<type>* temp;

            //Se adapta el listado de conexiones, dado como objeto genérico DS,
            //a un objeto DSSL, un objeto para listas enlazadas simples.
            DSSL<int>* L = (DSSL<int>*) C;

            //Se recorre la lista de indicadores de nodos conectados
            //Se usa como límite la longitud de la lista <L>, la cual se obtiene
            //invocando su método extension()
            for(int i= 0; i < L->extension(); i++){
                /*Se envía a la función para extracción de un nodo en un grafo:
                    - El grafo.
                    - El id del nodo cuya dirección necesitamos, indicado por el
                      entero en la posición actual de la lista de identificadores.
                    - La variable auxiliar temp, **por referencia**, para almacenar
                      la dirección obtenida.                                       */
                extractNode(G,L->extract(i),&temp);

                //Insertamos la dirección obtenida en el lista enlazada simple de
                //punteros a Nodos de Grafo de datos de tipo <type>
                graph_nodes->insert(temp);
            }

            /*Se envía a la función para inserción de conexiones:
                - El grafo.
                - El identificador del Nodo del grafo cuyas conexiones queremos
                  insertar.
                - La dirección del primer nodo de la lista de enlazada simple de
                  punteros a Nodos de Grafo de datos de tipo <type>, que ha sido
                  construido para ser las conexiones del grafo indicado.
                  Esta dirección se obtiene a través de getRoot() que devuelve la
                  dirección de un nodo genérico a Nodo de estructura de datos,
                  por lo que se hace casting a la dirección de un Nodo
                  de lista enlazada simple de direcciones de Nodos de Grafo con
                  datos de tipo <type>.                                          */
            insert_connections(G,id, (NodeSL<NodeG<type>*>*) graph_nodes->getRoot());

            //Se libera el espacio de memoria utilizado por la lista enlazada simple
            //de punteros a Nodos de Grafo con datos de tipo <type> que fue utilizada
            //como variable auxiliar en el proceso
            delete graph_nodes;
        }

        /*
            Función que recibe un objeto DS de tipo <type> por valor, y
            un segundo objeto DS, también de tipo <type>, por referencia, para copiar
            todo el contenido de la estructura de datos del primero
            en la estructura de datos del segundo.
        */
        static void create_copy(DS<type>* original, DS<type>** clone){
            //Se determina si el tipo de estructura de datos a copiar
            //invocando el método getCategory() del objeto original
            switch(original->getCategory()){
                case ARRAY: {
                    //Se instancia la copia creando un objeto DSA
                    //haciendo uso del operador de contenido
                    *clone = new DSA<type>();

                    //Se invoca el método extension_aux() enviando el
                    //objeto original casteado a DSA, para almacenar el
                    //resultado en <n>
                    int n;
                    extension_aux( ((DSA<type>*) original), &n);

                    //Se castea el objeto copia a DSA para invocar su
                    //método create() enviando <n>
                    ((DSA<type>*) *clone)->create(n);

                    //Se recorre el arreglo del objeto original
                    for(int i = 0; i < n; i++){
                        //Se invoca el método extract_aux() enviando el
                        //objeto original casteado a DSA, el iterador <i> como
                        //la posición deseada, a fin de almacenar el
                        //resultado en <v>
                        int v;
                        extract_aux(((DSA<type>*) original),i,&v);

                        //Se invoca el método insert_pos_aux() enviando el
                        //objeto copia casteado a DSA, el iterador <i> como
                        //la posición deseada para insertar <v>
                        insert_pos_aux(((DSA<type>*) *clone),i,v);
                    }
                    break;
                }

                case MATRIX: {
                    //Se instancia la copia creando un objeto DSM
                    //haciendo uso del operador de contenido
                    *clone = new DSM<type>();

                    //Se invoca el método extension() del objeto original
                    //casteado a DSM, para almacenar el resultado en la
                    //variable auxiliar
                    Data dim = ((DSM<type>*) original)->extension();

                    //Se castea el objeto copia a DSM para invocar su
                    //método create() enviando la variable auxiliar
                    ((DSM<type>*) *clone)->create(dim);

                    //Se recorre la matriz del objeto original
                    for(int i = 0; i < dim.n*dim.m; i++){
                        //Se almacena el número de fila y número de columna
                        //de la celda actual en la variable auxiliar
                        ref.n = i/dim.m;
                        ref.m = i%dim.m;

                        //Se invoca el método insert() de la copia, casteada a
                        //objeto DSM, enviando como dato a insertar el obtenido
                        //invocando el método extract() del objeto original, también
                        //casteado a DSM, para la celda actual
                        ((DSM<type>*) *clone)->insert(ref, ((DSM<type>*) original)->extract(ref));
                    }
                    break;
                }
                
                case SINGLE_LINKED_LIST: {
                    *clone = new DSSL<type>();
                    ((DSSL<type>*) *clone)->create();
                    NodeSL<type>* SL = (NodeSL<type>*) ((DSSL<type>*) original)->getRoot();
                    while(SL != NULL){
                        insert_aux( ((DSSL<type>*) *clone), SL->data);
                        SL = SL->next;
                    }
                    reverse_aux( ((DSSL<type>*) *clone) );
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    *clone = new DSDL<type>();
                    ((DSDL<type>*) *clone)->create();
                    NodeDL<type>* DL = (NodeDL<type>*) ((DSDL<type>*) original)->getRoot();
                    while(DL != NULL){
                        insert_aux( ((DSDL<type>*) *clone), DL->data);
                        DL = DL->next;
                    }
                    reverse_aux( ((DSDL<type>*) *clone) );
                    break;
                }
                case BINARY_SEARCH_TREE: {
                    *clone = new DST<type>();
                    ((DST<type>*) *clone)->create();
                    NodeT<type>* T = (NodeT<type>*) ((DST<type>*) original)->getRoot();
                    copy_tree(T, (DST<type>**) clone);
                    break; 
                }
                case GRAPH: {
                    *clone = new DSG<type>();
                    ((DSG<type>*) *clone)->create();
                    NodeG<type>* G = (NodeG<type>*) ((DSG<type>*) original)->getRoot();
                    while(G != NULL){
                        insert_pos_aux( ((DSG<type>*) *clone), G->id, G->data);
                        NodeSL<NodeG<type>*>* O = G->connections;
                        DSSL<NodeG<type>*>* L = new DSSL<NodeG<type>*>();
                        L->create();
                        while(O != NULL){
                            L->insert(O->data);
                            O = O->next;
                        }
                        L->reverse();
                        insert_connections(*clone,G->id,(NodeSL<NodeG<type>*>* ) L->getRoot());
                        G = G->next;
                        delete L;
                    }
                    break;
                }
            }
        }
};
