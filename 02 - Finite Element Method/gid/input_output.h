void read_input_file(Mesh* G, char* filename){
    string line;
    float rho, Cp, k, Q, Td, Tn, initial_T, delta_t, t_0, t_f, x, y;
    int nnodes, nelems, ndirichlet, nneumann, index, n1, n2, n3;

    ifstream datFile( filename );

    if( datFile.is_open() ){

        datFile >> rho >> Cp >> k >> Q >> Td >> Tn >> initial_T >> delta_t >> t_0 >> t_f >> nnodes >> nelems >> ndirichlet >> nneumann;
        G->set_parameters(rho,Cp,k,Q,Td,Tn,initial_T,delta_t,t_0,t_f);
        G->set_quantities(nnodes,nelems,ndirichlet,nneumann);
        G->init_geometry();

        datFile >> line >> line;

        for(int i = 0; i < nnodes; i++){
            datFile >> index >> x >> y;
            G->add_node( new FEMNode(index, new Point(x,y) ) );
        }

        datFile >> line >> line;

        for(int i = 0; i < nelems; i++){
            datFile >> index >> n1 >> n2 >> n3;
            G->add_element( new Element( index, G->get_node(n1), G->get_node(n2), G->get_node(n3) ) );
        }

        datFile >> line >> line;

        for(int i = 0; i < ndirichlet; i++){
            datFile >> index;
            G->add_dirichlet_cond( G->get_node(index), i );
        }

        datFile >> line >> line;

        for(int i = 0; i < nneumann; i++){
            datFile >> index;
            G->add_neumann_cond( G->get_node(index), i );
        }

        datFile.close();

    }else{
        cout << "Problem opening the input file. :(\n";
        exit(EXIT_FAILURE);
    }
}