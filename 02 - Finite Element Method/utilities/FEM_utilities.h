class FEM{
    private:
        static float calculate_local_J(Point* P1, Point* P2, Point* P3){
            return (P2->get_x() - P1->get_x())*(P3->get_y() - P1->get_y()) - (P3->get_x() - P1->get_x())*(P2->get_y() - P1->get_y());
        }

        static float calculate_local_Area(Point* P1, Point* P2, Point* P3){
            return abs((P1->get_x()*( P2->get_y() - P3->get_y() ) + P2->get_x()*( P3->get_y() - P1->get_y() ) + P3->get_x()*( P1->get_y() - P2->get_y() ))/2);
        }

        static float calculate_local_D(Point* P1, Point* P2, Point* P3){
            return (P2->get_x() - P1->get_x())*(P3->get_y() - P1->get_y()) - (P3->get_x() - P1->get_x())*(P2->get_y() - P1->get_y());
        }

        static void calculate_local_A(DS<float>* A, Point* P1, Point* P2, Point* P3){
            SDDS<float>::insert(A,0,0, P3->get_y() - P1->get_y()); SDDS<float>::insert(A,0,1, P1->get_y() - P2->get_y());
            SDDS<float>::insert(A,1,0, P1->get_x() - P3->get_x()); SDDS<float>::insert(A,1,1, P2->get_x() - P1->get_x());
        }

        static void calculate_B(DS<float>* B){
            SDDS<float>::insert(B,0,0,-1); SDDS<float>::insert(B,0,1,1); SDDS<float>::insert(B,0,2,0);
            SDDS<float>::insert(B,1,0,-1); SDDS<float>::insert(B,1,1,0); SDDS<float>::insert(B,1,2,1);
        }

    public:
        static void built_T_Neumann(DS<float>* T_N, float Tn, DS<int>* indices){
            int nrows, ncols, T_pos = 0;
            SDDS<float>::extension(T_N,&nrows,&ncols);
            for(int i = 0; i < nrows; i++){
                bool bres;
                SDDS<int>::search(indices,i+1,&bres);
                if(bres)
                    SDDS<float>::insert(T_N,i,0,Tn);
                else
                    SDDS<float>::insert(T_N,i,0,0);
            }
        }

        static void build_full_T(DS<float>* T_full, DS<float>* T, float Td, DS<int>* indices){
            int nrows, ncols, T_pos = 0;
            SDDS<float>::extension(T_full,&nrows,&ncols);
            for(int i = 0; i < nrows; i++){
                bool bres;
                SDDS<int>::search(indices,i+1,&bres);
                if(bres)
                    SDDS<float>::insert(T_full,i,0,Td);
                else{
                    float value;
                    SDDS<float>::extract(T,T_pos,0,&value);
                    T_pos++;
                    SDDS<float>::insert(T_full,i,0,value);
                }
            }
        }

        static DS<float>* calculate_local_M(float rho, float Cp, Element* e){
            DS<float>* M;
            SDDS<float>::create(&M,3,3,MATRIX);

            float J = calculate_local_J(e->get_Node(0)->get_Point(), e->get_Node(1)->get_Point(), e->get_Node(2)->get_Point());

            SDDS<float>::insert(M,0,0,2); SDDS<float>::insert(M,0,1,1); SDDS<float>::insert(M,0,2,1);
            SDDS<float>::insert(M,1,0,1); SDDS<float>::insert(M,1,1,2); SDDS<float>::insert(M,1,2,1);
            SDDS<float>::insert(M,2,0,1); SDDS<float>::insert(M,2,1,1); SDDS<float>::insert(M,2,2,2);

            Math::product_in_place(M, rho*Cp*J/24);

            return M;
        }

        static DS<float>* calculate_local_K(float thermal_k, Element* e){
            DS<float> *A, *B, *A_T, *B_T, *K;

            Point* P1 = e->get_Node(0)->get_Point();
            Point* P2 = e->get_Node(1)->get_Point();
            Point* P3 = e->get_Node(2)->get_Point();

            float Area = calculate_local_Area(P1,P2,P3);
            float D = calculate_local_D(P1, P2, P3);

            SDDS<float>::create(&A,2,2,MATRIX);
            SDDS<float>::create(&A_T,2,2,MATRIX);
            calculate_local_A(A,P1,P2,P3);
            Math::transpose(A_T, A);

            SDDS<float>::create(&B,2,3,MATRIX);
            SDDS<float>::create(&B_T,3,2,MATRIX);
            calculate_B(B);
            Math::transpose(B_T, B);

            K = Math::product( Math::product( Math::product( B_T, A_T ), A ), B );

            Math::product_in_place(K, thermal_k*Area/(D*D));

            SDDS<float>::destroy(A); SDDS<float>::destroy(A_T);
            SDDS<float>::destroy(B); SDDS<float>::destroy(B_T);

            return K;
        }

        static DS<float>* calculate_local_b(float Q, Element* e){
            DS<float>* b;
            SDDS<float>::create(&b,3,1,MATRIX);
            
            float J = calculate_local_J(e->get_Node(0)->get_Point(), e->get_Node(1)->get_Point(), e->get_Node(2)->get_Point());

            SDDS<float>::insert(b,0,0,1);
            SDDS<float>::insert(b,1,0,1);
            SDDS<float>::insert(b,2,0,1);

            Math::product_in_place(b, Q*J/6);

            return b;
        }

        static void assembly(DS<float>* global, DS<float>* local, Element* elem, bool is_2D){
            DS<int>* indices;
            SDDS<int>::create(&indices,3,ARRAY);

            SDDS<int>::insert(indices,0, elem->get_Node(0)->get_ID() - 1);
            SDDS<int>::insert(indices,0, elem->get_Node(1)->get_ID() - 1);
            SDDS<int>::insert(indices,0, elem->get_Node(2)->get_ID() - 1);
            
            if(is_2D){
                float temp;
                int pos1, pos2;
                for(int i = 0; i < 3; i++)
                    for(int j = 0; j < 3; j++){
                        SDDS<float>::extract(local,i,j,&temp);

                        SDDS<int>::extract(indices,i,&pos1);
                        SDDS<int>::extract(indices,j,&pos2);
                        Math::add_to_cell(global,pos1,pos2,temp);
                    }
            }else{
                float temp;
                int pos;
                for(int i = 0; i < 3; i++){
                    SDDS<float>::extract(local,i,0,&temp);

                    SDDS<int>::extract(indices,i,&pos);
                    Math::add_to_cell(global,pos,0,temp);
                }
            }

            SDDS<int>::destroy(indices);
        }

        static void apply_Dirichlet(int nnodes, int free_nodes, DS<float>* b, DS<float>* K, float Td, DS<int>* dirichlet_indices){
            DS<float> *new_b, *T_D;
            SDDS<float>::create(&new_b, free_nodes, 1, MATRIX);
            SDDS<float>::create(&T_D, free_nodes, 1, MATRIX);

            bool res_i, res_j;
            float row1 = 0, row2 = 0, b_i;
            for(int i = 0; i < nnodes; i++){
                SDDS<int>::search(dirichlet_indices,i+1,&res_i);
                if(!res_i){
                    SDDS<float>::extract(b,i,0,&b_i);
                    SDDS<float>::insert(new_b,row1,0,b_i);
                    row1++;
                }else{
                    float acum = 0, temp;
                    for(int j = 0; j < nnodes; j++){
                        SDDS<int>::search(dirichlet_indices,j+1,&res_j);
                        if(res_j){
                            SDDS<float>::extract(K,i,j,&temp);
                            acum += Td*temp;
                        }
                        SDDS<float>::insert(T_D,row2,0,-acum);
                        row2++;
                    }
                }
            }

            Math::sum_in_place(new_b,T_D);

            SDDS<float>::destroy(T_D);
            SDDS<float>::destroy(b);

            b = new_b;
        }

        static void apply_Dirichlet(int nnodes, int free_nodes, DS<float>* matrix, DS<int>* dirichlet_indices){
            DS<float>* new_matrix;
            SDDS<float>::create(&new_matrix, free_nodes, free_nodes, MATRIX);

            bool res_i, res_j;
            float row = 0, column = 0, Mij;
            for(int i = 0; i < nnodes; i++){
                SDDS<int>::search(dirichlet_indices,i+1,&res_i);
                if(!res_i){
                    for(int j = 0; j < nnodes; j++){
                        SDDS<int>::search(dirichlet_indices,j+1,&res_j);
                        if(!res_j){
                            SDDS<float>::extract(matrix,i,j,&Mij);
                            SDDS<float>::insert(new_matrix,row,column,Mij);
                            column++;
                        }
                    }
                    row++;
                    column = 0;
                }
            }

            SDDS<float>::destroy(matrix);
            matrix = new_matrix;
        }
};