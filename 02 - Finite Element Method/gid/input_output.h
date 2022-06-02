string add_extension(char* filename, string extension){
    string name(filename);
    return name + extension;
}

void read_input_file(Mesh* G, char* filename){
    string line;
    float rho, Cp, k, Q, Td, Tn, initial_T, delta_t, t_0, t_f, x, y;
    int nnodes, nelems, ndirichlet, nneumann, index, n1, n2, n3;

    string input_file = add_extension(filename, ".dat");
    ifstream datFile( input_file );

    if( datFile.is_open() ){
        
        datFile >> rho >> Cp >> k >> Q >> Td >> Tn >> initial_T >> delta_t >> t_0 >> t_f >> nnodes >> nelems >> ndirichlet >> nneumann;
        G->set_parameters(rho,Cp,k,Q,Td,Tn,initial_T,delta_t,t_0,t_f);
        G->set_quantities(nnodes,nelems,ndirichlet,nneumann);
        G->init_geometry();

        datFile >> line;

        for(int i = 0; i < nnodes; i++){
            datFile >> index >> x >> y;
            G->add_node( new FEMNode(index, new Point(x,y) ), i );
        }

        datFile >> line >> line;

        for(int i = 0; i < nelems; i++){
            datFile >> index >> n1 >> n2 >> n3;
            G->add_element( new Element( index, G->get_node(n1), G->get_node(n2), G->get_node(n3) ), i );
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

void write_output_file(DS<DS<float>*>* R, char* filename){
    string output_file = add_extension(filename, ".post.res");
    ofstream postResFile( output_file );

    if( postResFile.is_open() ){
        postResFile << "GiD Post Results File 1.0\n";

        int length;
        SDDS<DS<float>*>::extension(R, &length);
        for(int i = 0; i < length; i++){
            DS<float>* temp;
            SDDS<DS<float>*>::extract(R,i,&temp);

            postResFile << "Result \"Temperature\" \"Load Case 1\" " << i+1 << " Scalar OnNodes\n";
            postResFile << "ComponentNames \"T\"\n";
            postResFile << "Values\n";

            int nrows, ncols;
            SDDS<float>::extension(temp, &nrows, &ncols);
            for(int f = 0; f < nrows; f++){
                float value;
                SDDS<float>::extract(temp, f, 0, &value);
                postResFile << f+1 << "     " << value << "\n";
            }

            postResFile << "End values\n";
        }

        postResFile.close();
    }else{
        cout << "Problem opening the output file. :(\n";
        exit(EXIT_FAILURE);
    }
}
