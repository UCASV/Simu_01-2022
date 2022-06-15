#include "point.h"

/*
    Clase que se utiliza para representar un nodo en una malla
    para la discretización de algún dominio, con el objetivo de
    someterla a un proceso de Elementos Finitos.

    La clase hace uso de la clase Point para indicar las coordenadas
    espaciales del nodo en cuestión.
*/
class FEMNode{
    private:
        /*
            Los atributos privados son:
            - Un identificador del nodo, dato único en toda la malla.
            - Un Punto que define al nodo en el espacio bidimensional.
        */
        int ID;
        Point* P;

    public:
        /********** Constructores ************/
        /*
            Se proveen dos constructores:
            - Uno genérico que no inicializa los atributos.
            - Uno que recibe datos para inicializar los atributos.
        */
        FEMNode(){}
        FEMNode(int identifier, Point* punto){
            ID = identifier;
            P = punto;
        }

        /********** Destructor ************/
        /*
            El destructor se encarga de liberar la memoria
            asignada para el Punto privado.
        */
        ~FEMNode(){
            delete P;
        }

        /********* Setters y Getters para los atributos *************/
        void set_ID(int identifier){
            ID = identifier;
        }
        void set_Point(Point* punto){
            P = punto;
        }
        int get_ID(){
            return ID;
        }
        Point* get_Point(){
            return P;
        }
};