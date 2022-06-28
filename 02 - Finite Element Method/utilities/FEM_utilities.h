/*
    Clase utilitaria para los procedimientos propios del proceso de aplicación
    del Método de los Elementos Finitos a un problema en 2D (MEF2D) utilizando
    funciones de forma lineales isoparamétricas y el Método de Galerkin para las
    funciones de peso.

    La clase hace uso de la clase utilitaria SDDS para la manipulación de
    estructuras de datos, así como también de la clase DS para la definición de
    dichas estructuras.

    La clase hace uso de la clase utilitaria Math para todas las operaciones de
    álgebra de matrices.
*/
class FEM{
    /*
        Los métodos privados son procedimientos auxiliares de los métodos públicos,
        específicamente los procedimientos auxiliares para la construcción de las
        matrices presentes en las fórmulas obtenidas en el MEF2D.
    */
    private:
        /*
            Función para calcular el valor J para un elemento de la malla.

            J representa el determinante de la matriz Jacobiana, sin embargo,
            no es necesario utilizar matrices ya que contamos con fórmulas para
            calcular directamente sus elementos, y por ende, su determinante:

                            [ x_2 - x_1       x_3 - x_1 ]
                        J = [                           ]
                            [ y_2 - y_1       y_3 - y_1 ]

                        |J| = (x_2 - x_1)*(y_3 - y_1) - (x_3 - x_1)*(y_2 - y_1)

            Se reciben <P1>, <P2> y <P3> como los puntos que definen los nodos
            del elemento.
        */
        static float calculate_local_J(Point* P1, Point* P2, Point* P3){
            return abs((P2->get_x() - P1->get_x())*(P3->get_y() - P1->get_y()) - (P3->get_x() - P1->get_x())*(P2->get_y() - P1->get_y()));  //o_O
        }

        /*
            Función para calcular el área de un elemento de la malla.

            Dado que los elementos son triangulares, y que solo tenemos acceso a
            las coordenadas de sus nodos, para cálcular su área se utiliza la siguiente
            fórmula:
                    
                A = (1/2) * | x_1 * (y_2 - y_3) + x_2 * (y_3 - y_1) + x_3 * (y_1 - y_2) |

            Se reciben <P1>, <P2> y <P3> como los puntos que definen los nodos del elemento.
        */
        static float calculate_local_Area(Point* P1, Point* P2, Point* P3){
            return (abs(P1->get_x()*( P2->get_y() - P3->get_y() ) + P2->get_x()*( P3->get_y() - P1->get_y() ) + P3->get_x()*( P1->get_y() - P2->get_y() ))/2);
        }

        /*
            Función para calcular el valor D para un elemento de la malla.

            D representa el determinante del gradiente del vector fila de variables
            espaciales cartesianas, sin embargo, no es necesario utilizar matrices
            ya que contamos con fórmulas para calcular directamente sus elementos,
            y por ende, su determinante:

                            [ x_2 - x_1       y_2 - y_1 ]
                        a = [                           ]
                            [ x_3 - y_1       y_3 - y_1 ]

                        D = (x_2 - x_1)*(y_3 - y_1) - (x_3 - x_1)*(y_2 - y_1)

            Se reciben <P1>, <P2> y <P3> como los puntos que definen los nodos
            del elemento.
        */
        static float calculate_local_D(Point* P1, Point* P2, Point* P3){
            return (P2->get_x() - P1->get_x())*(P3->get_y() - P1->get_y()) - (P3->get_x() - P1->get_x())*(P2->get_y() - P1->get_y());
        }

