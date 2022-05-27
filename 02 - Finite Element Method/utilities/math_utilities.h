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

        static void sum(DS<float>* A, DS<float>* B, DS<float>* C){
            int nrows, ncols;
            SDDS<float>::extension(C,&nrows,&ncols);
            for(int i = 0; i < nrows; i++)
                for(int j = 0; j < ncols; j++){
                    float Aij, Bij;
                    SDDS<float>::extract(A,i,j,&Aij);
                    SDDS<float>::extract(B,i,j,&Bij);
                    SDDS<float>::insert(C,i,j,Aij+Bij);
                }
        }
};