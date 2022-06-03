/*
    Función que recibe:
    - Un arreglo de caracteres como el nombre sin extensión de un
      archivo de texto.
    - Una cadena que contiene una extensión de archivo.

    La función anexa la extensión al nombre de archivo, y retorna
    la cadena resultante.
*/
string add_extension(char* filename, string extension){
    string name(filename);      //Se traduce el arreglo de caracteres a objeto string
    return name + extension;    //Se retorna el anexo entre el nombre y su extensión
}

/*
    Función para obtener del archivo de entrada generado por GiD toda la información
    relacionada a la malla del problema y su geometría.

    Se recibe <G> como un objeto Mesh para almacenar en sus atributos toda la información
    obtenida, y se recibe <filename> como el nombre del archivo de entrada sin extensión.
*/
void read_input_file(Mesh* G, char* filename){
    //Variable auxiliar para ignorar líneas en el archivo de entrada
    string line;
    //Variables auxiliares para la lectura de parámetros, cantidades, nodos, elementos, y condiciones
    float rho, Cp, k, Q, Td, Tn, initial_T, delta_t, t_0, t_f, x, y;
    int nnodes, nelems, ndirichlet, nneumann, index, n1, n2, n3;

    //Se anexa al nombre del archivo de entrada su extensión, y se abre para lectura
    string input_file = add_extension(filename, ".dat");
    ifstream datFile( input_file );

    //Se verifica si la apertura del archivo fue exitosa
    if( datFile.is_open() ){
        
        /*
            Se extraen del archivo de entrada todos los parámetros y cantidades:
            - La densidad del material (rho).
            - El calor específico del material (Cp).
            - La permeabilidad térmica del material (k).
            - La fuente de calor (Q).
            - El valor a aplicar en las condiciones de Dirichlet (Td).
            - El valor a aplicar en las condiciones de Neumann (Tn).
            - La temperatura inicial en el material (initial_T).
            - El paso de tiempo (delta_t).
            - El tiempo inicial (t0).
            - El tiempo final (tf).
            - La cantidad de nodos en la malla (nnodes).
            - La cantidad de elementos en la malla (nelems).}
            - La cantidad de nodos con condición de Dirichlet (ndirichlet).
            - La cantidad de nodos con condición de Neumann (nneumann).
        */
        datFile >> rho >> Cp >> k >> Q >> Td >> Tn >> initial_T >> delta_t >> t_0 >> t_f >> nnodes >> nelems >> ndirichlet >> nneumann;
        //Se colocan los parámetros en el objeto Mesh
        G->set_parameters(rho,Cp,k,Q,Td,Tn,initial_T,delta_t,t_0,t_f);
        //Se colocan las cantidades en el objeto Mesh
        G->set_quantities(nnodes,nelems,ndirichlet,nneumann);
        //Se inicializan los atributos pendientes en el objeto Mesh ahora que ya se han colocado las cantidades
        G->init_geometry();

        //Se salta la línea de encabezado del bloque de datos de los nodos de la malla
        datFile >> line;

        //Utilizando el dato de la cantidad de nodos se obtienen el ID y coordenadas de cada uno
        for(int i = 0; i < nnodes; i++){
            //Se extraen los datos del archivo
            datFile >> index >> x >> y;
            //Se crea un nuevo punto con las coordenadas extraídas, y con este punto y el ID extraído
            //se crea un nuevo nodo y se añade en el arreglo de nodos del objeto Mesh
            G->add_node( new FEMNode(index, new Point(x,y) ), i );
        }

        //Se salta la línea de cierre del bloque de datos de los nodos de la malla, y
        //se salta la línea de encabezado del bloque de datos de los elementos de la malla
        datFile >> line >> line;

        //Utilizando el dato de la cantidad de elementos se obtienen el ID de cada uno junto con los IDs de sus tres nodos
        for(int i = 0; i < nelems; i++){
            //Se extraen los datos del archivo
            datFile >> index >> n1 >> n2 >> n3;
            //Utilizando los tres IDs de nodos extraídos, se obtienen del objeto Mesh los tres nodos correspondientes, y
            //luego, junto con el ID de elemento extraído, se crea un nuevo elemento y se añade al arreglo de elementos
            //del objeto Mesh
            G->add_element( new Element( index, G->get_node(n1), G->get_node(n2), G->get_node(n3) ), i );
        }

        //Se salta la línea de cierre del bloque de datos de los elementos de la malla, y
        //se salta la línea de encabezado del bloque de datos de las condiciones de Dirichlet
        datFile >> line >> line;

        //Utilizando el dato de la cantidad de nodos con condición de Dirichlet se obtiene el ID de cada uno
        for(int i = 0; i < ndirichlet; i++){
            //Se extraen el dato del archivo
            datFile >> index;
            //Utilizando el ID extraído, se obtiene del objeto Mesh el nodo correspondiente, y éste se añade
            //al arreglo de nodos con condición de Dirichlet del objeto Mesh
            G->add_dirichlet_cond( G->get_node(index), i );
        }

        //Se salta la línea de cierre del bloque de datos de las condiciones de Dirichlet, y
        //se salta la línea de encabezado del bloque de datos de las condiciones de Neumann
        datFile >> line >> line;

        //Utilizando el dato de la cantidad de nodos con condición de Neumann se obtiene el ID de cada uno
        for(int i = 0; i < nneumann; i++){
            //Se extraen el dato del archivo
            datFile >> index;
            //Utilizando el ID extraído, se obtiene del objeto Mesh el nodo correspondiente, y éste se añade
            //al arreglo de nodos con condición de Neumann del objeto Mesh
            G->add_neumann_cond( G->get_node(index), i );
        }

        //Se cierra al archivo ya que ha terminado el proceso de lectura
        datFile.close();

    }
    //Si la apertura falló, se informa y se termina el programa
    else{
        cout << "Problem opening the input file. :(\n";
        exit(EXIT_FAILURE);
    }
}

