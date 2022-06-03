#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

#include "data_structures/SDDS.h"
#include "geometry/mesh.h"
#include "gid/input_output.h"
#include "utilities/math_utilities.h"
#include "utilities/FEM_utilities.h"

/*
    Este archivo hace uso de la clase SDDS, la cual se ha
    definido exclusivamente con métodos y atributos estáticos,
    ya que se ha concebido como una clase utilitaria.

    C++ requiere, para los atributos estáticos, que se
    realice, antes del proceso, una asignación para que
    se genere el espacio de memoria correspondiente.

    En este escenario, ref es de tipo Data, que es una struct,
    y es un atributo estático de la clase SDDS, por lo que
    comenzamos por asignarle un struct vacío.

    La sintaxis de esta asignación es:

            <tipo> <Clase>::<atributo> = <valor_nulo>;

    Para el caso:
        - <tipo> es Data.
        - Clase es SDDS.
        - <atributo> es ref.
        - <valor_nulo>, por ser un struct, requiere una
          instanciación vacía de la misma haciendo uso
          de un constructor genérico.

    Por último, dado que SDDS es un template, es necesario
    realizar esta instanciación establecienco el "meta-parámetro";
    sin embargo, ya que el proceso no ha comenzado aún no está
    definido el tipo de dato concreto a utilizar, por lo que
    se "acarrea" el template.
*/
template <typename T>
Data SDDS<T>::ref = Data();

