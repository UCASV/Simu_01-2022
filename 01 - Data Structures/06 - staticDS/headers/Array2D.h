/*
    Implementación de la interfaz Array, definida en "Array.h",
    para una estructura de datos estática bidimensional, es decir,
    para una matriz.

    Se define la implementación como independiente del tipo de
    dato a almacenar mediante el uso de template.
*/
template <typename type>
/*
    En C++, la implementación se maneja como una herencia,
    de modo que Array2D hereda de Array.

    El indicador de visibilidad 'public' indica que Array2D tendrá
    acceso a todos los métodos de Array manteniendo la visibilidad
    original.

    Dado que Array es un template, debe indicarse el tipo de dato
    a utilizar mediante un "meta-parámetro". Sin embargo, el tipo
    de dato aún no ha sido definido, ya que Array2D también es un
    template, por lo que el "meta-parámetro" es del tipo de dato
    genérico local <type>.
*/
class Array2D: public Array<type>{
    /*
        Como atributo privado local se manejará la matriz de datos tipo
        <type> como tal. Se declara un puntero doble ya que se manejará
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
        type** matrix;
        int nrows, ncols;
    
    //Se procede a la implementación como tal de los métodos de la interfaz
    //override indica la respectiva sobreescritura de cada método
    public:
        /*
            Función que retorna la categoría de la estructura
            de datos estática local.

            La función hace uso de la enumeración ndimensions
            definida en "staticDS.h".
        */
        ndimensions category() override {
            //Se retorna TWO_DIMENSIONS ya que localmente manejamos una matriz
            return TWO_DIMENSIONS;
        }

        /*
            Función para crear espacio en memoria para una
            estructura de datos estática de tipo <type>.

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
            //a que se almacenarán punteros simples a tipo <type>.
            //sizeof(type*) ya que se almacenarán datos de tipo <type*>.
            //sizeof(type*)*nrows para generar tantos espacios
            //como los indicados por el número de filas de la matriz.
            matrix = (type**) malloc(sizeof(type*)*nrows);

            //Se recorre el arreglo principal:
            for(int i = 0; i < nrows; i++)
                //Por cada espacio, que es equivalente a decir, por
                //cada fila, se construye un arreglo:

                //Casting a (type*) ya que el bloque de memoria
                //se provee "crudo" ( void* ).
                //sizeof(type) ya que se almacenarán datos de tipo <type>.
                //sizeof(type)*ncols para generar tantos espacios
                //como los indicados por el número de columnas de la matriz.
                *(matrix+i) = (type*) malloc(sizeof(type)*ncols);
        }

        /*
            Función que retorna las dimensiones de la estructura
            de datos estática local mediante un objeto de tipo
            "struct Data".
            
            Ya que localmente se maneja una matriz, el objeto contendrá
            dos datos, que serán el número de filas y el número de
            columnas de la matriz.
        */
        Data getDim() override {
            Data dim;   //Se crea el objeto de tipo Data
            //Se almacenan el número de filas y el número
            //de columnas de la matriz
            dim.n = nrows; dim.m = ncols;
            return dim; //Se retorna el objeto de tipo Data
        }

