/*
    Enumeración utilizada para determinar la categoría de una
    estructura de datos estática:
        - ONE_DIMENSION para arreglos.
        - TWO_DIMENSIONS para matrices.
*/
enum ndimensions {ONE_DIMENSION, TWO_DIMENSIONS};

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
    Data(){};
} Data;

#include "Array.h"
#include "Array1D.h"
#include "Array2D.h"

/*
    Clase utilitaria para la manipulación y administración
    de estructuras de datos estáticas.

    La clase se encarga de la lógica de diferenciación entre
    arreglos y matrices, a fin de que el "cliente" no se preocupe
    por ello.

    La clase hace uso de Array1D o de Array2D según sea el caso,
    recibiendo de parte del "cliente" objetos Array, clase padre
    en ambos casos, para aprovechar el polimorfismo en la
    transparencia de las operaciones.

    Al utilizar Array, Array1D y/o Array2D, dado que las tres clases
    son templates, es necesario colocar el "meta-parámetro" que
    especifique el tipo de dato. Sin embargo, el tipo de dato
    aún no ha sido definido, ya que Arrays también es un template,
    por lo que el "meta-parámetro" es del tipo de dato genérico
    local <type>.
*/
template <typename type>
class Arrays{
    /*
        Como atributo privado local se maneja una variable auxiliar
        de tipo "struct Data", para poder facilitar los procesos
        de manejo de las estructuras de datos estáticas.
    */
    private:
        static Data ref;

    //Se definen los métodos para cada una de las operaciones que el
    //"cliente" podrá realizar.
    public:
        /*
            Función que instancia un puntero a objeto Array de tipo
            <type> enviado por referencia creando un objeto Array1D.

            Se recibe <size> como el tamaño del arreglo a crear en el
            objeto Array1D.
        */
        static void create(Array<type>** array, int size){
            //Se utiliza la variable auxiliar para empaquetar
            //la longitud del arreglo solicitado
            ref.n = size;

            //Se crea un objeto Array1D, ya que se ha solicitado
            //un arreglo
            //array ha sido enviado por referencia, para modificar
            //la variable en su contexto original hacemos uso del
            //operador de contenido *
            *array = new Array1D<type>();

            //Una vez creado el objeto, invocamos su método create()
            //pasando por valor la variable auxiliar
            /*
                Recordando:
                
                < Array** array > en este escenario es un Array* enviando
                por referencia, por lo que:

                                *array es de tipo Array*                    (A)
                (el contenido de un puntero doble es un puntero simple)

                Array* apuntaría entonces a la dirección de memoria
                donde está almacenado un objeto Array, para acceder a
                los métodos de este objeto necesitamos primero obtener
                el contenido a través del puntero, entonces:

                Digamos que la variable de tipo Array* se llama <var>,
                para obtener el objeto Array usamos operador de contenido:

                                        *var

                Y una vez lo tenemos en las manos, accedemos a sus métodos
                de la manera tradicional, eso sí, colocando paréntesis para
                que el operador de contenido '*' se ejecute antes del
                operador de acceso '.' (ejemplificamos con el método create):
                
                                    (*var).create()

                C++ permite hacer lo siguiente:

                                    (*var).create()
                                    var->create()                           (B)

                De forma que el '->' sustituye al '(*  ).'.

                Ahora bien, <var> no lo tenemos directamente, es decir, la
                variable que es de tipo Array* no la tenemos en las manos,
                tenemos solamente su dirección, por lo que introduciendo
                la expresión (A) en la expresión (B) obtenemos:

                                    var->create()
                                (*array)->create()
                
                Recapitulando:
                    - array es la dirección de una variable de tipo Array*
                    - *array nos otorga la variable de tipo Array*
                    - Con (*array) tenemos la dirección de un objeto Array
                    - Con (*array)-> accedemos a los métodos del objeto Array
            */
            (*array)->create(ref);
        }
        /*
            Función que instancia un puntero a objeto Array de tipo <type>
            enviado por referencia creando un objeto Array2D.

            Se reciben <nrows> como el número de filas y <ncols> como el
            número de columnas de la matriz a crear en el objeto Array2D.
        */
        static void create(Array<type>** matrix, int nrows, int ncols){
            //Se utiliza la variable auxiliar para empaquetar
            //el número de filas y el número de columnas de la matriz
            //solicitada
            ref.n = nrows; ref.m = ncols;

            //Se crea un objeto Array2D, ya que se ha solicitado
            //una matriz
            //matrix ha sido enviado por referencia, para modificar
            //la variable en su contexto original hacemos uso del
            //operador de contenido *
            *matrix = new Array2D<type>();

            //Una vez creado el objeto, invocamos su método create()
            //pasando por valor la variable auxiliar
            (*matrix)->create(ref);
        }

