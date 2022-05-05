/*************************************************************************/
/*                             **suDOSku**                               */
/*                                                                       */
/*  Este programa permite al usuario jugar el juego de Sudoku a nivel    */
/*  de consola mediante el uso de menús e ingreso de opciones y valores  */
/*  mediante el uso del teclado.                                         */
/*************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

#include "Game.h"

/*
    C++ requiere, para los atributos estáticos, que se
    realice, antes del proceso, una asignación para que
    se genere el espacio de memoria correspondiente.

    La sintaxis de esta asignación es:

            <tipo> <Clase>::<atributo> = <valor_nulo>;
*/

/*
    La clase Arrays se ha definido exclusivamente con
    métodos y atributos estáticos, ya que se ha concebido
    como una clase utilitaria.

    En este escenario, ref es de tipo Data, que es una struct,
    y es un atributo estático de la clase Arrays, por lo que
    comenzamos por asignarle un struct vacío mediante el uso
    de un constructor genérico.

    Por último, dado que Arrays es un template, es necesario
    realizar esta instanciación establecienco el "meta-parámetro";
    sin embargo, ya que el proceso no ha comenzado aún no está
    definido el tipo de dato concreto a utilizar, por lo que
    se "acarrea" el template.
*/
template <typename type>
Data Arrays<type>::ref = Data();

/*
    La clase Game se ha definido exclusivamente con
    métodos y atributos estáticos, ya que se ha concebido
    como una clase utilitaria.

    En este escenario, las variables cont, Q, I, J y V, todas
    de tipo int, son atributos estáticos de la clase Game, por
    lo que comenzamos por asignarles un valor 0.

    Adicionalmente, la variable board, que es de tipo Array* de
    tipo char, también es un atributo estático de la clase Game,
    por lo que comenzamos por asignarle un valor NULL.
*/
int Game::cont = 0, Game::Q = 0, Game::I = 0, Game::J = 0, Game::V = 0;
Array<char>* Game::board = NULL;

int main(void){
    //Se comienza por inicializar el tablero del juego
    Game::createBoard();
    
    //Se invoca el menú principal y se inicia la ejecución
    //del programa
    Game::mainMenu();
    
    //Al terminar el programa se le agradece al usuario por
    //su preferencia
    cout << "Thanks for playing! :D\n";

    //Se libera toda la memoria utilizada
    Game::cleanup();
    
    return 0;
}
