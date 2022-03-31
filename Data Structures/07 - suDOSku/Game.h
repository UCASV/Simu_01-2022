#include "headers/staticDS.h"

/* Enumeraciones utilizadas para generar legibilidad en los procesos del juego */
/*
Enumeración utilizada para las opciones del menú principal:
    - TAB1 corresponde a jugar con el Tablero #1.
    - TAB2 corresponde a jugar con el Tablero #2.
    - QUIT siginifica terminar el programa.                                    
*/
enum opmain  {QUIT, TAB1, TAB2};
/*
Enumeración utilizada para las opciones del menú del tablero:
    - INSERT corresponde a colocar un dato en el tablero.
    - ERASE corresponde a remover un dato del tablero.
    - RAGEQUIT significa dejar de jugar.                                       
*/
enum opboard {RAGEQUIT, INSERT, ERASE};
/*
Enumeración utilizada para los modos en los que se solicitan datos al jugador:
    - MAIN corresponde al menú principal.
    - BOARD corresponde al menú de opciones del tablero de juego.
    - CELLI corresponde a la inserción de un dato en el tablero.
    - CELLE corresponde a la remoción de un dato del tablero.                   
*/
enum mode    {MAIN, BOARD, CELLI, CELLE};

/*
    Clase utilitaria que administra toda la lógica del juego de Sudoku a nivel
    de consola.
*/
class Game{
    private:
        //Variables auxiliares a utilizar en la lógica del juego y larecepción
        //de datos
        static int cont, Q, I, J, V;
        //Objeto array que almacenará el tablero, manejado como una matriz de
        //caracteres
        static Array<char>* board;

        /*=========== Operaciones para los menús del juego ==================*/
        /*
            Función que muestra en pantalla el menú principal del juego.

            De momento el juego permite dos tableros diferentes de dificultad
            Easy.
        */
        static void showMainMenu(){
            cout << "MENÚ PRINCIPAL\n"
                     "===============\n"
                     "1. Jugar Tablero # 1.\n"
                     "2. Jugar Tablero # 2.\n"
                     "0. Salir.\n";
        }

        /*
            Función que muestra en pantalla el menú de opciones para el tablero
            de juego.
        */
        static void showBoardMenu(){
            cout << "Operaciones del tablero\n"
                     "=======================\n"
                     "1. Colocar dato.\n"
                     "2. Borrar dato.\n"
                     "0. ragequit REEEEEEEEEEEEE!.\n";
        }

        /*
            Función que administra el menú de opciones para el tablero del juego.
        */
        static void boardMenu(){
            //El menú debe mostrarse al menos una vez
            do{
                /*
                    Si la cantidad de datos colocados en el tablero es igual a 81,
                    uno por cada celda del tablero, significa que el jugador ha
                    completado el juego exitosamente.

                    Esto funciona debido a que no se permite la inserción de un dato
                    a menos que se garantice que no rompe las reglas del juego.
                */
                if(cont == 81){ cout << "YEAH! YOU WIN!!!!\n"; break; }

                //Se muestra el menú de opciones del tablero
                showBoardMenu();

                //Se solicita información al usuario estableciendo BOARD como el modo
                //de recepción de datos
                getUserInput(BOARD,"Ingrese el número de la operación que desea realizar: ");

            //La continuación del bucle depende de la opción solicitada por el jugador
            //y el resultado de su respectiva ejecución.
            //Se establece BOARD como el modo de procesamiento de datos.
            }while( processUserInput(BOARD) );
        }

        /*============ Operaciones para la administración del tablero ===================*/
        /*
            Función que recibe <filename> como la ruta de un archivo de texto
            que contiene un tablero de juego de Sudoku de dificultad Easy.

            La función abre el archivo, y obtiene todo el contenido del tablero
            para colocarlo en la matriz de caracteres local.
        */
        static void readBoard(string filename){
            //Variable auxiliar para la lectura de datos
            char c;

            //Se abre el archivo para lectura
            ifstream file(filename);

            //Se puede añadir acá una verificación de que el archivo se haya abierto
            //exitosamente

            /*
                Vamos a leer un dato por cada celda del tablero, el cual es 9x9,
                para un total de 81 datos.

                Cada uno de estos datos puede ser:
                    - Un dígito pero en caracter: '0', '1', ...
                    - Un '_' para representar una celda vacía.
            */
            for(int i = 0; i < 9*9; i++){
                //Se lee un dato
                file >> c;
                //Insertamos el dato en el tablero en la celda correspondiente.
                /*Se utilizan las fórmular de recorrido con un iterador para una
                matriz:
                        fila    = i \ 9
                        columna = i % 9                                          */
                Arrays<char>::insert(board,i/9,i%9,c);
            }
            //Se cierra el archivo
            file.close();
        }