        /*
            Función que retorna las dimensiones del arreglo de un objeto
            Array de tipo <type> enviado por referencia.

            Se recibe por referencia una variable <size> donde se almacenará
            la longitud del arreglo.
        */
        static void getDim(Array<type>* array, int* size){
            //Se invoca el método getDim() del objeto array y el
            //resultado se almacena en la variable auxiliar
            ref = array->getDim();
            //Se extrae la longitud del arreglo y se almacena en
            //<size> haciendo uso del operador de contenido
            *size = ref.n;
        }
        /*
            Función que retorna las dimensiones de la matriz de un objeto
            Array de tipo <type> enviado por referencia.

            Se reciben por referencia una variable <rows> donde se almacenará
            el número de filas de la matriz y una variable <columns> donde
            se almacenará el número de columnas de la matriz.
        */
        static void getDim(Array<type>* matrix, int* rows, int* columns){
            //Se invoca el método getDim() del objeto matrix y el
            //resultado se almacena en la variable auxiliar
            ref = matrix->getDim();
            //Se extraen el número de filas y el número de columnas,
            //el primer dato se almacena en <rows> y el segundo se almacena
            //en <columns>, en ambos caso haciendo uso del operador de
            //contenido
            *rows = ref.n;
            *columns = ref.m;
        }

        /*
            Función que recibe un objeto Array de tipo <type> y lo inicializa
            con valores nulos correspondientes
        */
        static void init(Array<type>* var){
            //Se invoca el método init() del objeto var
            var->init();
        }

        /*
            Función que inserta un valor <value> de tipo <type> en el
            arreglo de un objeto Array de tipo <type>.

            Se recibe <pos> como la posición en el arreglo en la que
            se desea insertar <value>.
        */
        static void insert(Array<type>* array, int pos, type value){
            //Se coloca la posición del arreglo en la variable auxiliar
            ref.n = pos;

            //Se invoca el método insert() del objeto array
            array->insert(ref,value);
        }
        /*
            Función que inserta un valor <value> de tipo <type> en la
            matriz de un objeto Array de tipo <type>.

            Se reciben <row> y <column> como el número de fila y el 
            número de columna, respectivamente, que corresponden a la
            celda de la matriz en la que se desea insertar <value>.
        */
        static void insert(Array<type>* matrix, int row, int column, type value){
            //Se colocan el número de fila y el número de columna en la
            //variable auxiliar
            ref.n = row; ref.m = column;

            //Se invoca el método insert() del objeto matrix
            matrix->insert(ref,value);
        }

        /*
            Función que extra un dato de tipo <type> del arreglo de un
            objeto Array de tipo <type>.

            Se recibe <pos> como la posición en el arreglo en la que se
            desea extraer el dato.

            Se recibe <result> por referencia como la variable de tipo
            <type> donde se desea almacenar el dato extraído.
        */
        static void extract(Array<type>* array, int pos, type* result){
            //Se coloca la posición del arreglo en la variable auxiliar
            ref.n = pos;

            //Se invoca el método extract() del objeto array
            *result = array->extract(ref);
        }
        /*
            Función que extra un dato de tipo <type> de la matriz de un
            objeto Array de tipo <type>.

            Se reciben <row> y <column> como el número de fila y el 
            número de columna, respectivamente, que corresponden a la
            celda de la matriz en la que se desea extraer el dato.

            Se recibe <result> por referencia como la variable de tipo
            <type> donde se desea almacenar el dato extraído.
        */
        static void extract(Array<type>* matrix, int row, int column, type* result){
            //Se colocan el número de fila y el número de columna en la
            //variable auxiliar
            ref.n = row; ref.m = column;

            //Se invoca el método extract() del objeto matrix
            *result = matrix->extract(ref);
        }

