/*
    Enumeración utilizada para determinar la categoría de una
    estructura de datos dinámica:
        - SINGLE_LINKED_LIST para listas enlazadas simples.
        - DOUBLE_LINKED_LIST para listas enlazadas dobles.
        - BINARY_SEARCH_TREE para árboles binarios de búsqueda.
        - GRAPH para grafos.
*/
enum category {SINGLE_LINKED_LIST,DOUBLE_LINKED_LIST,BINARY_SEARCH_TREE,GRAPH};

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
#include "DSSL.h"
#include "DSDL.h"
#include "DST.h"
#include "DSG.h"

/*
    Clase utilitaria para la manipulación y administración
    de estructuras de datos dinámicas.

    La clase se encarga de la lógica de diferenciación entre
    listas enlazadas, árboles y grafos, a fin de que el "cliente"
    no se preocupe por ello.

    La clase hace uso de DSSL, DSDL, DST, o de DSG según sea el caso,
    recibiendo de parte del "cliente" objetos DS, clase padre
    en todos los casos, para aprovechar el polimorfismo en la
    transparencia de las operaciones.

    Al utilizar DS, DSSL, DSDL, DST, y/o DSG, dado que las cinco clases
    son templates, es necesario colocar el "meta-parámetro" que
    especifique el tipo de dato. Sin embargo, el tipo de dato
    aún no ha sido definido, ya que Dynamic_Structures también es un
    template, por lo que el "meta-parámetro" es del tipo de dato genérico
    local <type>.
*/
template <typename type>
class Dynamic_Structures{
    /*
        Funciones internas de uso exclusivo de la clase utilitaria misma.
    */
    private:
        /*
            Función que, dado un árbol binario de búsqueda, cuenta su cantidad
            de nodos y retorna el resultado.

            Se recibe <tree> como el árbol binario de búsqueda cuyos nodos de
            contarán.
        */
        static int count_nodes(NodeT<type>* tree){
            //Si el árbol está vacío, no hay nada que contar, se retorna 0
            if(tree == NULL) return 0;

            //Se cuenta el total de nodos del sub-árbol izquierdo, a esto
            //se le agrega el total de nodos del sub-árbol derecho, y luego
            //se le agrega 1 para tomar en cuenta el nodo actual, el resultado
            //se retorna como respuesta de la función
            return 1 + count_nodes(tree->left) + count_nodes(tree->right);
        }

