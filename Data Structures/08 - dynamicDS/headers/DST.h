/*
    Implementación de la interfaz DS, definida en "DS.h", para un árbol
    binario de búsqueda.

    Se define la implementación como independiente del tipo de dato
    a almacenar mediante el uso de template.
*/
template <typename type>
/*
    En C++, la implementación se maneja como una herencia,
    de modo que DST hereda de DS.

    El indicador de visibilidad 'public' indica que DST tendrá
    acceso a todos los métodos de DS manteniendo la visibilidad
    original.

    Dado que DS es un template, debe indicarse el tipo de dato
    a utilizar mediante un "meta-parámetro". Sin embargo, el tipo
    de dato aún no ha sido definido, ya que DST también es un
    template, por lo que el "meta-parámetro" es el tipo de dato
    genérico local <type>.
*/
class DST: public DS<type>{
    private:
        /*
            Como atributo privado local se manejará el árbol binario de
            búsqueda de tipo <type> como tal.
        
            Se declara un puntero a NodeT, un Nodo para árboles binarios
            de búsqueda.
        */
        NodeT<type>* T;

        /*
            Función que crea espacio en memoria para un NodeT<type>,
            es decir, un Nodo para un árbol binario de búsqueda de tipo
            <type>.

            Se retorna la dirección del nuevo nodo creado, y esta
            dirección se retorna en forma "cruda" como void*.
        */
        void* createNode() override {
            //sizeof( NodeT<type> ) ya que se necesita espacio para
            //un Nodo para árboles binarios de búsqueda para almacenar un
            //dato de tipo <type>
            return malloc(sizeof(NodeT<type>));
        }

        /*=== Funciones auxiliares para el manejo de árboles binarios de búsqueda ===*/
        /*
            Función auxiliar para calcular la altura de un árbol binario de búsqueda
            de tipo <type>.

            Se recibe <tree> como el árbol cuya altura se desea calcular.
        */
        int height(NodeT<type>* tree){
            //Si el árbol está vacío su altura es 0
            if(tree == NULL) return 0;

            //Si el árbol no está vacío, se calcula la altura del sub-árbol
            //izquierdo y la altura del sub-árbol derecho, luego se determina
            //cuál de estos resultados es el más grande y se retorna sumándole 1,
            //para incluir el nodo actual en el conteo
            return max( 1 + height(tree->left) , 1 + height(tree->right) );
        }

        /*
            Función auxiliar para insertar un nuevo nodo en un árbol binario de
            búsqueda de tipo <type>.

            Se recibe <node> como el nuevo nodo a insertar en el árbol, y se recibe
            <tree> como el árbol donde se insertará dicho nodo.

            Se asume que se recibe un árbol no vacío.
        */
        void insert_aux(NodeT<type>* tree, NodeT<type>* node){
            //Si el dato del nuevo nodo es menor o igual al dato
            //del nodo actual, el nuevo nodo deberá insertarse en el
            //sub-árbol izquierdo
            if(node->data <= tree->data)
                //Se verifica si el sub-árbol izquierdo es una hoja
                if(tree->left == NULL){
                    //El nuevo nodo será el nuevo hijo izquierdo

                    //El padre del nuevo nodo es el nodo actual
                    node->parent = tree;
                    //El hijo izquierdo del nodo actual es el nuevo nodo
                    tree->left = node;
                }else
                    //Si el sub-árbol izquierdo no es una hoja, se procede
                    //a insertar el nuevo nodo en dicho sector
                    insert_aux(tree->left,node);
            
            //Si el dato del nuevo nodo es mayor al dato del nodo actual,
            //el nuevo nodo deberá insertarse en el sub-árbol derecho
            else
                //Se verifica si el sub-árbol derecho es una hoja
                if(tree->right == NULL){
                    //El nuevo nodo será el nuevo hijo derecho

                    //El padre del nuevo nodo es el nodo actual
                    node->parent = tree;
                    //El hijo derecho del nodo actual es el nuevo nodo
                    tree->right = node;
                }else
                    //Si el sub-árbol derecho no es una hoja, se procede
                    //a insertar el nuevo nodo en dicho sector
                    insert_aux(tree->right,node);
        }

        /*
            Función auxiliar para la liberación de memoria de un árbol binario
            de búsqueda de tipo <type>.

            Se recibe <tree> como el árbol cuyo espacio en memoria se liberará.
        */
        void destroy_aux(NodeT<type>* tree){
            //Si el árbol está vacío no hay nada que liberar
            if(tree == NULL) return;

            //Se libera todo el espacio de memoria utilizado por el sub-árbol
            //izquierdo
            destroy_aux(tree->left);

            //Se libera todo el espacio de memoria utilizado por el sub-árbol
            //derecho
            destroy_aux(tree->right);

            //Se libera el espacio de memoeria utilizado por el nodo actual
            free(tree);
        }

