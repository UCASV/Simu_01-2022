/*
    Implementación de la interfaz Array, definida en "Array.h",
    para una estructura de datos estática unidimensional, es decir,
    para un arreglo.

    Se define la implementación como independiente del tipo de
    dato a almacenar mediante el uso de template.
*/
template <typename type>
/*
    En C++, la implementación se maneja como una herencia,
    de modo que Array1D hereda de Array.

    El indicador de visibilidad 'public' indica que Array1D tendrá
    acceso a todos los métodos de Array manteniendo la visibilidad
    original.

    Dado que Array es un template, debe indicarse el tipo de dato
    a utilizar mediante un "meta-parámetro". Sin embargo, el tipo
    de dato aún no ha sido definido, ya que Array1D también es un
    template, por lo que el "meta-parámetro" es el tipo de dato
    genérico local <type>.
*/
class Array1D: public Array<type>{
    /*
        Como atributo privado local se manejará el arreglo de
        datos tipo <type> como tal. Se declara un puntero ya que
        se manejará por dirección el bloque de memoria correspondiente.

        El otro atributo privado local es el tamaño <size> del arreglo,
        como dato acompañante para controlar procesos de recorrido.
    */
    private:
        type* array;
        int size;

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
            //Se retorna ONE_DIMENSION ya que localmente manejamos un arreglo
            return ONE_DIMENSION;
        }

        /*
            Función para crear espacio en memoria para una
            estructura de datos estática de tipo <type>.

            <dim> es de tipo "struct Data", y dado que localmente
            manejamos un arreglo, se asume que contiene un solo
            dato, que será la longitud del arreglo.
        */
        void create(Data length) override {
            size = length.n; //Se extrae y almacena la longitud del arreglo

            /*Casting a (type*) ya que el bloque de memoria
              se provee "crudo" ( void* ).*/
            //sizeof(type) ya que se almacenarán datos de tipo <type>.
            /*sizeof(type)*size para generar tantos espacios
              como los indicados por el tamaño del arreglo.*/
            array = (type*) malloc(sizeof(type)*size);
        }

        /*
            Función que retorna las dimensiones de la estructura
            de datos estática local mediante un objeto de tipo
            "struct Data".
            
            Ya que localmente se maneja un arreglo, el objeto contendrá
            sólo un dato, que será la longitud del arreglo.
        */
        Data getDim() override {
            Data dim;     //Se crea el objeto de tipo Data
            dim.n = size; //Se almacena la longitud del arreglo
            return dim;   //Se retorna el objeto de tipo Data
        }

        /*
            Función que coloca en cada posición de la estructura
            de datos estática local un valor nulo correspondiente
            al tipo <type> utilizado.
        */
        void init() override {
            //Se recorre el arreglo
            for(int i = 0; i < size; i++)
                array[i] = (type) 0; //Se coloca <(type) 0> en cada posición del arreglo
        }

        /*
            Función para insertar un valor <value> de tipo <type>
            en la posición <pos> de un arreglo de datos de tipo <type>.

            <pos> es de tipo "struct Data", y como localmente se maneja
            un arreglo, se asume que contiene un solo dato, que será la
            posición en el arreglo en la que se desea insertar <value>.
        */
        void insert(Data pos, type value) override {
            //Se extrae la posición de <pos> y se usa para indexar el arreglo
            array[pos.n] = value;
        }

        /*
            Función para extraer un dato de tipo <type> de la
            posición indicada por <pos> en la estructura de datos
            estática local.

            <pos> es de tipo "struct Data", y dado que localmente se
            maneja un arreglo, se asume que contiene un solo dato, que
            será la posición en el arreglo en la que se desea extraer
            el dato.
        */
        type extract(Data pos) override {
            //Se extrae la posición de <pos> y se usa para indexar el arreglo
            return array[pos.n];
        }

        /*
            Función para liberar todo el espacio en memoria
            utilizado por una estructura de datos estática de
            tipo <type>.
        */
        void destroy() override {
            /*Se indica la dirección inicial del bloque de
              memoria a liberar.*/
            free(array);
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
            //Se recorre el arreglo
            for(int i = 0; i < size; i++)
                //Verifico en la posición actual si se ha
                //encontrado el dato buscado.
                if(array[i] == value){
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
            //Recorro el arreglo
            for(int i = 0; i < size; i++)
                //Verifico si hay ocurrencia en la posición
                //actual del arreglo
                if(array[i] == value)
                    //Si hay ocurrencia, actualizo el contador.
                    //No hay break, ya que me interesa saber
                    //el total de ocurrencias, sigo buscando.
                    cont++;
            //Retorno el resultado
            return cont;
        }

        /*
            Función que invierte el contenido de una estructura de datos
            estática de tipo <type>.
        */
        void reverse() override {
            //Se crea un nuevo arreglo de datos de tipo <type>
            //del mismo tamaño del original.
            type* array2 = (type*) malloc(sizeof(type)*size);

            //Se recorre el arreglo original en reversa desde
            //la última posición.
            for (int i = size-1; i >= 0; i--)
                /*
                    Para determinar el índice en el nuevo arreglo
                    donde se insertará el dato en la posición actual
                    del recorrido del arreglo original, se toma en
                    cuenta lo siguiente:

                    Si el arreglo original tiene 5 posiciones,
                    size es 5
                    Posiciones: 0 1 2 3 4
                    Queremos:
                        - Guardar el dato de la posición 4 del
                        original en la posición 0 del nuevo arreglo.
                        - Guardar el dato de la posición 3 del
                        original en la posición 1 del nuevo arreglo.
                    
                    Observando:
                    4 -> 0 --> 5 - (4 + 1) = 0
                    3 -> 1 --> 5 - (3 + 1) = 1
                    2 -> 2 --> 5 - (2 + 1) = 2
                    1 -> 3 --> 5 - (1 + 1) = 3
                    0 -> 4 --> 5 - (0 + 1) = 4

                    Es decir, a partir de la posición del arreglo
                    original, se le suma 1 y el resultado se le resta
                    a 5, y con esto se obtiene la posición requerida en
                    el nuevo arreglo.

                    Generalizando:

                    indice_nuevo_arreglo = size - (indice_arreglo_original + 1)

                */
                array2[ size - (i + 1) ] = array[i];

            //El arreglo original será sustituido por el nuevo arreglo,
            //por lo que dicho contenido ya no será utilizado y se puede
            //liberar.
            //Para esto se invoca el metodo local destroy()
            destroy();

            //Se almacena como nuevo arreglo local el nuevo arreglo creado
            //que contiene la información invertida.
            array = array2;
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
                for(int i = 0; i < size; i++)
                    //Se especifica explícitamente el valor de cada elemento
                    //almacenado en el arreglo, uno por línea.
                    cout << "Element #" << i+1 << " is: " << array[i] << "\n";
            else{
                //Se muestra el contenido del arreglo como una secuencia de datos
                //representando las distintas posiciones mediante el uso de ','.

                //Se abre la secuencia
                cout << "[ ";

                //Se recorre el arreglo hasta la penúltima posición
                for(int i = 0; i < size-1; i++)
                    //Se coloca el dato en la posición actual seguido de ','
                    cout << array[i] << ", ";
                
                //Se coloca el dato de la última posición seguido del cierre de la secuencia
                cout << array[size-1] << " ]\n";
            }
        }
};
