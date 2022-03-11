#include "static.h"

template <typename type>
Data Arrays<type>::ref = Data();

char create_letter(int n){
    return char(65 + n % 26);
}

int main(void){
    int n = 5, f = 3, c = 4, val;
    int n2, f2, c2, cont;
    bool bval;
    char cval;

    Array<int>* array;
    Arrays<int>::create(&array, n);
    Arrays<int>::insert(array,2,5);
    Arrays<int>::extract(array,2,&val);
    cout << val << "\n";
    Arrays<int>::destroy(array);
    Arrays<int>::create(&array,n+3);
    Arrays<int>::insert(array,5,15);
    Arrays<int>::extract(array,5,&val);
    cout << val << "\n";
    Arrays<int>::getDim(array,&n2);
    cout << n2 << "\n";
    for(int i = 0; i < n2; i++)
        Arrays<int>::insert(array,i,i);
    Arrays<int>::show(array,false);
    Arrays<int>::reverse(array);
    Arrays<int>::show(array,false);
    Arrays<int>::search(array,4,&bval);
    cout << bval << "\n";
    Arrays<int>::search(array,54,&bval);
    cout << bval << "\n";
    Arrays<int>::show(array,true);
    Array<int>* array2;
    Arrays<int>::create_copy(array,&array2);
    Arrays<int>::show(array2,false);
    Arrays<int>::init(array2);
    Arrays<int>::show(array2,false);
    Arrays<int>::count(array2,0,&cont);
    cout << cont << "\n";

    cout << "==================\n";

    Array<char>* matrix;
    Arrays<char>::create(&matrix,f,c);
    Arrays<char>::insert(matrix,2,2,'H');
    Arrays<char>::extract(matrix,2,2,&cval);
    cout << cval << "\n";
    Arrays<char>::destroy(matrix);
    Arrays<char>::create(&matrix,f+3,c+3);
    Arrays<char>::insert(matrix,5,5,'K');
    Arrays<char>::extract(matrix,5,5,&cval);
    cout << cval << "\n";
    Arrays<char>::getDim(matrix,&f2,&c2);
    cout << f2 << " - " << c2 << "\n";
    for(int i = 0; i < f2*c2; i++)
        Arrays<char>::insert(matrix,i/c2,i%c2,create_letter(i));
    Arrays<char>::show(matrix,false);
    Arrays<char>::reverse(matrix);
    Arrays<char>::search(matrix,create_letter(4),&bval);
    cout << bval << "\n";
    Arrays<char>::search(matrix,'#',&bval);
    cout << bval << "\n";
    Arrays<char>::show(matrix,true);
    Array<char>* matrix2;
    Arrays<char>::create_copy(matrix,&matrix2);
    Arrays<char>::show(matrix2,false);
    Arrays<char>::init(matrix2);
    Arrays<char>::show(matrix2,false);
    Arrays<char>::count(matrix2,(char) 0,&cont);
    cout << cont << "\n";

    delete array;
    delete matrix;
    
    return 0;
}