/*
    Procedimiento principal para la implementación del Método de los
    Elementos Finitos en 2D a la ecuación de Transferencia de Calor,
    utilizando funciones de forma lineales isoparamétricas, el Método
    de Galerkin para las funciones de peso, y Forward Euler en la
    discretización del tiempo.

    Se hace uso de la clase utilitaria SDDS para la manipulación de
    estructuras de datos, así como también de la clase DS para la definición de
    dichas estructuras.

    Se hace uso de la clase utilitaria Math para todas las operaciones de
    álgebra de matrices.

    Se hace uso de la clase utilitaria FEM para todos los procedimientos propios
    del Método de los Elementos Finitos en 2D.
*/
int main(int argc, char** argv){

    cout << "Initializing process...\nCreating auxiliar variables... ";
    
    DS<float> *T, *T_full, *T_N, *M, *K, *b;
    DS<int> *dirichlet_indices, *neumann_indices;

    DS<DS<float>*> *Result,*M_locals,*K_locals,*b_locals;

    //Se crea la lista para almacenar los resultados de cada tiempo
    SDDS<DS<float>*>::create(&Result,SINGLE_LINKED_LIST);

    cout << "OK\nReading input file and creating geometry object... ";

    //Se instancia un objeto Mesh
    Mesh* G = new Mesh();
    //Se recibe en la línea de comando como segundo parámetro el nombre del
    //archivo de entrada sin extensión, se envía este dato junto con el objeto
    //Mesh para obtener todos los datos de la malla, la geometría y el problema
    //en general
    read_input_file(G, argv[1]);

    cout << "OK\nCreating temperature vectors... ";

    int nelems = G->get_quantity(NUM_ELEMENTS); //Se extrae la cantidad de elementos en la malla
    int nnodes = G->get_quantity(NUM_NODES);    //Se extrae la cantidad de nodos en la malla
    //Los "nodos libres" son los nodos que no tienen asignada una condición
    //de Dirichlet, su cantidad se calcula restando al total de nodos la
    //cantidad de nodos que sí tienen condición de Dirichlet
    int free_nodes = nnodes - G->get_quantity(NUM_DIRICHLET_BCs);
    //Se define <T> como el vector columna para almacenar los resultados de un tiempo, los
    //cuales se calculan únicamente para los "nodos libres"
    //Su cantidad de filas es igual a la cantidad de "nodos libres"
    SDDS<float>::create(&T, free_nodes, 1, MATRIX);
    //Se define <T_full> como el vector columna para almacenar los resultados completos de un
    //tiempo, que incluyen tanto a los "nodos libres" como a los nodos que tienen condición de
    //Dirichlet
    //Su cantidad de filas es igual a la cantidad de nodos en la malla
    SDDS<float>::create(&T_full, nnodes, 1, MATRIX);
    //Se define <T_N> como el vector columna para almacenar los valores de condición de Neumann indicados
    //Su cantidad de filas es igual a la cantidad de nodos en la malla
    SDDS<float>::create(&T_N, nnodes, 1, MATRIX);

    cout << "OK\nInitializing temperature vectors... ";
    
    //Se llena <T> con el valor de temperatura inicial proporcionado para todos los nodos, por lo
    //que de momento pasa a constituir el vector columna de temperaturas inicial
    Math::init(T, G->get_parameter(INITIAL_TEMPERATURE));

    //Se define <neumann_indices> como un arreglo de enteros para almacenar los IDs de todos
    //los nodos que tienen asignada una condición de Neumann
    //Su longitud es igual a la cantidad de nodos con condición de Neumann
    SDDS<int>::create(&neumann_indices, G->get_quantity(NUM_NEUMANN_BCs), ARRAY);
    //Se llena el arreglo con los IDs de los nodos con condición de Neumann
    G->get_condition_indices(neumann_indices, NEUMANN);
    //Se construye <T_N> con los valores de Neumann para todos los nodos:
    //  - Para nodos con condición de Neumann, se les coloca el valor de Neumann proporcionado.
    //  - Para todos los demás nodos, se les coloca un 0.
    FEM::built_T_Neumann(T_N, G->get_parameter(NEUMANN_VALUE), neumann_indices);

    //Se define <dirichlet_indices> como un arreglo de enteros para almacenar los IDs de todos
    //los nodos que tienen asignada una condición de Dirichlet
    //Su longitud es igual a la cantidad de nodos con condición de Dirichlet
    SDDS<int>::create(&dirichlet_indices, G->get_quantity(NUM_DIRICHLET_BCs), ARRAY);
    //Se llena el arreglo con los IDs de los nodos con condición de Dirichlet
    G->get_condition_indices(dirichlet_indices, DIRICHLET);
    float Td = G->get_parameter(DIRICHLET_VALUE); //Se extrae el valor para las condiciones de Dirichlet
    //Se construye el vector columna inicial de temperaturas completo:
    //  - Para nodos con condición de Dirichlet, se les coloca el valor de Dirichlet extraído.
    //  - Para todos los demás nodos, se les coloca su correspondiente dato en <T>, que a su vez corresponde
    //    con el valor de temperatura inicial proporcionado.
    FEM::build_full_T(T_full, T, Td, dirichlet_indices);

    cout << "OK\nInitializing list of results... ";

    //Se coloca la matriz de resultados inicial completa como primer elemento de la lista de resultados
    FEM::append_results(Result, T_full);

    cout << "OK\n\nObtaining time parameters and starting loop...\n";

    float dt = G->get_parameter(TIME_STEP);    //Se extrae el paso de tiempo
    float t = G->get_parameter(INITIAL_TIME);  //Se extrae el tiempo inicial
    //Avanzamos al primer tiempo a calcular
    t += dt;
    float tf = G->get_parameter(FINAL_TIME);   //Se extrae el tiempo final

    //Comienza el ciclo de ejecución, el cual continúa hasta alcanzar el tiempo final
    while( t <= tf ){

        cout << "\tWorking at TIME = " << t << "s:\n\n";
        
        //Se preparan los arreglos para almacenar todas las matrices locales de todos los elementos
        //La longitud de los 3 arreglos es igual a la cantidad de elementos
        SDDS<DS<float>*>::create(&M_locals, nelems, ARRAY);
        SDDS<DS<float>*>::create(&K_locals, nelems, ARRAY);
        SDDS<DS<float>*>::create(&b_locals, nelems, ARRAY);

        //Se recorren los elementos
        for(int e = 0; e < nelems; e++){
            cout << "\t\tWorking with ELEMENT = " << e+1 << ":\n";
            //Se interpreta el contador como un ID de elemento, con la salvedad
            //que el contador comienza en 0 y los IDs comienzan en 1

            //Se extrae el elemento actual, se envía e+1 para compensar la diferencia en los conteos
            Element* current_elem = G->get_element(e+1);

            cout << "\t\tCalculating local systems... ";
            //Se calcula la M local y se añade al listado de matrices M. Se envían la densidad y el calor específico del material
            SDDS<DS<float>*>::insert(M_locals, e, FEM::calculate_local_M(G->get_parameter(DENSITY), G->get_parameter(SPECIFIC_HEAT), current_elem));
            //Se calcula la K local y se añade al listado de matrices K. Se envía la conductividad térmica del material
            SDDS<DS<float>*>::insert(K_locals, e, FEM::calculate_local_K(G->get_parameter(THERMAL_CONDUCTIVITY), current_elem));
            //Se calcula la b local y se añade al listado de matrices b. Se envía la fuente de calor
            SDDS<DS<float>*>::insert(b_locals, e, FEM::calculate_local_b(G->get_parameter(HEAT_SOURCE), current_elem));
            cout << "OK\n\n";
        }

        cout << "\tCreating global system...\n";

        //Se crean las matrices globales, y se inicializan todas sus posiciones con 0
        SDDS<float>::create(&M, nnodes, nnodes, MATRIX); Math::zeroes(M);
        SDDS<float>::create(&K, nnodes, nnodes, MATRIX); Math::zeroes(K);
        SDDS<float>::create(&b, nnodes, 1, MATRIX);      Math::zeroes(b);

        //Se recorren los listados de matrices locales, un elemento a la vez
        for(int e = 0; e < nelems; e++){
            cout << "\t\tAssembling ELEMENT = " << e+1 << ":\n";
            //Se extrae el elemento actual, se envía e+1 para compensar la diferencia en los conteos
            Element* current_elem = G->get_element(e+1);
            DS<float> *temp;

            cout << "\t\tAssembling local matrices... ";
            //Se extrae la matriz M del elemento actual y se envía a ensamblaje
            SDDS<DS<float>*>::extract(M_locals,e,&temp);
            FEM::assembly(M, temp, current_elem, true);  //Se indica que ensamblará una matriz 3 x 3
            //Se extrae la matriz K del elemento actual y se envía a ensamblaje
            SDDS<DS<float>*>::extract(K_locals,e,&temp);
            FEM::assembly(K, temp, current_elem, true);
            //Se extrae la matriz b del elemento actual y se envía a ensamblaje
            SDDS<DS<float>*>::extract(b_locals,e,&temp);
            FEM::assembly(b, temp, current_elem, false); //Se indica que ensamblará una matriz 3 x 1
            cout << "OK\n\n";
        }

        cout << "\tApplying Neumann conditions... ";
        //Se agrega la matriz de valores de Neumann a la matriz b global
        Math::sum_in_place(b,T_N);
        cout << "OK\n\n";

        cout << "\tApplying Dirichlet conditions... ";
        //Se modifican las matrices globales para aplicar las condiciones de Dirichlet
        FEM::apply_Dirichlet(nnodes, free_nodes, &b, K, Td, dirichlet_indices);
        FEM::apply_Dirichlet(nnodes, free_nodes, &K, dirichlet_indices);
        FEM::apply_Dirichlet(nnodes, free_nodes, &M, dirichlet_indices);
        cout << "OK\n\n";

        cout << "\tCalculating temperature at next time step.\n\tUsing FEM generated formulas and Forward Euler... ";

        /*
            Se procede a ejecutar la ecuación de transferencia de calor en su versión discretizada con Forward Euler:

                        T^(i+1) = T^i + M^(-1) * delta_t * ( b - K * T^i )

            En la expresión anterior, a la matriz b ya se le han incorporado el vector columna de las condiciones
            de Neumann, y el vector columna generado por la aplicación de las condiciones de Dirichlet.
        */

        //Se ejecuta K * T, donde T son las temperaturas en el tiempo actual
        DS<float>* temp = Math::product(K,T);
        //Se multiplica el contenido del resultado anterior por -1 para simular la resta
        Math::product_in_place(temp, -1);
        //Se suma el resultado de -K*T a la matriz b
        Math::sum_in_place(b, temp);
        //Se multiplica el contenido del resultado anterior por delta_t, el paso de tiempo
        Math::product_in_place(b, dt);
        //Se multiplica el resultado anterior por la inversa de la matriz M, y el resultado se añade a los
        //resultados del tiempo actual, obteniendo así los resultados del siguiente tiempo
        Math::sum_in_place(T, Math::product( Math::inverse(M), b ) );
        //La matriz temp ya no será utilizada, por lo que se libera su espacio en memoria
        SDDS<float>::destroy(temp);

        cout << "OK\n\n\tUpdating list of results... ";

        //Se construye la matriz de resultados completa para el tiempo actual
        FEM::build_full_T(T_full, T, Td, dirichlet_indices);
        //Se añade la matriz de resultados complete del tiempo actual a la lista de resultados
        FEM::append_results(Result, T_full);

        cout << "OK\n\nCleaning up and advancing in time... ";

        //Se libera todo el espacio en memoria utilizado en el tiempo actual
        SDDS<float>::destroy(M); SDDS<DS<float>*>::destroy(M_locals);
        SDDS<float>::destroy(K); SDDS<DS<float>*>::destroy(K_locals);
        SDDS<float>::destroy(b); SDDS<DS<float>*>::destroy(b_locals);

        //Avanzamos al siguiente tiempo a calcular
        t = t + dt;

        cout << "OK\n\n";
    }

    cout << "Writing output file... ";

    //El ingreso en las listas enlazadas simples se hace al inicio en SDDS,
    //por lo que hay que invertir la lista para tener los resultados en el orden
    //en el que se calcularon
    SDDS<DS<float>*>::reverse(Result);
    //Se envía el listado de resultados, y el nombre de archivo recibido en línea de
    //comandos, para crear el archivo de salida que será utilizado por GiD
    write_output_file(Result, argv[1]);

    cout << "OK\n\nCleaning up and finalizing process... ";

    //Se libera el espacio en memoria asignado para todas las estructuras utilizadas
    SDDS<float>::destroy(T); SDDS<float>::destroy(T_full); SDDS<float>::destroy(T_N);
    SDDS<int>::destroy(dirichlet_indices); SDDS<int>::destroy(neumann_indices);
    //Para la lista de resultados, por estar compuesta por otras estructuras de datos,
    //es necesario liberar una por una:
    //Se calcula la longitud de la lista
    int length;
    SDDS<DS<float>*>::extension(Result, &length);
    //Se recorre la lista
    for(int i = 0; i < length; i++){
        //Se extrae la matriz actual
        DS<float>* temp;
        SDDS<DS<float>*>::extract(Result,i,&temp);

        //Se libera el espacio en memoria de la matriz actual
        SDDS<float>::destroy(temp);
    }
    //Se libera el espacio en memoria de la lista de resultados
    SDDS<DS<float>*>::destroy(Result);
    
    cout << "OK\n\nHave a nice day!! :D\n";
    
    return 0;
}
