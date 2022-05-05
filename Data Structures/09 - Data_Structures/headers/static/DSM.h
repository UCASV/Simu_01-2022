/*
    Implementación para una estructura de datos estática biidimensional,
    es decir, para una matriz.

    Se define la implementación como independiente del tipo de
    dato a almacenar mediante el uso de template.
*/
template <typename T>
/*
    En C++, la implementación se maneja como una herencia,
    de modo que DSM hereda de staticDS_2D, ya que es la que provee
    su funcionalidad básica.

    El indicador de visibilidad 'public' indica que DSM tendrá
    acceso a todos los métodos de staticDS_2D manteniendo su
    visibilidad original.

    Dado que staticDS_2D es un template, debe indicarse
    el tipo de dato a utilizar mediante un "meta-parámetro". Sin
    embargo, el tipo de dato aún no ha sido definido, ya que DSM
    también es un template, por lo que el "meta-parámetro" es el
    tipo de dato genérico local <T>.
*/
class DSM: public staticDS_2D<T> {
    /*
        Como atributo privado local se manejará la matriz de datos tipo
        <T> como tal. Se declara un puntero doble ya que se manejará
        por dirección el bloque de memoria correspondiente.

        Recordando, la estructura en memoria corresponde a un arreglo
        principal de punteros simples, donde cada uno apunta a un arreglo
        que corresponde a una de las filas de la matriz:

        int** matriz -->  [ int* ]-[ int* ]-[ int* ]     //Arreglo principal
                             |        |        |
                             v        v        v
                          [ int ]  [ int ]  [ int ]
                          [ int ]  [ int ]  [ int ]
                          [ int ]  [ int ]  [ int ]

        Los otros atributos privados locales son el número de filas <nrows>
        y el número de columnas <ncols> de la matriz, como datos acompañantes
        para controlar procesos de recorrido.
    */
    private:
        T** matrix;
        int nrows, ncols;

    //Se procede a la implementación como tal de los métodos de la interfaz
    //override indica la respectiva sobreescritura de cada método
    public:
        /*
            Función que retorna la categoría de la matriz local.

            La función hace uso de la enumeración category
            definida en "SDDS.h".
        */
        category getCategory() override {
            //Se retorna MATRIX ya que localmente manejamos una matriz
            return MATRIX;
        }

        /*
            Función para liberar todo el espacio en memoria
            utilizado por una matriz de tipo <T>.
        */
        void destroy() override {
            //Es necesario liberar primero todas las filas
            //antes de liberar el arreglo principal, a fin
            //de no perder la referencia.

            //Se recorre el arreglo principal:
            for(int i = 0; i < nrows; i++)
                //Se libera cada fila, utilizando el contenido
                //de cada celda del arreglo principal, el cual
                //corresponde a los punteros a cada una de las
                //filas.
                free(*(matrix+i));
            
            //Por último, se libera el arreglo principal usando
            //la dirección de memoria inicial de toda la matriz.
            free(matrix);
        }

        /*
            Función que determina si un valor <value> de tipo <T>
            se encuentra o no dentro de una matriz de tipo <T>.

            Se retorna true si se encuentra, false en caso
            contrario.
        */
        bool search(T value) override {
            //Respuesta por defecto: "No se encuentra."
            bool ans = false;

            //Se recorre la matriz:
            for(int i = 0; i < nrows*ncols; i++)
                //Verifico en la celda actual si se ha
                //encontrado el dato buscado.
                if(matrix[i/ncols][i%ncols] == value){
                    //Si se encontró, se actualiza la respuesta.
                    ans = true;
                    //Basta una ocurrencia, no es necesario
                    //continuar el recorrido.
                    break;
                }
            return ans;
        }

        /*
            Función que determina la cantidad de ocurrencias de un valor
            <value> de tipo <T> en una matriz de tipo <T>.
        */
        int count(T value) override {
            //Se inicializa un contador de suma
            int cont = 0;

            //Se recorre la matriz:
            for(int i = 0; i < nrows*ncols; i++)
                //Verifico si hay ocurrencia en la celda
                //actual de la matriz
                if(matrix[i/ncols][i%ncols] == value)
                    //Si hay ocurrencia, actualizo el contador.
                    //No hay break, ya que me interesa saber
                    //el total de ocurrencias, sigo buscando.
                    cont++;
            //Retorno el resultado
            return cont;
        }

