template <typename T>
class DSM: public staticDS_2D<T> {
    private:
        T** matrix;
        int nrows, ncols;

    public:
        category getCategory() override {
            return MATRIX;
        }
        void destroy() override {
            for(int i = 0; i < nrows; i++)
                free(*(matrix+i));
            free(matrix);
        }
        bool search(T value) override {
            bool ans = false;
            for(int i = 0; i < nrows*ncols; i++)
                if(matrix[i/ncols][i%ncols] == value){
                    ans = true;
                    break;
                }
            return ans;
        }
        int count(T value) override {
            int cont = 0;
            for(int i = 0; i < nrows*ncols; i++)
                if(matrix[i/ncols][i%ncols] == value) cont++;
            return cont;
        }
        void show(bool verbose) override {
            if(verbose)
                for(int i = 0; i < nrows*ncols; i++)
                    cout << "Element in cell [ " << i/ncols+1 << ", " << i%ncols+1 << " ] is: " << matrix[i/ncols][i%ncols] << "\n";
            else{
                cout << "[\n";
                for(int i = 0; i < nrows; i++){
                    cout << "[ ";
                    for(int j = 0; j < ncols-1; j++)
                        cout << matrix[i][j] << ", ";
                    cout << matrix[i][ncols-1] << " ]\n";
                }
                cout << "]\n";
            }
        }

        void create(Data dim) override {
            nrows = dim.n;
            ncols = dim.m;
            matrix = (T**) malloc(sizeof(T*)*nrows);
            for(int i = 0; i < nrows; i++)
                *(matrix+i) = (T*) malloc(sizeof(T)*ncols);
        }
        Data extension() override {
            Data dim;
            dim.n = nrows; dim.m = ncols;
            return dim;
        }
        void insert(Data pos, T value) override {
            matrix[pos.n][pos.m] = value;
        }
        T extract(Data pos) override {
            return matrix[pos.n][pos.m];
        }
};
