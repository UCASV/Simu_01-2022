/*
    Implementación para una lista enlazada doble.

    Se define la implementación como independiente del tipo de dato
    a almacenar mediante el uso de template.
*/
template <typename T>
/*
    En C++, la implementación se maneja como una herencia,
    de modo que DSDL hereda de:
        - dynamicDS, ya que es la que provee la funcionalidad
          básica de una estructura de datos dinámica.
        - insertable, ya que permite la inserción de datos sin
          necesidad de indexamiento.
        - measurable, ya que es posible obtener la longitud de una
          lista enlazada doble.
        - positionable, ya que es posible indexar una lista enlazada
          doble por posición.
        - reversible, ya que es posible invertir el contenido de una
          lista enlazada doble.

    El indicador de visibilidad 'public' indica que DSDL tendrá
    acceso a todos los métodos de las interfaces que implementa,
    manteniendo la visibilidad original de todas ellas.

    Dado que varias de las interfaces son templates, debe indicarse
    el tipo de dato a utilizar mediante un "meta-parámetro". Sin
    embargo, el tipo de dato aún no ha sido definido, ya que DSDL
    también es un template, por lo que el "meta-parámetro" es el
    tipo de dato genérico local <T>.
*/
class DSDL: public dynamicDS<T>,public insertable<T>,public measurable,public positionable<T>,public reversible {
    private:
        /*
            Como atributo privado local se manejará la lista enlazada
            doble de datos tipo <type> como tal.
        
            Se declara un puntero a NodeDL, un Nodo para listas enlazadas
            dobles.
        */
        NodeDL<T>* L;

        /*
            Función que crea espacio en memoria para un NodeDL<type>,
            es decir, un Nodo para una lista enlazada doble de tipo
            <type>.

            Se retorna la dirección del nuevo nodo creado, y esta
            dirección se retorna en forma "cruda" como void*.
        */
        void* createNode() override {
            //sizeof( NodeDL<type> ) ya que se necesita espacio para
            //un Nodo para listas enlazadas dobles para almacenar un
            //dato de tipo <type>
            return malloc(sizeof(NodeDL<T>));
        }

    public:
        /*
            Función que retorna la categoría de la lista enlazada
            doble local de tipo <type>.
        */
        category getCategory() override {
            //Al tratarse de una lista enlazada doble, se retorna
            //DOUBLE_LINKED_LIST.
            return DOUBLE_LINKED_LIST;
        }

        /*
            Función para liberar todo el espacio en memoria
            utilizado por una lista enlazada doble de tipo
            <type>.
        */
        void destroy() override {
            //Variable auxiliar para el proceso
            NodeDL<T>* temp;

            //Se recorre la lista hasta el final
            while(L != NULL){
                //Se copia la referencia al nodo actual en la
                //variable auxiliar para "rescatarlo"
                temp = L;

                //Avanzamos al siguiente nodo de la lista
                //Acá es donde perderíamos la referencia al nodo
                //actual si no lo hubiéramos "rescatado"
                L = L->next;

                //A través de la variable auxiliar, liberamos
                //el nodo previamente "rescatado"
                free(temp);
            }
            //Al final del proceso, L habrá quedado apuntando a NULL,
            //lo cual está bien ya que se interpreta como una lista
            //vacía, y eso es coherente con la operación realizada.
        }

        /*
            Función que determina si un valor <value> de tipo <type>
            se encuentra o no dentro de una lista enlazada doble
            de tipo <type>.

            Se retorna true si se encuentra, false en caso
            contrario.
        */
        bool search(T value) override {
            //Respuesta por defecto: "No se encuentra"
            bool ans = false;

            //Se copia el puntero al inicio de la lista enlazada
            //doble para no perder la referencia durante el
            //proceso de recorrido
            NodeDL<T>* Lcopy = L;

            //Se recorre la lista hasta el final
            while(Lcopy != NULL){
                //Verificamos si el dato almacenado en el nodo
                //actual es igual al que buscamos
                if(Lcopy->data == value){
                    //Se ha encontrado el dato, se setea una
                    //respuesta positiva
                    ans = true;
                    //Se termina el proceso de recorrido porque
                    //ya no es necesario seguir buscando
                    break;
                }
                //Se avanza al siguiente nodo de la lista
                Lcopy = Lcopy->next;
            }
            //Se retorna el resultado
            return ans;
        }

        /*
            Función que determina la cantidad de ocurrencias de un valor
            <value> de tipo <type> en una lista enlazada doble de tipo
            <type>.
        */
        int count(T value) override {
            //Se inicializa un contador en 0
            int cont = 0;

            //Se copia el puntero al inicio de la lista enlazada
            //doble para no perder la referencia durante el
            //proceso de recorrido
            NodeDL<T>* Lcopy = L;

            //Se recorre la lista hasta el final
            while(Lcopy != NULL){
                //Verificamos si el dato almacenado en el nodo
                //actual es igual al que buscamos, en cuyo caso
                //aumentamos el contador
                if(Lcopy->data == value) cont++;

                //Se avanza al siguiente nodo de la lista
                Lcopy = Lcopy->next;
            }

            //Se retorna el resultado
            return cont;
        }