        /*
            Función para calcular la matriz A para un elemento de la malla.

            La matriz A surge durante la creación de las fórmulas para la matriz K
            del proceso MEF2D, y su correspondiente fórmula quedó definida de la
            siguiente manera:

                            [ y_3 - y_1       y_1 - y_2 ]
                        A = [                           ]
                            [ x_1 - x_3       x_2 - x_1 ]

            Se reciben <P1>, <P2> y <P3> como los puntos que definen los nodos
            del elemento.
        */
        static void calculate_local_A(DS<float>* A, Point* P1, Point* P2, Point* P3){
            //Se definen los elementos de la matriz de acuerdo a la fórmula posición por posición
            SDDS<float>::insert(A,0,0, P3->get_y() - P1->get_y()); SDDS<float>::insert(A,0,1, P1->get_y() - P2->get_y());
            SDDS<float>::insert(A,1,0, P1->get_x() - P3->get_x()); SDDS<float>::insert(A,1,1, P2->get_x() - P1->get_x());
        }

        /*
            Función para calcular la matriz B para un elemento de la malla.

            La matriz B surge durante la creación de las fórmulas para la matriz K
            del proceso MEF2D, y su correspondiente fórmula quedó definida de la
            siguiente manera:

                                    [ -1   1   0 ]
                                B = [            ]
                                    [ -1   0   1 ]
        */
        static void calculate_B(DS<float>* B){
            //Se definen los elementos de la matriz de acuerdo a la fórmula posición por posición
            SDDS<float>::insert(B,0,0,-1); SDDS<float>::insert(B,0,1,1); SDDS<float>::insert(B,0,2,0);
            SDDS<float>::insert(B,1,0,-1); SDDS<float>::insert(B,1,1,0); SDDS<float>::insert(B,1,2,1);
        }

    /*
        Los métodos públicos son los procedimientos utilitarios directamente
        accesibles por parte de las aplicaciones "cliente".
    */
    public:
        /*
            Función para construir el vector columna correspondiente a los valores
            de condiciones de contorno de Neumann en el problema:
            - Se recibe <T_N> como la matriz de dimensiones n x 1 a llenar, donde n
              es el total de nodos de la malla.
            - Se recibe <Tn> como el valor de flujo de temperatura específico que
              constituye la condición de Neumann a imponer.
            - Se recibe <indices> como un arreglo de enteros que contiene los identificadores
              de todos los nodos a los que se les aplica la condición de Neumann.

            El vector columna a construir contendrá:
            - El valor <Tn> en la posición correspondiente a un nodo con condición
              de Neumann.
            - Un 0 en todas las demás posiciones.
        */
        static void built_T_Neumann(DS<float>* T_N, float Tn, DS<int>* indices){
            //Se extraen las dimensiones de <T_N>
            int nrows, ncols, T_pos = 0;
            SDDS<float>::extension(T_N,&nrows,&ncols);

            //Se recorre la matriz <T_N>
            //Se sabe que es un vector columna, por lo que se recorre como un arreglo
            for(int i = 0; i < nrows; i++){
                //Se interpreta el contador como un ID de nodo, con la salvedad
                //que el contador comienza en 0 y los IDs comienzan en 1

                //Se determina si el ID actual se encuentra en el arreglo de IDs
                //de nodos con condición de Neumann
                bool bres;
                SDDS<int>::search(indices,i+1,&bres); //Se envía i+1 para compensar la diferencia en los conteos

                //Si el nodo actual posee condición de Neumann, se inserta el valor <Tn>
                if(bres)
                    SDDS<float>::insert(T_N,i,0,Tn);
                //Si el nodo actual no posee condición de Neumann, se inserta un 0
                else
                    SDDS<float>::insert(T_N,i,0,0);
            }
        }