        /*
            Función que muestra el tablero del juego actual.
        */
        static void showBoard(){
            cout << "CURRENT BOARD:\n"
                    "===============\n";
            /*Se utiliza el método show() de la clase utilitaria enviando el
              objeto board.
              El modo VERBOSE no es necesario, solo necesitamos la matriz como tal.*/
            Arrays<char>::show(board,false);
        }

        /*
            Función que prepara el tablero solicitado por el usuario para poder comenzar
            a jugar.

            Se recibe <filename> como la ruta del archivo de texto que contiene el tablero
            en dificultad Easy que el jugador ha expresado que quiere jugar.
        */
        static void processBoard(string filename){
            //Se lee el contenido del tablero
            readBoard(filename);
            /*
            cont se utiliza para controlar el total de datos colocados en el tablero, cuando
            cont llegue a 81 se entenderá que el jugador ha ganado.

            Se comienza el conteo en 38 ya que, por lo general, un tablero de sudoku en
            dificultad Easy inicia con 38 datos colocados.
            */
            cont = 38;

            //Se muestra el tablero
            showBoard();
            //Se muestra el menú de opciones del tablero y se comienza a jugar
            boardMenu();
        }

        /*============== Operaciones para el ingreso de datos ===========================*/
        /*
            Función que determina si un dato <n> se encuentre en el intervalo cerrado
            [ <i>, <s> ].

            La función retorna true si efectivamente el dato es parte del intervalo, y
            false en caso contrario.
        */
        static bool vRange(int n, int i, int s){
            return n >= i && n <= s;
        }

        /*
            Función que verifica que los datos ingresados por el jugador sean correctos
            dependiendo del contexto en que fueron solicitados.

            Se recibe <m> como el modo de recepción de datos, para poder determinar
            cuáles son las validaciones necesarias.
        */
        static bool validateInput(mode m){
            //Se verifica el modo en el que fueron solicitados los datos
            switch(m){

                /*Si se trata de opciones del menú principal se verifica que la opción
                  ingresada esté dentro de las opciones válidas, para esto se hace uso
                  de la enumeración opmain.                                           */
                case MAIN:  return Q >= QUIT && Q <= TAB2;

                /*Si se trata de opciones del menú de uso del tablero se verifica que la
                  opción ingresada esté dentro de las opciones válidas, para esto se hace
                  uso de la enumeración opboard.                                          */
                case BOARD: return Q >= RAGEQUIT && Q <= ERASE;

                /*La validación por defecto corresponde al ingreso de datos para la
                  manipulación de una celda:
                    - Se verifica que Q sea una de las 9 zonas de 3x3 celdas del tablero.
                    - Se verifica que (I,J) sea una celda válida de la zona indicada, es decir,
                      que cada uno de los índices sea un dato entre 1 y 3.
                    - En el caso de ingreso de datos, es necesario también que el valor V
                      a ingresar sea uno de los datos permitidos: un dígito del 1 al 9.        */
                default:
                    return vRange(Q,1,9) && vRange(I,1,3) && vRange(J,1,3) && ( (m == CELLI) ? vRange(V,1,9) : true );
            }
        }