        /*
            Función que coloca en cada posición de la estructura
            de datos estática local un valor nulo correspondiente
            al tipo <type> utilizado.
        */
        void init() override {
            //Se recorre la matriz mediante un sólo iterador
            
            //Se recuerda:

            /*
                Se realiza el recorrido de la matriz con un solo iterador
                'for' utilizando un sólo índice k.

                La equivalencia entre los índices del esquema con dos
                iteradores (i,j) y el índice del esquema con un iterador
                (k) es el siguiente:

                    i = k \ ncols
                    j = k % ncols

                Donde el operador '\' hace referencia a la "División Entera".

                Estas equivalencias surgen del análisis siguiente:

                        Usando (i,j)                          Usando k

                    0        1        2                  0        1        2
                0 [ (0,0) ][ (0,1) ][ (0,2) ]        0 [   0   ][   1   ][   2   ]
                1 [ (1,0) ][ (1,1) ][ (1,2) ]  <-->  1 [   3   ][   4   ][   5   ]
                2 [ (2,0) ][ (2,1) ][ (2,2) ]        2 [   6   ][   7   ][   8   ]

                Observando las columnas:

                    0        1        2                  0        1        2
                0 [ (_,0) ][ (_,1) ][ (_,2) ]        0 [   0   ][   1   ][   2   ]
                1 [ (_,0) ][ (_,1) ][ (_,2) ]  <-->  1 [   3   ][   4   ][   5   ]
                2 [ (_,0) ][ (_,1) ][ (_,2) ]        2 [   6   ][   7   ][   8   ]

                Puede observarse que para cada fila se repite el ciclo {0,1,2}

                Como ya sabemos, usando la propiedad de la operación módulo podemos
                generar ciclos:
                                    n mod m --> dato en [0...m-1]

                Por lo que, para tener un dato en {0,1,2}, hacemos módulo 3, que es
                lo mismo que decir, hacemos módulo <ncols>.

                Usando el iterador k como input del proceso, obtenemos la equivalencia
                para el iterador j:
                                            j = k % ncols

                Ahora, observemos las filas:

                    0        1        2                  0        1        2
                0 [ (0,_) ][ (0,_) ][ (0,_) ]        0 [   0   ][   1   ][   2   ]
                1 [ (1,_) ][ (1,_) ][ (1,_) ]  <-->  1 [   3   ][   4   ][   5   ]
                2 [ (2,_) ][ (2,_) ][ (2,_) ]        2 [   6   ][   7   ][   8   ]

                El patrón esta vez corresponde a mantener el número de la fila como
                el índice i.

                Observando los valores de k, podemos ver lo siguiente:

                    0        1        2                   0          1          2
                0 [ (0,_) ][ (0,_) ][ (0,_) ]        0 [    0    ][    1    ][    2    ]
                1 [ (1,_) ][ (1,_) ][ (1,_) ]  <-->  1 [   0+3   ][   1+3   ][   2+3   ]
                2 [ (2,_) ][ (2,_) ][ (2,_) ]        2 [   0+6   ][   1+6   ][   2+6   ]

                Trabajándolo un poco más:

                    0        1        2                   0            1            2
                0 [ (0,_) ][ (0,_) ][ (0,_) ]        0 [   0+3*0   ][   1+3*0   ][   2+3*0   ]
                1 [ (1,_) ][ (1,_) ][ (1,_) ]  <-->  1 [   0+3*1   ][   1+3*1   ][   2+3*1   ]
                2 [ (2,_) ][ (2,_) ][ (2,_) ]        2 [   0+3*2   ][   1+3*2   ][   2+3*2   ]

                El patrón que necesitamos ha aparecido a la derecha como el factor del 3,
                generalizando de la forma:
                                                n+3*n
                
                Para extraer la n de la expresión anterior, aplicamos división entera entre 3:

                                            (n + 3*n) \ 3 = n
                        { (n + 3*n) \ 3 = floor( (n + 3*n) / 3 ) = floor( n/3 + n ) = n }

                Como la expresión n+3*n viene de la k, y como el 3 corresponde a <ncols>, 
                podemos definir la equivalencia con el índice i como:
                                            
                                            i = k \ ncols

                Por último, se observa que la k en el ejemplo varía desde o hasta un valor de 8,
                este valor de 8 se puede reescribir como 9 -1 , el cual a su vez se puede reescribir
                como 3*3 - 1, lo que, generalizando, es equivalente a decir <nrows>*<ncols> - 1.

                Por lo que la variación de la k se generaliza como:

                                k pertenece al intervalo [ 0 ... nrows*ncols-1 ]
            */

            for(int i = 0; i < nrows*ncols; i++)
                //Se coloca <(type) 0> en cada celda de la matriz
                matrix[i/ncols][i%ncols] = (type) 0;
        }

        /*
            Función para insertar un valor <value> de tipo <type>
            en la posición <pos> de una matriz de datos de tipo <type>.

            <pos> es de tipo "struct Data", y como localmente se maneja
            una matriz, se asume que contiene dos datos, que serán el
            número de fila y el número de columnas de la celda en la
            matriz en la que se desea insertar <value>.
        */
        void insert(Data pos, type value) override {
            //Se extraen la fila y la columna de <pos> y se usan para indexar
            //la matriz
            matrix[pos.n][pos.m] = value;
        }

        /*
            Función para extraer un dato de tipo <type> de la
            posición indicada por <pos> en la estructura de datos
            estática local.

            <pos> es de tipo "struct Data", y dado que localmente se
            maneja una matriz, se asume que contiene dos datos, que
            serán el número de fila y el número de columna de la celda
            en la matriz en la que se desea extraer el dato.
        */
        type extract(Data pos) override {
            //Se extraen la fila y la columna de <pos> y se usan para indexar
            //la matriz
            return matrix[pos.n][pos.m];
        }

        /*
            Función para liberar todo el espacio en memoria
            utilizado por una estructura de datos estática de
            tipo <type>.
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
            Función que determina si un valor <value> de tipo <type>
            se encuentra o no dentro de una estructura de datos estática
            de tipo <type>.

            Se retorna true si se encuentra, false en caso
            contrario.
        */
        bool search(type value) override {
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
            <value> de tipo <type> en una estructura de datos estática
            de tipo <type>.
        */
        int count(type value) override {
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

        /* La operación de inversión de datos no es aplicable a una matriz */
        void reverse() override {
            cout << "->**WARNING: Operation not applicable to a two-dimensional array** :^).\n";
        }

        /*
            Función que muestra el contenido de una estructura de datos
            estática de tipo <type>.

            <verbose> indica el nivel de detalle a mostrar:
                - Si es false, solo se muestra la estructura de datos como tal.

                - Si es true, se detalla posición por posición el contenido de
                  la estructura de datos.
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
};
