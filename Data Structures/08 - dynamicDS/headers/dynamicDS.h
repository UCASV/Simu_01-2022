enum ndimensions {ONE_DIMENSION, TWO_DIMENSIONS};

typedef struct Node{
    
} Node;

#include "Array.h"
#include "Array1D.h"
#include "Array2D.h"

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
            ref.n = nrows; ref.m = ncols;
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

        //Utilidades externas a la familia de clases 'Array'
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
