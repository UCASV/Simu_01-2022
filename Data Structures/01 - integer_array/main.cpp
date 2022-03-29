#include "iarray.h"

int main(void){
    int n = 10;
    //Arreglo utilizado en las pruebas
    int* array;
    //Segundo arreglo utilizado en la prueba
    //de creción de copia
    int* array2;

    cout << "Probando creación de arreglo... ";
    //Quemado a 10 posiciones ya que es solo para
    //propósitos ilustrativos
    array = create(n);
    cout << "OK\n";

    cout << "Probando inserción en arreglo... ";
    //array[3] = 145; //También funciona
    insert(array,3,145);
    cout << "OK\n";

    cout << "Mostrando valor insertado...\n";
    cout << "El valor insertado es: " << array[3] << "\n";

    cout << "Sobreescribiendo valor insertado anteriormente... ";
    insert(array, 3, 225);
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
        //Se coloca directamente el valor del iterador
        //una vez más, ya que es puramente ilustrativo
        insert(array,i,i);
    cout << "OK\n";

    cout << "Mostrando primeras posiciones del arreglo...\n";
    cout << array[0] << " - " << array[1] << " - " << array[2] << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    cout << "Resultado de búsqueda de dato existente: " << search(array, n, 5) << "\n";     //Sé que el 5 está en el arreglo
    cout << "Resultado de búsqueda de dato no existente: " << search(array, n, 45) << "\n"; //Sé que el 45 no está en el arreglo

    cout << "Provocando una repetición de dato en el arreglo... ";
    //Esto es para hacer más representativa la prueba de conteo
    insert(array,7,3);
    cout << "OK\n";

    cout << "Probando conteo de elementos en arreglo...\n";
    //Cuento ocurrencias del dato que ahora está repetido
    cout << "El resultado del conteo es: " << count(array, n, 3) << "\n";

    cout << "Probando creación de copia del arreglo... ";
    array2 = create_copy(array, n);
    cout << "OK\n";

    cout << "Repetición del conteo utilizando la copia...\n";
    cout << "El resultado del conteo en la copia es: " << count(array2, n, 3) << "\n";

    cout << "Probando inversión del arreglo... ";
    array = reverse(array, n);
    cout << "OK\n";

    cout << "Mostrando primeras posiciones del arreglo invertido...\n";
    cout << array[0] << " - " << array[1] << " - " << array[2] << "\n";

    return 0;
}
