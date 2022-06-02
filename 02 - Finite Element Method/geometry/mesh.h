#include "element.h"

/*
    Enumeraciones utilizadas para proveer de mayor legibilidad al código de
    implementación del Método de los Elementos Finitos.
*/
//Enumeración para identificar los parámetros del problema, los datos proveídos en el archivo de entrada
enum parameter {DENSITY,SPECIFIC_HEAT,THERMAL_CONDUCTIVITY,HEAT_SOURCE,DIRICHLET_VALUE,NEUMANN_VALUE,INITIAL_TEMPERATURE,TIME_STEP,INITIAL_TIME,FINAL_TIME};
//Enumeración para identificar las cantidades utilizadas en el problema, que también son proveídas en el archivo de entrada
enum quantity  {NUM_NODES,NUM_ELEMENTS,NUM_DIRICHLET_BCs,NUM_NEUMANN_BCs};
//Enumeración para identificar el escenario de trabajo con condiciones de contorno
enum condition {DIRICHLET,NEUMANN};

/*
    Clase utilizada para representar una malla bidimensional de triángulos.

    La clase incorpora todos los datos relacionados a la geometría del problema:
    - Parámetros de entrada.
    - Cantidades utilizadas: nodos, elementos, y condiciones de contorno.
    - Nodos y Elementos.
    - Condiciones de Dirichlet.
    - Condiciones de Neumann.

    La clase además provee de los procedimientos básicos para la manipúlación y
    utilización de todos estos aspectos y datos geométricos.

    Adicionalmente, la clase hace uso de la clase utilitaria SDDS
    para la manipulación de estructuras de datos, así como de la clase
    DS para la definición de dichas estructuras.
*/
class Mesh{
    private:
        /*
            Los atributos privados son los siguientes (en orden de declaración
            en el código):
            - Una estructura para definir un arreglo de 10 números reales para
              almacenar todos los parámetros del problema.
            - Una estructura para definir un arreglo de 4 números enteros para
              almacenar todas las cantidades del problema.
            - Una estructura para definir un arreglo para almacenar todos los nodos
              de la malla. Su longitud la definirá una de las cantidades recibidas
              en la entrada.
            - Una estructura para definir un arreglo para almacenar todos los elementos
              de la malla. Su longitud la definirá una de las cantidades recibidas
              en la entrada.
            - Una estructura para definir un arreglo para almacenar todos los nodos
              de la malla que tendrán asignada una condición de contorno de Dirichlet.
              Su longitud la definirá una de las cantidades recibidas en la entrada.
            - Una estructura para definir un arreglo para almacenar todos los nodos
              de la malla que tendrán asignada una condición de contorno de Neumann.
              Su longitud la definirá una de las cantidades recibidas en la entrada.
        */
        DS<float>* parameters;
        DS<int>* quantities;
        DS<FEMNode*>* nodes;
        DS<Element*>* elements;
        DS<FEMNode*>* dirichlet_conditions;
        DS<FEMNode*>* neumann_conditions;

    public:
        /********** Constructor ************/
        /*
            El constructor inicializa únicamente los arreglos para los parámetros
            y las cantidades del problema, ya que son los dos conjuntos de los que se
            conoce previamente su tamaño.
        */
        Mesh(){
            SDDS<float>::create(&parameters,10,ARRAY);
            SDDS<int>::create(&quantities,4,ARRAY);
        }

        /********** Destructor ************/
        /*
            El destructor libera el espacio en memoria asignado para todas las
            estructuras de datos de los atributos privados.
        */
        ~Mesh(){
            SDDS<float>::destroy(parameters);
            SDDS<int>::destroy(quantities);
            SDDS<FEMNode*>::destroy(nodes);
            SDDS<Element*>::destroy(elements);
            SDDS<FEMNode*>::destroy(dirichlet_conditions);
            SDDS<FEMNode*>::destroy(neumann_conditions);
        }

