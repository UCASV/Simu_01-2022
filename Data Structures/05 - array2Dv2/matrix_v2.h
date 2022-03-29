#include <iostream>
#include <stdlib.h>

using namespace std;

/*

*/


template <typename type>
type** create(int nrows, int ncols){
    type** matrix = (type**) malloc(sizeof(type*)*nrows);
    for(int i = 0; i < nrows; i++)
        *(matrix+i) = (type*) malloc(sizeof(type)*ncols);
    return matrix;
}

template <typename type>
void insert(type** matrix, int row, int col, type value){
    matrix[row][col] = value;
}

template <typename type>
void destroy(type** matrix, int nrows){
    for(int i = 0; i < nrows; i++)
        free(*(matrix+i));
    free(matrix);
}

template <typename type>
bool search(type** matrix, int nrows, int ncols, type value){
    bool ans = false;
    for(int i = 0; i < nrows*ncols; i++)
        if(matrix[i/ncols][i%ncols] == value){
            ans = true;
            break;
        }
    return ans;
}

template <typename type>
int count(type** matrix, int nrows, int ncols, type value){
    int cont = 0;
    for(int i = 0; i < nrows*ncols; i++)
        if(matrix[i/ncols][i%ncols] == value)
            cont++;
    return cont;
}

template <typename type>
type** create_copy(type** original, int nrows, int ncols){
    type** new_one = (type**) malloc(sizeof(type*)*nrows);
    for(int i = 0; i < nrows; i++)
        *(new_one+i) = (type*) malloc(sizeof(type)*ncols);
    for(int i = 0; i < nrows*ncols; i++)
        new_one[i/ncols][i%ncols] = original[i/ncols][i%ncols];
    return new_one;
}