        /*
            Función para construir un vector columna de resultados completos a partir
            de un vector columna de resultados de un paso del proceso MEF2D.

            El vector columna de resultados del proceso MEF2D toma en cuenta únicamente
            los nodos libres, es decir, los nodos que no tienen condición de Dirichlet
            asignada.

            Se entiende como vector columna de resultados completo un vector que, además
            de incorporar los resultados del paso MEF2D, incorpora los nodos con condición
            de Dirichlet.

            Se reciben:
            - <T_full> como el vector columna de resultados completo a construir.
            - <T> como el vector columna de resultados del proceso MEF2D.
            - <Td> el valor de temperatura impuesto en las condiciones de Dirichlet.
            - <indices> como un arreglo de enteros que contiene los identificadores
              de todos los nodos a los que se les aplica la condición de Dirichlet.

            El vector columna a construir contendrá:
            - Para los nodos libres, su valor respectivo en el vector <T>.
            - Para los demás nodos, el valor <Td>.
        */
        static void build_full_T(DS<float>* T_full, DS<float>* T, float Td, DS<int>* indices){
            //<T_pos> se utilizará para llevar un control de las posiciones recorridas
            //en el vector columna <T>, inicia en 0 ya que primero se ocupará su posición (0,0).
            int T_pos = 0;
            //Se extraen las dimensiones de la matriz <T_full>
            int nrows, ncols;
            SDDS<float>::extension(T_full,&nrows,&ncols);

            //Se recorre la matriz <T_full>
            //Se sabe que es un vector columna, por lo que se recorre como un arreglo
            for(int i = 0; i < nrows; i++){
                //Se interpreta el contador como un ID de nodo, con la salvedad
                //que el contador comienza en 0 y los IDs comienzan en 1

                //Se determina si el ID actual se encuentra en el arreglo de IDs
                //de nodos con condición de Dirichlet
                bool bres;
                SDDS<int>::search(indices,i+1,&bres); //Se envía i+1 para compensar la diferencia en los conteos

                //Si el nodo actual posee condición de Dirichlet, se inserta el valor <Td>
                if(bres)
                    SDDS<float>::insert(T_full,i,0,Td);
                //Si el nodo actual no posee condición de Dirichlet,...
                else{
                    //... se extrae el dato a insertar de la matriz <T>
                    float value;
                    SDDS<float>::extract(T,T_pos,0,&value);
                    //Se avanza en las filas de la matriz <T>
                    T_pos++;

                    //Se inserta el valor extraído en <T_full>
                    SDDS<float>::insert(T_full,i,0,value);
                }
            }
        }

        /*
            Función que añade un vector columna de resultados del proceso
            MEF2D al listado global de resultados.

            Se recibe <R> como la lista de resultados, y se recibe <T> como
            el vector columna de resultados a añadir a la lista.
        */
        static void append_results(DS<DS<float>*>* R, DS<float>* T){
            //Se crea una copia del vector columna de resultados <T>
            DS<float>* copy;
            SDDS<float>::create_copy(T,&copy);

            //Se inserta la copia en la lista de resultados
            SDDS<DS<float>*>::insert(R,copy);
        }

        /*
            Función para calcular la matriz M para un elemento de la malla.

            Se reciben:
            - <rho> como la densidad del material del problema.
            - <Cp> como el calor específico del material del problema.
            - <e> como un objeto Element que representa el elemento en proceso.

            La matriz M surge durante la discretización del término temporal en
            el proceso MEF2D, y su correspondiente fórmula quedó definida de la
            siguiente manera:

                                            [ 2   1   1 ]
                        M = (rho*Cp*J/24) * [ 1   2   1 ]
                                            [ 1   1   2 ]

            Los detalles teóricos de J pueden consultarse en los comentarios del
            método privado calculate_local_J() en esta clase.
        */
        static DS<float>* calculate_local_M(float rho, float Cp, Element* e){
            //Se define la matriz M con dimensiones 3 x 3
            //Esto corresponde a las dimensiones resultantes para la aplicación del MEF
            //a un problema 2D
            DS<float>* M;
            SDDS<float>::create(&M,3,3,MATRIX);

            //Se extraen los respectivos puntos que definen los nodos del objeto <e> y se envían para el cálculo de J
            float J = calculate_local_J(e->get_Node(0)->get_Point(), e->get_Node(1)->get_Point(), e->get_Node(2)->get_Point());

            //Se definen los elementos de la matriz de acuerdo a la fórmula posición por posición
            SDDS<float>::insert(M,0,0,2); SDDS<float>::insert(M,0,1,1); SDDS<float>::insert(M,0,2,1);
            SDDS<float>::insert(M,1,0,1); SDDS<float>::insert(M,1,1,2); SDDS<float>::insert(M,1,2,1);
            SDDS<float>::insert(M,2,0,1); SDDS<float>::insert(M,2,1,1); SDDS<float>::insert(M,2,2,2);

            //Se multiplica el contenido de la matriz M por el factor rho*Cp*J/24
            Math::product_in_place(M, rho*Cp*J/24);

            //Se retorna la matriz construida
            return M;
        }

