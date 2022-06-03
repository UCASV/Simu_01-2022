/*
    Clase utilitaria para las operaciones de álgebra de matrices utilizadas
    durante el proceso de aplicación del Método de los Elementos Finitos.

    La clase hace uso de la clase utilitaria SDDS para la manipulación de
    estructuras de datos, así como de la clase DS para la definición de
    dichas estructuras.
*/
class Math{
    /*
        Los métodos privados son procedimientos auxiliares de los métodos
        públicos, específicamente los procedimientos auxiliares para el
        cálculo de una matriz inversa.
    */
    private:
        /*
            Función que calcula el determinante de una matrix de dimensiones
            2 x 2, de acuerdo a la siguiente fórmula:

            | a  b |
            |      | = a*d - b*c
            | c  d |
        */
        static float determinant2x2(DS<float>* M){
            //Variables para almacenar los elementos de la matriz
            float a,b,c,d;
            
            //Se extraen los elementos de la matriz
            SDDS<float>::extract(M,0,0,&a); SDDS<float>::extract(M,0,1,&b);  //[ a  b ]
            SDDS<float>::extract(M,1,0,&c); SDDS<float>::extract(M,1,1,&d);  //[ c  d ]

            return a*d - b*c;
        }
        /*
            Función que calcula el determinante de una matrix de dimensiones
            3 x 3, de acuerdo a la Regla de Sarrus:

            | a  b  c |
            | d  e  f | = (a*e*i + b*f*g + c*d*h) - (c*e*g + a*f*h + b*d*i)
            | g  h  i |
        */
        static float determinant3x3(DS<float>* M){
            //Variables para almacenar los elementos de la matriz
            float a,b,c,d,e,f,g,h,i;
            
            //Se extraen los elementos de la matriz
            SDDS<float>::extract(M,0,0,&a); SDDS<float>::extract(M,0,1,&b); SDDS<float>::extract(M,0,2,&c);  //[ a  b  c ]
            SDDS<float>::extract(M,1,0,&d); SDDS<float>::extract(M,1,1,&e); SDDS<float>::extract(M,1,2,&f);  //[ d  e  f ]
            SDDS<float>::extract(M,2,0,&g); SDDS<float>::extract(M,2,1,&h); SDDS<float>::extract(M,2,2,&i);  //[ g  h  i ]

            return (a*e*i + b*f*g + c*d*h) - (c*e*g + a*f*h + b*d*i);
        }
        /*
            Función para calcular el determinante de una matrix.

            La función determina las dimensiones de la matriz e invoca
            la función auxiliar correspondiente.

            Dadas las características de aplicar el Método de los Elementos
            Finitos en 2D, se sabe que solo serán necesarios los determinantes
            de matrices 2 x 2 y 3 x 3.
        */
        static float determinant(DS<float>* M){
            //Se extraen las dimensiones de la matriz
            int nrows, ncols;
            SDDS<float>::extension(M,&nrows,&ncols);

            //Se determina la función auxiliar a invocar
            if(nrows == 2) return determinant2x2(M);
            else           return determinant3x3(M);
        }

        /*
            Función que construye la reducción de una matriz, correspondiente
            a eliminar la fila y la columna indicadas de la matriz original.

            Se recibe <R> como la matriz reducida a construir, <M> como la
            matriz original, y <row> y <column> como la fila y columna que
            se desean eliminar de la matriz original.
        */
        static void reduce_matrix(DS<float>* R, DS<float>* M, int row, int column){
            /*
                Se definen las variables auxiliares del proceso.

                <nrows> y <ncols> se usan para almacenar las dimensiones de
                la matrix proporcionada.

                <row_index> y <col_index> se utilizarán para llevar un control
                de las posiciones a llenar en la matriz reducida, ambas inician
                en 0 ya que primero se llenará su posición (0,0).
            */
            int nrows, ncols, row_index = 0, col_index = 0;

            //Se extraen las dimensiones de la matriz original
            SDDS<float>::extension(M,&nrows,&ncols);

            //Se recorre la matriz original
            for(int i = 0; i < nrows; i++){

                //Si la fila actual no es la que debe eliminarse, se procede
                //al recorrido de sus columnas, de lo contrario se ignora
                if(i != row){
                    //Se recorre la fila actual
                    for(int j = 0; j < nrows; j++){

                        ////Si la columna actual no es la que debe eliminarse, se procede
                        //a almacenar el valor de la celda actual en la matriz reducida,
                        //de lo contrario se ignora
                        if(j != column){
                            //Se extrae el valor de la celda actual
                            float value;
                            SDDS<float>::extract(M,i,j,&value);

                            //Se ingresa el valor extraído en la matriz reducida,
                            //en la posición actualmente indicada por <row_index> y <col_index>
                            SDDS<float>::insert(R,row_index,col_index,value);

                            //Se avanza en las columnas de la matriz reducida
                            col_index++;
                        }
                    }
                    //Dado que se terminó el recorrido de una fila en la matriz original,
                    //se avanza en las filas de la matriz reducida y...
                    row_index++;
                    //... se retrocede en las columnas de la matriz reducida
                    col_index = 0;
                }
            }
        }

