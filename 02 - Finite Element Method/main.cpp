#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#define MIKE cout<<"\nMIKE\n";
#define PAUSE int pause;cin >> pause;

using namespace std;

#include "data_structures/SDDS.h"
#include "geometry/mesh.h"
#include "gid/input_output.h"
#include "utilities/math_utilities.h"
#include "utilities/FEM_utilities.h"

template <typename T>
Data SDDS<T>::ref = Data();

int main(int argc, char** argv){

    cout << "Initializing process...\nCreating auxiliar variables... ";
    
    DS<float> *T, *T_full, *T_N, *M, *K, *b;
    DS<int> *dirichlet_indices, *neumann_indices;

    DS<DS<float>*> *Result,*M_locals,*K_locals,*b_locals;

    SDDS<DS<float>*>::create(&Result,SINGLE_LINKED_LIST);

    cout << "OK\nReading input file and creating geometry object... ";

    Mesh* G = new Mesh();    
    read_input_file(G, argv[1]);

    cout << "OK\nCreating temperature vectors... ";

    int nelems = G->get_quantity(NUM_ELEMENTS);
    int nnodes = G->get_quantity(NUM_NODES);
    int free_nodes = nnodes - G->get_quantity(NUM_DIRICHLET_BCs);
    SDDS<float>::create(&T, free_nodes, 1, MATRIX);
    SDDS<float>::create(&T_full, nnodes, 1, MATRIX);
    SDDS<float>::create(&T_N, nnodes, 1, MATRIX);

    cout << "OK\nInitializing temperature vectors... ";
    
    Math::init(T, G->get_parameter(INITIAL_TEMPERATURE));

    SDDS<int>::create(&neumann_indices, G->get_quantity(NUM_NEUMANN_BCs), ARRAY);
    G->get_condition_indices(neumann_indices, NEUMANN);
    FEM::built_T_Neumann(T_N, G->get_parameter(NEUMANN_VALUE), neumann_indices);

    SDDS<int>::create(&dirichlet_indices, G->get_quantity(NUM_DIRICHLET_BCs), ARRAY);
    G->get_condition_indices(dirichlet_indices, DIRICHLET);
    float Td = G->get_parameter(DIRICHLET_VALUE);
    FEM::build_full_T(T_full, T, Td, dirichlet_indices);

    cout << "OK\nInitializing list of results... ";

    FEM::append_results(Result, T_full);

    cout << "OK\n\nObtaining time parameters and starting loop...\n";

    float dt = G->get_parameter(TIME_STEP);
    float t = G->get_parameter(INITIAL_TIME) + dt;
    float tf = G->get_parameter(FINAL_TIME);
    while( t <= tf ){

        cout << "\tWorking at TIME = " << t << "s:\n\n";
        
        SDDS<DS<float>*>::create(&M_locals, nelems, ARRAY);
        SDDS<DS<float>*>::create(&K_locals, nelems, ARRAY);
        SDDS<DS<float>*>::create(&b_locals, nelems, ARRAY);

        cout << "\tCalculating local systems...\n";

        for(int e = 0; e < nelems; e++){
            cout << "\t\tWorking with ELEMENT = " << e+1 << ":\n";
            Element* current_elem = G->get_element(e+1);

            cout << "\t\tCalculating local M... ";
            SDDS<DS<float>*>::insert(M_locals, e, FEM::calculate_local_M(G->get_parameter(DENSITY), G->get_parameter(SPECIFIC_HEAT), current_elem));
            cout << "OK\n\t\tCalculating local K... ";
            SDDS<DS<float>*>::insert(K_locals, e, FEM::calculate_local_K(G->get_parameter(THERMAL_CONDUCTIVITY), current_elem));
            cout << "OK\n\t\tCalculating local b... ";
            SDDS<DS<float>*>::insert(b_locals, e, FEM::calculate_local_b(G->get_parameter(HEAT_SOURCE), current_elem));
            cout << "OK\n\n";
        }

        cout << "\tCreating global system...\n";

        SDDS<float>::create(&M, nnodes, nnodes, MATRIX); Math::zeroes(M);
        SDDS<float>::create(&K, nnodes, nnodes, MATRIX); Math::zeroes(K);
        SDDS<float>::create(&b, nnodes, 1, MATRIX);      Math::zeroes(b);

        for(int e = 0; e < nelems; e++){
            cout << "\t\tAssembling ELEMENT = " << e+1 << ":\n";
            Element* current_elem = G->get_element(e+1);
            DS<float> *temp;

            cout << "\t\tAssembling local M... ";
            SDDS<DS<float>*>::extract(M_locals,e,&temp);
            FEM::assembly(M, temp, current_elem, true);
            cout << "OK\n\t\tAssembling local K... ";
            SDDS<DS<float>*>::extract(K_locals,e,&temp);
            FEM::assembly(K, temp, current_elem, true);
            cout << "OK\n\t\tAssembling local b... ";
            SDDS<DS<float>*>::extract(b_locals,e,&temp);
            FEM::assembly(b, temp, current_elem, false);
            cout << "OK\n\n";
        }

        cout << "\tApplying Neumann conditions... ";
        Math::sum_in_place(b,T_N);
        cout << "OK\n\n";

        cout << "\tApplying Dirichlet conditions... ";
        FEM::apply_Dirichlet(nnodes, free_nodes, &b, K, Td, dirichlet_indices);
        FEM::apply_Dirichlet(nnodes, free_nodes, &K, dirichlet_indices);
        FEM::apply_Dirichlet(nnodes, free_nodes, &M, dirichlet_indices);
        cout << "OK\n\n";

        cout << "\tCalculating temperature at next time step.\n\tUsing FEM generated formulas and Forward Euler... ";

        DS<float>* temp = Math::product(K,T);
        Math::product_in_place(temp, -1);
        Math::sum_in_place(b, temp);
        Math::sum_in_place(b, T_N);
        Math::product_in_place(b, dt);
        Math::sum_in_place(T, Math::product( Math::inverse(M), b ) );
        SDDS<float>::destroy(temp);

        cout << "OK\n\n\tUpdating list of results... ";

        FEM::build_full_T(T_full, T, Td, dirichlet_indices);
        FEM::append_results(Result, T_full);

        cout << "OK\n\nCleaning up and advancing in time... ";

        SDDS<float>::destroy(M); SDDS<DS<float>*>::destroy(M_locals);
        SDDS<float>::destroy(K); SDDS<DS<float>*>::destroy(K_locals);
        SDDS<float>::destroy(b); SDDS<DS<float>*>::destroy(b_locals);

        t = t + dt;

        cout << "OK\n\n";
    }

    cout << "Writing output file... ";

    SDDS<DS<float>*>::reverse(Result);
    write_output_file(Result, argv[1]);

    cout << "OK\n\nFinalizing process... ";

    /*SDDS<float>::destroy(T); SDDS<float>::destroy(T_full); SDDS<float>::destroy(T_N);
    SDDS<int>::destroy(dirichlet_indices); SDDS<int>::destroy(neumann_indices);*/

    cout << "OK\n\nHave a nice day!! :D\n";
    
    return 0;
}