        /*
            Función para calcular la matriz K para un elemento de la malla.

            Se reciben:
            - <thermal_k> como la conductividad térmica del material del problema.
            - <e> como un objeto Element que representa el elemento en proceso.

            La matriz K surge durante la discretización del término espacial en
            el proceso MEF2D, y su correspondiente fórmula quedó definida de la
            siguiente manera:

                        K = (k*Area/D^2) * B^T * A^T * A * B

            Se puede operar desde la izquierda:

            ((B^T * A^T) * A) * B

            res1 = B^T * A^T
            res2 = res1 * A
            res3 = res2 * B

            Se puede operar desde la derecha:

            B^T * (A^T * (A * B))

            res1 = A * B
            res2 = A^T * res1
            res3 = B^T * res2

            Donde <Area> es el área del elemento.

            Los detalles teóricos de las matrices A y B, y del valor D, pueden consultarse
            en los comentarios de los métodos privados calculate_local_A(), calculate_B() y
            calculate_local_D() en esta clase.
        */
        static DS<float>* calculate_local_K(float thermal_k, Element* e){
            //Se preparan las variables para el proceso
            DS<float> *A, *B, *A_T, *B_T, *K;

            //Se extraen los puntos que definen los nodos del elemento
            Point* P1 = e->get_Node(0)->get_Point();
            Point* P2 = e->get_Node(1)->get_Point();
            Point* P3 = e->get_Node(2)->get_Point();

            //Se calcula el área del elemento enviando los 3 puntos de sus vértices
            float Area = calculate_local_Area(P1,P2,P3);

            //Se calcula el valor D para el elemento enviando los 3 puntos de sus vértices
            float D = calculate_local_D(P1, P2, P3);

            //Se definen la matrix A y su transpuesta con dimensiones 2 x 2
            //Esto corresponde a las dimensiones resultantes para la aplicación del MEF
            //a un problema 2D
            SDDS<float>::create(&A,2,2,MATRIX);
            SDDS<float>::create(&A_T,2,2,MATRIX);
            //Se calcula la matriz A para el elemento enviando los 3 puntos de sus vértices
            calculate_local_A(A,P1,P2,P3);
            //Se calcula la transpuesta de la matriz A
            Math::transpose(A_T, A);

            //Se definen la matrix B con dimensiones 2 x 3, y su transpuesta con dimensiones 3 x 2
            //Esto corresponde a las dimensiones resultantes para la aplicación del MEF
            //a un problema 2D
            SDDS<float>::create(&B,2,3,MATRIX);
            SDDS<float>::create(&B_T,3,2,MATRIX);
            //Se calcula la matriz B
            calculate_B(B);
            //Se calcula la transpuesta de la matriz B
            Math::transpose(B_T, B);

            //Se efectúa B^T * A^T * A * B y el resultado se almacena en <K>
            DS<float>* temp = Math::product( B_T, A_T );
            DS<float>* temp2 = Math::product( temp, A );
            K = Math::product( temp2, B );
            SDDS<float>::destroy(temp);SDDS<float>::destroy(temp2);

            //Se multiplica el contenido de la matriz K por el factor k*Area/D^2
            Math::product_in_place(K, thermal_k*Area/(D*D));

            //Las matrices A y B, y sus transpuestas, ya no son necesarias, por lo
            //que se liberan sus espacios en memoria asignados
            SDDS<float>::destroy(A); SDDS<float>::destroy(A_T);
            SDDS<float>::destroy(B); SDDS<float>::destroy(B_T);

            //Se retorna la matriz construida
            return K;
        }