        /*
            Función que construye la matriz de cofactores de una matriz
            proporcionada.

            Se recibe <C> como la matriz de cofactores a llenar, y <M>
            como la matriz original.

            La elementos de la matriz de cofactores se definen de la 
            siguiente manera:

            Cof_ij = ( (-1)^(i+j) ) * m_ij

            Donde el término (-1)^(i+j) se utiliza para generar un signo
            alternante, y m_ij representa el menor correspondiente a la
            posicion (i,j).

            El menor de la posición (i,j) en una matriz se calcula como
            el determinante de la matriz reducida que se obtiene al eliminar
            la fila i y la columna j de la matriz original.
        */
        static void cofactors(DS<float>* C, DS<float>* M){
            //Se preparan las variables auxiliares del proceso
            int nrows, ncols;
            DS<float>* M_reduced;

            //Se extraen las dimensiones de la matriz original
            SDDS<float>::extension(C,&nrows,&ncols);

            //Se recorre la matriz original
            for(int i = 0; i < nrows; i++){
                for(int j = 0; j < nrows; j++){
                    //Se prepara una matriz con dimensiones (nrows-1) x (ncols-1)
                    //para almacenar la matriz reducida que se obtendrá al
                    //eliminar la fila i y la columna j de la matriz original
                    SDDS<float>::create(&M_reduced,nrows-1,ncols-1,MATRIX);
                    //Se construye dicha matriz reducida
                    reduce_matrix(M_reduced,M,i,j);

                    //Se calcula el menor de la posición actual como el determinante
                    //de la matriz reducida
                    float m_ij = determinant(M_reduced);

                    //Se ingresa en la matriz de cofactores el menor obtenido
                    //multiplicado por el signo alternante
                    SDDS<float>::insert(C, i,j, pow(-1,i+j)*m_ij);

                    //Se libera el espacio en memoria para la matriz reducida
                    //construida ya que no se utilizará más
                    SDDS<float>::destroy(M_reduced);
                }
            }
        }

    /*
        Los métodos públicos son los procedimientos utilitarios directamente
        accesibles por parte de las aplicaciones "cliente".
    */
    public:
        /*
            Función para inicializar con ceros todas las posiciones
            de una matriz.

            Se recibe <matrix> como la matriz a llenar con ceros.
        */
        static void zeroes(DS<float>* matrix){
            //Se extraen las dimensiones de la matriz
            int nrows, ncols;
            SDDS<float>::extension(matrix,&nrows,&ncols);

            //Se recorre la matriz
            for(int i = 0; i < nrows; i++)
                for(int j = 0; j < ncols; j++)
                    //Se coloca un 0 en la celda actual
                    SDDS<float>::insert(matrix,i,j,0);
        }

        /*
            Función para inicializar con un valor específico todas
            las posiciones de una matriz.

            Se recibe <matrix> como la matriz a inicializar, y se
            recibe <value> como el dato a colocar en todas las celdas.
        */
        static void init(DS<float>* matrix, float value){
            //Se extraen las dimensiones de la matriz
            int nrows, ncols;
            SDDS<float>::extension(matrix,&nrows,&ncols);

            //Se recorre la matriz
            for(int i = 0; i < nrows; i++)
                for(int j = 0; j < ncols; j++)
                    //Se coloca <value> en la celda actual
                    SDDS<float>::insert(matrix,i,j,value);
        }