        /*
            Función que muestra el contenido de una matriz de tipo <T>.

            <verbose> indica el nivel de detalle a mostrar:
                - Si es false, solo se muestra la matriz como tal.

                - Si es true, se detalla posición por posición el contenido de
                  la matriz.
        */
        void show(bool verbose) override {
            if(verbose)
                for(int i = 0; i < nrows*ncols; i++)
                    //Se especifica explícitamente el valor de cada elemento
                    //almacenado en la matriz, uno por línea, indicando número
                    //de fila y número de columna correspondiente.
                    cout << "Element in cell [ " << i/ncols+1 << ", " << i%ncols+1 << " ] is: " << matrix[i/ncols][i%ncols] << "\n";
            else{
                //Se muestra el contenido de la matriz colocando cada fila como
                //una secuencia de datos, representando cada una sus posiciones
                //mediante el uso de ','.
                //Se coloca una fila por línea, a manera de alinear el contenido
                //correspondiente a cada columna.

                //Se abre la matriz
                cout << "[\n";

                //Se recorren las filas
                for(int i = 0; i < nrows; i++){
                    //Se abre la secuencia de la fila
                    cout << "[ ";
                    //Se recorre la fila hasta la penúltima posición
                    for(int j = 0; j < ncols-1; j++)
                        //Se coloca el dato en la posición actual seguido de ','
                        cout << matrix[i][j] << ", ";
                    
                    //Se coloca el dato de la última posición seguido del cierre de la secuencia
                    cout << matrix[i][ncols-1] << " ]\n";
                }

                //Se cierra la matriz
                cout << "]\n";
            }
        }

        /*
            Función para crear espacio en memoria para una
            matriz de tipo <T>.

            <dim> es de tipo "struct Data", y dado que localmente
            manejamos una matriz, se asume que contiene dos
            datos, que serán el número de filas y el número de
            columnas de la matriz.
        */
        void create(Data dim) override {
            //Se extraen y almacenan el número de filas y el número
            //de columnas de la matriz
            nrows = dim.n;
            ncols = dim.m;

            //Se construye primero el arreglo principal:

            //Casting a (type**) ya que el bloque de memoria
            //se provee "crudo" ( void* ), el doble puntero responde
            //a que se almacenarán punteros simples a tipo <T>.
            //sizeof(type*) ya que se almacenarán datos de tipo <type*>.
            //sizeof(type*)*nrows para generar tantos espacios
            //como los indicados por el número de filas de la matriz.
            matrix = (T**) malloc(sizeof(T*)*nrows);

            //Se recorre el arreglo principal:
            for(int i = 0; i < nrows; i++)
                //Por cada espacio, que es equivalente a decir, por
                //cada fila, se construye un arreglo:

                //Casting a (type*) ya que el bloque de memoria
                //se provee "crudo" ( void* ).
                //sizeof(type) ya que se almacenarán datos de tipo <T>.
                //sizeof(type)*ncols para generar tantos espacios
                //como los indicados por el número de columnas de la matriz.
                *(matrix+i) = (T*) malloc(sizeof(T)*ncols);
        }

        /*
            Función que retorna las dimensiones de la matriz local
            mediante un objeto de tipo "struct Data".
            
            Ya que localmente se maneja una matriz, el objeto contendrá
            dos datos, que serán el número de filas y el número de
            columnas de la matriz.
        */
        Data extension() override {
            Data dim;   //Se crea el objeto de tipo Data
            //Se almacenan el número de filas y el número
            //de columnas de la matriz
            dim.n = nrows; dim.m = ncols;
            return dim; //Se retorna el objeto de tipo Data
        }

        /*
            Función para insertar un valor <value> de tipo <T>
            en la posición <pos> de una matriz de datos de tipo <T>.

            <pos> es de tipo "struct Data", y como localmente se maneja
            una matriz, se asume que contiene dos datos, que serán el
            número de fila y el número de columnas de la celda en la
            matriz en la que se desea insertar <value>.
        */
        void insert(Data pos, T value) override {
            //Se extraen la fila y la columna de <pos> y se usan para indexar
            //la matriz
            matrix[pos.n][pos.m] = value;
        }

        /*
            Función para extraer un dato de tipo <T> de la
            posición indicada por <pos> en la matriz local.

            <pos> es de tipo "struct Data", y dado que localmente se
            maneja una matriz, se asume que contiene dos datos, que
            serán el número de fila y el número de columna de la celda
            en la matriz en la que se desea extraer el dato.
        */
        T extract(Data pos) override {
            //Se extraen la fila y la columna de <pos> y se usan para indexar
            //la matriz
            return matrix[pos.n][pos.m];
        }
};