        /********** Operaciones sobre la malla y sus datos ************/
        /*
            Función para inicializar los arreglos de nodos, elementos
            y condiciones, posterior a la inicialización de sus cantidades
            en el constructor.
        */
        void init_geometry(){
            int n;                                                  //Variable auxiliar para el proceso
            SDDS<int>::extract(quantities,NUM_NODES,&n);            //Se extrae la cantidad de nodos
            SDDS<FEMNode*>::create(&nodes,n,ARRAY);                 //Se inicializa el arreglo de nodos
            SDDS<int>::extract(quantities,NUM_ELEMENTS,&n);         //Se extrae la cantidad de elementos
            SDDS<Element*>::create(&elements,n,ARRAY);              //Se inicializa el arreglo de elementos
            SDDS<int>::extract(quantities,NUM_DIRICHLET_BCs,&n);    //Se extrae la cantidad de nodos con condición de Dirichlet
            SDDS<FEMNode*>::create(&dirichlet_conditions,n,ARRAY);  //Se inicializa el arreglo de condiciones de Dirichlet
            SDDS<int>::extract(quantities,NUM_NEUMANN_BCs,&n);      //Se extrae la cantidad de nodos con condición de Neumann
            SDDS<FEMNode*>::create(&neumann_conditions,n,ARRAY);    //Se inicializa el arreglo de condiciones de Neumann
        }

        /*
            Función para colocar en el arreglo de parámetros todos los datos
            del problema recibidos en el archivo de entrada.

            Para indicar las posiciones en el arreglo con alta legibilidad, se
            hace uso de la enumeración <parameter>.
        */
        void set_parameters(float rho, float Cp, float k, float Q, float Td, float Tn, float initial_T, float delta_t, float t_0, float t_f){
            SDDS<float>::insert(parameters,DENSITY,rho);
            SDDS<float>::insert(parameters,SPECIFIC_HEAT,Cp);
            SDDS<float>::insert(parameters,THERMAL_CONDUCTIVITY,k);
            SDDS<float>::insert(parameters,HEAT_SOURCE,Q);
            SDDS<float>::insert(parameters,DIRICHLET_VALUE,Td);
            SDDS<float>::insert(parameters,NEUMANN_VALUE,Tn);
            SDDS<float>::insert(parameters,INITIAL_TEMPERATURE,initial_T);
            SDDS<float>::insert(parameters,TIME_STEP,delta_t);
            SDDS<float>::insert(parameters,INITIAL_TIME,t_0);
            SDDS<float>::insert(parameters,FINAL_TIME,t_f);
        }
        /*
            Función para extraer un parámetro específico del arreglo de
            parámetros.

            La función recibe <indicator> como un dato de enumeración
            <parameter> para indicar con alta legibilidad la posición
            de interés en el arreglo.
        */
        float get_parameter(parameter indicator){
            float param;
            SDDS<float>::extract(parameters,indicator,&param);
            return param;
        }

        /*
            Función para colocar en el arreglo de cantidades todos los datos
            del problema recibidos en el archivo de entrada.

            Para indicar las posiciones en el arreglo con alta legibilidad, se
            hace uso de la enumeración <quantity>.
        */
        void set_quantities(int nnodes, int nelems, int ndirichlet, int nneumann){
            SDDS<int>::insert(quantities,NUM_NODES,nnodes);
            SDDS<int>::insert(quantities,NUM_ELEMENTS,nelems);
            SDDS<int>::insert(quantities,NUM_DIRICHLET_BCs,ndirichlet);
            SDDS<int>::insert(quantities,NUM_NEUMANN_BCs,nneumann);
        }
        /*
            Función para extraer una cantidad específica del arreglo de
            cantidades.

            La función recibe <indicator> como un dato de enumeración
            <quantity> para indicar con alta legibilidad la posición
            de interés en el arreglo.
        */
        int get_quantity(quantity indicator){
            int qty;
            SDDS<int>::extract(quantities,indicator,&qty);
            return qty;
        }

