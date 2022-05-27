/*
    Implementación para un grafo.

    Se define la implementación como independiente del tipo de dato
    a almacenar mediante el uso de template.
*/
template <typename T>
/*
    En C++, la implementación se maneja como una herencia,
    de modo que DSG hereda de:
        - dynamicDS, ya que es la que provee la funcionalidad
          básica de una estructura de datos dinámica.
        - measurable, ya que es posible obtener la cantidad de nodos
          de un grafo.
        - positionable, ya que es posible indexar un grafo.

    El indicador de visibilidad 'public' indica que DSG tendrá
    acceso a todos los métodos de las interfaces que implementa,
    manteniendo la visibilidad original de todas ellas.

    Dado que varias de las interfaces son templates, debe indicarse
    el tipo de dato a utilizar mediante un "meta-parámetro". Sin
    embargo, el tipo de dato aún no ha sido definido, ya que DSG
    también es un template, por lo que el "meta-parámetro" es el
    tipo de dato genérico local <T>.
*/
class DSG: public dynamicDS<T>,public measurable,public positionable<T> {
    private:
        /*
            Como atributo privado local se manejará el grafo de datos de
            tipo <type> como tal.
        
            Se declara un puntero a NodeG, un Nodo para grafos.
        */
        NodeG<T>* G;

        /*
            Función que crea espacio en memoria para un NodeG<type>,
            es decir, un Nodo para un grafo de tipo <type>.

            Se retorna la dirección del nuevo nodo creado, y esta
            dirección se retorna en forma "cruda" como void*.
        */
        void* createNode() override {
            //sizeof( NodeG<type> ) ya que se necesita espacio para
            //un Nodo para grafos para almacenar un dato de tipo <type>
            return malloc(sizeof(NodeG<T>));
        }

    public:
        /*
            Función que retorna la categoría del grafo local de
            tipo <type>.
        */
        category getCategory() override {
            //Al tratarse de una lista enlazada doble, se retorna
            //GRAPH.
            return GRAPH;
        }

        /*
            Función para liberar todo el espacio en memoria
            utilizado por un grafo de tipo <type>.
        */
        void destroy() override {
            //Variables auxiliares para el proceso
            NodeG<T>* temp;
            NodeSL<NodeG<T>*>* L;
            NodeSL<NodeG<T>*>* tempL;

            //Se recorre el listado de nodos del grafo hasta el final
            while(G != NULL){
                //Se copia la referencia al nodo actual en la
                //variable auxiliar temp para "rescatarlo"
                temp = G;

                //Se almacena el listado de conexiones del nodo "rescatado"
                //en la variable auxiliar L
                L = temp->connections;

                //Se recorre el listado de conexiones hasta el final
                while(L != NULL){
                    //Se copia la referencia a la conexión actual en la
                    //variable auxiliar tempL para "rescatarla"
                    tempL = L;

                    //Avanzamos a la siguiente conexión del listado
                    //Acá es donde perderíamos la referencia a la conexión
                    //actual si no la hubiéramos "rescatado"
                    L = L->next;

                    //A través de la variable auxiliar tempL, liberamos
                    //la conexión previamente "rescatada"
                    free(tempL);
                }

                //Avanzamos al siguiente nodo del grafo
                //Acá es donde perderíamos la referencia al nodo
                //actual si no lo hubiéramos "rescatado"
                G = G->next;

                //A través de la variable auxiliar temp, liberamos
                //el nodo previamente "rescatado"
                free(temp);
            }
            //Al final del proceso, G habrá quedado apuntando a NULL,
            //lo cual está bien ya que se interpreta como un grafo
            //vacío, y eso es coherente con la operación realizada.
        }