        /*
            Función que muestra el contenido de una lista enlazada doble de
            tipo <type>.

            <verbose> indica el nivel de detalle a mostrar:
                - Si es false, solo se muestra la lista como tal.

                - Si es true, se detalla posición por posición el contenido de
                  la lista.
        */
        void show(bool verbose) override {
            //Se verifica si la lista está vacía,
            //en cuyo caso no hay nada que mostrar y se
            //terminaría el proceso de mostrado
            if(L == NULL){
                cout << "La lista está vacía.\n";
                return;
            }

            //Se copia el puntero al inicio de la lista enlazada
            //simple para no perder la referencia durante el
            //proceso de recorrido
            NodeDL<T>* Lcopy = L;

            if(verbose){
                //Variable auxiliar para mostrar el contenido de la lista
                int index = 1;

                //Se recorre la lista hasta el final
                while(Lcopy != NULL){
                    //Se especifica explícitamente el valor de cada elemento
                    //almacenado en la lista, uno por línea, indicando la posición
                    //haciendo uso de la variable auxiliar
                    cout << "Element #" << index << " is: " << Lcopy->data << "\n";
                    //Se le suma 1 a la variable auxiliar
                    index++;

                    //Se avanza al siguiente nodo de la lista
                    Lcopy = Lcopy->next;
                }       
            }else{
                //Se muestra el contenido de la lista como una secuencia de datos
                //conectados entre sí en una sola línea, representando las
                //conexiones con '<->'.

                //Se recorre la lista hasta el final
                while(Lcopy != NULL){
                    //Se coloca el dato actual seguido de '<->'
                    cout << Lcopy->data << " <-> ";

                    //Se avanza al siguiente nodo de la lista
                    Lcopy = Lcopy->next;
                }

                //El último dato conecta con NULL, indicando el final de la lista
                cout << "NULL\n";
            }
        }

        /*
            Función que obtiene el Nodo inicial de la lista enlazada doble
            local de tipo <type>.

            La función retorna la dirección de dicho Nodo.
        */
        Node<T>* getRoot(){
            return L;
        }

        /*
            Función para inicializar la lista enlazada doble de
            tipo <type>.
        */
        void create() override {
            //Para inicializar una lista enlazada doble basta con
            //que el puntero al inicio de la lista apunte a NULL
            L = NULL;
        }

        /*
            Función para insertar un valor <value> de tipo <type>
            en la lista enlazada doble local de tipo <type>.

            Se asume inserción al inicio de la lista.
        */
        void insert(T value) override {
            //Se crea un nuevo nodo para la lista enlazada doble
            //que alojará el nuevo valor <value>
            NodeDL<T>* temp = (NodeDL<T>*) createNode();
            //Se coloca el valor <value> en el nuevo nodo
            temp->data = value;
            //Como el nuevo nodo se colocará al inicio de la lista,
            //su nodo anterior será NULL
            temp->prev = NULL;

            //Se verifica si la lista se encuentra actualmente vacía
            if(L == NULL)
                //Si la lista está vacía, el nodo siguiente al nuevo
                //nodo no existe aún, por lo que se define como NULL
                temp->next = NULL;
            else{
                //Si la lista no está vacía, el nodo anterior al nodo
                //que actualmente está al inicio de la lista será el
                //nuevo nodo
                L->prev = temp;

                //El nodo siguiente al nuevo nodo, será el que está
                //actualmente al inicio de la lista
                temp->next = L;
            }

            //El nuevo inicio de la lista es el nuevo nodo
            L = temp;
        }

        /*
            Función que retorna la longitud de la lista enlazada
            doble local de tipo <type>.
        */
        int extension() override {
            //Se inicializa un contador en 0
            int cont = 0;

            //Se copia el puntero al inicio de la lista enlazada
            //doble para no perder la referencia durante el
            //proceso de recorrido
            NodeDL<T>* Lcopy = L;

            //Se recorre la lista hasta el final
            while(Lcopy != NULL){
                //Si entramos al while, hay un nodo no evaluado
                //Se actualiza el contador
                cont++;

                //Se avanza al siguiente nodo de la lista
                Lcopy = Lcopy->next;
            }

            //Se retorna el resultado
            return cont;
        }

