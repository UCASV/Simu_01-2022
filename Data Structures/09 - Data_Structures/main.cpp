#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#include "headers/SDDS.h"

template <typename T>
Data SDDS<T>::ref = Data();

int main(void){
    DS<int> *A,*M,*SL,*DL,*T,*G;

    SDDS<int>::create(&A,10,ARRAY);
    SDDS<int>::create(&M,3,3,MATRIX);
    SDDS<int>::create(&SL,SINGLE_LINKED_LIST);
    SDDS<int>::create(&DL,DOUBLE_LINKED_LIST);
    SDDS<int>::create(&T,BINARY_SEARCH_TREE);
    SDDS<int>::create(&G,GRAPH);

    for(int i = 0; i < 10; i++){
        SDDS<int>::insert(A,i,i);
        SDDS<int>::insert(SL,i);
        SDDS<int>::insert(DL,i);
        SDDS<int>::insert(G,i,i);
    }
    for(int k = 0; k < 9; k++) SDDS<int>::insert(M,k/3,k%3,k);

    SDDS<int>::show(A,false);
    SDDS<int>::show(A,true);
    SDDS<int>::show(M,false);
    SDDS<int>::show(M,true);
    SDDS<int>::show(SL,false);
    SDDS<int>::show(SL,true);
    SDDS<int>::show(DL,false);
    SDDS<int>::show(DL,true);
    SDDS<int>::show(G,false);
    SDDS<int>::show(G,true);

    SDDS<int>::destroy(A);
    SDDS<int>::destroy(M);
    SDDS<int>::destroy(SL);
    SDDS<int>::destroy(DL);
    SDDS<int>::destroy(T);
    SDDS<int>::destroy(G);

    delete A;
    delete M;
    delete SL;
    delete DL;
    delete T;
    delete G;

    return 0;
}
