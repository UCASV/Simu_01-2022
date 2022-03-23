#include <iostream>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

#include "Game.h"

template <typename type>
Data Arrays<type>::ref = Data();

int Game::cont = 0, Game::Q = 0, Game::I = 0, Game::J = 0, Game::V = 0;
Array<char>* Game::board = NULL;

int main(void){
    Game::createBoard();
    
    Game::mainMenu();
    
    cout << "Thanks for playing! :D\n";
    Game::cleanup();
    
    return 0;
}