        /*
            Función para ingresar al arreglo de nodos de la malla
            un nuevo nodo en una posición específica.

            <node> es el nodo de malla a ingresar, mientras que <pos>
            es la posición de interés en el arreglo de nodos.
        */
        void add_node(FEMNode* node, int pos){
            SDDS<FEMNode*>::insert(nodes,pos,node);
        }
        /*
            Función que, dado un identificador <ID>, busca en el
            arreglo de nodos de la malla el nodo cuyo ID sea igual
            al dato proveído.
        */
        FEMNode* get_node(int ID){
            int n;
            //Se extrae la longitud del arreglo de nodos de la malla
            SDDS<int>::extract(quantities,NUM_NODES,&n);
            //Se recorre el arreglo de nodos de la malla
            for(int i = 0; i < n; i++){
                FEMNode* node;
                //Se extrae el nodo actual
                SDDS<FEMNode*>::extract(nodes,i,&node);
                //Si el nodo actual tiene un ID igual al recibido, se retorna
                if(node->get_ID() == ID) return node;
            }
            //Si no se encontró, se retorna un puntero nulo
            return NULL;
        }

        /*
            Función para ingresar al arreglo de elementos de la malla
            un nuevo elemento en una posición específica.

            <elem> es el elemento a ingresar, mientras que <pos>
            es la posición de interés en el arreglo de elementos.
        */
        void add_element(Element* elem, int pos){
            SDDS<Element*>::insert(elements,pos,elem);
        }
        /*
            Función que, dado un identificador <ID>, busca en el
            arreglo de elementos el elemento cuyo ID sea igual
            al dato proveído.
        */
        Element* get_element(int ID){
            int n;
            //Se extrae la longitud del arreglo de elementos
            SDDS<int>::extract(quantities,NUM_ELEMENTS,&n);
            //Se recorre el arreglo de elementos
            for(int i = 0; i < n; i++){
                Element* elem;
                //Se extrae el elemento actual
                SDDS<Element*>::extract(elements,i,&elem);
                //Si el elemento actual tiene un ID igual al recibido, se retorna
                if(elem->get_ID() == ID) return elem;
            }
            //Si no se encontró, se retorna un puntero nulo
            return NULL;
        }

        /*
            Función para ingresar al arreglo de condiciones de Dirichlet
            un nuevo nodo en una posición específica.

            <node> es el nodo a ingresar, mientras que <i>
            es la posición de interés en el arreglo de condiciones de
            Dirichlet.
        */
        void add_dirichlet_cond(FEMNode* node,int i){
            SDDS<FEMNode*>::insert(dirichlet_conditions,i,node);
        }

        /*
            Función para ingresar al arreglo de condiciones de Neumann
            un nuevo nodo en una posición específica.

            <node> es el nodo a ingresar, mientras que <i>
            es la posición de interés en el arreglo de condiciones de
            Neumann.
        */
        void add_neumann_cond(FEMNode* node,int i){
            SDDS<FEMNode*>::insert(neumann_conditions,i,node);
        }

        /*
            Función que recibe un arreglo de enteros para llenarlos
            con los identificadores de todos los nodos que tienen
            asignada un tipo de condición de contorno.

            <indices> es el arreglo a llenar, mientras que <mode> es
            un dato de enumeración <condition> que indica el tipo de
            condición de contorno de interés.
        */
        void get_condition_indices(DS<int>* indices, condition mode){
            int n;
            DS<FEMNode*>* conditions;

            /*
                Se determina el tipo de condición de contorno solicitado.

                En caso se realiza lo siguiente:
                - Se obtiene la longitud del arreglo correspondiente al tipo
                  de condición de contorno indicado.
                - Se define como arreglo a utilizar el correspondiente al
                  tipo de condición de contorno indicado.
            */
            switch(mode){
                case DIRICHLET: {
                    SDDS<int>::extract(quantities,NUM_DIRICHLET_BCs,&n);
                    conditions = dirichlet_conditions;
                    break;
                }
                case NEUMANN: {
                    SDDS<int>::extract(quantities,NUM_NEUMANN_BCs,&n);
                    conditions = neumann_conditions;
                    break;
                }
            }

            FEMNode* node;
            //Se recorre el arreglo correspondiente al tipo de condición de contorno indicado
            for(int i = 0; i < n; i++){
                //Se extrae el nodo actual
                SDDS<FEMNode*>::extract(conditions,i,&node);
                //Se coloca el ID del nodo actual en el arreglo de enteros
                SDDS<int>::insert(indices,i,node->get_ID());
            }
        }
};