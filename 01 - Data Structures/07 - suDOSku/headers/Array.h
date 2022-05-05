/*
    Interfaz que define los métodos a utilizar para la
    manipulación y administración de estructuras de datos
    estáticas.

    Se define la interfaz como independiente del tipo de
    dato a almacenar mediante el uso de template.
*/
template <typename type>
class Array{
    public:
        /*
            Función que retorna la categoría de la estructura
            de datos estática local.

            Esta categoría puede ser:
                - ONE_DIMENSION para los arreglos.
                - TWO_DIMENSIONS para las matrices.

            La función hace uso de la enumeración ndimensions
            definida en "staticDS.h".
        */
        virtual ndimensions category() = 0;

        /*
            Función para crear espacio en memoria para una
            estructura de datos estática de tipo <type>.

            <dim> es de tipo "struct Data":
                - Si la estructura es un arreglo, <dim> contendrá
                  un dato, que será la longitud del arreglo.

                - Si la estructura es una matriz, <dim> contendrá
                  dos datos, que serán el número de filas y el
                  número de columnas de la matriz.
        */
        virtual void create(Data dim) = 0;

        /*
            Función que retorna las dimensiones de la estructura
            de datos estática local mediante un objeto de tipo
            "struct Data":
                - Si la estructura es un arreglo, el objeto contendrá
                  un dato, que será la longitud del arreglo.

                - Si la estructura es una matriz, el objeto contendrá
                  dos datos, que serán el número de filas y el
                  número de columnas de la matriz.
        */
        virtual Data getDim() = 0;

        /*
            Función que coloca en cada posición de la estructura
            de datos estática local un valor nulo correspondiente
            al tipo <type> utilizado.
        */
        virtual void init() = 0;

        /*
            Función para insertar un valor <value> de tipo <type>
            en la posición <pos> de un arreglo de datos de tipo <type>.

            <pos> es de tipo "struct Data":
                - Si la estructura es un arreglo, <pos> contendrá
                  un dato, que será la posición en el arreglo en la
                  que se desea insertar <value>.

                - Si la estructura es una matriz, <pos> contendrá
                  dos datos, que serán el número de fila y el
                  número de columnas de la celda en la matriz en la
                  que se desea insertar <value>.
        */
        virtual void insert(Data pos, type value) = 0;

        /*
            Función para extraer un dato de tipo <type> de la
            posición indicada por <pos> en la estructura de datos
            estática local.

            <pos> es de tipo "struct Data":
                - Si la estructura es un arreglo, <pos> contendrá
                  un dato, que será la posición en el arreglo en la
                  que se desea extraer el dato.

                - Si la estructura es una matriz, <pos> contendrá
                  dos datos, que serán el número de fila y el
                  número de columna de la celda en la matriz en la
                  que se desea extraer el dato.
        */
        virtual type extract(Data pos) = 0;

        /*
            Función para liberar todo el espacio en memoria
            utilizado por una estructura de datos estática de
            tipo <type>.
        */
        virtual void destroy() = 0;

        /*
            Función que determina si un valor <value> de tipo <type>
            se encuentra o no dentro de una estructura de datos estática
            de tipo <type>.

            Se retorna true si se encuentra, false en caso
            contrario.
        */
        virtual bool search(type value) = 0;

        /*
            Función que determina la cantidad de ocurrencias de un valor
            <value> de tipo <type> en una estructura de datos estática
            de tipo <type>.
            
            Se retorna true si se encuentra, false en caso
            contrario.
        */
        virtual int count(type value) = 0;

        /*
            Función que invierte el contenido de una estructura de datos
            estática de tipo <type>, si la operación es posible de realizar.
            
            Si la operación no es posible, se informa.
        */
        virtual void reverse() = 0;

        /*
            Función que muestra el contenido de una estructura de datos
            estática de tipo <type>.

            <verbose> indica el nivel de detalle a mostrar:
                - Si es false, solo se muestra la estructura de datos como tal.

                - Si es true, se detalla posición por posición el contenido de
                  la estructura de datos.
        */
        virtual void show(bool verbose) = 0;
};
