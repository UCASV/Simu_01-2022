#include "array.h"

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
    //Arreglo utilizado en las pruebas con tipo int
    int* array;
    //Arreglo utilizado en la prueba
    //de creción de copia con tipo int
    int* array2;
    //Arreglo utilizado en las pruebas con tipo char
    char* array3;
    //Arreglo utilizado en la prueba
    //de creción de copia con tipo char
    char* array4;

    cout << "Probando creación de arreglo de enteros... ";
    //Quemado a 10 posiciones ya que es solo para
    //propósitos ilustrativos
    //Dado que las funciones en "array.h" son templates,
    //es necesario definir el tipo que el template de la
    //función create() utilizará.
    //Para el caso definimos el tipo int colocándolo como
    //un "meta-parámetro" haciendo uso de las brackets < >
    array = create<int>(n);
    cout << "OK\n";

    //De acá en adelante, toda llamada a una función de
    //"array.h" requerirá el "meta-parámetro" para "instanciar"
    //el template respectivo.

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
        //Se coloca directamente el valor del iterador
        //ya que es puramente ilustrativo
        insert<int>(array,i,i);
    cout << "OK\n";

    cout << "Mostrando primeras posiciones del arreglo de enteros...\n";
    cout << array[0] << " - " << array[1] << " - " << array[2] << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    cout << "Resultado de búsqueda de dato existente: " << search<int>(array, n, 5) << "\n";     //Sé que el 5 está en el arreglo
    cout << "Resultado de búsqueda de dato no existente: " << search<int>(array, n, 45) << "\n"; //Sé que el 45 no está en el arreglo

    cout << "Provocando una repetición de dato en el arreglo de enteros... ";
    //Esto es para hacer más representativa la prueba de conteo
    insert<int>(array,7,3);
    cout << "OK\n";

    cout << "Probando conteo de elementos en arreglo de enteros...\n";
    //Cuento ocurrencias del dato que ahora está repetido
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

    //Se realizan ahora las pruebas con un tipo de dato distinto, en este
    //caso el tipo char, estableciéndolo a través del "meta-parámetro".

    cout << "Probando creación de arreglo de caracteres... ";
    //Quemado a 10 posiciones ya que es solo para
    //propósitos ilustrativos
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
        //Se coloca la letra que se obtiene al enviar
        //el valor del iterador a nuestra función para
        //obtener una letra mayúscula. Nuevamente, esto
        //es sólo para propósitos ilustrativos.
        insert<char>(array3,i,create_letter(i));
    cout << "OK\n";

    cout << "Mostrando primeras posiciones del arreglo de caracteres...\n";
    cout << array3[0] << " - " << array3[1] << " - " << array3[2] << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    cout << "Resultado de búsqueda de dato existente: " << search<char>(array3, n, create_letter(5)) << "\n"; //Sé que la letra obtenida a partir del número 5 está en el arreglo
    cout << "Resultado de búsqueda de dato no existente: " << search<char>(array3, n, '#') << "\n";           //Sé que el caracter '#' no está en el arreglo

    cout << "Provocando una repetición de dato en el arreglo de caracteres... ";
    //Esto es para hacer más representativa la prueba de conteo
    insert<char>(array3,7,create_letter(3));
    cout << "OK\n";

    cout << "Probando conteo de elementos en arreglo de caracteres...\n";
    //Cuento ocurrencias del dato que ahora está repetido
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
