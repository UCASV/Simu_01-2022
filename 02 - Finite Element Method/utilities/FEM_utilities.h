class FEM{
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

        }

        static DS<float>* calculate_local_K(float k, Element* e){
            
        }

        static DS<float>* calculate_local_b(float Q, Element* e){
            
        }

        static void assembly(DS<float>* global, DS<float>* local, Element* elem, bool is_2D){

        }
};