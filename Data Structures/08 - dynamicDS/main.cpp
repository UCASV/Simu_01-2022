#include <iostream>
#include <string>

using namespace std;

#include "headers/dynamicDS.h"

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
    Array<int>* array; Array<int>* array2;
    Array<char>* matrix; Array<char>* matrix2;

    cout << "Probando creación de arreglo de enteros... ";
    Arrays<int>::create(&array, n);
    cout << "OK\n";

    cout << "Probando inserción en arreglo de enteros... ";
    Arrays<int>::insert(array,2,5);
    cout << "OK\n";

    cout << "Mostrando valor insertado...\n";
    Arrays<int>::extract(array,2,&val);
    cout << "El valor insertado es: " << val << "\n";

    cout << "Probando eliminación de arreglo de enteros... ";
    Arrays<int>::destroy(array);
    cout << "OK\n";

    cout << "Creando nuevo arreglo de enteros... ";
    Arrays<int>::create(&array,n+3);
    cout << "OK\n";

    cout << "Probando inserción en nuevo arreglo de enteros... ";
    Arrays<int>::insert(array,5,15);
    cout << "OK\n";

    cout << "Mostrando nuevo valor insertado...\n";
    Arrays<int>::extract(array,5,&val);
    cout << "El valor insertado es: " << val << "\n";

    cout << "Obteniendo dimensiones del arreglo de enteros...\n";
    Arrays<int>::getDim(array,&n2);
    cout << "La longitud del arreglo es: " << n2 << "\n";
    cout << "Llenando arreglo de enteros con valores... ";
    for(int i = 0; i < n2; i++)
        Arrays<int>::insert(array,i,i);
    cout << "OK\n";

    cout << "Mostrando el arreglo de enteros...\n";
    Arrays<int>::show(array,false);

    cout << "Probando inversión del arreglo de enteros... ";
    Arrays<int>::reverse(array);
    cout << "OK\n";

    cout << "Mostrando el arreglo invertido...\n";
    Arrays<int>::show(array,false);

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    Arrays<int>::search(array,4,&bval);
    cout << "Resultado de búsqueda de dato existente: " << bval << "\n";
    Arrays<int>::search(array,54,&bval);
    cout << "Resultado de búsqueda de dato no existente: " << bval << "\n";

    cout << "Mostrando el arreglo de enteros en modo VERBOSE...\n";
    Arrays<int>::show(array,true);
    
    cout << "Probando creación de copia del arreglo de enteros... ";
    Arrays<int>::create_copy(array,&array2);
    cout << "OK\n";

    cout << "Mostrando la copia del arreglo de enteros...\n";
    Arrays<int>::show(array2,false);

    cout << "Probando inicialización de arreglo con valores nulos... ";
    Arrays<int>::init(array2);
    cout << "OK\n";

    cout << "Mostrando el arreglo después de la inicialización con valores nulos...\n";
    Arrays<int>::show(array2,false);

    cout << "Probando conteo de elementos en arreglo de enteros...\n";
    Arrays<int>::count(array2,0,&cont);
    cout << "El resultado del conteo es: " << cont << "\n";

    cout << "\n======================================\n\n";

    cout << "Probando creación de matriz de caracteres... ";
    Arrays<char>::create(&matrix,f,c);
    cout << "OK\n";

    cout << "Probando inserción en matriz de caracteres... ";
    Arrays<char>::insert(matrix,2,2,'H');
    cout << "OK\n";

    cout << "Mostrando valor insertado...\n";
    Arrays<char>::extract(matrix,2,2,&cval);
    cout << "El valor insertado es: " << cval << "\n";

    cout << "Probando eliminación de matriz de caracteres... ";
    Arrays<char>::destroy(matrix);
    cout << "OK\n";

    cout << "Creando nueva matriz de caracteres... ";
    Arrays<char>::create(&matrix,f+3,c+3);
    cout << "OK\n";

    cout << "Probando inserción en nueva matriz de caracteres... ";
    Arrays<char>::insert(matrix,5,5,'K');
    cout << "OK\n";

    cout << "Mostrando nuevo valor insertado...\n";
    Arrays<char>::extract(matrix,5,5,&cval);
    cout << "El valor insertado es: " << cval << "\n";

    cout << "Obteniendo dimensiones de la matriz de caracteres...\n";
    Arrays<char>::getDim(matrix,&f2,&c2);
    cout << "Las dimensiones de la matriz son: " << f2 << "x" << c2 << "\n";
    cout << "Llenando matriz de caracteres con valores... ";
    for(int i = 0; i < f2*c2; i++)
        Arrays<char>::insert(matrix,i/c2,i%c2,create_letter(i));
    cout << "OK\n";

    cout << "Mostrando la matriz de caracteres...\n";
    Arrays<char>::show(matrix,false);

    cout << "Probando inversión (reverso) de una matriz de caracteres...\n";
    Arrays<char>::reverse(matrix);

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    Arrays<char>::search(matrix,create_letter(4),&bval);
    cout << "Resultado de búsqueda de dato existente: " << bval << "\n";
    Arrays<char>::search(matrix,'#',&bval);
    cout << "Resultado de búsqueda de dato no existente: " << bval << "\n";

    cout << "Mostrando el arreglo de enteros en modo VERBOSE...\n";
    Arrays<char>::show(matrix,true);
    
    cout << "Probando creación de copia de la matriz de caracteres... ";
    Arrays<char>::create_copy(matrix,&matrix2);
    cout << "OK\n";

    cout << "Mostrando la copia del arreglo de enteros...\n";
    Arrays<char>::show(matrix2,false);

    cout << "Probando inicialización de arreglo con valores nulos... ";
    Arrays<char>::init(matrix2);
    cout << "OK\n";

    cout << "Mostrando el arreglo después de la inicialización con valores nulos...\n";
    Arrays<char>::show(matrix2,false);

    cout << "Probando conteo de elementos en matriz de caracteres...\n";
    Arrays<char>::count(matrix2,(char) 0,&cont);
    cout << "El resultado del conteo es: " << cont << "\n";

    delete array;
    delete array2;
    delete matrix;
    delete matrix2;
    
    return 0;
}