        /*
            Función para solicitar datos al usuario.

            Se recibe <m> como el modo en el que deben solicitarse datos,
            esto define cuáles son los datos requeridos.

            Se recibe <msg> como el mensaje a mostrar para que el usuario
            comprenda cuáles son los datos a ingresar.
        */
        static void getUserInput(mode m, string msg){
            //Se deben solicitar los datos al menos una vez
            do{
                //Se muestra el mensaje para comunicarle al usuario lo que
                //debe ingresar
                cout << msg;

                /*Siempre se necesita al menos un dato, el cual se almacena
                  en Q:
                    - Cuando estemos en modo MAIN, Q almacenará la opción del
                      menú principal solicitada.
                    - Cuando estemos en modo BOARD, Q almacenará la opción del
                      menú de opciones del tablero solicitada.
                    - Cuando estemos en modo CELLI o modo CELLE, Q almacenará
                      la zona 3x3 del tablero en la que el usuario quiere colocar
                      o remover un dato.                                          */
                cin >> Q;

                /*Cuando estemos en modo CELLI o en modo CELLE, será necesario
                  también obtener los índices (I,J) de la celda local a la zona
                  Q establecida en la que el jugador quiere colocar o remover un
                  dato.                                                          */
                if(m == CELLI || m == CELLE) cin >> I >> J;

                /*Únicamente cuando estemos en modo CELLI, será necesario además
                  solicitar el valor V que el jugador quiere colocar en la celda
                  (I,J) informada de la zona Q establecida.                      */
                if(m == CELLI) cin >> V;

                /*Luego de obtener los datos limpiamos el buffer de entrada para
                  evitar datos "ruido" en la próxima obtención de datos.

                  Se hace uso de cin.ignore(), quien recibe dos parámteros:
                    - Un entero que establece la cantidad máxima de elementos a
                      remover del buffer de entrada.
                      Para el caso se envía INT_MAX, el entero más grande que el
                      lenguaje C puede manejar, para garantizar que no dejemos nada.
                    - Un caracter que establece un punto de finalización para el
                      proceso.
                      Para el caso se envía el ENTER para detener la limpieza al
                      encontrarlo, esto debido a que un ingreso de datos desde
                      teclado termina siempre con un ENTER.                         */
                cin.ignore(INT_MAX,'\n');

                //Se validan los datos recibidos, y si están bien ya no es necesario
                //seguir pidiendo datos
                if(validateInput(m)) break;

                //Si los datos no son válidos, se informa el hecho y se repite el
                //proceso de petición
                cout << "\nDato(s) incorrecto(s)! :(\n\n";
            }while(true);
        }

        /*
            Función que procesa opciones de menú ingresadas por el jugador, para
            poder ejecutar las operaciones correspondientes.

            La función retorna true siempre que una operación del juego se haya
            concluído exitosamente.

            La función retorna false en los casos que el usuario ha solicitado
            abandonar el proceso actual.

            Se recibe <m> como el modo en el que los datos a procesar fueron
            ingresados, para poder determinar las operaciones a ejecutar.
        */
        static bool processUserInput(mode m){
            //Se verifica el modo en el que los datos a procesar fueron ingresados
            switch(m){

                case MAIN:
                    //Si se trata del menú principal, Q contiene la opción solicitada
                    switch(Q){
                        //El jugador pidió jugar con el Tablero #1, por lo que se
                        //procede a cargar y jugar con dicho tablero
                        case TAB1: processBoard("boards/board1.txt"); return true;

                        //El jugador pidió jugar con el Tablero #2, por lo que se
                        //procede a cargar y jugar con dicho tablero
                        case TAB2: processBoard("boards/board2.txt"); return true;

                        //El jugador desea abandonar el programa
                        case QUIT: return false;
                    }
                case BOARD:
                    //Si se trata del menú de opciones del tablero, Q contiene la
                    //opción solicitada
                    switch(Q){
                        //El jugador pidió colocar un dato en el tablero
                        case INSERT:   insertValue(); return true;

                        //El jugador pidió remover un dato del tablero
                        case ERASE:    eraseValue(); return true;

                        //El jugador desea dejar de jugar
                        case RAGEQUIT: cout << "\ngit gud :^)\n\n"; return false;
                    }
            }
        }