        /*
            Función que determina si un valor <value> de tipo <type>
            se encuentra o no dentro de un grafo de tipo <type>.

            Se retorna true si se encuentra, false en caso
            contrario.
        */
        bool search(T value) override {
            //Respuesta por defecto: "No se encuentra"
            bool ans = false;

            //Se copia el puntero al inicio del grafo para no perder
            //la referencia durante el proceso de recorrido
            NodeG<T>* Gcopy = G;

            //Se recorre el listado de nodos del grafo hasta final
            while(Gcopy != NULL){
                //Verificamos si el dato almacenado en el nodo
                //actual es igual al que buscamos
                if(Gcopy->data == value){
                    //Se ha encontrado el dato, se setea una
                    //respuesta positiva
                    ans = true;
                    //Se termina el proceso de recorrido porque
                    //ya no es necesario seguir buscando
                    break;
                }
                //Se avanza al siguiente nodo del grafo
                Gcopy = Gcopy->next;
            }
            //Se retorna el resultado
            return ans;
        }

        /*
            Función que determina la cantidad de ocurrencias de un valor
            <value> de tipo <type> en un grafo de tipo <type>.
        */
        int count(T value) override {
            //Se inicializa un contador en 0
            int cont = 0;

            //Se copia el puntero al inicio del grafo para no perder
            //la referencia durante el proceso de recorrido
            NodeG<T>* Gcopy = G;

            //Se recorre el listado de nodos del grafo hasta final
            while(Gcopy != NULL){
                //Verificamos si el dato almacenado en el nodo
                //actual es igual al que buscamos, en cuyo caso
                //aumentamos el contador
                if(Gcopy->data == value) cont++;

                //Se avanza al siguiente nodo del grafo
                Gcopy = Gcopy->next;
            }

            //Se retorna el resultado
            return cont;
        }

        /*
            Función que muestra el contenido de un grafo de tipo <type>.

            <verbose> indica el nivel de detalle a mostrar:
                - Si es false, solo se muestra el grafo como tal.

                - Si es true, se detalla posición por posición, y conexión por
                  por conexión, el contenido del grafo.
        */
        void show(bool verbose) override {
            //Se verifica si el grafo está vacío,
            //en cuyo caso no hay nada que mostrar y se
            //terminaría el proceso de mostrado
            if(G == NULL){
                cout << "El grafo está vacío.\n";
                return;
            }

            //Se copia el puntero al inicio del grafo para no perder
            //la referencia durante el proceso de recorrido
            NodeG<T>* Gcopy = G;
            //Variable auxiliar para el proceso
            NodeSL<NodeG<T>*>* L;

            if(verbose)
                //Se recorre el listado de nodos del grafo hasta final
                while(Gcopy != NULL){
                    /*
                        Se muestra el contenido de cada nodo con el formato siguiente:

                                        Nodo #: <id>
                                        Datos: <dato>
                                        Conexiones:
                                            Conexión #1 corresponde al Nodo #<id>
                                            Conexión #2 corresponde al Nodo #<id>
                                                            ...
                    */

                    //Se muestran id y dato del nodo actual
                    cout << "Nodo #" << Gcopy->id << ":\n\tDatos: " << Gcopy->data << "\n\tConexiones:\n";

                    //Se extrae el listado de conexiones del nodo actual en la
                    //variable auxiliar L
                    L = Gcopy->connections;

                    //Variable auxiliar para generar un correlativo en el proceso
                    int index = 1;

                    //Se recorre el listado de conexiones hasta el final
                    while(L != NULL){
                        //Se informan los detalles de la conexión actual
                        cout << "\tConexión #" << index << " corresponde al Nodo #" << L->data->id << "\n";
                        //Se aumenta el correlativo
                        index++;

                        //Se avanza a la siguiente conexión
                        L = L->next;
                    }

                    //Se avanza al siguiente nodo del grafo
                    Gcopy = Gcopy->next;
                }
            else{
                //Se recorre el listado de nodos del grafo hasta final
                while(Gcopy != NULL){
                    /*
                        Se muestra el contenido en una sola línea colocando la información de cada
                        nodo con el formato siguiente:

                                    ( <id> , <dato> , [ <id1>-><id2>->...->NULL ] ) ->
                    */

                    //Se abre el nodo actual y se coloca su identificador y su dato, y se abre
                    //su listado de conexiones
                    cout << "( " << Gcopy->id << " , " << Gcopy->data << " , [ ";

                    //Se extrae el listado de conexiones del nodo actual y se almacena
                    //en la variable auxiliar L
                    L = Gcopy->connections;

                    //Se recorre el listado de conexiones hasta el final
                    while(L != NULL){
                        //Se muestra el identificador del nodo de la conexión actual
                        cout << L->data->id << "->";

                        //Se avanza a la siguiente conexión
                        L = L->next;
                    }
                    //Se coloca NULL como la última conexión, se cierra el listado de conexiones,
                    //y se cierra el nodo actual del grafo
                    cout << "NULL ] )" << " -> ";

                    //Se avanza al siguiente nodo del grafo
                    Gcopy = Gcopy->next;
                }

                //Se coloca NULL como el último nodo del listado de nodos del grafo
                cout << "NULL\n";
            }
        }