        /*
            Función para calcular la matriz b para un elemento de la malla.

            Se reciben:
            - <Q> como la fuente de calor del problema.
            - <e> como un objeto Element que representa el elemento en proceso.

            La matriz b es un vector columna que surge durante la discretización
            del término independiente en el proceso MEF2D, y su correspondiente
            fórmula quedó definida de la siguiente manera:

                                                  [ 1 ]
                                    b = (Q*J/6) * [ 1 ]
                                                  [ 1 ]

            Los detalles teóricos de J pueden consultarse en los comentarios del
            método privado calculate_local_J() en esta clase.
        */
        static DS<float>* calculate_local_b(float Q, Element* e){
            //Se define la matriz b con dimensiones 3 x 1
            //Esto corresponde a las dimensiones resultantes para la aplicación del MEF
            //a un problema 2D
            DS<float>* b;
            SDDS<float>::create(&b,3,1,MATRIX);
            
            //Se extraen los respectivos puntos que definen los nodos del objeto <e> y se envían para el cálculo de J
            float J = calculate_local_J(e->get_Node(0)->get_Point(), e->get_Node(1)->get_Point(), e->get_Node(2)->get_Point());

            //Se definen los elementos de la matriz de acuerdo a la fórmula posición por posición
            SDDS<float>::insert(b,0,0,1);
            SDDS<float>::insert(b,1,0,1);
            SDDS<float>::insert(b,2,0,1);

            //Se multiplica el contenido de la matriz b por el factor Q*J/6
            Math::product_in_place(b, Q*J/6);

            //Se retorna la matriz construida
            return b;
        }

        /*
            Función para el ensamblaje de una matriz local en la matriz global
            para un proceso MEF2D.

            Se reciben:
            - <global> como la matriz global en construcción.
            - <local> como la matriz local a ensamblar en la matriz global.
            - <e> como un objeto Element que representa el elemento en proceso.
            - <is_3x3> como una bandera que indica si se está ensamblando una matriz
              con dimensiones 3 x 3 o un vector columna con dimensiones 3 x 1. Estas
              dimensiones son las correspondientes a aplicar el MEF a un problema 2D.
        */
        static void assembly(DS<float>* global, DS<float>* local, Element* elem, bool is_3x3){
            //Se construye un arreglo de enteros de longitud 3, para almacenar los
            //índices globales de los nodos locales del elemento en proceso
            DS<int>* indices;
            SDDS<int>::create(&indices,3,ARRAY);

            //Se extraen los IDs de los 3 nodos que conforman el elemento en proceso.
            //Estos IDs constituyen los índices globales a utilizar en el proceso de ensamblaje,
            //por lo que se colocan en orden en el arreglo de enteros.
            //El conteo de los nodos comienza en 1, se resta 1 a cada dato extraído para ajustarlos
            //al conteo de posiciones de las matrices, que comienza en 0.
            int index1 = elem->get_Node(0)->get_ID() - 1;
            int index2 = elem->get_Node(1)->get_ID() - 1;
            int index3 = elem->get_Node(2)->get_ID() - 1;

            SDDS<int>::insert(indices,0, index1);
            SDDS<int>::insert(indices,1, index2);
            SDDS<int>::insert(indices,2, index3);
            
            //Variables auxiliares para el proceso
            float temp;
            int pos1, pos2;

            //Se recorre la matriz local a ensamblar
            for(int i = 0; i < 3; i++)
                //El límite superior del segundo for depende de si se trata de una
                //matriz 3 x 3 o una matriz 3 x 1
                for(int j = 0; j < ((is_3x3)?3:1); j++){
                    //Se extrae el dato en la celda actual de la matriz local
                    SDDS<float>::extract(local,i,j,&temp);

                    //Se extrae el índice global de filas correspondiente al
                    //índice local de filas actual
                    SDDS<int>::extract(indices,i,&pos1);

                    //Si se trata de una matriz 3 x 3, se extrae el índice global
                    //de columnas correspondiente al índice local de columnas actual.
                    if(is_3x3) SDDS<int>::extract(indices,j,&pos2);
                    //Si se trata de una matriz 3 x 1, el índice global de columnas es 0
                    else      pos2 = 0;

                    //En la matriz global, en la celda indicada por los índices globales
                    //definidos, se acumula el valor extraído de la matriz local
                    Math::add_to_cell(global,pos1,pos2,temp);
                }

            //El arreglo de enteros construido ya no es necesario, por lo que se libera su
            //espacio de memoria asignado
            SDDS<int>::destroy(indices);
        }