        /*============================ Operaciones del juego ==============================*/
        /*
            Función que ejecuta el proceso para colocar un dato en el tablero de juego.
        */
        static void insertValue(){
            //Se solicitan al jugador datos en modo CELLI con su mensaje correspondiente
            getUserInput(CELLI,"Ingrese la celda en la que desea ingresar dato y el dato a ingresar en el formato \"Q I J V\": ");

            /*
                Dado que el jugador ingresa datos que son locales a una de las zonas 3x3 del tablero, y que además ingresa datos contando a partir de 1, es
                necesario operar la información ingresada para obtener los índices (i,j) reales de la matriz de caracteres del tablero que corresponden a la
                celda en la que el jugador desea colocar un dato.

                Para obtener (i,j) a partir de (Q,I,J) se realiza el análisis siguiente:

                                                                                                           Esquema de zonas como lo entiende el jugador

                                                                                                                        [ 1 ][ 2 ][ 3 ]
                                                                                                                        [ 4 ][ 5 ][ 6 ]
                                                                                                                        [ 7 ][ 8 ][ 9 ]

                                Matriz de caracteres interna                                                Tablero como lo entiende el jugador                

                     0      1      2       3      4      5       6      7      8                1      2      3       1      2      3       1      2      3
                0 [ 0,0 ][ 0,1 ][ 0,2 ] [ 0,3 ][ 0,4 ][ 0,5 ] [ 0,6 ][ 0,7 ][ 0,8 ]        1 [ 1,1 ][ 1,2 ][ 1,3 ] [ 1,1 ][ 1,2 ][ 1,3 ] [ 1,1 ][ 1,2 ][ 1,3 ]
                1 [ 1,0 ][ 1,1 ][ 1,2 ] [ 1,3 ][ 1,4 ][ 1,5 ] [ 1,6 ][ 1,7 ][ 1,8 ]        2 [ 2,1 ][ 2,2 ][ 2,3 ] [ 2,1 ][ 2,2 ][ 2,3 ] [ 2,1 ][ 2,2 ][ 2,3 ]
                2 [ 2,0 ][ 2,1 ][ 2,2 ] [ 2,3 ][ 2,4 ][ 2,5 ] [ 2,6 ][ 2,7 ][ 2,8 ]        3 [ 3,1 ][ 3,2 ][ 3,3 ] [ 3,1 ][ 3,2 ][ 3,3 ] [ 3,1 ][ 3,2 ][ 3,3 ]

                3 [ 3,0 ][ 3,1 ][ 3,2 ] [ 3,3 ][ 3,4 ][ 3,5 ] [ 3,6 ][ 3,7 ][ 3,8 ]        1 [ 1,1 ][ 1,2 ][ 1,3 ] [ 1,1 ][ 1,2 ][ 1,3 ] [ 1,1 ][ 1,2 ][ 1,3 ]
                4 [ 4,0 ][ 4,1 ][ 4,2 ] [ 4,3 ][ 4,4 ][ 4,5 ] [ 4,6 ][ 4,7 ][ 4,8 ]  <==>  2 [ 2,1 ][ 2,2 ][ 2,3 ] [ 2,1 ][ 2,2 ][ 2,3 ] [ 2,1 ][ 2,2 ][ 2,3 ]
                5 [ 5,0 ][ 5,1 ][ 5,2 ] [ 5,3 ][ 5,4 ][ 5,5 ] [ 5,6 ][ 5,7 ][ 5,8 ]        3 [ 3,1 ][ 3,2 ][ 3,3 ] [ 3,1 ][ 3,2 ][ 3,3 ] [ 3,1 ][ 3,2 ][ 3,3 ]

                6 [ 6,0 ][ 6,1 ][ 6,2 ] [ 6,3 ][ 6,4 ][ 6,5 ] [ 6,6 ][ 6,7 ][ 6,8 ]        1 [ 1,1 ][ 1,2 ][ 1,3 ] [ 1,1 ][ 1,2 ][ 1,3 ] [ 1,1 ][ 1,2 ][ 1,3 ]
                7 [ 7,0 ][ 7,1 ][ 7,2 ] [ 7,3 ][ 7,4 ][ 7,5 ] [ 7,6 ][ 7,7 ][ 7,8 ]        2 [ 2,1 ][ 2,2 ][ 2,3 ] [ 2,1 ][ 2,2 ][ 2,3 ] [ 2,1 ][ 2,2 ][ 2,3 ]
                8 [ 8,0 ][ 8,1 ][ 8,2 ] [ 8,3 ][ 8,4 ][ 8,5 ] [ 8,6 ][ 8,7 ][ 8,8 ]        3 [ 3,1 ][ 3,2 ][ 3,3 ] [ 3,1 ][ 3,2 ][ 3,3 ] [ 3,1 ][ 3,2 ][ 3,3 ]


                Veamos las celdas (0,0), (3,0) y (6,0) de la matriz de caracteres, éstas corresponden con los datos (1,1,1), (4,1,1) y (7,1,1) que el usuario
                utilizaría para describirlas, lo que significa que:
                    - En la zona 1, (1,1) debe transformarse en (0,0).
                    - En la zona 4, (1,1) debe transformarse en (3,0).
                    - En la zona 7, (1,1) debe transformarse en (6,0).
                
                Pensando por el momento solamente en el índice i de las filas:
                    - En la zona 1, 1 debe transformarse en 0.
                    - En la zona 4, 1 debe transformarse en 3.
                    - En la zona 7, 1 debe transformarse en 6.

                Reformulando aprovechando la existencia de factores de 3 en los valores que deseamos obtener:
                    - En la zona 1, 1 debe transformarse en 0.
                    - En la zona 4, 1 debe transformarse en 3.
                    - En la zona 7, 1 debe transformarse en 3*2.

                Replicando la forma 3*n en los otros casos:
                    - En la zona 1, 1 debe transformarse en 3*0.
                    - En la zona 4, 1 debe transformarse en 3*1.
                    - En la zona 7, 1 debe transformarse en 3*2.

                Tres observaciones importantes, llamando Q al número de zona:
                    a. El valor Q, utilizado para las zonas, sigue un comportamiento idéntico al índice k para el recorrido de matrices con un iterador (tal y como
                       está descrito en "headers/Array2D.h").
                    b. El índice k en dicho proceso, para generar una secuencia 0,1,2 a lo largo de las filas se le aplicó división entera entre 3, lo que sugiere que
                       dicha fórmula puede aplicarse también a Q.
                    c. k trabaja contando desde 0, mientras que Q comienza desde 1, así que si se desean aplicar fórmulas de k se deberá primero restarle 1 a Q, para
                       ponerlos al mismo nivel.

                Tomando en cuenta lo anterior, podemos reexpresar nuestro análisis de la siguiente forma:
                    - En la zona 1, 1 debe transformarse en 3*( (1-1)\3 ), siendo Q = 1.
                    - En la zona 4, 1 debe transformarse en 3*( (4-1)\3 ), siendo Q = 4.
                    - En la zona 7, 1 debe transformarse en 3*( (7-1)\3 ), siendo Q = 7.

                Se puede verificar rápidamente que esto cumple para el resto de zonas:
                    - En la zona 2, 1 debe transformarse en 3*( (2-1)\3 ).
                    - En la zona 5, 1 debe transformarse en 3*( (5-1)\3 ).
                    - En la zona 8, 1 debe transformarse en 3*( (8-1)\3 ).
                    - En la zona 3, 1 debe transformarse en 3*( (3-1)\3 ).
                    - En la zona 6, 1 debe transformarse en 3*( (6-1)\3 ).
                    - En la zona 9, 1 debe transformarse en 3*( (9-1)\3 ).                

                Generalizando:   "En la zona Q, 1 debe transformarse en 3*( (Q-1)\3 )"

                Ahora bien, lo anterior solo incluye la primera fila de cada zona, veamos brevemente lo que debe ocurrir en las otras filas:
                    Segunda fila:
                    - En la zona 1, (2,1) debe transformarse en (1,0).
                    - En la zona 4, (2,1) debe transformarse en (4,0).
                    - En la zona 7, (2,1) debe transformarse en (7,0).
                    Tercera fila:
                    - En la zona 1, (3,1) debe transformarse en (2,0).
                    - En la zona 4, (3,1) debe transformarse en (5,0).
                    - En la zona 7, (3,1) debe transformarse en (8,0).

                Quedándonos solo con el índice i, podemos reformular rápidamente de la siguiente manera:
                    - En la zona 1, 2 debe transformarse en 0+1.
                    - En la zona 4, 2 debe transformarse en 3+1.
                    - En la zona 7, 2 debe transformarse en 6+1.
                    - En la zona 1, 3 debe transformarse en 0+2.
                    - En la zona 4, 3 debe transformarse en 3+2.
                    - En la zona 7, 3 debe transformarse en 6+2.

                Observamos que aparece el patrón 0,3,6 que ya resolvimos para la primera fila, por lo que podemos concluir y resumir:
                    - En la zona Q, 1 debe transformarse en 3*( (Q-1)\3 ).
                    - En la zona Q, 2 debe transformarse en 3*( (Q-1)\3 ) + 1.
                    - En la zona Q, 3 debe transformarse en 3*( (Q-1)\3 ) + 2.

                Provocando el patrón +n en la primera afirmación:
                    - En la zona Q, 1 debe transformarse en 3*( (Q-1)\3 ) + 0.
                    - En la zona Q, 2 debe transformarse en 3*( (Q-1)\3 ) + 1.
                    - En la zona Q, 3 debe transformarse en 3*( (Q-1)\3 ) + 2.
                
                Finalmente, observamos que el dato que se suma es el mismo índice I del que partimos restándole 1, llegando entonces a la fórmula final:

                                                    I debe transformarse en 3*( (Q-1)\3 ) + (I-1)

                                                            i = (I-1) + 3*( (Q-1)\3 )

                Luego, si se hace el análisis complementario para j, el patrón procedimental a seguir será el mismo (se invita al lector a realizarlo
                personalmente), de modo que obtendremos como contraparte:

                                                            j = (J-1) + 3*( (Q-1)% 3 )
            */
            //Se calculan entonces los índices (i,j) para la matriz a partir de los datos ingresados por el jugador
            int i = (I-1)+3*((Q-1)/3);
            int j = (J-1)+3*((Q-1)%3);

            /*
                El tablero se maneja como una matriz de caracteres, por lo que contendrá los dígitos 1-9 como
                caracteres.

                Los códigos ASCII para los dígitos como caracteres son:

                                                    Dígito          ASCII
                                                    1              49
                                                    2              50
                                                    3              51
                                                    4              52
                                                    5              53
                                                    6              54
                                                    7              55
                                                    8              56
                                                    9              57

                Puede verse rápidamente que para obtener el código ASCII a partir del dígito ingresado, basta con
                hacer la operación:

                                                ASCII = 48 + Dígito
            */
            //Se obtiene el dígito a colocar en el tablero como caracter utilizando la fórmula anterior
            char c = char(48+V);

            //Se verifica que el dato a colocar no rompa ninguna de las reglas del juego de Sudoku, si no es
            //así se le informa al jugador
            if(validateBoard( i,j,c )){
                //Si todo está bien, colocamos el dato en el tablero en la posición (i,j) haciendo uso del
                //método insert() se la clase utilitaria Arrays para matrices de caracteres
                Arrays<char>::insert(board, i, j, c);
                //Se actualiza el contador ya que se ha colocado un nuevo dato
                cont++;
            }else cout << "\nEl dato no puede ubicarse en la celda indicada sin romper las reglas. :(\n\n";

            //Se muestra nuevamente el tablero
            showBoard();            
        }

