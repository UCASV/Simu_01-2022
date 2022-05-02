/*
    Interfaces que define los métodos a utilizar para la
    manipulación y administración de estructuras de datos.

    Toda interfaz que lo necesite se define como independiente
    del tipo de dato a almacenar mediante el uso de template.
*/

/*
    Interfaz base para todo tipo de estructura de dato.

    Contiene todas las operaciones comunes a cualquier
    estructura, ya sea estática o dinámica.
*/
template <typename T>
class DS{
    public:
        /*
            Función que retorna la categoría de la estructura
            de datos local.

            Esta categoría puede ser:
                - ARRAY para los arreglos.
                - MATRIX para las matrices.
                - SINGLE_LINKED_LIST para las listas enlazadas
                  simples.
                - DOUBLE_LINKED_LIST para las listas enlazadas
                  simples.
                - BINARY_SEARCH_TREE para los árboles de búsqueda
                  binarios.
                - GRAPH para los grafos.

            La función hace uso de la enumeración category
            definida en "SDDS.h".
        */
        virtual category getCategory() = 0;

        /*
            Función para liberar todo el espacio en memoria
            utilizado por una estructura de datos de tipo <T>.
        */
        virtual void destroy() = 0;

        /*
            Función que determina si un valor <value> de tipo <T>
            se encuentra o no dentro de una estructura de datos
            de tipo <T>.

            Se retorna true si se encuentra, false en caso
            contrario.
        */
        virtual bool search(T value) = 0;

        /*
            Función que determina la cantidad de ocurrencias de un
            valor <value> de tipo <T> en una estructura de datos 
            de tipo <T>.
        */
        virtual int count(T value) = 0;

        /*
            Función que muestra el contenido de una estructura de
            datos de tipo <T>.

            <verbose> indica el nivel de detalle a mostrar:
                - Si es false, solo se muestra la estructura de datos como tal.

                - Si es true, se detalla posición por posición, y nivel por nivel,
                  el contenido de la estructura de datos.
        */
        virtual void show(bool verbose) = 0;
};

/*
    Interfaz que extiende la interfaz base para estructuras de datos
    con la funcionalidad propia de una estructura de datos estática
    unidimensional.
*/
template <typename T>
class staticDS_1D: public DS<T>{
    public:
        /*
            Función para crear espacio en memoria para un arreglo
            de tipo <T>.

            Se recibe <size> como la longitud del arreglo a crear
            en memoria.
        */
        virtual void create(int size) = 0;
};

/*
    Interfaz que extiende la interfaz base para estructuras de datos
    con la funcionalidad propia de una estructura de datos estática
    bidimensional.
*/
template <typename T>
class staticDS_2D: public DS<T>{
    public:
        /*
            Función para crear espacio en memoria para una
            matriz de tipo <T>.

            <dim> es de tipo "struct Data", y contendrá dos datos,
            que serán el número de filas y el número de columnas
            de la matriz.
        */
        virtual void create(Data dim) = 0;

        /*
            Función que retorna las dimensiones de la matriz local
            mediante un objeto de tipo "struct Data" que contendrá
            dos datos: el número de filas y el número de columnas
            de la matriz.
        */
        virtual Data extension() = 0;

        /*
            Función para insertar un valor <value> de tipo <T>
            en la posición <pos> de una matriz de tipo <T>.

            <pos> es de tipo "struct Data" y contendrá dos datos,
            que serán el número de fila y el número de columnas
            de la celda en la matriz en la que se desea insertar
            <value>.
        */
        virtual void insert(Data pos, T value) = 0;

        /*
            Función para extraer un dato de tipo <T> de la
            posición indicada por <pos> en la matriz local.

            <pos> es de tipo "struct Data" y contendrá dos datos,
            que serán el número de fila y el número de columna
            de la celda en la matriz en la que se desea extraer
            el dato.
        */
        virtual T extract(Data pos) = 0;
};

/*
    Interfaz que extiende la interfaz base para estructuras de datos
    con la funcionalidad propia de una estructura de datos dinámica.
*/
template <typename T>
class dynamicDS: public DS<T>{
    private:
        /*
            Función que crea espacio en memoria para un
            Nodo de una estructura de datos dinámica de tipo
            <T>.
        */
        virtual void* createNode() = 0;

    public:
        /*
            Función que obtiene el Nodo inicial o de entrada
            de la estructura de datos dinámica local de tipo
            <T>.

            La función retorna la dirección de dicho Nodo.
        */
        virtual Node<T>* getRoot() = 0;

        /*
            Función para inicializar una estructura de datos
            dinámica de tipo <T>.
        */
        virtual void create() = 0;
};

/************************************************************/
/*    Interfaces implementables por múltiples variantes de  */
/*    por múltiples tipos de estructuras de datos.          */
/************************************************************/

/*
    Interfaz para estructuras de datos que permiten la inserción
    libre de datos.
*/
template <typename T>
class insertable{
    public:
        /*
            Función para insertar un valor <value> de tipo <T>
            en la estructura de datos local de tipo <T>.
        */
        virtual void insert(T value) = 0;
};

/*
    Interfaz para estructuras de datos que permiten la definición
    de una extensión mediante el cálculo de un número entero.
*/
class measurable{
    public:
        /*
            Función que retorna la extensión de la estructura
            de datos local de tipo <T>.

            Se define como extensión la cantidad de información
            almacenada por la estructura de datos y que es
            representable mediante un solo número entero.
        */
        virtual int extension() = 0;
};

/*
    Interfaz para estructuras de datos que permiten la manipulación
    de su información almacenada estableciendo una posición en la
    estructura mediante un número entero.
*/
template <typename T>
class positionable{
    public:
        /*
            Función para insertar un valor <value> de tipo <T>
            en la posición indicada por <pos> de la estructura de datos
            local de tipo <T>.
        */
        virtual void insert(int pos, T value) = 0;

        /*
            Función para extraer un dato de tipo <T> de la
            posición indicada por <pos> en la estructura de datos
            local de tipo <T>.
        */
        virtual T extract(int pos) = 0;
};

/*
    Interfaz para estructuras de datos que permiten la inversión
    de su contenido.
*/
class reversible{
    public:
        /*
            Función que invierte el contenido de una estructura de datos
            de tipo <T>.
        */
        virtual void reverse() = 0;
};
