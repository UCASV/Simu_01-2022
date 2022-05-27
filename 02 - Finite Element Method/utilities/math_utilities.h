class Math{
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
            //TODO: inverse procedure
            return matrix; //Para mientras
        }
};