        /*
            Función utilizada para modificar la matriz b en el sistema de ecuaciones global
            del proceso MEF2D.

            Estas modificaciones consisten en las siguientes tareas:
            - Remover de la matriz b las filas correspondientes a los nodos que tienen asignada
              una condición de Dirichlet.
            - Obtener las columnas de la matriz K correspondientes a los nodos que tienen asignada
              una condición de Dirichlet, y utilizarlos para construir el vector columna adicional
              para el lado derecho de la ecuación del MEF2D.
            - Restar este vector columna adicional de la matriz b.

            Ilustración con un sistema global de 5 incógnitas, donde los nodos 1 y 2 tienen asignado un
            valor Td como condición de Dirichlet:

                                    [ a  b  c  d  e ]                [ alpha   ]
                                    [ f  g  h  i  j ]                [ beta    ]
                                K = [ k  l  m  n  o ]            b = [ gamma   ]
                                    [ p  q  r  s  t ]                [ delta   ]
                                    [ u  v  w  x  y ]                [ epsilon ]
            
                Se remueven las primeras dos filas porque las temperaturas en los nodo 1 y 2 ya no son incógnitas:

                                    [ k  l  m  n  o ]                [ gamma   ]
                                K = [ p  q  r  s  t ]            b = [ delta   ]
                                    [ u  v  w  x  y ]                [ epsilon ]

                Se identifican las columnas 1 y 2 de lo restante en K como las columnas correspondintes a los nodos con
                condición de Dirichlet:

                                                    [ k  l ]
                                                    [ p  q ]
                                                    [ u  v ]

                Para construir el vector columna adicional para el lado derecho, los datos en una misma fila en estas columnas
                identificadas se suman y el resultado se multiplica por el valor de la condición de Dirichlet:

                                [ k  l ]        [ k+l ]             [ k+l ]        [ Td*(k+l) ]
                                [ p  q ] =====> [ p+q ] =====> Td * [ p+q ] =====> [ Td*(p+q) ]
                                [ u  v ]        [ u+v ]             [ u+v ]        [ Td*(u+v) ]

                Y es este vector columna adicional es el que se resta de la matriz b:

                                                 [ gamma   ]   [ Td*(k+l) ]
                                                 [ delta   ] - [ Td*(p+q) ]
                                                 [ epsilon ]   [ Td*(u+v) ]
            
            Para realizar este proceso se reciben:
            - <nnodes> como la cantidad de nodos total en la malla.
            - <free_nodes> como la cantidad de nodos que no tienen una condición de Dirichlet.
            - <b> como la matriz b de la ecuación del MEF2D. Se recibe por referencia para que las modificaciones
              efectuadas se vean reflejadas en el procedimiento principal.
            - <K> como la matriz K de la ecuación del MEF2D.
            - <Td> como la temperatura impuesta en los nodos con condición de Dirichlet.
            - <dirichlet_indices> como un arreglo de enteros que contiene los IDs de todos los nodos que tienen
              asignada una condición de Dirichlet.
        */
        static void apply_Dirichlet(int nnodes, int free_nodes, DS<float>** b, DS<float>* K, float Td, DS<int>* dirichlet_indices){
            //Se preparan las matrices a construir como parte del proceso
            //<new_b> será la matriz b después de remover las filas de los nodos con condición
            //de Dirichlet, mientras que <T_D> será el vector columna adicional
            DS<float> *new_b, *T_D;
            //Se definen <new_b> y <T_D> como vectores columna con una cantidad de filas igual
            //a la cantidad de nodos que no tienen una condición de Dirichlet
            SDDS<float>::create(&new_b, free_nodes, 1, MATRIX);
            SDDS<float>::create(&T_D, free_nodes, 1, MATRIX);

            //Se preparan las variables auxiliares del proceso
            bool bres;
            float temp, acum;
            //<row_index> se utilizará para llevar un control de las posiciones definidas
            //tanto en <new_b> como en <T_D>, inicia en 0 ya que en ambos casos primero se
            //definirán sus posiciones (0,0).
            float row_index = 0;

            //Se recorren las filas de la matriz b
            //Se sabe que su cantidad de filas es igual a la cantidad de nodos en la malla
            for(int i = 0; i < nnodes; i++){
                //Se interpreta el contador como un ID de nodo, con la salvedad
                //que el contador comienza en 0 y los IDs comienzan en 1

                //Se determina si el ID actual se encuentra en el arreglo de IDs
                //de nodos con condición de Dirichlet
                SDDS<int>::search(dirichlet_indices,i+1,&bres); //Se envía i+1 para compensar la diferencia en los conteos

                //Si el nodo actual no posee condición de Dirichlet, se procede
                //a definir las posiciones respectivas en <new_b> y <T_D>, de lo
                //contrario se ignora
                if(!bres){
                    //Se extrae el valor en la posición actual de la matriz b
                    //Se utiliza *b, ya que la matriz b fue enviada por referencia
                    SDDS<float>::extract(*b,i,0,&temp);
                    //Se inserta el valor estraído en la nueva matriz b en la
                    //posición actual de su recorrido, indicada por <row_index>
                    SDDS<float>::insert(new_b,row_index,0,temp);

                    //Se inicializa el acumulador
                    acum = 0;

                    //Se recorren en la matriz K las columnas de la fila actual
                    for(int j = 0; j < nnodes; j++){
                        //De manera similar al contador para las filas, el contador para las
                        //columnas también se interpreta como un ID de nodo

                        //Se determina si la columna actual se encuentra en el arreglo de IDs
                        //de nodos con condición de Dirichlet
                        SDDS<int>::search(dirichlet_indices,j+1,&bres); //Se envía i+1 para compensar la diferencia en los conteos

                        //Si la columna actual posee condición de Dirichlet, se procede
                        //a calcular la posición respectiva en el vector columna adicional
                        //<T_D>, de lo contrario se ignora
                        if(bres){
                            //Se extrae el valor de la celda actual en K
                            SDDS<float>::extract(K,i,j,&temp);
                            //Se acumula el producto del valor extraído por el valor de las condiciones de Dirichlet
                            acum += Td*temp;
                        }
                    }

                    //Se inserta el resultado del acumulador en el vector columna adicional en la
                    //posición actual de su recorrido, indicada por <row_index>
                    //El resultado se inserta multiplicado por -1 para simular la resta que debe ejecutarse
                    SDDS<float>::insert(T_D,row_index,0,-acum);

                    //Actualizamos <row_index> para avanzar en su recorrido
                    row_index++;
                }
            }

            //Se suma el vector columna adicional <T_D> a la nueva matriz b
            Math::sum_in_place(new_b,T_D);

            //<T_D> ya no será utilizado, por lo que se libera su espacio en memoria
            SDDS<float>::destroy(T_D);
            //Dado que la actual matriz b será sustituida por la nueva, liberamos también
            //su espacio en memoria
            //Se utiliza *b, ya que la matriz b fue enviada por referencia
            SDDS<float>::destroy(*b);

            //Concretizamos <new_b> como la nueva matriz b
            *b = new_b;
        }