        /*
            Función para la suma de dos matrices <A> y <B>.

            El término "in place" significa que el resultado
            se almacena en la primera matriz <A> de la operación,
            sobreescribiendo su contenido anterior.
        */
        static void sum_in_place(DS<float>* A, DS<float>* B){
            //Se extraen las dimensiones de <A>
            //Se asume que <B> posee la mismas dimensiones
            int nrows, ncols;
            SDDS<float>::extension(A,&nrows,&ncols);

            //Se recorren las dos matrices a la vez
            for(int i = 0; i < nrows; i++)
                for(int j = 0; j < ncols; j++){
                    //Se extraen los valores en las celdas actuales
                    //en <A> y en <B>
                    float Aij, Bij;
                    SDDS<float>::extract(A,i,j,&Aij);
                    SDDS<float>::extract(B,i,j,&Bij);

                    //Se inserta la suma de los valores extraídos en
                    //la celda actual de <A>
                    SDDS<float>::insert(A,i,j,Aij+Bij);
                }
        }

        /*
            Función para la multiplicación una matriz <A> por un
            escalar <factor>.

            El término "in place" significa que el resultado
            se almacena en la primera matriz <A> de la operación,
            sobreescribiendo su contenido anterior.
        */
        static void product_in_place(DS<float>* A, float factor){
            //Se extraen las dimensiones de <A>
            int nrows, ncols;
            SDDS<float>::extension(A,&nrows,&ncols);

            //Se recorre la matriz <A>
            for(int i = 0; i < nrows; i++)
                for(int j = 0; j < ncols; j++){
                    //Se extrae el valor en la celda actual de <A>
                    float Aij;
                    SDDS<float>::extract(A,i,j,&Aij);

                    //Se inserta en la celda actual de <A> el valor
                    //extraído multiplicado por <factor>
                    SDDS<float>::insert(A,i,j,Aij*factor);
                }
        }

        /*
            Función para la multiplicación de dos matrices <A> y <B>,
            el resultado se almacena en una matriz <C> que constituye
            el valor de retorno del proceso.

            Si:
            - Una matriz A tiene dimensiones m x n
            - Una segunda matriz B tiene dimensiones s x t
            
            Su multiplicación es realizable si y solo si:
                        <<el valor n es igual al valor s>>
            
            Es decir, si y solo si:
                    <<la cantidad de columnas de A es igual a la cantidad
                                    de filas de B>>

            Lo que permite reexpresar las dimensiones de las matrices de
            la siguiente manera:
            - A tiene dimensiones p x q
            - B tiene dimensiones q x r

            Cumplido esto, se sabe entonces que:
            - La matriz C resultante tendrá dimensiones p x r

            Es decir, C tendrá:
                    <<la misma cantidad de filas que A y la misma
                                                cantidad de columnas que B>>

            La posición (i,j) de C se calcula con la siguiente fórmula:

                   ===
                   \
            C_ij = /    A_ik * B_kj
                   ===
                    k

            Es decir, se multiplica elemento por elemento de la fila i de A y
            la columna j de B, sumando estos resultados parciales.

            Un diagrama ilustrativo de este proceso puede consultarse en el
            siguiente enlace: https://tinyurl.com/mr4x7b5a
        */
        static DS<float>* product(DS<float>* A, DS<float>* B){
            //Se preparan las variables auxiliares del proceso
            int p, q, r;
            float Aij, Bij, Cij;
            DS<float>* C;

            //Se extraen las dimensiones de <A> y <B>
            //Se asume que la cantidad de columnas de <A> es igual a la
            //cantidad de filas de <B>
            SDDS<float>::extension(A,&p,&q);
            SDDS<float>::extension(B,&q,&r);

            //Se crea la matriz <C> con una cantidad de filas igual a la
            //de <A> y una cantidad de columnas igual a la de <B>
            SDDS<float>::create(&C,p,r,MATRIX);

            //Se recorren las posiciones de la matriz <C>
            for(int i = 0; i < p; i++)
                for(int j = 0; j < r; j++){
                    //Se inicia un acumulador para la celda actual de <C>
                    Cij = 0;

                    //Se recorren a la vez la fila i de <A> y la columna j de <B>
                    for(int k = 0; k < q; k++){
                        //Se extraen los valores en:
                        //  - La posición (i,k) de <A>.
                        //  - La posición (k,j) de <B>
                        SDDS<float>::extract(A,i,k,&Aij);
                        SDDS<float>::extract(B,k,j,&Bij);

                        //Se acumula la multiplicación de los valores extraídos
                        Cij += Aij*Bij;
                    }

                    //Se almacena el acumulador en la posición (i,j) de <C>
                    SDDS<float>::insert(C,i,j,Cij);
                }

            //Se retorna la matriz resultante
            return C;
        }