        /*
            Función que ejecuta el proceso para remover un dato del tablero de juego.
        */
        static void eraseValue(){
            //Variable auxiliar para el proceso
            char c;

            //Se solicitan al jugador datos en modo CELLE con su mensaje correspondiente
            getUserInput(CELLE,"Ingrese la celda en la que desea borrar dato en el formato \"Q I J\": ");

            //Se calculan los índices (i,j) para la matriz a partir de los datos ingresados por el jugador
            //Se utilizan las fórmulas explicadas en la función anterior: insertValue()
            int i = (I-1)+3*((Q-1)/3);
            int j = (J-1)+3*((Q-1)%3);

            //Se extrae el caracter que actualmente está en la celda indicada
            Arrays<char>::extract(board,i,j,&c);

            //Se verifica que la celda no corresponda a un dato vacío, representado por '_',
            //en cuyo caso se informa que no hay dato a remover
            if(c != '_'){
                //Sí hay dato a remover, se emula la remoción sobreescribiéndolo con un '_'
                Arrays<char>::insert(board, i, j, '_');
                //Se actualiza el contador ya que ahora hay un dato menos en el tablero
                cont--;
            }else cout << "La celda indicada no contiene dato removible. :/\n\n";

            //Se muestra el tablero nuevamente
            showBoard();
        }

