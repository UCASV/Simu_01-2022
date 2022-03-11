#include "array.h"

char create_letter(int n){
    return char(65 + n % 26);
}

int main(void){
    int n = 10;
    int* array;
    int* array2;
    char* array3;
    char* array4;

    cout << "Probando creación de arreglo de enteros... ";
    array = create<int>(n);
    cout << "OK\n";

    cout << "Probando inserción en arreglo de enteros... ";
    //array[3] = 145; //También funciona
    insert<int>(array,3,145);
    cout << "OK\n";

    cout << "Mostrando valor insertado...\n";
    cout << "El valor insertado es: " << array[3] << "\n";

    cout << "Sobreescribiendo valor insertado anteriormente... ";
    insert<int>(array, 3, 225);
    cout << "OK\n";

    cout << "Mostrando nuevo valor insertado...\n";
    cout << "El nuevo valor insertado es: " << array[3] << "\n";

    cout << "Probando eliminación de arreglo de enteros... ";
    destroy<int>(array);
    cout << "OK\n";

    cout << "Valor de celda eliminada ahora es: " << array[3] << "\n";

    cout << "Creando nuevo arreglo de enteros... ";
    array = create<int>(n);
    cout << "OK\n";

    cout << "Llenando arreglo de enteros con valores... ";
    for(int i = 0; i < n; i++)
        insert<int>(array,i,i);
    cout << "OK\n";

    cout << "Mostrando primeras posiciones del arreglo de enteros...\n";
    cout << array[0] << " - " << array[1] << " - " << array[2] << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    cout << "Resultado de búsqueda de dato existente: " << search<int>(array, n, 5) << "\n";
    cout << "Resultado de búsqueda de dato no existente: " << search<int>(array, n, 45) << "\n";

    cout << "Provocando una repetición de dato en el arreglo de enteros... ";
    insert<int>(array,7,3);
    cout << "OK\n";

    cout << "Probando conteo de elementos en arreglo de enteros...\n";
    cout << "El resultado del conteo es: " << count<int>(array, n, 3) << "\n";

    cout << "Probando creación de copia del arreglo de enteros... ";
    array2 = create_copy<int>(array, n);
    cout << "OK\n";

    cout << "Repetición del conteo utilizando la copia...\n";
    cout << "El resultado del conteo en la copia es: " << count<int>(array2, n, 3) << "\n";

    cout << "Probando inversión del arreglo de enteros... ";
    array = reverse<int>(array, n);
    cout << "OK\n";

    cout << "Mostrando primeras posiciones del arreglo invertido...\n";
    cout << array[0] << " - " << array[1] << " - " << array[2] << "\n";

    cout << "\n======================================\n\n";

    cout << "Probando creación de arreglo de caracteres... ";
    array3 = create<char>(n);
    cout << "OK\n";

    cout << "Probando inserción en arreglo de caracteres... ";
    //array3[3] = 'K'; //También funciona
    insert<char>(array3,3,'K');
    cout << "OK\n";

    cout << "Mostrando valor insertado...\n";
    cout << "El valor insertado es: " << array3[3] << "\n";

    cout << "Sobreescribiendo valor insertado anteriormente... ";
    insert<char>(array3, 3, 'L');
    cout << "OK\n";

    cout << "Mostrando nuevo valor insertado...\n";
    cout << "El nuevo valor insertado es: " << array3[3] << "\n";

    cout << "Probando eliminación de arreglo de caracteres... ";
    destroy<char>(array3);
    cout << "OK\n";

    cout << "Valor de celda eliminada ahora es: " << array3[3] << "\n";

    cout << "Creando nuevo arreglo de caracteres... ";
    array3 = create<char>(n);
    cout << "OK\n";

    cout << "Llenando arreglo de caracteres con valores... ";
    for(int i = 0; i < n; i++)
        insert<char>(array3,i,create_letter(i));
    cout << "OK\n";

    cout << "Mostrando primeras posiciones del arreglo de caracteres...\n";
    cout << array3[0] << " - " << array3[1] << " - " << array3[2] << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    cout << "Resultado de búsqueda de dato existente: " << search<char>(array3, n, create_letter(5)) << "\n";
    cout << "Resultado de búsqueda de dato no existente: " << search<char>(array3, n, '#') << "\n";

    cout << "Provocando una repetición de dato en el arreglo de caracteres... ";
    insert<char>(array3,7,create_letter(3));
    cout << "OK\n";

    cout << "Probando conteo de elementos en arreglo de caracteres...\n";
    cout << "El resultado del conteo es: " << count<char>(array3, n, create_letter(3)) << "\n";

    cout << "Probando creación de copia del arreglo de caracteres... ";
    array4 = create_copy<char>(array3, n);
    cout << "OK\n";

    cout << "Repetición del conteo utilizando la copia...\n";
    cout << "El resultado del conteo en la copia es: " << count<char>(array4, n, create_letter(3)) << "\n";

    cout << "Probando inversión del arreglo de caracteres... ";
    array3 = reverse<char>(array3, n);
    cout << "OK\n";

    cout << "Mostrando primeras posiciones del arreglo invertido...\n";
    cout << array3[0] << " - " << array3[1] << " - " << array3[2] << "\n";
    
    return 0;
}