        /*
            Función que recibe un objeto Array de tipo <type> y libera todo
            el espacio de memoria utilizado por su respectiva estructura
            de datos estática.
        */
        static void destroy(Array<type>* var){
            //Se invoca el método destroy() del objeto var
            var->destroy();
        }
        
        /*
            Función que recibe un objeto Array de tipo <type> y un valor
            <value> también de tipo <type> para determinar si el dato se
            encuentra almacenado en la estructura de datos estática
            correspondiente al objeto.
            
            Se recibe <result> por referencia como la variable de tipo
            bool donde se desea almacenar el resultado.
        */
        static void search(Array<type>* var, type value, bool* result){
            //Se invoca el método search() del objeto var
            *result = var->search(value);
        }

        /*
            Función que recibe un objeto Array de tipo <type> y un valor
            <value> también de tipo <type> para contar la cantidad de
            ocurrencias del dato en la estructura de datos estática
            correspondiente al objeto.
            
            Se recibe <result> por referencia como la variable de tipo
            int donde se desea almacenar el resultado.
        */
        static void count(Array<type>* var, type value, int* result){
            //Se invoca el método count() del objeto var
            *result = var->count(value);
        }

        /*
            Función que recibe un objeto Array de tipo <type> e invierte
            el contenido de su respectiva estructura de datos estática,
            cuando sea posible.
        */
        static void reverse(Array<type>* var){
            //Se invoca el método reverse() del objeto var
            var->reverse();
        }

        /*
            Función que recibe un objeto Array de tipo <type> y muestra su
            contenido almacenado.

            <verbose> indica el nivel de detalle a mostrar:
                - Si es false, solo se muestra la estructura de datos como tal.

                - Si es true, se detalla posición por posición el contenido de
                  la estructura de datos.
        */
        static void show(Array<type>* var, bool verbose){
            //Se invoca el método show() del objeto var
            var->show(verbose);
        }

        /* Utilidades adicionales que no forman parte de la interfaz Array
           ni de sus implementaciones */

        /*
            Función que recibe un objeto Array de tipo <type> por valor, y
            un segundo objeto Array de tipo <type> por referencia, para copiar
            todo el contenido de la estructura de datos estática del primero
            en la estructura de datos estática del segundo.
        */
        static void create_copy(Array<type>* original, Array<type>** clone){
            //Variable auxiliar local a utilizar en el proceso
            Data dim;

            //Se invoca el metodo getDim() del objeto original
            //y se almacena el resultado en la variable auxiliar local
            dim = original->getDim();

            //Se determina si se debe copiar un arreglo o una matriz invocando
            //el método category() del objeto original
            switch(original->category()){

                //Si se trata de un arreglo
                case ONE_DIMENSION:
                    //Se instancia la copia creando un objeto Array1D
                    //haciendo uso del operador de contenido
                    *clone = new Array1D<type>();
                    
                    //Se invoca el método create() de la copia enviando
                    //la variable auxiliar local, que contiene la longitud del
                    //arreglo del objeto original
                    (*clone)->create(dim);

                    //Se recorre el arreglo del objeto original
                    for(int i = 0; i < dim.n; i++){
                        //Se almacena la posición actual en la variable
                        //auxiliar de la clase
                        ref.n = i;

                        //Se invoca el método insert() de la copia, enviando
                        //como dato a insertar el obtenido invocando el
                        //método extract() del objeto original para la
                        //posición actual
                        (*clone)->insert(ref, original->extract(ref));
                    }
                    break;

                //Si se trata de una matriz
                case TWO_DIMENSIONS:
                    //Se instancia la copia creando un objeto Array2D
                    //haciendo uso del operador de contenido
                    *clone = new Array2D<type>();
                    
                    //Se invoca el método create() de la copia enviando
                    //la variable auxiliar local, que contiene el número de filas
                    //y el número de columnas de la matriz del objeto original
                    (*clone)->create(dim);

                    //Se recorre la matriz del objeto original
                    for(int i = 0; i < dim.n*dim.m; i++){
                        //Se almacena el número de fila y número de columna
                        //de la celda actual en la variable auxiliar de la clase
                        ref.n = i/dim.m;
                        ref.m = i%dim.m;

                        //Se invoca el método insert() de la copia, enviando
                        //como dato a insertar el obtenido invocando el
                        //método extract() del objeto original para la
                        //celda actual
                        (*clone)->insert(ref, original->extract(ref));
                    }
                    break;
            }
        }
};
