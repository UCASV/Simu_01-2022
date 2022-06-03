#include "mesh_node.h"

/*
    Clase utilizada para representar un elemento triangular
    lineal en una malla destinada a ser sometida a un proceso
    de Elementos Finitos.

    La clase hace uso de la clase FEMNode para representar los
    nodos del elemento en cuestión.

    Adicionalmente, la clase hace uso de la clase utilitaria SDDS
    para la manipulación de estructuras de datos, así como también de la clase
    DS para la definición de dichas estructuras.
*/
class Element{
    private:
        /*
            Los atributos privados son:
            - Un identificador del elemento, único en toda la malla.
            - Un puntero a estructura de datos para almacenar punteros
              a nodos de malla. Esta estructura será definida como un
              arreglo de longitud 3, al tratarse de un elemento triangular
              lineal.
        */
        int ID;
        DS<FEMNode*>* nodes;

    public:
        /********** Constructores ************/
        /*
            Constructor genérico que inicializa el
            arreglo privado que almacenará los nodos.
        */
        Element(){
            SDDS<FEMNode*>::create(&nodes,3,ARRAY);
        }
        /*
            Constructor que recibe un identificador y tres
            punteros a nodo de malla, para inicializar el ID
            y construir e inicializar el arreglo privado.
        */
        Element(int identifier, FEMNode* node1, FEMNode* node2, FEMNode* node3){
            ID = identifier;
            //Se crea el arreglo de longitud 3
            SDDS<FEMNode*>::create(&nodes,3,ARRAY);
            //Se colocan en el arreglo los 3 punteros a nodo de malla proporcionados
            SDDS<FEMNode*>::insert(nodes,0,node1);
            SDDS<FEMNode*>::insert(nodes,1,node2);
            SDDS<FEMNode*>::insert(nodes,2,node3);
        }

        /********** Destructor ************/
        /*
            El destructor se encarga de liberar la memoria
            asignada para el arreglo privado.
        */
        ~Element(){
            SDDS<FEMNode*>::destroy(nodes);
        }

        /********* Setters y Getters para los atributos *************/
        void set_ID(int identifier){
            ID = identifier;
        }
        int get_ID(){
            return ID;
        }

        /*
            Para el arreglo, no se permite un set/get para toda
            la estructura, solamente para una posición en particular,
            la cual viene indicada en el parámetro <index>.

            Es decir, se hace lo siguiente:
            - Set: Dada una posición, y puntero a nodo de malla, se coloca
              el puntero en la posición indicada del arreglo privado.
            - Get: Dada una posición, se retorna el puntero a nodo de malla
              que se encuentra en la posición indicada del arreglo privado.
        */
        void set_Node(FEMNode* node,int index){
            SDDS<FEMNode*>::insert(nodes,index,node);
        }
        FEMNode* get_Node(int index){
            FEMNode* res;
            SDDS<FEMNode*>::extract(nodes,index,&res);
            return res;
        }
};