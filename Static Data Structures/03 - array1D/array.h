#include <iostream>
#include <stdlib.h>

using namespace std;

template <typename type>
type* create(int size){
    type* array = (type*) malloc(sizeof(type)*size);
    return array;
}

template <typename type>
void insert(type* array, int pos, type value){
    array[pos] = value;
}

template <typename type>
void destroy(type* array){
    free(array);
}

template <typename type>
bool search(type* array, int size, type value){
    bool ans = false;
    for(int i = 0; i < size; i++)
        if(array[i] == value){
            ans = true;
            break;
        }
    return ans;
}

template <typename type>
int count(type* array, int size, type value){
    int cont = 0;
    for(int i = 0; i < size; i++)
        if(array[i] == value)
            cont++;
    return cont;
}

template <typename type>
type* create_copy(type* original, int size){
    type* new_one = (type*) malloc(sizeof(type)*size);
    for(int i = 0; i < size; i++)
        new_one[i] = original[i];
    return new_one;
}

template <typename type>
type* reverse(type* array, int size){
    type* array2 = (type*) malloc(sizeof(type)*size);
    for (int i = size-1; i >= 0; i--){
        array2[ size - (i + 1) ] = array[i];
    }
    destroy(array);
    return array2;
}
