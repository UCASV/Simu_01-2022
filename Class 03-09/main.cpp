#include "array_i.h"
//#include "array_c.h"
//#include "array.h"
//#include "matrix.h"
//#include "matrix_v2.h"

int main(void){

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
    return 0;
}
