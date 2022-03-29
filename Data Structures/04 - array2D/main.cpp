#include "matrix.h"

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
    int filas = 3, columnas = 4;

    /*
        Esta vez, las estructuras de datos se declaran como
        punteros dobles, ya que la estructura interna de una matriz
        es un arreglo principal de punteros simples, donde cada uno
        apunta a un arreglo que corresponde a una de las filas de la
        matriz:

        int** matriz -->  [ int* ]-[ int* ]-[ int* ]     //Arreglo principal
                             |        |        |
                             v        v        v
                          [ int ]  [ int ]  [ int ]
                          [ int ]  [ int ]  [ int ]
                          [ int ]  [ int ]  [ int ]
    */

    //Matriz utilizada en las pruebas con tipo int
    int** matrix;
    //Matriz utilizada en la prueba
    //de creación de copia con tipo int
    int** matrix2;
    //Matriz utilizada en las pruebas con tipo char
    char** matrix3;
    //Matriz utilizada en la prueba
    //de creación de copia con tipo char
    char** matrix4;

    cout << "Probando creación de matriz de enteros... ";
    //Quemada a 3 filas y 4 columnas ya que es solo para
    //propósitos ilustrativos
    //Dado que las funciones en "matrix.h" son templates,
    //es necesario definir el tipo que el template de la
    //función create() utilizará.
    //Para el caso definimos el tipo int colocándolo como
    //un "meta-parámetro" haciendo uso de las brackets < >
    matrix = create<int>(filas, columnas);
    cout << "OK\n";

    //De acá en adelante, toda llamada a una función de
    //"matrix.h" requerirá el "meta-parámetro" para "instanciar"
    //el template respectivo.

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
    for(int i = 0; i < filas; i++)
        for(int j = 0; j < columnas; j++)
            //Se coloca la suma de los iteradores como contenido
            //ya que es puramente ilustrativo
            insert<int>(matrix,i,j,i+j);
    cout << "OK\n";

    cout << "Mostrando primeras posiciones de la matriz de enteros...\n";
    cout << matrix[0][0] << " - " << matrix[0][1] << " - " << matrix[0][2] << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    cout << "Resultado de búsqueda de dato existente: " << search<int>(matrix, filas, columnas, 3) << "\n";     //Sé que el 3 se encuentra en la matriz
    cout << "Resultado de búsqueda de dato no existente: " << search<int>(matrix, filas, columnas, 87) << "\n"; //Sé que el 87 no se encuentra en la matriz

    cout << "Provocando una repetición de dato en la matriz de enteros... ";
    //Esto es para hacer más representativa la prueba de conteo
    insert<int>(matrix,2,3,3);
    cout << "OK\n";

    cout << "Probando conteo de elementos en matriz de enteros...\n";
    //Cuento ocurrencias del dato repetido
    cout << "El resultado del conteo es: " << count<int>(matrix, filas, columnas, 3) << "\n";

    cout << "Probando creación de copia de la matriz de enteros... ";
    matrix2 = create_copy<int>(matrix, filas, columnas);
    cout << "OK\n";

    cout << "Repetición del conteo utilizando la copia...\n";
    cout << "El resultado del conteo en la copia es: " << count<int>(matrix2, filas, columnas, 3) << "\n";

    
    cout << "\n======================================\n\n";

    //Se realizan ahora las pruebas con un tipo de dato distinto, en este
    //caso el tipo char, estableciéndolo a través del "meta-parámetro".

    cout << "Probando creación de matriz de caracteres... ";
    //Quemada a 3 filas y 4 columnas ya que es solo para
    //propósitos ilustrativos
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
    for(int i = 0; i < filas; i++)
        for(int j = 0; j < columnas; j++)
            //Se coloca como contenido el resultado de enviar
            //la suma de los iteradores a nuestra función para
            //obtener una letra mayúscula. Es suficiente, ya que
            //es un proceso ilustrativo.
            insert<char>(matrix3,i,j,create_letter(i+j));
    cout << "OK\n";

    cout << "Mostrando primeras posiciones de la matriz de caracteres...\n";
    cout << matrix3[0][0] << " - " << matrix3[0][1] << " - " << matrix3[0][2] << "\n";

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    cout << "Resultado de búsqueda de dato existente: " << search<char>(matrix3, filas, columnas, create_letter(3)) << "\n"; //Sé que la letra obtenida al enviar un 3 a la función create_letter está en la matriz
    cout << "Resultado de búsqueda de dato no existente: " << search<char>(matrix3, filas, columnas, '#') << "\n";           //Sé que el caracter '#' no está en la matriz

    cout << "Provocando una repetición de dato en la matriz de caracteres... ";
    //Esto es para hacer más representativa la prueba de conteo
    insert<char>(matrix3,2,3,create_letter(3));
    cout << "OK\n";

    cout << "Probando conteo de elementos en matriz de caracteres...\n";
    //Cuento ocurrencias del dato repetido
    cout << "El resultado del conteo es: " << count<char>(matrix3, filas, columnas, create_letter(3)) << "\n";

    cout << "Probando creación de copia de la matriz de caracteres... ";
    matrix4 = create_copy<char>(matrix3, filas, columnas);
    cout << "OK\n";

    cout << "Repetición del conteo utilizando la copia...\n";
    cout << "El resultado del conteo en la copia es: " << count<char>(matrix4, filas, columnas, create_letter(3)) << "\n";

    return 0;
}
