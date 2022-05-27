/*
    Implementación para una estructura de datos estática unidimensional,
    es decir, para un arreglo.

    Se define la implementación como independiente del tipo de
    dato a almacenar mediante el uso de template.
*/
template <typename T>
/*
    En C++, la implementación se maneja como una herencia,
    de modo que DSA hereda de:
        - staticDS_1D, ya que es la que provee su funcionalidad
          básica.
        - measurable, ya que es posible obtener la longitud de un
          arreglo.
        - positionable, ya que es posible indexar un arreglo por
          posición.
        - reversible, ya que es posible invertir el contenido de un
          arreglo.

    El indicador de visibilidad 'public' indica que DSA tendrá
    acceso a todos los métodos de las interfaces que implementa,
    manteniendo la visibilidad original de todas ellas.

    Dado que varias de las interfaces son templates, debe indicarse
    el tipo de dato a utilizar mediante un "meta-parámetro". Sin
    embargo, el tipo de dato aún no ha sido definido, ya que DSA
    también es un template, por lo que el "meta-parámetro" es el
    tipo de dato genérico local <T>.
*/
class DSA: public staticDS_1D<T>,public measurable,public positionable<T>,public reversible {
    /*
        Como atributo privado local se manejará el arreglo de
        datos tipo <T> como tal. Se declara un puntero ya que
        se manejará por dirección el bloque de memoria correspondiente.

        El otro atributo privado local es el tamaño <size> del arreglo,
        como dato acompañante para controlar procesos de recorrido.
    */
    private:
        T* array;
        int size;

    //Se procede a la implementación como tal de los métodos de las interfaces
    //override indica la respectiva sobreescritura de cada método
    public:
        /*
            Función que retorna la categoría del arreglo local.

            La función hace uso de la enumeración category
            definida en "SDDS.h".
        */
        category getCategory() override {
            //Se retorna ARRAY ya que localmente manejamos un arreglo
            return ARRAY;
        }
        /*
            Función para liberar todo el espacio en memoria
            utilizado por una estructura de datos estática de
            tipo <T>.
        */
        void destroy() override {
            /*Se indica la dirección inicial del bloque de
              memoria a liberar.*/
            free(array);
        }
        /*
            Función que determina si un valor <value> de tipo <T>
            se encuentra o no dentro de un arreglo de tipo <type>.

            Se retorna true si se encuentra, false en caso
            contrario.
        */
        bool search(T value) override {
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
            <value> de tipo <T> en un arreglo de tipo <type>.
        */
        int count(T value) override {
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
            Función que muestra el contenido de un arreglo de tipo <type>.

            <verbose> indica el nivel de detalle a mostrar:
                - Si es false, solo se muestra el arreglo como tal.

                - Si es true, se detalla posición por posición el contenido del
                  arreglo.
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

        /*
            Función para crear espacio en memoria para un
            arreglo de tipo <type>.

            Se recibe <n>, que será la longitud del arreglo.
        */
        void create(int n) override {
            //Se extrae y almacena la longitud del arreglo
            size = n;

            /*Casting a (T*) ya que el bloque de memoria
              se provee "crudo" ( void* ).*/
            //sizeof(T) ya que se almacenarán datos de tipo <T>.
            /*sizeof(T)*size para generar tantos espacios
              como los indicados por el tamaño del arreglo.*/
            array = (T*) malloc(sizeof(T)*n);
        }

        /*
            Función que retorna la longitud del arreglo local.
        */
        int extension() override {
            //Se retorna la longitud almacenado en el atributo
            //privado correspondiente
            return size;
        }

        /*
            Función para insertar un valor <value> de tipo <T>
            en la posición <pos> de un arreglo de datos de tipo <T>.

            <pos> es la posición en el arreglo en la que se desea
            insertar <value>.
        */
        void insert(int pos, T value) override {
            //Indexamos el arreglo utilizando <pos> para insertar <value>
            array[pos] = value;
        }
        /*
            Función para extraer un dato de tipo <T> de la
            posición indicada por <pos> en el arreglo local.

            <pos> es la posición en el arreglo en la que se
            desea extraer el dato.
        */
        T extract(int pos) override {
            //Indexamos el arreglo utilizando <pos> para extraer el dato
            return array[pos];
        }

        /*
            Función que invierte el contenido de un arreglo de tipo <T>.
        */
        void reverse() override {
            //Se crea un nuevo arreglo de datos de tipo <T>
            //del mismo tamaño del original.
            T* array2 = (T*) malloc(sizeof(T)*size);

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
};