        /*
            Función auxiliar para la búsqueda de un dato de tipo <type> en un
            árbol binario de búsqueda de tipo <type>.

            Se recibe <value> como el dato a buscar en el árbol, y se recibe
            <tree> como él árbol donde se hará la búsqueda.

            Se retorna true si el dato se encuentra en el árbol, y se retorna
            false en caso contrario.
        */
        bool search_aux(NodeT<type>* tree, type value){
            //Si el árbol está vacío no hay nada que buscar
            if(tree == NULL) return false;

            //Si el árbol no está vacío, se verifica si el dato actual coincide
            //con el dato buscado.
            //De ser así se retorna una respuesta de éxito.
            if(tree->data == value) return true;

            //De no haberse encontrado el dato en el nodo actual, se retorna el
            //resultado de buscarlo en el sub-árbol izquierdo y/o el sub-árbol
            //derecho
            return search_aux(tree->left,value) || search_aux(tree->right,value);
        }

        /*
            Función auxiliar para el conteo de ocurrencias de un dato de tipo
            <type> en un árbol binario de búsqueda de tipo <type>.

            Se recibe <value> como el dato cuyas ocurrencias se desean contar,
            y se recibe <tree> como el árbol donde se hará el proceso.

            Se retorna el resultado del conteo
        */
        int count_aux(NodeT<type>* tree, type value){
            //Si el árbol está vacío, no hay nada que contar
            if(tree == NULL) return 0;

            //Si el árbol no está vacío, se cuentan las ocurrencias de <value> en
            //el sub-árbol izquierda, a esto se le suma el total de ocurrencias de
            //<value> en el sub-árbol derecho, y finalmente a esto se le suma 1 sólo
            //si el dato del nodo actual también es una ocurrencia de <value>.
            return ((tree->data == value)?1:0) + count_aux(tree->left,value) + count_aux(tree->right,value);
        }

        /*
            Función auxiliar para mostrar el contenido de un árbol binario de búsqueda
            de tipo <type>.

            Se recibe <tree> como el árbol cuyo contenido se desea mostrar.

            Se muestra el contenido en una sola línea colocando la información de cada
            nodo con el formato siguiente:

                            [ <dato> HIJO_IZQUIERDO HIJO_DERECHO ]

            Donde HIJO_IZQUIERDO e HIJO_DERECHO siguen a su vez el mismo formato.

            Toda hijo nulo se mostrará directamente como NULL.
        */
        void show_aux(NodeT<type>* tree){
            //Si el árbol está vacío, se muestra únicamente NULL
            if(tree == NULL){ cout << " NULL "; return; }

            //Si el árbol no está vacío se abre el contenido
            //y se coloca el dato del nodo actual
            cout << "[ " << tree->data << " ";

            //Se muestra el contenido del sub-árbol izquierdo
            show_aux(tree->left);
            //Se muestra el contenido del sub-árbol derecho
            show_aux(tree->right);

            //Se cierra el contenido del árbol
            cout << "]";
        }

        /*
            Función auxiliar para el mostrado verbose del contenido de un árbol binario
            de búsqueda de tipo <type>.

            Se recibe <tree> como el árbol cuyo contenido se desea mostrar.

            Se recibe <level> como el nivel del árbol cuyo contenido se desea mostrar.

            Se muestra el contenido de cada nodo con el formato siguiente:

                            Padre: <dato>.
                            Hijo izquierdo:
                                HIJO_IZQUIERDO
                            Hijo derecho:
                                HIJO_DERECHO

            Donde HIJO_IZQUIERDO e HIJO_DERECHO siguen a su vez el mismo formato.

            Toda hijo nulo se mostrará con el mensaje "Hijo nulo.".

            Adicionalmente, el formato anterior será precedido por una cantidad de tabulaciones
            igual al nivel del árbol que se está mostrando. Esto se hace mediante el uso de la
            clase string de la siguiente forma:

                                    string(<numero>,<caracter>)

            Lo cual provee una cadena de caracteres formada por <caracter> repetido <numero> veces.
        */
        void show_aux_verbose(NodeT<type>* tree, int level){
            //Si el árbol está vacío solo se muestra el mensaje "Hijo nulo."
            if(tree == NULL){
                //Se tabula una cantidad <level> de veces
                cout << string(level,'\t') << "Hijo nulo.\n";
                return;
            }

            //Si el árbol no está vacío, se muestra primero el contenido del
            //nodo actual.
            //Se tabula una cantidad <level> de veces
            cout << string(level,'\t') << "Padre: " << tree->data << ".\n";
            
            //Se introduce la sección para el contenido del sub-árbol izquierdo
            //tabulando una cantidad <level> de veces
            cout << string(level,'\t') << "Hijo izquierdo:\n";
            //Se muestra el contenido del sub-árbol izquierdo aumentando el nivel en 1
            show_aux_verbose(tree->left,level+1);

            //Se introduce la sección para el contenido del sub-árbol derecho
            //tabulando una cantidad <level> de veces
            cout << string(level,'\t') << "Hijo derecho:\n";
            //Se muestra el contenido del sub-árbol derecho aumentando el nivel en 1
            show_aux_verbose(tree->right,level+1);
        }

