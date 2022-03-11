#include <iostream>
#include <stdlib.h>

using namespace std;

enum ndimensions {ONE_DIMENSION, TWO_DIMENSIONS};

typedef struct Data{
    int n;
    int m;
    Data(){};
} Data;

template <typename type>
class Array{
    public:
        virtual ndimensions category() = 0;
        virtual void create(Data dim) = 0;
        virtual Data getDim() = 0;
        virtual void init() = 0;
        virtual void insert(Data pos, type value) = 0;
        virtual type extract(Data pos) = 0;
        virtual void destroy() = 0;
        virtual bool search(type value) = 0;
        virtual int count(type value) = 0;
        virtual void reverse() = 0;
        virtual void show(bool verbose) = 0;
};

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
            cout << "Operation not applicable to a two-dimensional array :).\n";
        }
        void show(bool verbose) override {
            if(verbose)
                for(int i = 0; i < nrows*ncols; i++)
                    cout << "Element in cell with indices [ " << i/ncols+1 << ", " << i%ncols+1 << " ] is: " << matrix[i/ncols][i%ncols] << "\n";
            else{
                cout << "[ ";
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

template <typename type>
class Arrays{
    private:
        static Data ref;

        Arrays(){}
    public:
        static void create(Array<type>** array, int size){
            ref.n = size;
            *array = new Array1D<type>();
            (*array)->create(ref);
        }
        static void create(Array<type>** matrix, int nrows, int ncols){
            ref.n = nrows, ref.m = ncols;
            *matrix = new Array2D<type>();
            (*matrix)->create(ref);
        }

        static void getDim(Array<type>* array, int* size){
            ref = array->getDim();
            *size = ref.n;
        }
        static void getDim(Array<type>* matrix, int* rows, int* columns){
            ref = matrix->getDim();
            *rows = ref.n;
            *columns = ref.m;
        }

        static void init(Array<type>* var){
            var->init();
        }

        static void insert(Array<type>* array, int pos, type value){
            ref.n = pos;
            array->insert(ref,value);
        }
        static void insert(Array<type>* matrix, int row, int column, type value){
            ref.n = row; ref.m = column;
            matrix->insert(ref,value);
        }

        static void extract(Array<type>* array, int pos, type* result){
            ref.n = pos;
            *result = array->extract(ref);
        }
        static void extract(Array<type>* matrix, int row, int column, type* result){
            ref.n = row; ref.m = column;
            *result = matrix->extract(ref);
        }

        static void destroy(Array<type>* var){
            var->destroy();
        }

        static void search(Array<type>* var, type value, bool* result){
            *result = var->search(value);
        }

        static void count(Array<type>* var, type value, int* result){
            *result = var->count(value);
        }

        static void reverse(Array<type>* var){
            var->reverse();
        }

        static void show(Array<type>* var, bool verbose){
            var->show(verbose);
        }

        //Utilidades externas a las clases Array
        static void create_copy(Array<type>* original, Array<type>** clone){
            Data dim;
            switch(original->category()){
                case ONE_DIMENSION:
                    *clone = new Array1D<type>();
                    dim = original->getDim();
                    (*clone)->create(dim);
                    for(int i = 0; i < dim.n; i++){
                        ref.n = i;
                        (*clone)->insert(ref, original->extract(ref));
                    }
                    break;
                case TWO_DIMENSIONS:
                    *clone = new Array2D<type>();
                    dim = original->getDim();
                    (*clone)->create(dim);
                    for(int i = 0; i < dim.n*dim.m; i++){
                        ref.n = i/dim.m;
                        ref.m = i%dim.m;
                        (*clone)->insert(ref, original->extract(ref));
                    }
                    break;
            }
        }
};
