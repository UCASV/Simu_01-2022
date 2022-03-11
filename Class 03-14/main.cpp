//#include "array_i.h"
//#include "array_c.h"
//#include "array.h"
//#include "matrix.h"
//#include "matrix_v2.h"
#include "static.h"

template<>
Data Arrays<int>::ref = Data();

int main(void){
//********** Primer bloque de pruebas: arreglos de enteros **********/
/*
    int n = 10;
    int* array = create(n);
    int* array2;
    array[3] = 145;
    cout << array[3] << "\n";
    insert(array, 3, 225);
    cout << array[3] << "\n";
    eliminate(array);
    cout << array[3] << "\n";
    array = create(n);
    for(int i = 0; i < n; i++)
        array[i] = i;
    cout << search(array, n, 5) << " - " << search(array, n, 45) << "\n";
    array[7] = 3;
    cout << count(array, n, 3) << "\n";
    array2 = create_copy(array, n);
    cout << count(array2, n, 3) << "\n";
    array = reverse(array, n);
    cout << array[0] << " - " << array[1] << " - " << array[2] << "\n";
*/
//********** Segundo bloque de pruebas: arreglos de caracteres **********/
/*
    int n = 10;
    char* array = create(n);
    char* array2;
    array[3] = 'K';
    cout << array[3] << "\n";
    insert(array, 3, 'L');
    cout << array[3] << "\n";
    eliminate(array);
    cout << array[3] << "\n";
    array = create(n);
    for(int i = 0; i < n; i++)
        array[i] = char(i+65);
    cout << search(array, n, char(5+65)) << " - " << search(array, n, char(45+65)) << "\n";
    array[7] = char(3+65);
    cout << count(array, n, char(3+65)) << "\n";
    array2 = create_copy(array, n);
    cout << count(array2, n, char(3+65)) << "\n";
    array = reverse(array, n);
    cout << array[0] << " - " << array[1] << " - " << array[2] << "\n";
*/
//********** Tercer bloque de pruebas: arreglos de cualquier tipo **********/
/*
    int n = 10;
    int* array = create<int>(n);
    int* array2;
    array[3] = 145;
    cout << array[3] << "\n";
    insert<int>(array, 3, 225);
    cout << array[3] << "\n";
    eliminate<int>(array);
    cout << array[3] << "\n";
    array = create<int>(n);
    for(int i = 0; i < n; i++)
        array[i] = i;
    cout << search<int>(array, n, 5) << " - " << search<int>(array, n, 45) << "\n";
    array[7] = 3;
    cout << count<int>(array, n, 3) << "\n";
    array2 = create_copy<int>(array, n);
    cout << count<int>(array2, n, 3) << "\n";
    array = reverse<int>(array, n);
    cout << array[0] << " - " << array[1] << " - " << array[2] << "\n";

    char* array3 = create<char>(n);
    char* array4;
    array3[3] = 'K';
    cout << array3[3] << "\n";
    insert<char>(array3, 3, 'L');
    cout << array3[3] << "\n";
    eliminate<char>(array3);
    cout << array3[3] << "\n";
    array3 = create<char>(n);
    for(int i = 0; i < n; i++)
        array3[i] = i+65;
    cout << search<char>(array3, n, 5+65) << " - " << search<char>(array3, n, 45+65) << "\n";
    array3[7] = 3+65;
    cout << count<char>(array3, n, 3+65) << "\n";
    array4 = create_copy<char>(array3, n);
    cout << count<char>(array4, n, 3+65) << "\n";
    array3 = reverse<char>(array3, n);
    cout << array3[0] << " - " << array3[1] << " - " << array3[2] << "\n";
*/
//********** Cuarto bloque de pruebas: matrices de cualquier tipo **********/
/*
    int filas = 3, columnas = 4;
    int** matrix = create<int>(filas, columnas);
    int** matrix2;
    matrix[2][3] = 145;
    cout << matrix[2][3] << "\n";
    insert<int>(matrix, 2, 3, 225);
    cout << matrix[2][3] << "\n";
    eliminate<int>(matrix, filas);
    cout << matrix[2][3] << "\n";
    matrix = create<int>(filas, columnas);
    for(int i = 0; i < filas; i++)
        for(int j = 0; j < columnas; j++)
            matrix[i][j] = i+j;
    cout << search<int>(matrix, filas, columnas, 3) << " - " << search<int>(matrix, filas, columnas, 87) << "\n";
    matrix[2][3] = 3;
    cout << count<int>(matrix, filas, columnas, 3) << "\n";
    matrix2 = create_copy<int>(matrix, filas, columnas);
    cout << count<int>(matrix2, filas, columnas, 3) << "\n";
*/
//********** Quinto bloque de pruebas: clase administradora de arreglos estáticos **********/

    int n = 5, f = 3, c = 4, val;
    int n2, f2, c2, cont;
    bool bval;

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

    //TODO: Examples para Matrix y usando char
    /*
    Array<int>* matrix;
    Arrays<int>::create(&matrix, f,c);
    Arrays<int>::insert(matrix,2,2,75);
    Arrays<int>::extract(matrix,2,2,&val);
    cout << val << "\n";
*/
    delete array;
    //delete matrix;
    
    return 0;
}