        /*
            Función para insertar un valor <value> de tipo <type>
            en la posición indicada por <pos> de la lista enlazada doble
            local de tipo <type>.

            Se asume pre-validación de una posición válida.
        */
        void insert(int pos, T value) override {
            //Se crea un nuevo nodo para la lista enlazada doble
            //que alojará el nuevo valor <value>
            NodeDL<T>* temp = (NodeDL<T>*) createNode();
            //Se coloca el valor <value> en el nuevo nodo
            temp->data = value;

            //Se copia el puntero al inicio de la lista enlazada
            //doble para no perder la referencia durante el
            //proceso de recorrido
            NodeDL<T>* Lcopy = L;

            //Se avanza en la lista hasta la posición anterior a la
            //posición en la que se desea insertar el nuevo nodo
            //Nos referiremos a esta posición como "antecedente"
            for(int i = 0; i < pos-1; i++) Lcopy = Lcopy->next;

            /* Se procede a realizar las conexiones y desconexiones
               necesarias para la inserción del nuevo nodo:         */

            //El nodo anterior al nuevo nodo será el "nodo antecedente"
            temp->prev = Lcopy;
            //El nodo siguiente al nuevo nodo será el que actualmente es
            //el nodo siguiente del "nodo antecedente"
            temp->next = Lcopy->next;
            //El nodo anterior del nodo siguiente del "nodo antecedente"
            //será el nuevo nodo
            Lcopy->next->prev = temp;
            //El nodo siguiente del "nodo antecedente" será el nuevo nodo
            Lcopy->next       = temp;
        }

        /*
            Función para extraer un dato de tipo <type> de la
            posición indicada por <pos> en la lista enlazada doble
            local de tipo <type>.

            Se asume pre-validación de una posición válida.
        */
        T extract(int pos) override {
            //Se copia el puntero al inicio de la lista enlazada
            //doble para no perder la referencia durante el
            //proceso de recorrido
            NodeDL<T>* Lcopy = L;

            //Se avanza en la lista hasta la posición indicada por
            //el parámetro <pos>
            for(int i = 0; i < pos; i++) Lcopy = Lcopy->next;

            //Se retorna el dato almacenado en el nodo ubicado en
            //la posición solicitada
            return Lcopy->data;
        }

        /*
            Función que invierte el contenido de una lista enlazada
            doble de tipo <type>.
        */
        void reverse() override {
            //Se prepara un puntero a Nodo de lista enlazada doble para
            //datos de tipo <type> que servirá para apuntar al inicio de
            //una nueva lista que contendrá los datos de la lista actual
            //en orden invertido
            NodeDL<T>* new_one = NULL;

            //Se copia el puntero al inicio de la lista enlazada
            //simple para no perder la referencia durante el
            //proceso de recorrido
            NodeDL<T>* Lcopy = L;

            //Se prepara un puntero a nodo de lista enlazada doble
            //de tipo <type> adicional que servirá como variable auxiliar
            NodeDL<T>* temp;

            //Se recorre la lista hasta el final
            while(Lcopy != NULL){
                /*Se crea un nodo para la nueva lista, manteniendo que
                  sea para una lista enlazada doble para datos de tipo
                  <type>.
                  Dado que createNode() retorna un puntero "crudo", es
                  necesario hacer el casting correspondiente para darle
                  formato al bloque de memoria otorgado.               */
                temp = (NodeDL<T>*) createNode();

                //Se coloca en el nuevo nodo el dato ubicado en el nodo
                //actual del recorrido de la lista local
                temp->data = Lcopy->data;

                //El nodo nuevo, ya que se colocará al inicio, no tendrá
                //nodo anterior, por lo que se setea como NULL
                temp->prev = NULL;

                //Se procede a insertar el nuevo nodo al inicio de la
                //nueva lista
                //Se verifica primero si la nueva lista se encuentra vacía
                if(new_one == NULL)
                    //Si la nueva lista se encuentra vacía, el nodo siguiente
                    //al nuevo nodo creado aún no existe, por lo que se define
                    //como NULL
                    temp->next = NULL;
                else{
                    //Si la nueva lista no está vacía, entonces el nodo anterior al
                    //que actualmente se encuentra al inicio de la nueva lista será
                    //el nuevo nodo
                    new_one->prev = temp;
                    //Además, el nodo siguiente al nuevo nodo creado es el nodo que
                    //actualmente se encuentra al inicio de la nueva lista
                    temp->next = new_one;
                }

                //El nuevo inicio de la nueva lista es ahora el nuevo nodo creado
                new_one = temp;

                //Se avanza al siguiente nodo de la lista local
                Lcopy = Lcopy->next;
            }

            //La lista local en su estado actual ya no será utilizada, por lo que
            //se invoca a la función destroy() para liberar todo el espacio de
            //memoria que le corresponde
            destroy();

            //La nueva lista local será ahora la nueva lista creada, que contiene
            //los datos de la lista original en el orden inverso
            L = new_one;
        }
};
