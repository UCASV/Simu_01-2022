#include <iostream>
#include <stdlib.h>

using namespace std;

class Array {
    public:
        virtual ~Array() {}
        virtual void* create(int size) const = 0;
};

class intArray: public Array {
    public:
        void* create(int size) const override {
            int* array = (int*) malloc(sizeof(int)*size);
            return array;
        }
};

class charArray: public Array {
    public:
        void* create(int size) const override {
            char* array = (char*) malloc(sizeof(char)*size);
            return array;
        }
};

class Creator {
    public:
        virtual ~Creator() {}
        virtual Array* FactoryMethod() const = 0;

        void* create(int size) const {
            Array* array = this->FactoryMethod();
            void* new_one = array->create(size);

            delete array;
            return new_one;
        }
};

class intArrayCreator: public Creator {
    public:
        Array* FactoryMethod() const override {
            return new intArray();
        }
};

class charArrayCreator: public Creator {
    public:
        Array* FactoryMethod() const override {
            return new charArray();
        }
};

/*
int* create(int size){
    int* array = (int*) malloc(sizeof(int)*size);
    return array;
}

void insert(int* array, int pos, int value){
    array[pos] = value;
}

void eliminate(int* array){
    free(array);
}

bool search(int* array, int size, int value){
    bool ans = false;
    for(int i = 0; i < size; i++)
        if(array[i] == value){
            ans = true;
            break;
        }
    return ans;
}

int count(int* array, int size, int value){
    int cont = 0;
    for(int i = 0; i < size; i++)
        if(array[i] == value)
            cont++;
    return cont;
}

int* create_copy(int* original, int size){
    int* new_one = (int*) malloc(sizeof(int)*size);
    for(int i = 0; i < size; i++)
        new_one[i] = original[i];
    return new_one;
}

int* reverse(int* array, int size){
    int* array2 = (int*) malloc(sizeof(int)*size);
    for (int i = size-1; i >= 0; i--){
        array2[ size - (i + 1) ] = array[i];
    }
    eliminate(array);
    return array2;
}
*/