        /*
            Función para construir la matriz transpuesta de una
            matriz proporcionada.

            Se recibe <trans_M> como la matriz transpuesta a construir,
            y <M> como la matriz original.

            Los elementos de una matriz transpuesta M^T de una matriz
            M se definen como:

                        M^T_ji = M_ji

            Es decir, un dato en la posición (i,j) de la matriz original
            estará ubicado en la posición (j,i) de la matriz transpuesta.
        */
        static void transpose(DS<float>* trans_M, DS<float>* M){
            //Se extraen las dimensiones de la matriz original
            int nrows, ncols;
            SDDS<float>::extension(M,&nrows,&ncols);

            //Se recorre la matriz original
            for(int i = 0; i < nrows; i++)
                for(int j = 0; j < ncols; j++){
                    //Se extrae el dato en la celda actual
                    float Aij;
                    SDDS<float>::extract(M,i,j,&Aij);

                    //Se inserta el dato extraído en la celda correspondiente
                    //de la matriz transpuesta
                    SDDS<float>::insert(trans_M,j,i,Aij);
                }
        }

        /*
            Función para añadir un valor al dato en la posición (i,j) de
            una matriz.

            Se recibe <A> como la matriz, <i> y <j> como los índices de la
            celda de interés, y <value> como el dato a añadir a dicha celda.
        */
        static void add_to_cell(DS<float>* A, int i, int j, float value){
            //Se extrae el valor en la posición (i,j) de <A>
            float Aij;
            SDDS<float>::extract(A,i,j,&Aij);

            //Se inserta en la misma posición el valor extraído sumándole <value>
            SDDS<float>::insert(A,i,j,Aij+value);
        }

        /*
            Función para calcular la matriz inversa de una matriz proporcionada.

            Se recibe <matrix> como la matriz cuya inversa se debe calcular, y es
            esta matriz inversa la que constituye el valor de retorno de la función.

            La matriz inversa M^(-1) de una matriz M, es una matriz tal que:
                            M * M^(-1) = I

            Donde I es la matriz identidad.

            Para el cálculo de la matriz inversa de utiliza la siguiente fórmula:
                            M^(-1) = (1/|M|) * Adj( M )

            Donde |M| es el determinante de la matriz M, y Adj( M ) es la matriz
            adjunta de la matriz M. La matriz adjunta se define como:
                            Adj( M ) = Cof( M )^T

            Es decir, la transpuesta de la matriz de cofactores (la teoría relacionada
            a la matriz de cofactores se puede consultar en los comentarios de la función
            cofactors() en la sección de métodos privados de esta clase).

            Este proceso de define exclusivamente para matrices de dimensiones 3 x 3,
            ya que es el único caso posible en la aplicación del Método de los Elementos
            Finitos en 2D.
        */
        static DS<float>* inverse(DS<float>* matrix){
            //Se calcula el determinante de la matriz
            float D = determinant(matrix);

            //Se preparan variables para la matriz de cofactores
            //y la matriz adjunta
            DS<float> *Cof, *Adj;

            //Se define la matriz de cofactores como una matriz 3 x 3
            SDDS<float>::create(&Cof,3,3,MATRIX);
            //Se construye la matriz de cofactores
            cofactors(Cof, matrix);

            //Se define la matriz adjunta como una matriz 3 x 3
            SDDS<float>::create(&Adj,3,3,MATRIX);
            //Se construye la matriz adjunta como la transpuesta de
            //la matriz de cofactores
            transpose(Adj, Cof);

            //Se multiplica el contenido de la matriz adjunta por
            //el factor 1/|M|, "1 sobre el determinante de la matriz"
            product_in_place(Adj, 1/D);

            //La matriz de cofactores ya no se utilizará, por lo que
            //se libera el espacio en memoria asignado para su contenido
            SDDS<float>::destroy(Cof);

            //Se retorna la matriz resultante del proceso
            return Adj;
        }
};