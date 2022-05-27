#include <iostream>
//#include <stdlib.h>
#include <string>
#include <fstream>

#include "data_structures/SDDS.h"
#include "geometry/mesh.h"
#include "gid/input_output.h"
#include "utilities/math_utilities.h"
#include "utilities/FEM_utilities.h"

using namespace std;

int main(int argc, char** argv){
    DS<float> *T, *T_full, *T_N, *M, *K, *b;
    DS<int> *dirichlet_indices, *neumann_indices;

    DS<DS<float>*> *Result,*M_locals,*K_locals,*b_locals;

    SDDS<DS<float>*>::create(&Result,SINGLE_LINKED_LIST);

    Mesh* G = new Mesh();
    read_input_file(G, argv[1]);

    int nelems = G->get_quantity(NUM_ELEMENTS);
    int nnodes = G->get_quantity(NUM_NODES);
    int free_nodes = nnodes - G->get_quantity(NUM_DIRICHLET_BCs);
    
    SDDS<float>::create(&T, free_nodes, 1, MATRIX);
    SDDS<float>::create(&T_full, nnodes, 1, MATRIX);
    
    Math::init(T, G->get_parameter(INITIAL_TEMPERATURE));

    SDDS<float>::create(&T_N, free_nodes, 1, MATRIX);
    SDDS<int>::create(&neumann_indices, G->get_quantity(NUM_NEUMANN_BCs), ARRAY);
    G->get_condition_indices(neumann_indices, NEUMANN);
    FEM::built_T_Neumann(T_N, G->get_parameter(NEUMANN_VALUE), neumann_indices);

    SDDS<int>::create(&dirichlet_indices, G->get_quantity(NUM_DIRICHLET_BCs), ARRAY);
    G->get_condition_indices(dirichlet_indices, DIRICHLET);

    FEM::build_full_T(T_full, T, G->get_parameter(DIRICHLET_VALUE), dirichlet_indices);
    SDDS<DS<float>*>::insert(Result,T_full);

    float t = G->get_parameter(INITIAL_TIME);
    float dt = G->get_parameter(TIME_STEP);
    float tf = G->get_parameter(FINAL_TIME);
    while( t <= tf ){
        
        SDDS<DS<float>*>::create(&M_locals, nelems, ARRAY);
        SDDS<DS<float>*>::create(&K_locals, nelems, ARRAY);
        SDDS<DS<float>*>::create(&b_locals, nelems, ARRAY);

        for(int e = 0; e < nelems; e++){
            Element* current_elem = G->get_element(e+1);
            SDDS<DS<float>*>::insert(M_locals, FEM::calculate_local_M(G->get_parameter(DENSITY), G->get_parameter(SPECIFIC_HEAT), current_elem));
            SDDS<DS<float>*>::insert(K_locals, FEM::calculate_local_K(G->get_parameter(THERMAL_CONDUCTIVITY), current_elem));
            SDDS<DS<float>*>::insert(b_locals, FEM::calculate_local_b(G->get_parameter(HEAT_SOURCE), current_elem));
        }

        SDDS<float>::create(&M, nnodes, nnodes, MATRIX); Math::zeroes(M);
        SDDS<float>::create(&K, nnodes, nnodes, MATRIX); Math::zeroes(K);
        SDDS<float>::create(&b, nnodes, 1, MATRIX);      Math::zeroes(b);

        for(int e = 0; e < nelems; e++){
            Element* current_elem = G->get_element(e+1);
            DS<float> *temp;

            SDDS<DS<float>*>::extract(M_locals,e,&temp);
            FEM::assembly(M, temp, current_elem, true);
            SDDS<DS<float>*>::extract(K_locals,e,&temp);
            FEM::assembly(K, temp, current_elem, true);
            SDDS<DS<float>*>::extract(b_locals,e,&temp);
            FEM::assembly(b, temp, current_elem, false);
        }

        Math::sum(b,T_N,b);

        //TODO: Apply Dirichlet
        //TODO: Euler bifurcation
        //TODO: Result update

        SDDS<float>::destroy(M); SDDS<DS<float>*>::destroy(M_locals);
        SDDS<float>::destroy(K); SDDS<DS<float>*>::destroy(K_locals);
        SDDS<float>::destroy(b); SDDS<DS<float>*>::destroy(b_locals);

        t = t + dt;
    }

    //TODO: write_output_file
    
    return 0;
}