/*
    Función para crear el archivo de salida del programa que contendrá
    los resultados del proceso de aplicación del Método de los Elementos
    Finitos.

    Se recibe <R> como una lista enlazada simple de matrices, donde cada
    una de ellas contiene los resultados de temperatura en los nodos de la
    malla para cada uno de los pasos de tiempo del proceso.

    Se recibe <filename> como el nombre del archivo de salida sin extensión.
*/
void write_output_file(DS<DS<float>*>* R, char* filename){
    //Se anexa al nombre del archivo de salida su extensión, y se abre para escritura
    string output_file = add_extension(filename, ".post.res");
    ofstream postResFile( output_file );

    //Se verifica si la apertura del archivo fue exitosa
    if( postResFile.is_open() ){
        //Se coloca el encabezado de archivo tal como lo solicita GiD
        postResFile << "GiD Post Results File 1.0\n";

        //Se extrae la longitud de la lista de resultados
        int length;
        SDDS<DS<float>*>::extension(R, &length);

        //Se recorre la lista de resultados
        for(int i = 0; i < length; i++){
            //Se extrae el resultado actual, el cual es una matriz de dimensiones
            //n x 1, donde n es el total de nodos en la malla
            DS<float>* temp;
            SDDS<DS<float>*>::extract(R,i,&temp);

            //Se colocan los encabezados para el resultado actual
            postResFile << "Result \"Temperature\" \"Load Case 1\" " << i+1 << " Scalar OnNodes\n";
            postResFile << "ComponentNames \"T\"\n";
            postResFile << "Values\n";

            //Se extraen las dimensiones de la matriz actual de resultados
            int nrows, ncols;
            SDDS<float>::extension(temp, &nrows, &ncols);

            //Sabiendo que la matriz es un vector columna, se recorre de manera
            //similar a un arreglo
            for(int f = 0; f < nrows; f++){
                //Se extrae el resultado actual
                float value;
                SDDS<float>::extract(temp, f, 0, &value);   //Todo se encuentra en la primera, y única, columna

                //Se coloca el resultado actual precedido de un correlativo
                postResFile << f+1 << "     " << value << "\n";
            }

            //Se coloca un cierre para el resultado actual
            postResFile << "End values\n";
        }

        //Se cierra al archivo ya que ha terminado el proceso de escritura
        postResFile.close();
    }
    //Si la apertura falló, se informa y se termina el programa
    else{
        cout << "Problem opening the output file. :(\n";
        exit(EXIT_FAILURE);
    }
}