        /*
            Función que, dado un árbol binario de búsqueda de tipo <type>, y un
            objeto DS, enviado **por referencia**, que contiene un árbol binario
            de búsqueda, también de tipo <type>, copia el contenido del árbol
            original en el árbol del objeto DS.

            Se recibe <O> como el árbol binario de búsqueda original, y se
            recibe <clone> como la dirección del puntero al objeto DS en cuyo
            árbol se copiará el contenido del árbol original.
        */
        static void copy_tree(NodeT<type>* O, DS<type>** clone){
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
        static void extract_graph_node(DS<type>* G, int id, NodeG<type>** node){
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
            NodeG<type>* graph = (NodeG<type>*) G->getRoot();

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
            NodeG<type>* graph = (NodeG<type>*) G->getRoot();

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

        /*
            Función que, dado un objeto DS que contiene un grafo de datos tipo
            <type>, el identificador de un nodo en dicho grafo, y una lista
            enlazada simple que contiene identificadores de nodos que se definirán
            como conexiones del nodo cuyo id sea igual al identificador dado.

            Se recibe <G> como el objeto DS que contiene el grafo de datos tipo
            <type>, se recibe <id> como el identificador del nodo cuyas conexiones
            se desean definir, y se recibe <C> como el listado de identificadores
            que definirán el listado de conexiones del nodo con el identificador
            dado.
        */
        static void define_connections_aux(DS<type>* G, int id, DS<int>* C){
            //Se construye un objeto DSSL que contendrá una lista enlazada simple
            //de punteros a Nodos de Grafo con datos de tipo <type>
            DSSL<NodeG<type>*>* graph_nodes = new DSSL<NodeG<type>*>();
            //Se define temp como una variable auxiliar puntero a Nodo de Grafo con
            //dato de tipo <type>
            NodeG<type>* temp;

            //Se recorre la lista de indicadores de nodos conectados
            //Se usa como límite la longitud de la lista <C>, la cual se obtiene
            //invocando su método extension()
            for(int i= 0; i < C->extension(); i++){
                /*Se envía a la función para extracción de dirección de un nodo en
                  un grafo:
                    - El grafo.
                    - El id del nodo cuya dirección necesitamos, indicado por el
                      entero en la posición actual de la lista de identificadores.
                    - La variable auxiliar temp, **por referencia**, para almacenar
                      la dirección obtenida.                                       */
                extract_graph_node(G,C->extract(i),&temp);

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
                  dirección de un nodo genérico a Nodo de estructura de datos
                  dinámica, por lo que se hace casting a la dirección de un Nodo
                  de lista enlazada simple de direcciones de Nodos de Grafo con
                  datos de tipo <type>.                                          */
            insert_connections(G,id, (NodeSL<NodeG<type>*>*) graph_nodes->getRoot());

            //Se libera el espacio de memoria utilizado por la lista enlazada simple
            //de punteros a Nodos de Grafo con datos de tipo <type> que fue utilizada
            //como variable auxiliar en el proceso
            delete graph_nodes;
        }
    
    //Se definen los métodos para cada una de las operaciones que el
    //"cliente" podrá realizar.
    public:
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
                case SINGLE_LINKED_LIST:
                    *var = new DSSL<type>(); break;
                case DOUBLE_LINKED_LIST:
                    *var = new DSDL<type>(); break;
                case BINARY_SEARCH_TREE:
                    *var = new DST<type>();  break;
                case GRAPH:
                    *var = new DSG<type>(); break;
            }
            
            //Una vez creado el objeto, invocamos su método create():
            /*
                Recordando:
                
                < DS** var > en este escenario es un DS* enviando
                por referencia, por lo que:

                                *var es de tipo DS*                         (A)
                (el contenido de un puntero doble es un puntero simple)

                DS* apuntaría entonces a la dirección de memoria
                donde está almacenado un objeto DS, para acceder a
                los métodos de este objeto necesitamos primero obtener
                el contenido a través del puntero, entonces:

                Digamos que la variable de tipo DS* se llama <data>,
                para obtener el objeto DS usamos operador de contenido:

                                        *data

                Y una vez lo tenemos en las manos, accedemos a sus métodos
                de la manera tradicional, eso sí, colocando paréntesis para
                que el operador de contenido '*' se ejecute antes del
                operador de acceso '.' (ejemplificamos con el método create):
                
                                    (*data).create()

                C++ permite hacer lo siguiente:

                                    (*data).create()
                                    data->create()                           (B)

                De forma que el '->' sustituye al '(*  ).'.

                Ahora bien, <data> no lo tenemos directamente, es decir, la
                variable que es de tipo DS* no la tenemos en las manos,
                tenemos solamente su dirección, por lo que introduciendo
                la expresión (A) en la expresión (B) obtenemos:

                                    data->create()
                                   (*var)->create()
                
                Recapitulando:
                    - var es la dirección de una variable de tipo DS*
                    - *var nos otorga la variable de tipo DS*
                    - Con (*var) tenemos la dirección de un objeto DS
                    - Con (*var)-> accedemos a los métodos del objeto DS
            */
            (*var)->create();
        }

        /*
            Función que retorna la extensión de la estructura
            de datos dinámica de un objeto DS de tipo <type>.

            El concepto de extensión de la estructura de datos dinámica:
                - Si la estructura es un árbol, su extensión es
                  su altura.
                - Si la estructura es un grafo, su extensión es
                  su cantidad de nodos.
                - En cualquier otro caso, la extensión será la
                  longitud de la estructura.
        */
        static void extension(DS<type>* var, int* n){
            //Se invoca el método extension() del objeto var y el
            //resultado se almacena en <n>
            *n = var->extension();
        }

        /*
            Función para insertar un valor <value> de tipo <type>
            en la estructura de datos dinámica de un objeto DS de tipo <type>.
        */
        static void insert(DS<type>* var, type value){
            //Se invoca el método insert() del objeto var enviando el valor
            //<value> a insertar
            var->insert(value);
        }
        /*
            Función para insertar un valor <value> de tipo <type>
            en la posición indicada por <n> de la estructura de datos
            dinámica de un objeto DS de tipo <type>.
        */
        static void insert(DS<type>* var, int n, type value){
            //Se invoca el método insert() del objeto var enviando la posición
            //<n> el valor <value> a insertar
            var->insert(n,value);
        }

        /*
            Función para extraer un dato de tipo <type> de la
            posición indicada por <pos> en la estructura de datos
            dinámica de un objeto DS de tipo <type>.
        */
        static void extract(DS<type>* var, int pos, type* res){
            //Se invoca el método extract() del objeto var enviando la posición
            //<pos> del dato a extraer, el resultado se almacena en <res>
            *res = var->extract(pos);
        }
        
        /*
            Función para liberar todo el espacio en memoria
            utilizado por una estructura de datos dinámica de un objeto DS de
            tipo <type>.
        */
        static void destroy(DS<type>* var){
            //Se invoca el método destroy() del objeto var
            var->destroy();
        }

        /*
            Función que determina si un valor <value> de tipo <type>
            se encuentra o no dentro de una estructura de datos dinámica
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
            <value> de tipo <type> en una estructura de datos dinámica
            de un objeto DS de tipo <type>.
        */
        static void count(DS<type>* var, type value, int* res){
            //Se invoca el método count() del objeto var enviando el valor <value>
            //cuyas ocurrencias se contarán, el resultado se almacena en <res>
            *res = var->count(value);
        }
        
        /*
            Función que invierte el contenido de una estructura de datos
            dinámica de un objeto DS detipo <type>.
        */
        static void reverse(DS<type>* var){
            //Se invoca el método reverse() del objeto var
            var->reverse();
        }

        /*
            Función que muestra el contenido de una estructura de datos
            dinámica de un objeto DS de tipo <type>.

            <verbose> indica el nivel de detalle a mostrar:
                - Si es false, solo se muestra la estructura de datos como tal.

                - Si es true, se detalla posición por posición, y nivel por nivel,
                  el contenido de la estructura de datos.
        */
        static void show(DS<type>* var, bool verbose){
            //Se invoca el método show() del objeto var
            var->show(verbose);
        }

        /* Utilidades adicionales que no forman parte de la interfaz DS
           ni de sus implementaciones */

        /*
            Función para contar los nodos de un árbol binario de búsqueda de
            un objeto DS de tipo <type>.
        */
        static void count(DS<type>* T, int* n){
            //Se obtiene la categoría del objeto DS de tipo <type> recibido
            //para verificar que se trate de un árbol binario de búsqueda
            if(T->getCategory() == BINARY_SEARCH_TREE){
                //Se invoca el método getRoot() del objeto T para obtener la
                //dirección del nodo raíz del árbol
                //getRoot() retorna la dirección a un Nodo genérico Node<type>,
                //por lo que es necesario hacer un casting a la dirección de un
                //nodo de un árbol binario de búsqueda con (NodeT<type>*)
                NodeT<type>* tree = (NodeT<type>*) T->getRoot();

                //Se envía el árbol a la función auxiliar para conteo de nodos,
                //y el resultado se almacena en <n>
                *n = count_nodes(tree);

            //Si no se trata de un árbol binario de búsqueda, se informa la
            //imposibilidad de la operación
            }else cout << "N/A\n";
        }

        /*
            Función para definir las conexiones de los nodos de un grafo de un
            objeto DS de tipo <type>.

            Por simplicidad, la información necesaria para las conexiones se
            recibe mediante una matriz de enteros bajo el método tradicional,
            quemada a dimensiones 5 x 4 por ser parte del ejemplo ilustrativo.
        */
        static void define_connections(DS<type>* G, int M[5][4]){
            //Se obtiene la categoría del objeto DS de tipo <type> recibido
            //para verificar que se trate de un grafo
            if(G->getCategory() == GRAPH){
                //Se prepara un objeto DS para una lista enlazada simple de
                //enteros
                DS<int>* indices;

                //Se invoca el método create() para inicializar la lista
                //enlazada simple de enteros
                create(&indices,SINGLE_LINKED_LIST);

                //Se recorren los nodos del grafo
                //Como se trata de un ejemplo ilustrativo se sabe que hay un
                //total de 5 nodos en el grafo
                for(int i = 0; i < 5; i++){

                    //Como se trata de un ejemplo ilustrativo se sabe que hay un
                    //total de 4 columnas en la matriz que contienen datos de
                    //conexiones: de la columna 1 a la columna 4
                    for(int j = 1; j < 4; j++)
                        //Sabemos que si la última columna tiene un -99, no hay
                        //que tomarla en cuenta
                        if(M[i][j] != -99)
                            //Se inserta en la lista de enteros el id del nodo con
                            //el que se tiene conexión
                            insert(indices,M[i][j]);
                    
                    /*Se envía a la función auxiliar para definición de conexiones:
                        - El objeto DS que contiene el grafo.
                        - La primera columna de la fila actual de la matriz, que es
                          el id del nodo cuyas conexiones estamos definiendo.
                        - El objeto DS que contiene la lista de enteros de los id de
                          los nodos con los que el nodo actual tiene conexión.      */
                    define_connections_aux(G,M[i][0],indices);

                    //Se libera el espacio de memoria de la lista construida
                    indices->destroy();
                }

                //Se libera el espacio de memoria del objeto DS creado para las listas de
                //enteros
                delete indices;

            //Si no se trata de un grafo, se informa la imposibilidad de
            //la operación
            }else cout << "N/A\n";
        }

        /*
            Función que recibe un objeto DS de tipo <type> por valor, y
            un segundo objeto DS, también de tipo <type>, por referencia, para copiar
            todo el contenido de la estructura de datos dinámica del primero
            en la estructura de datos dinámica del segundo.
        */
        static void create_copy(DS<type>* original, DS<type>** clone){
            //Se determina si el tipo de estructura de datos dinámica a copiar
            //invocando el método category() del objeto original
            switch(original->getCategory()){

                //Si se trata de una lista enlaza simple
                case SINGLE_LINKED_LIST: {
                    //Se instancia la copia creando un objeto DSSL
                    //haciendo uso del operador de contenido
                    *clone = new DSSL<type>();

                    //Se invoca el método create() de la copia
                    (*clone)->create();

                    /*
                      Se copia la referencia al primer nodo de la lista del
                      objeto original para no perderla durante el recorrido.
                      
                      Para obtener la dirección del primer nodo de la lista del
                      objeto original invocamos el método getRoot().
                      
                      Como getRoot() retorna la dirección de un Nodo genérico
                      para estructuras de datos dinámicas, hacemos casting a la
                      dirección de un Nodo de una lista enlazada simple de datos
                      tipo <type>.
                    */
                    NodeSL<type>* SL = (NodeSL<type>*) original->getRoot();

                    //Recorremos la lista del objeto original hasta el final
                    while(SL != NULL){
                        //El dato del nodo actual de la lista del objeto original
                        //se inserta en la lista del objeto copia
                        (*clone)->insert(SL->data);

                        //Se avanza al siguiente nodo de la lista
                        SL = SL->next;
                    }

                    //Dado que los datos se insertan al inicia de la lista, los
                    //datos del objeto original han quedado en orden inverso, por
                    //lo que invocamos el método reverse() del objeto copia
                    (*clone)->reverse();
                    break;
                }

                //Si se trata de una lista enlaza doble
                case DOUBLE_LINKED_LIST: {
                    //Se instancia la copia creando un objeto DSDL
                    //haciendo uso del operador de contenido
                    *clone = new DSDL<type>();

                    //Se invoca el método create() de la copia
                    (*clone)->create();

                    /*
                      Se copia la referencia al primer nodo de la lista del
                      objeto original para no perderla durante el recorrido.
                      
                      Para obtener la dirección del primer nodo de la lista del
                      objeto original invocamos el método getRoot().
                      
                      Como getRoot() retorna la dirección de un Nodo genérico
                      para estructuras de datos dinámicas, hacemos casting a la
                      dirección de un Nodo de una lista enlazada doble de datos
                      tipo <type>.
                    */
                    NodeDL<type>* DL = (NodeDL<type>*) original->getRoot();

                    //Recorremos la lista del objeto original hasta el final
                    while(DL != NULL){
                        //El dato del nodo actual de la lista del objeto original
                        //se inserta en la lista del objeto copia
                        (*clone)->insert(DL->data);

                        //Se avanza al siguiente nodo de la lista
                        DL = DL->next;
                    }

                    //Dado que los datos se insertan al inicia de la lista, los
                    //datos del objeto original han quedado en orden inverso, por
                    //lo que invocamos el método reverse() del objeto copia
                    (*clone)->reverse();
                    break;
                }

                //Si se trata de un árbol binario de búsqueda
                case BINARY_SEARCH_TREE: {
                    //Se instancia la copia creando un objeto DST
                    //haciendo uso del operador de contenido
                    *clone = new DST<type>();

                    //Se invoca el método create() de la copia
                    (*clone)->create();

                    /*
                      Se copia la referencia a la raíz del árbol del
                      objeto original para no perderla durante el recorrido.
                      
                      Para obtener la dirección de la raíz del árbol del
                      objeto original invocamos el método getRoot().
                      
                      Como getRoot() retorna la dirección de un Nodo genérico
                      para estructuras de datos dinámicas, hacemos casting a la
                      dirección de un Nodo de un árbol binario de búsqueda de datos
                      tipo <type>.
                    */
                    NodeT<type>* T = (NodeT<type>*) original->getRoot();

                    //Se envía el árbol del objeto original y el objeto copia a la
                    //función auxiliar para copiar árboles
                    copy_tree(T,clone);
                    break; 
                }

                //Si se trata de un grafo
                case GRAPH: {
                    //Se instancia la copia creando un objeto DSG
                    //haciendo uso del operador de contenido
                    *clone = new DSG<type>();

                    //Se invoca el método create() de la copia
                    (*clone)->create();

                    /*
                      Se copia la referencia al primer nodo del listado de
                      nodos del grafo del objeto original para no perderla
                      durante el recorrido.
                      
                      Para obtener la dirección del primer nodo del listado de
                      nodos del grafo del objeto original invocamos el método
                      getRoot().
                      
                      Como getRoot() retorna la dirección de un Nodo genérico
                      para estructuras de datos dinámicas, hacemos casting a la
                      dirección de un Nodo de una grafo de datos tipo <type>.
                    */
                    NodeG<type>* G = (NodeG<type>*) original->getRoot();

                    //Recorremos el listado de nodos del grafo hasta el final
                    while(G != NULL){
                        //Se coloca el dato del nodo actual del objeto original
                        //en el grafo del objeto copia, establenciendo como id
                        //el mismo identificador del nodo actual
                        (*clone)->insert(G->id,G->data);

                        /*
                            Se copia la referencia al primer nodo de la lista de
                            conexiones del nodo actual del grafo del objeto original
                            para no perderla durante el recorrido.
                            
                            El listado de conexiones del nodo actual se obtiene
                            directamente del nodo actual, es su campo 'connections'.

                            Recordar:
                                El listado de conexiones es una lista enlazada simple
                                que contiene punteros a Nodos de Grafo de tipo <type>.
                        */
                        NodeSL<NodeG<type>*>* O = G->connections;

                        //Se crea, a manera de variable auxiliar, un objeto DSSL para
                        //una lista enlazada simple de datos puntero a Nodo de grafo de
                        //datos tipo <type>
                        DSSL<NodeG<type>*>* L = new DSSL<NodeG<type>*>();

                        //Inicializamos la lista enlazada simple de la variable auxiliar
                        L->create();

                        //Recorremos las conexiones del nodo actual del grafo del objeto
                        //original hasta el final
                        while(O != NULL){
                            //La conexión actual se almacena en la lista de la variable
                            //auxiliar
                            L->insert(O->data);

                            //Se avanza a la conexión siguiente
                            O = O->next;
                        }

                        //Dado que los datos se insertan al inicia de la lista, las
                        //conexiones del nodo actual del grafo del objeto original han
                        //quedado en orden inverso, por lo que invocamos el método
                        //reverse() de la variable auxiliar
                        L->reverse();

                        /*Enviamos a la función para inserción de conexiones:
                            - El objeto copia.
                            - El identificador del nodo actual, para que se sepa a qué
                              nodo del grafo del objeto copia se le agregarán conexiones.
                            - El nodo inicial de la lista de la variable auxiliar, la cual
                              contiene las conexiones del nodo actual.
                              Para esto se hace uso de su método getRoot(), que como retorna
                              la dirección de un nodo genérico de estructura de datos dinámica,
                              se le hace casting a la dirección de un nodo de una lista enlazada
                              simple que contiene punteros a nodos de grafo con datos de tipo
                              <type>.                                                           */
                        insert_connections(*clone, G->id, (NodeSL<NodeG<type>*>* ) L->getRoot());

                        //Se avanza al siguiente nodo del grafo.
                        //Dado que el orden de los nodos en el listado principal del grafo no es
                        //relevante, no es necesario invocar el método reverse()
                        G = G->next;

                        //Se libera el espacio de memoria utilizado por la variable auxiliar
                        delete L;
                    }
                    break;
                }
            }
        }
};
