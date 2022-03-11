#include "carray.h"

char create_letter(int n){
    return char(65 + n % 26);
}

int main(void){
    int n = 10;
    char* array;
    char* array2;

    cout << "Probando creación de arreglo... ";
    array = create(n);
    cout << "OK\n";

    cout << "Probando inserción en arreglo... ";
    //array[3] = 'K'; //También funciona
    insert(array,3,'K');
    cout << "OK\n";

    cout << "Mostrando valor insertado...\n";
    cout << "El valor insertado es: " << array[3] << "\n";

    cout << "Sobreescribiendo valor insertado anteriormente... ";
    insert(array, 3, 'L');
    cout << "OK\n";

    cout << "Mostrando nuevo valor insertado...\n";
    cout << "El nuevo valor insertado es: " << array[3] << "\n";

    cout << "Probando eliminación de arreglo... ";
    destroy(array);
    cout << "OK\n";

    cout << "Valor de celda eliminada ahora es: " << array[3] << "\n";

    cout << "Creando nuevo arreglo... ";
    array = create(n);
    cout << "OK\n";

    cout << "Llenando arreglo de valores... ";
    for(int i = 0; i < n; i++)
        insert(array,i,create_letter(i));
    cout << "OK\n";

    cout << "Mostrando primeras posiciones del arreglo...\n";
    cout << array[0] << " - " << array[1] << " - " << array[2] << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    cout << "Resultado de búsqueda de dato existente: " << search(array, n, create_letter(5)) << "\n";
    cout << "Resultado de búsqueda de dato no existente: " << search(array, n, '#') << "\n";

    cout << "Provocando una repetición de dato en el arreglo... ";
    insert(array,7,create_letter(3));
    cout << "OK\n";

    cout << "Probando conteo de elementos en arreglo...\n";
    cout << "El resultado del conteo es: " << count(array, n, create_letter(3)) << "\n";

    cout << "Probando creación de copia del arreglo... ";
    array2 = create_copy(array, n);
    cout << "OK\n";

    cout << "Repetición del conteo utilizando la copia...\n";
    cout << "El resultado del conteo en la copia es: " << count(array2, n, create_letter(3)) << "\n";

    cout << "Probando inversión del arreglo... ";
    array = reverse(array, n);
    cout << "OK\n";

    cout << "Mostrando primeras posiciones del arreglo invertido...\n";
    cout << array[0] << " - " << array[1] << " - " << array[2] << "\n";
    
    return 0;
}