        /*
            Función que, cuando el jugador desea colocar un dato en una celda, verifica que
            la acción no rompa ninguna de las reglas del juego de Sudoku.

            La función retorna true si el colocar el dato no rompe ninguna regla, y retorna
            false en caso contrario.

            La función recibe (<i>,<j>) como los índices de la celda en el tablero donde se
            desea colocar un dato, y recibe <c> como el dato que se desea colocar.
        */
        static bool validateBoard(int i, int j, char c){
            //Variables auxiliares del proceso
            char c1, c2;

            /*
                Para que la acción de colocar un dato en el tablero no rompa ninguna regla
                deben de cumplirse tres reglas:
                    1. El dato a colocar no puede ser una repetición de ningún dato en la
                       misma fila del tablero.
                    2. El dato a colocar no puede ser una repetición de ningún dato en la
                       misma columna del tablero.
                    3. El dato a colocar no puede ser una repetición de ningún dato en la
                       misma zona 3x3 del tablero.
            */

            //Verificamos primero en conjunto el cumplimiento de las reglas 1 y 2
            //Iteramos valores entre 0 y 8, inclusive
            for(int k = 0; k < 9; k++){
                //Para la fila i, se extrae el dato en la columna actual del recorrido y
                //lo almacenamos en c1
                //Evitamos la columna j ya que ahí se desea colocar el dato
                if(k != j) Arrays<char>::extract(board,i,k,&c1);
                //Para la columna j, se extrae el dato en la fila actual del recorrido y
                //lo almacenamos en c2
                //Evitamos la fila i ya que ahí se desea colocar el dato
                if(k != i) Arrays<char>::extract(board,k,j,&c2);

                //Si cualquier de los dos datos extraídos implica una coincidencia con el
                //dato que se desea colocar, se rompen las reglas y se retorna false, ya
                //no es necesario verificar la regla 3
                if( c1 == c || c2 == c) return false;
            }

            //Se verifica el cumplimiento de la regla 3
            //Se recorrerá la zona 3x3 a la que la celda (i,j) pertenece usando un solo
            //iterador
            for(int k = 0; k < 9; k++){
                /*
                    Se obtienen las coordenadas locales de la zona 3x3 a la que pertenece
                    la celda (i,j) a partir de k utilizando las fórmulas explicadas en el
                    archivo "headers/Array2D.h":
                                    fila     = k\3
                                    columnas = k%3
                    
                    Dichos índices se adaptan a la zona correspondiente haciendo uso de la
                    fórmula diseñada y explicada arriba para la función insertValue():
                                    fila    = k/3+3*((Q-1)/3)
                                    columna = k%3+3*((Q-1)%3)

                    Entonces, haciendo uso de estas fórmulas se extrae el dato de la celda
                    actual del recorrido de la zona 3x3 a la que pertenece la celda (i,j) y
                    lo almacenamos en c1.
                */
                Arrays<char>::extract(board, k/3+3*((Q-1)/3) , k%3+3*((Q-1)%3) ,&c1);

                /*
                  Verificamos primero que no nos encontramos en las coordenadas locales
                  (I,J), ya que es esa la celda que el jugador ha establecido para colocar
                  el dato.
                  
                  Luego, verificamos que el dato de la celda actual no sea igual al que se
                  desea colocar en el tablero.                                            
                  
                  Si la coincidencia ocurre, entonces se rompe la regla 3, ya no continuamos
                  con el proceso y se retorna una respuesta negativa.                       

                  Es necesario adaptar las coordenadas actuales (k\3,k%3) a un conteo desde 1
                  para poderlas comparar con (I,J), esto se hace fácilmente sumando un 1.
                */
                if( !(k/3+1 == I && k%3+1 == J) && c1 == c ) return false;
            }
            //Si se sobrevive a ambos 'for', entonces no se rompe ninguna regla y se retorna true
            return true;
        }
    
