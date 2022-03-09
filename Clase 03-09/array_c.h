#include <iostream>
#include <stdlib.h>

using namespace std;

char* create(int size){
    char* array = (char*) malloc(sizeof(char)*size);
    return array;
}

void insert(char* array, int pos, char value){
    array[pos] = value;
}

void eliminate(char* array){
    free(array);
}

bool search(char* array, int size, char value){
    bool ans = false;
    for(int i = 0; i < size; i++)
        if(array[i] == value){
            ans = true;
            break;
        }
    return ans;
}

int count(char* array, int size, char value){
    int cont = 0;
    for(int i = 0; i < size; i++)
        if(array[i] == value)
            cont++;
    return cont;
}

char* create_copy(char* original, int size){
    char* new_one = (char*) malloc(sizeof(char)*size);
    for(int i = 0; i < size; i++)
        new_one[i] = original[i];
    return new_one;
}

char* reverse(char* array, int size){
    char* array2 = (char*) malloc(sizeof(char)*size);
    for (int i = size-1; i >= 0; i--){
        array2[ size - (i + 1) ] = array[i];
    }
    eliminate(array);
    return array2;
}