        /*
            Función que obtiene el Nodo inicial del grafo local
            de tipo <type>.

            La función retorna la dirección de dicho Nodo.
        */
        Node<T>* getRoot(){
            return G;
        }

        /*
            Función para inicializar el grafo de tipo <type>.
        */
        void create() override {
            //Para inicializar un grafo basta con que el puntero
            //al inicio del grafo apunte a NULL
            G = NULL;
        }
        
        /*
            Función que retorna la cantidad de nodos del grafo local
            de tipo <type>.
        */
        int extension() override {
            //Se inicializa un contador en 0
            int cont = 0;

            //Se copia el puntero al inicio del grafo para no
            //perder la referencia durante el proceso de recorrido
            NodeG<T>* Gcopy = G;

            //Se recorre el listado del grafo hasta el final
            while(Gcopy != NULL){
                //Si entramos al while, hay un nodo no evaluado
                //Se actualiza el contador
                cont++;

                //Se avanza al siguiente nodo del grafo
                Gcopy = Gcopy->next;
            }

            /* Se puede añadir acá el conteo del número de aristas */

            //Se retorna el resultado
            return cont;
        }

        /*
            Función para insertar un nodo con identificador <id> con un
            dato <value> de tipo <type> en un grafo de tipo <type>.

            El orden en el listado de nodos de un grafo no es relevante,
            por simplicidad se colocarán nuevos nodos al inicio del listado.
        */
        void insert(int id, T value) override {
            //Se crea un nuevo nodo para el grafo que alojará el nuevo valor <value>
            NodeG<T>* temp = (NodeG<T>*) createNode();
            //Se define por defecto que el nuevo nodo no es el punto de entrada
            temp->entry = false;
            //Se define el identificador del nuevo nodo como <id>
            temp->id = id;
            //Se coloca <value> como el dato del nuevo nodo
            temp->data = value;
            //Todavía no hay conexiones definidas para el nuevo nodo, se
            //inicializan en NULL
            temp->connections = NULL;

            //Se verifica si el grafo está vacío
            if(G == NULL){
                //Si el grafo está vacío, el nuevo nodo se marca como
                //el nodo de entrada al grafo
                temp->entry = true;
                //No existe aún nodo siguiente para el nuevo nodo
                temp->next = NULL;
            }else
                //El nodo siguiente al nuevo nodo será el nodo que
                //actualmente está al inicio del listado del grafo
                temp->next = G;

            //El nuevo inicio del listado de nodos del grafo será el
            //nuevo nodo creado
            G = temp;
        }

        /*
            Función para extraer un dato de tipo <type> del nodo con
            identificador <id> del grafo local de tipo <type>.

            Se asume pre-validación de un identificador válido.
        */
        T extract(int id) override {
            //Se copia el puntero al inicio del grafo para no
            //perder la referencia durante el proceso de recorrido
            NodeG<T>* Gcopy = G;

            //Se recorre el listado de nodos del grafo hasta el final
            while(Gcopy != NULL){
                //Si el nodo actual corresponde con el solicitado,
                //ya no seguimos recorriendo el listado
                if(Gcopy->id == id) break;

                //Se avanza al siguiente nodo del grafo
                Gcopy = Gcopy->next;
            }

            //Se retorna el dato del nodo del grafo solicitado
            return Gcopy->data;
        }
};
