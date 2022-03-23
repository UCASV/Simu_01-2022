template <typename type>
class Array1D: public Array<type>{
    private:
        type* array;
        int size;
    public:
        ndimensions category() override {
            return ONE_DIMENSION;
        }
        void create(Data length) override {
            size = length.n;
            array = (type*) malloc(sizeof(type)*size);
        }
        Data getDim() override {
            Data dim;
            dim.n = size;
            return dim;
        }
        void init() override {
            for(int i = 0; i < size; i++)
                array[i] = (type) 0;
        }
        void insert(Data pos, type value) override {
            array[pos.n] = value;
        }
        type extract(Data pos) override {
            return array[pos.n];
        }
        void destroy() override {
            free(array);
        }
        bool search(type value) override {
            bool ans = false;
            for(int i = 0; i < size; i++)
                if(array[i] == value){
                    ans = true;
                    break;
                }
            return ans;
        }
        int count(type value) override {
            int cont = 0;
            for(int i = 0; i < size; i++)
                if(array[i] == value)
                    cont++;
            return cont;
        }
        void reverse() override {
            type* array2 = (type*) malloc(sizeof(type)*size);
            for (int i = size-1; i >= 0; i--){
                array2[ size - (i + 1) ] = array[i];
            }
            destroy();
            array = array2;
        }
        void show(bool verbose) override {
            if(verbose)
                for(int i = 0; i < size; i++)
                    cout << "Element #" << i+1 << " is: " << array[i] << "\n";
            else{
                cout << "[ ";
                for(int i = 0; i < size-1; i++)
                    cout << array[i] << ", ";
                cout << array[size-1] << " ]\n";
            }
        }
};