    public:
        /*================= Operaciones a ejecutar desde el main ===========================*/
        /*
            Función que prepara el tablero para el juego.
        */
        static void createBoard(){
            //Se invoca el método create() de la clase utilitaria para que construya el
            //tablero como una matriz de caracteres 9x9
            Arrays<char>::create(&board,9,9);
        }

        /*
            Función que libera la memoria utilizada antes de termina la ejecución del
            programa.
        */
        static void cleanup(){
            //Se invoca el método destroy() de la clase utilitaria para que libere el
            //espacio de memoria utilizado por la matriz de caracteres que representó
            //el tablero durante el juego
            Arrays<char>::destroy(board);
        }

        /*
            Función que administra el menú principal del programa.
        */
        static void mainMenu(){
            //El menú debe mostrarse al menos una vez
            do{
                //Se muestra el menú principal
                showMainMenu();

                //Se solicita información al usuario estableciendo MAIN como el modo
                //de recepción de datos
                getUserInput(MAIN,"Ingrese el número de la opción a la que desea acceder: ");
            
            //La continuación del bucle depende de la opción solicitada por el jugador
            //y el resultado de su respectiva ejecución.
            //Se establece MAIN como el modo de procesamiento de datos.
            }while( processUserInput(MAIN) );
        }
};
