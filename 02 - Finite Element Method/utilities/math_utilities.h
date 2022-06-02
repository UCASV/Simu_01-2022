class Math{
    private:
        static float determinant2x2(DS<float>* M){
            float a,b,c,d;
            
            SDDS<float>::extract(M,0,0,&a); SDDS<float>::extract(M,0,1,&b);
            SDDS<float>::extract(M,1,0,&c); SDDS<float>::extract(M,1,1,&d);

            return a*d - b*c;
        }
        static float determinant3x3(DS<float>* M){
            float a,b,c,d,e,f,g,h,i;
            
            SDDS<float>::extract(M,0,0,&a); SDDS<float>::extract(M,0,1,&b); SDDS<float>::extract(M,0,2,&c);
            SDDS<float>::extract(M,1,0,&d); SDDS<float>::extract(M,1,1,&e); SDDS<float>::extract(M,1,2,&f);
            SDDS<float>::extract(M,2,0,&g); SDDS<float>::extract(M,2,1,&h); SDDS<float>::extract(M,2,2,&i);

            return (a*e*i + b*f*g + c*d*h) - (c*e*g + a*f*h + b*d*i);
        }
        static float determinant(DS<float>* M){
            int nrows, ncols;
            SDDS<float>::extension(M,&nrows,&ncols);

            if(nrows == 2) return determinant2x2(M);
            else           return determinant3x3(M);
        }

        static void reduce_matrix(DS<float>* R, DS<float>* M, int row, int column){
            int nrows, ncols, row_index = 0, col_index = 0;
            SDDS<float>::extension(M,&nrows,&ncols);
            for(int i = 0; i < nrows; i++){
                if(i != row){
                    for(int j = 0; j < nrows; j++){
                        if(j != column){
                            float value;
                            SDDS<float>::extract(M,i,j,&value);
                            SDDS<float>::insert(R,row_index,col_index,value);
                            col_index++;
                        }
                    }
                    row_index++;
                    col_index = 0;
                }
            }
        }

        static void cofactors(DS<float>* C, DS<float>* M){
            int nrows, ncols;
            DS<float>* M_reduced;

            SDDS<float>::extension(C,&nrows,&ncols);
            for(int i = 0; i < nrows; i++){
                for(int j = 0; j < nrows; j++){
                    SDDS<float>::create(&M_reduced,nrows-1,ncols-1,MATRIX);
                    reduce_matrix(M_reduced,M,i,j);

                    float m_ij = determinant(M_reduced);
                    SDDS<float>::insert(C, i,j, pow(-1,i+j)*m_ij);

                    SDDS<float>::destroy(M_reduced);
                }
            }
        }

    public:
        static void zeroes(DS<float>* matrix){
            int nrows, ncols;
            SDDS<float>::extension(matrix,&nrows,&ncols);
            for(int i = 0; i < nrows; i++)
                for(int j = 0; j < ncols; j++)
                    SDDS<float>::insert(matrix,i,j,0);
        }

        static void init(DS<float>* matrix, float value){
            int nrows, ncols;
            SDDS<float>::extension(matrix,&nrows,&ncols);
            for(int i = 0; i < nrows; i++)
                for(int j = 0; j < ncols; j++)
                    SDDS<float>::insert(matrix,i,j,value);
        }

        static void sum_in_place(DS<float>* A, DS<float>* B){
            int nrows, ncols;
            SDDS<float>::extension(A,&nrows,&ncols);
            for(int i = 0; i < nrows; i++)
                for(int j = 0; j < ncols; j++){
                    float Aij, Bij;
                    SDDS<float>::extract(A,i,j,&Aij);
                    SDDS<float>::extract(B,i,j,&Bij);
                    SDDS<float>::insert(A,i,j,Aij+Bij);
                }
        }

        static void product_in_place(DS<float>* A, float factor){
            int nrows, ncols;
            SDDS<float>::extension(A,&nrows,&ncols);
            for(int i = 0; i < nrows; i++)
                for(int j = 0; j < ncols; j++){
                    float Aij;
                    SDDS<float>::extract(A,i,j,&Aij);
                    SDDS<float>::insert(A,i,j,Aij*factor);
                }
        }

        static DS<float>* product(DS<float>* A, DS<float>* B){
            int p, q, r;
            float Aij, Bij, Cij;
            DS<float>* C;

            SDDS<float>::extension(A,&p,&q);
            SDDS<float>::extension(B,&q,&r);
            SDDS<float>::create(&C,p,r,MATRIX);

            for(int i = 0; i < p; i++)
                for(int j = 0; j < r; j++){
                    Cij = 0;
                    for(int k = 0; k < q; k++){
                        SDDS<float>::extract(A,i,k,&Aij);
                        SDDS<float>::extract(B,k,j,&Bij);

                        Cij += Aij*Bij;
                    }
                    SDDS<float>::insert(C,i,j,Cij);
                }

            return C;
        }

        static void transpose(DS<float>* trans_M, DS<float>* M){
            int nrows, ncols;
            SDDS<float>::extension(M,&nrows,&ncols);
            for(int i = 0; i < nrows; i++)
                for(int j = 0; j < ncols; j++){
                    float Aij;
                    SDDS<float>::extract(M,i,j,&Aij);
                    SDDS<float>::insert(trans_M,j,i,Aij);
                }
        }

        static void add_to_cell(DS<float>* A, int i, int j, float value){
            float Aij;
            SDDS<float>::extract(A,i,j,&Aij);
            SDDS<float>::insert(A,i,j,Aij+value);
        }

        static DS<float>* inverse(DS<float>* matrix){
            float D = determinant(matrix);
            DS<float> *Cof, *Adj;

            SDDS<float>::create(&Cof,3,3,MATRIX);
            cofactors(Cof, matrix);

            SDDS<float>::create(&Adj,3,3,MATRIX);
            transpose(Adj, Cof);
            product_in_place(Adj, 1/D);

            SDDS<float>::destroy(Cof);

            return Adj;
        }
};