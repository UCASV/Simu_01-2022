template <typename type>
class Array2D: public Array<type>{
    private:
        type** matrix;
        int nrows, ncols;
    public:
        ndimensions category() override {
            return TWO_DIMENSIONS;
        }
        void create(Data dim) override {
            nrows = dim.n;
            ncols = dim.m;
            matrix = (type**) malloc(sizeof(type*)*nrows);
            for(int i = 0; i < nrows; i++)
                *(matrix+i) = (type*) malloc(sizeof(type)*ncols);
        }
        Data getDim() override {
            Data dim;
            dim.n = nrows; dim.m = ncols;
            return dim;
        }
        void init() override {
            for(int i = 0; i < nrows*ncols; i++)
                matrix[i/ncols][i%ncols] = (type) 0;
        }
        void insert(Data pos, type value) override {
            matrix[pos.n][pos.m] = value;
        }
        type extract(Data pos) override {
            return matrix[pos.n][pos.m];
        }
        void destroy() override {
            for(int i = 0; i < nrows; i++)
                free(*(matrix+i));
            free(matrix);
        }
        bool search(type value) override {
            bool ans = false;
            for(int i = 0; i < nrows*ncols; i++)
                if(matrix[i/ncols][i%ncols] == value){
                    ans = true;
                    break;
                }
            return ans;
        }
        int count(type value) override {
            int cont = 0;
            for(int i = 0; i < nrows*ncols; i++)
                if(matrix[i/ncols][i%ncols] == value)
                    cont++;
            return cont;
        }
        void reverse() override {
            cout << "->**WARNING: Operation not applicable to a two-dimensional array** :^).\n";
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
};
