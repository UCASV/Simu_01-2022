#include "matrix_v2.h"

char create_letter(int n){
    return char(65 + n % 26);
}

int main(void){
    int filas = 3, columnas = 4;
    int** matrix;
    int** matrix2;
    char** matrix3;
    char** matrix4;

    cout << "Probando creación de matriz de enteros... ";
    matrix = create<int>(filas, columnas);
    cout << "OK\n";

    cout << "Probando inserción en matriz de enteros... ";
    //matrix[2][3] = 145; //También funciona
    insert<int>(matrix,2,3,145);
    cout << "OK\n";

    cout << "Mostrando valor insertado...\n";
    cout << "El valor insertado es: " << matrix[2][3] << "\n";

    cout << "Sobreescribiendo valor insertado anteriormente... ";
    insert<int>(matrix, 2, 3, 225);
    cout << "OK\n";

    cout << "Mostrando nuevo valor insertado...\n";
    cout << "El nuevo valor insertado es: " << matrix[2][3] << "\n";

    cout << "Probando eliminación de matriz de enteros... ";
    destroy<int>(matrix, filas);
    cout << "OK\n";

    cout << "Valor de celda eliminada ahora es: " << matrix[2][3]  << "\n";

    cout << "Creando nueva matriz de enteros... ";
    matrix = create<int>(filas, columnas);
    cout << "OK\n";

    cout << "Llenando matriz de enteros con valores... ";
    for(int i = 0; i < filas*columnas; i++)
        insert<int>(matrix,i/columnas,i%columnas,i);
    cout << "OK\n";

    cout << "Mostrando primeras posiciones de la matriz de enteros...\n";
    cout << matrix[0][0] << " - " << matrix[0][1] << " - " << matrix[0][2] << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    cout << "Resultado de búsqueda de dato existente: " << search<int>(matrix, filas, columnas, 3) << "\n";
    cout << "Resultado de búsqueda de dato no existente: " << search<int>(matrix, filas, columnas, 87) << "\n";

    cout << "Provocando una repetición de dato en la matriz de enteros... ";
    insert<int>(matrix,2,3,3);
    cout << "OK\n";

    cout << "Probando conteo de elementos en matriz de enteros...\n";
    cout << "El resultado del conteo es: " << count<int>(matrix, filas, columnas, 3) << "\n";

    cout << "Probando creación de copia de la matriz de enteros... ";
    matrix2 = create_copy<int>(matrix, filas, columnas);
    cout << "OK\n";

    cout << "Repetición del conteo utilizando la copia...\n";
    cout << "El resultado del conteo en la copia es: " << count<int>(matrix2, filas, columnas, 3) << "\n";

    cout << "\n======================================\n\n";

    cout << "Probando creación de matriz de caracteres... ";
    matrix3 = create<char>(filas, columnas);
    cout << "OK\n";

    cout << "Probando inserción en matriz de caracteres... ";
    //matrix3[2][3] = 'K'; //También funciona
    insert<char>(matrix3,2,3,'K');
    cout << "OK\n";

    cout << "Mostrando valor insertado...\n";
    cout << "El valor insertado es: " << matrix3[2][3] << "\n";

    cout << "Sobreescribiendo valor insertado anteriormente... ";
    insert<char>(matrix3, 2, 3, 'L');
    cout << "OK\n";

    cout << "Mostrando nuevo valor insertado...\n";
    cout << "El nuevo valor insertado es: " << matrix3[2][3] << "\n";

    cout << "Probando eliminación de matriz de caracteres... ";
    destroy<char>(matrix3, filas);
    cout << "OK\n";

    cout << "Valor de celda eliminada ahora es: " << matrix3[2][3]  << "\n";

    cout << "Creando nueva matriz de caracteres... ";
    matrix3 = create<char>(filas, columnas);
    cout << "OK\n";

    cout << "Llenando matriz de caracteres con valores... ";
    for(int i = 0; i < filas*columnas; i++)
        insert<char>(matrix3,i/columnas,i%columnas,create_letter(i));
    cout << "OK\n";

    cout << "Mostrando primeras posiciones de la matriz de caracteres...\n";
    cout << matrix3[0][0] << " - " << matrix3[0][1] << " - " << matrix3[0][2] << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    cout << "Resultado de búsqueda de dato existente: " << search<char>(matrix3, filas, columnas, create_letter(3)) << "\n";
    cout << "Resultado de búsqueda de dato no existente: " << search<char>(matrix3, filas, columnas, '#') << "\n";

    cout << "Provocando una repetición de dato en la matriz de caracteres... ";
    insert<char>(matrix3,2,3,create_letter(3));
    cout << "OK\n";

    cout << "Probando conteo de elementos en matriz de caracteres...\n";
    cout << "El resultado del conteo es: " << count<char>(matrix3, filas, columnas, create_letter(3)) << "\n";

    cout << "Probando creación de copia de la matriz de caracteres... ";
    matrix4 = create_copy<char>(matrix3, filas, columnas);
    cout << "OK\n";

    cout << "Repetición del conteo utilizando la copia...\n";
    cout << "El resultado del conteo en la copia es: " << count<char>(matrix4, filas, columnas, create_letter(3)) << "\n";

    return 0;
}
