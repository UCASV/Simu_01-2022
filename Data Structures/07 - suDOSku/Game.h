#include "headers/staticDS.h"

enum opmain  {QUIT, TAB1, TAB2};
enum opboard {RAGEQUIT, INSERT, ERASE};
enum mode    {MAIN, BOARD, CELLI, CELLE};

class Game{
    private:
        static int cont, Q, I, J, V;
        static Array<char>* board;

        /* Operaciones para los menús */

        static void showMainMenu(){
            cout << "MENÚ PRINCIPAL\n"
                     "===============\n"
                     "1. Jugar Tablero # 1.\n"
                     "2. Jugar Tablero # 2.\n"
                     "0. Salir.\n";
        }
        static void showBoardMenu(){
            cout << "Operaciones del tablero\n"
                     "=======================\n"
                     "1. Colocar dato.\n"
                     "2. Borrar dato.\n"
                     "0. ragequit REEEEEEEEEEEEE!.\n";
        }
        static void boardMenu(){
            do{
                if(cont == 81){ cout << "YEAH! YOU WIN!!!!\n"; break; }
                showBoardMenu();
                getUserInput(BOARD,"Ingrese el número de la operación que desea realizar: ");
            }while( processUserInput(BOARD) );
        }

        /* Operaciones del tablero */

        static void readBoard(string filename){
            char c;
            ifstream file(filename);
            //Se puede verificar si el archivo se pudo abrir exitosamente
            for(int i = 0; i < 9*9; i++){
                file >> c;
                Arrays<char>::insert(board,i/9,i%9,c);
            }
            file.close();
        }
        static void showBoard(){
            cout << "CURRENT BOARD:\n"
                    "===============\n";
            Arrays<char>::show(board,false);
        }
        static void processBoard(string filename){
            readBoard(filename);
            cont = 38;
            showBoard();
            boardMenu();
        }

        /* Operaciones para el ingreso de datos */

        static bool vRange(int n, int i, int s){
            return n >= i && n <= s;
        }
        static bool validateInput(mode m){
            switch(m){
                case MAIN:  return Q >= QUIT && Q <= TAB2;
                case BOARD: return Q >= RAGEQUIT && Q <= ERASE;
                default:
                    return vRange(Q,1,9) && vRange(I,1,3) && vRange(J,1,3) && ( (m==CELLI)?vRange(V,1,9):true );
            }
        }
        static void getUserInput(mode m, string msg){
            do{
                cout << msg;
                cin >> Q;
                if(m == CELLI || m == CELLE) cin >> I >> J;
                if(m == CELLI) cin >> V;
                cin.ignore(INT_MAX,'\n');
                if(validateInput(m)) break;
                cout << "\nDato(s) incorrecto(s)! :(\n\n";
            }while(true);
        }
        static bool processUserInput(mode m){
            switch(m){
                case MAIN:
                    switch(Q){
                        case TAB1: processBoard("boards/board1.txt"); return true;
                        case TAB2: processBoard("boards/board2.txt"); return true;
                        case QUIT: return false;
                    }
                case BOARD:
                    switch(Q){
                        case INSERT:   insertValue(); return true;
                        case ERASE:    eraseValue(); return true;
                        case RAGEQUIT: cout << "\ngit gud :^)\n\n"; return false;
                    }
            }
        }

        /* Operaciones del juego */
        static void insertValue(){
            getUserInput(CELLI,"Ingrese la celda en la que desea ingresar dato y el dato a ingresar en el formato \"Q I J V\": ");
            int i = (I-1)+3*((Q-1)/3);
            int j = (J-1)+3*((Q-1)%3);
            char c = char(48+V);
            if(validateBoard( i,j,c )){
                Arrays<char>::insert(board, i, j, c);
                cont++;
            }else cout << "\nEl dato no puede ubicarse en la celda indicada sin romper las reglas. :(\n\n";
            showBoard();            
        }
        static void eraseValue(){
            getUserInput(CELLE,"Ingrese la celda en la que desea borrar dato en el formato \"Q I J\": ");
            int i = (I-1)+3*((Q-1)/3);
            int j = (J-1)+3*((Q-1)%3);
            //TODO: validar que la celda a borrar contiene número
            Arrays<char>::insert(board, i, j, '_');
            cont--;
            showBoard();
        }
        static bool validateBoard(int i, int j, char c){
            bool ans = true;
            for(int k = 0; k < 9; k++){
                char cf, cc;
                Arrays<char>::extract(board,i,k,&cf);
                Arrays<char>::extract(board,k,j,&cc);
                if( cf == c || cc == c){
                    ans = false;
                    break;
                }
            }
            for(int k = 0; k < 9; k++){
                char ca;
                Arrays<char>::extract(board, k/3+3*((Q-1)/3) , k%3+3*((Q-1)%3) ,&ca);
                if( !(k == I) && !(k == J) && ca == c ){
                    ans = false;
                    break;
                }
            }
            return ans;
        }
    
    public:
        /* Operaciones a ejecutar desde el main */
        
        static void createBoard(){
            Arrays<char>::create(&board,9,9);
        }

        static void cleanup(){
            Arrays<char>::destroy(board);
        }

        static void mainMenu(){
            do{
                showMainMenu();
                getUserInput(MAIN,"Ingrese el número de la opción a la que desea acceder: ");
            }while( processUserInput(MAIN) );
        }
};
