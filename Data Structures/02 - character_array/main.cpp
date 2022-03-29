#include "carray.h"

/*
    Función que recibe un número entero
    y retorna una letra mayúscula de la A
    a la Z calculando su respectivo código
    ASCII en base al módulo 26 del entero
    dado.
*/
char create_letter(int n){
    /*
    Las 26 letras del alfabeto [A...Z]
    corresponden al intervalo de códigos
    ASCII [65...90], es decir, la secuencia
    
    65, 66, 67, 68, ..., 90

    corresponde a 

    A, B, C, D, ..., Z

    Dicha secuencia puede visualizarse como
    sumas del primer número, el 65, más un
    desplazamiento:

    65+0, 65+1, 65+2, 65+3, ..., 65+25

    Por lo que, utilizando el 65 y un número
    en el intervalo [0...25] podemos obtener
    el ASCII de una letra mayúscula.

    Para obtener un dato en el intervalo [0...25]
    a partir del entero recibido, simplemente se
    calcula su módulo 26, debido a la propiedad

    n mod m -> dato en [0...m-1]

    Por lo que:

    n mod 26 -> dato en [0...25]

    Entonces, la fórmula para obtener el código
    ASCII de una letra es

    65 + n%26

    A este resultado, finalmente, se le aplica el
    conversor char() para obtener el caracter
    correspondiente.

    */
    return char(65 + n % 26);
}

int main(void){
    int n = 10;
    //Arreglo utilizado en las pruebas
    char* array;
    //Segundo arreglo utilizado en la prueba
    //de creción de copia
    char* array2;

    cout << "Probando creación de arreglo... ";
    //Quemado a 10 posiciones ya que es solo para
    //propósitos ilustrativos
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
        //Se coloca la letra que se obtiene al enviar
        //el valor del iterador a nuestra función para
        //obtener una letra mayúscula. Nuevamente, esto
        //es sólo para propósitos ilustrativos.
        insert(array,i,create_letter(i));
    cout << "OK\n";

    cout << "Mostrando primeras posiciones del arreglo...\n";
    cout << array[0] << " - " << array[1] << " - " << array[2] << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    cout << "Resultado de búsqueda de dato existente: " << search(array, n, create_letter(5)) << "\n"; //Sé que la letra obtenida a partir del número 5 está en el arreglo
    cout << "Resultado de búsqueda de dato no existente: " << search(array, n, '#') << "\n";           //Sé que el caracter '#' no está en el arreglo

    cout << "Provocando una repetición de dato en el arreglo... ";
    //Esto es para hacer más representativa la prueba de conteo
    insert(array,7,create_letter(3));
    cout << "OK\n";

    cout << "Probando conteo de elementos en arreglo...\n";
    //Cuento ocurrencias del dato que ahora está repetido
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
