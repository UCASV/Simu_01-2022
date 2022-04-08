template <typename T>
class DSA: public staticDS_1D<T>,public measurable,public positionable<T>,public reversible {
    private:
        T* array;
        int size;

    public:
        category getCategory() override {
            return ARRAY;
        }
        void destroy() override {
            free(array);
        }
        bool search(T value) override {
            bool ans = false;
            for(int i = 0; i < size; i++)
                if(array[i] == value){
                    ans = true;
                    break;
                }
            return ans;
        }
        int count(T value) override {
            int cont = 0;
            for(int i = 0; i < size; i++)
                if(array[i] == value)
                    cont++;
            return cont;
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

        void create(int n) override {
            size = n;
            array = (T*) malloc(sizeof(T)*n);
        }

        int extension() override {
            return size;
        }

        void insert(int pos, T value) override {
            array[pos] = value;
        }
        T extract(int pos) override {
            return array[pos];
        }

        void reverse() override {
            T* array2 = (T*) malloc(sizeof(T)*size);
            for (int i = size-1; i >= 0; i--){
                array2[ size - (i + 1) ] = array[i];
            }
            destroy();
            array = array2;
        }
};