        /*
            Función utilizada para modificar una matriz en el sistema de ecuaciones global
            del proceso MEF2D.

            Estas modificaciones consisten en remover de la matriz las filas y las columnas
            correspondientes a los nodos que tienen asignada una condición de Dirichlet.

            Para realizar este proceso se reciben:
            - <nnodes> como la cantidad de nodos total en la malla.
            - <free_nodes> como la cantidad de nodos que no tienen una condición de Dirichlet.
            - <matrix> como la matriz de la ecuación del MEF2D. Se recibe por referencia para que las modificaciones
              efectuadas se vean reflejadas en el procedimiento principal.
            - <dirichlet_indices> como un arreglo de enteros que contiene los IDs de todos los nodos que tienen
              asignada una condición de Dirichlet.
        */
        static void apply_Dirichlet(int nnodes, int free_nodes, DS<float>** matrix, DS<int>* dirichlet_indices){
            //Se prepara la matriz a construir
            //<new_matrix> será <matrix> después de remover las filas y las columnas de los nodos con condición
            //de Dirichlet
            DS<float>* new_matrix;
            //Se define <new_matrix> con una cantidad de filas y columnas igual a la cantidad de nodos que no
            //tienen una condición de Dirichlet
            SDDS<float>::create(&new_matrix, free_nodes, free_nodes, MATRIX);

            //Se preparan las variables auxiliares del proceso
            bool res_i, res_j;
            float Mij;
            //<row> y <column> se utilizará para llevar un control de las posiciones definidas
            //en <new_matrix>, ambas inician en 0 ya que primero se definirá su posición (0,0).
            float row = 0, column = 0;

            //Se recorre la matriz original
            //Se sabe que su cantidad de filas y columnas son iguales a la cantidad de nodos en la malla
            for(int i = 0; i < nnodes; i++){
                //Se interpreta el contador como un ID de nodo, con la salvedad
                //que el contador comienza en 0 y los IDs comienzan en 1

                //Se determina si el ID actual se encuentra en el arreglo de IDs
                //de nodos con condición de Dirichlet
                SDDS<int>::search(dirichlet_indices,i+1,&res_i); //Se envía i+1 para compensar la diferencia en los conteos

                //Si el nodo actual no posee condición de Dirichlet, se procede
                //a definir la posición respectiva en <new_matrix>, de lo contrario se ignora
                if(!res_i){
                    for(int j = 0; j < nnodes; j++){
                        //De manera similar al contador para las filas, el contador para las
                        //columnas también se interpreta como un ID de nodo

                        //Se determina si la columna actual se encuentra en el arreglo de IDs
                        //de nodos con condición de Dirichlet
                        SDDS<int>::search(dirichlet_indices,j+1,&res_j);

                        //Si la columna actual no posee condición de Dirichlet, se procede
                        //a definir el valor en la posición correspondiente en <new_matrix>,
                        //de lo contrario se ignora
                        if(!res_j){
                            //Se extrae el dato en la posición actual de la matriz original.
                            //Se utiliza *matrix, ya que la matriz fue enviada por referencia
                            SDDS<float>::extract(*matrix,i,j,&Mij);

                            //Se inserta el dato extraído en la nueva matriz en la
                            //posición actual de su recorrido, indicada por <row> y <column>
                            SDDS<float>::insert(new_matrix,row,column,Mij);

                            //Se avanza en las columnas de la fila actual de la nueva matriz
                            column++;
                        }
                    }
                    //Ya que se ha terminado de recorrer una fila de la matriz original,
                    //Se avanza en las filas de la nueva matriz, y se reinicia en sus columnas
                    row++;
                    column = 0;
                }
            }

            //Dado que la actual matriz será sustituida por la nueva, liberamos su espacio en memoria
            //Se utiliza *matrix, ya que la matriz fue enviada por referencia
            SDDS<float>::destroy(*matrix);

            //Concretizamos <new_matrix> como la nueva matriz
            *matrix = new_matrix;
        }
};