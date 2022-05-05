/*
    Interfaz que define los métodos a utilizar para la
    manipulación y administración de estructuras de datos
    dinámicas.

    Se define la interfaz como independiente del tipo de
    dato a almacenar mediante el uso de template.
*/
template <typename type>
class DS{
    private:
        /*
            Función que crea espacio en memoria para un
            Nodo de una estructura de datos dinámica de tipo
            <type>.
        */
        virtual void* createNode() = 0;

    public:
        /*
            Función que obtiene el Nodo inicial o de entrada
            de la estructura de datos dinámica local de tipo
            <type>.

            La función retorna la dirección de dicho Nodo.
        */
        virtual Node<type>* getRoot() = 0;

        /*
            Función que retorna la categoría de la estructura
            de datos dinámica local de tipo <type>.

            Esta categoría puede ser:
                - SINGLE_LINKED_LIST para las listas enlazadas
                  simples.
                - DOUBLE_LINKED_LIST para las listas enlazadas
                  simples.
                - BINARY_SEARCH_TREE para los árboles de búsqueda
                  binarios.
                - GRAPH para los grafos.

            La función hace uso de la enumeración category
            definida en "dynamicDS.h".
        */
        virtual category getCategory() = 0;

        /*
            Función para inicializar una estructura de datos
            dinámica de tipo <type>.
        */
        virtual void create() = 0;

        /*
            Función que retorna la extensión de la estructura
            de datos dinámica local de tipo <type>.

            Se define como extensión la cantidad de información
            almacenada por la estructura de datos dinámica:
                - Si la estructura es un árbol, su extensión es
                  su altura.
                - Si la estructura es un grafo, su extensión es
                  su cantidad de nodos.
                - En cualquier otro caso, la extensión será la
                  longitud de la estructura.
        */
        virtual int extension() = 0;

        /*
            Función para insertar un valor <value> de tipo <type>
            en la estructura de datos dinámica local de tipo <type>.
        */
        virtual void insert(type value) = 0;

        /*
            Función para insertar un valor <value> de tipo <type>
            en la posición indicada por <pos> de la estructura de datos
            dinámica local de tipo <type>.
        */
        virtual void insert(int pos, type value) = 0;

        /*
            Función para extraer un dato de tipo <type> de la
            posición indicada por <pos> en la estructura de datos
            dinámica local de tipo <type>.
        */
        virtual type extract(int pos) = 0;

        /*
            Función para liberar todo el espacio en memoria
            utilizado por una estructura de datos dinámica de
            tipo <type>.
        */
        virtual void destroy() = 0;

        /*
            Función que determina si un valor <value> de tipo <type>
            se encuentra o no dentro de una estructura de datos dinámica
            de tipo <type>.

            Se retorna true si se encuentra, false en caso
            contrario.
        */
        virtual bool search(type value) = 0;

        /*
            Función que determina la cantidad de ocurrencias de un valor
            <value> de tipo <type> en una estructura de datos dinámica
            de tipo <type>.
        */
        virtual int count(type value) = 0;

        /*
            Función que invierte el contenido de una estructura de datos
            dinámica de tipo <type>, si la operación es posible de realizar.
            
            Si la operación no es posible, se informa.
        */
        virtual void reverse() = 0;

        /*
            Función que muestra el contenido de una estructura de datos
            dinámica de tipo <type>.

            <verbose> indica el nivel de detalle a mostrar:
                - Si es false, solo se muestra la estructura de datos como tal.

                - Si es true, se detalla posición por posición el contenido de
                  la estructura de datos.
        */
        virtual void show(bool verbose) = 0;
};