    public:
        /*
            Función que obtiene el Nodo inicial del árbol binario de
            búsqueda local de tipo <type>.

            La función retorna la dirección de dicho Nodo.
        */
        Node<type>* getRoot(){
            return T;
        }

        /*
            Función que retorna la categoría del árbol binario de
            búsqueda local de tipo <type>.
        */
        category getCategory() override {
            //Al tratarse de un árbol binario de búsqueda, se retorna
            //BINARY_SEARCH_TREE.
            return BINARY_SEARCH_TREE;
        }

        /*
            Función para inicializar el árbol binario de búsqueda
            de tipo <type>.
        */
        void create() override {
            //Para inicializar un árbol binario de búsqueda basta con
            //que el puntero al inicio del árbol apunte a NULL
            T = NULL;
        }

        /*
            Función que retorna la altura del árbol binario de búsqueda
            local de tipo <type>.
        */
        int extension() override {
            //Se envía el árbol binario de búsqueda local a la función
            //auxiliar para el cálculo de altura y se retorna dicho
            //resultado
            return height(T);
        }

        /*
            Función para insertar un valor <value> de tipo <type>
            en el árbol binario de búsqueda local de tipo <type>.
        */
        void insert(type value) override {
            //Se crea un nuevo nodo para el árbol binario de búsqueda
            //local que alojará el nuevo valor <value>
            NodeT<type>* temp = (NodeT<type>*) createNode();
            //Se coloca el valor <value> en el nuevo nodo
            temp->data = value;
            //El nuevo nodo será una hoja del árbol, se setean sus
            //hijos en NULL
            temp->left   = NULL;
            temp->right  = NULL;

            //Se verifica si el árbol se encuentra actualmente vacío
            if(T == NULL){
                //Si el árbol está vacío, el padre para el nuevo
                //nodo no existe aún, por lo que se define como NULL
                temp->parent = NULL;
                //Se define el nuevo nodo como la raíz del árbol
                T = temp;
            }else
                //Si el árbol no está vacío, se envía el árbol binario
                //de búsqueda local y el nuevo nodo creado a la función
                //auxiliar para inserción de nodos en un árbol
                insert_aux(T,temp);
        }

        /* La operación de inserción por posición no es aplicable a un árbol
           binario de búsqueda.                                             */
        void insert(int pos, type value) override {
            cout << "N/A\n";
        }

        /* La operación de extracción por posición no es aplicable a un árbol
           binario de búsqueda.                                              */
        type extract(int pos) override {
            cout << "N/A\nSe retorna valor nulo.\n";
            return (type) 0;
        }

        /*
            Función para liberar todo el espacio en memoria
            utilizado por un árbol binario de búsqueda de tipo
            <type>.
        */
        void destroy() override {
            //Se envía el árbol binario de búsqueda local a la función
            //auxiliar para liberación de memoria
            destroy_aux(T);
            //Se define el árbol como vacío
            T = NULL;
        }

        /*
            Función que determina si un valor <value> de tipo <type>
            se encuentra o no dentro de un árbol binario de búsqueda
            de tipo <type>.

            Se retorna true si se encuentra, false en caso
            contrario.
        */
        bool search(type value) override {
            //Se envía el árbol binario de búsqueda local y el dato a
            //buscar a la función auxiliar para búsqueda de un dato
            return search_aux(T,value);
        }

        /*
            Función que determina la cantidad de ocurrencias de un valor
            <value> de tipo <type> en un árbol binario de búsqueda de tipo
            <type>.
        */
        int count(type value) override {
            //Se envía el árbol binario de búsqueda local y el dato cuyas
            //ocurrencias se contarán a la función auxiliar para conteo de
            //ocurrencias
            return count_aux(T,value);
        }

        /* La operación de inversión de contenido no es aplicable a un árbol
           binario de búsqueda.                                              */
        void reverse() override {
            cout << "N/A\n";
        }

        /*
            Función que muestra el contenido de un árbol binario de búsqueda de
            tipo <type>.

            <verbose> indica el nivel de detalle a mostrar:
                - Si es false, solo se muestra el árbol como tal.

                - Si es true, se detalla posición por posición y nivel por nivel
                  el contenido del árbol.

            Se implementa recorrido en Pre-Order.
        */
        void show(bool verbose) override {
            //Se verifica si el árbol está vacío,
            //en cuyo caso no hay nada que mostrar y se
            //terminaría el proceso de mostrado
            if(T == NULL){
                cout << "El árbol está vacío.\n";
                return;
            }

            if(verbose)
                //Se envía el árbol binario de búsqueda local a la función
                //auxiliar para mostrado verbose
                //Se envía un 0 para indicar que el proceso comienza en la raíz
                //del árbol, es decir, en el nivel 0 del árbol
                show_aux_verbose(T,0);
            else{
                //Se envía el árbol binario de búsqueda local a la función
                //auxiliar para mostrado no verbose
                show_aux(T);
                cout << "\n";
            }
        }
};
