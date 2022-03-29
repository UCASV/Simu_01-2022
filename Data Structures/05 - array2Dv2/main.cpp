#include "matrix_v2.h"

/*
    Esta versión trabaja el recorrido de la matriz
    con un solo iterador 'for' utilizando un sólo índice k.

    La equivalencia entre los índices del esquema con dos
    iteradores (i,j) y el índice del esquema con un iterador
    (k) es el siguiente:

        i = k \ ncols
        j = k % ncols

    Donde el operador '\' hace referencia a la "División Entera".

    Estas equivalencias surgen del análisis siguiente:

              Usando (i,j)                          Usando k

          0        1        2                  0        1        2
    0 [ (0,0) ][ (0,1) ][ (0,2) ]        0 [   0   ][   1   ][   2   ]
    1 [ (1,0) ][ (1,1) ][ (1,2) ]  <-->  1 [   3   ][   4   ][   5   ]
    2 [ (2,0) ][ (2,1) ][ (2,2) ]        2 [   6   ][   7   ][   8   ]

    Observando las columnas:

          0        1        2                  0        1        2
    0 [ (_,0) ][ (_,1) ][ (_,2) ]        0 [   0   ][   1   ][   2   ]
    1 [ (_,0) ][ (_,1) ][ (_,2) ]  <-->  1 [   3   ][   4   ][   5   ]
    2 [ (_,0) ][ (_,1) ][ (_,2) ]        2 [   6   ][   7   ][   8   ]

    Puede observarse que para cada fila se repite el ciclo {0,1,2}

    Como ya sabemos, usando la propiedad de la operación módulo podemos
    generar ciclos:
                        n mod m --> dato en [0...m-1]

    Por lo que, para tener un dato en {0,1,2}, hacemos módulo 3, que es
    lo mismo que decir, hacemos módulo <ncols>.

    Usando el iterador k como input del proceso, obtenemos la equivalencia
    para el iterador j:
                                j = k % ncols

    Ahora, observemos las filas:

          0        1        2                  0        1        2
    0 [ (0,_) ][ (0,_) ][ (0,_) ]        0 [   0   ][   1   ][   2   ]
    1 [ (1,_) ][ (1,_) ][ (1,_) ]  <-->  1 [   3   ][   4   ][   5   ]
    2 [ (2,_) ][ (2,_) ][ (2,_) ]        2 [   6   ][   7   ][   8   ]

    El patrón esta vez corresponde a mantener el número de la fila como
    el índice i.

    Observando los valores de k, podemos ver lo siguiente:

          0        1        2                   0          1          2
    0 [ (0,_) ][ (0,_) ][ (0,_) ]        0 [    0    ][    1    ][    2    ]
    1 [ (1,_) ][ (1,_) ][ (1,_) ]  <-->  1 [   0+3   ][   1+3   ][   2+3   ]
    2 [ (2,_) ][ (2,_) ][ (2,_) ]        2 [   0+6   ][   1+6   ][   2+6   ]

    Trabajándolo un poco más:

          0        1        2                   0            1            2
    0 [ (0,_) ][ (0,_) ][ (0,_) ]        0 [   0+3*0   ][   1+3*0   ][   2+3*0   ]
    1 [ (1,_) ][ (1,_) ][ (1,_) ]  <-->  1 [   0+3*1   ][   1+3*1   ][   2+3*1   ]
    2 [ (2,_) ][ (2,_) ][ (2,_) ]        2 [   0+3*2   ][   1+3*2   ][   2+3*2   ]

    El patrón que necesitamos ha aparecido a la derecha como el factor del 3,
    generalizando de la forma:
                                    n+3*n
    
    Para extraer la n de la expresión anterior, aplicamos división entera entre 3:

                                (n + 3*n) \ 3 = n
            { (n + 3*n) \ 3 = floor( (n + 3*n) / 3 ) = floor( n/3 + n ) = n }

    Como la expresión n+3*n viene de la k, y como el 3 corresponde a <ncols>, 
    podemos definir la equivalencia con el índice i como:
                                
                                i = k \ ncols

    Por último, se observa que la k en el ejemplo varía desde o hasta un valor de 8,
    este valor de 8 se puede reescribir como 9 -1 , el cual a su vez se puede reescribir
    como 3*3 - 1, lo que, generalizando, es equivalente a decir <nrows>*<ncols> - 1.

    Por lo que la variación de la k se generaliza como:

                    k pertenece al intervalo [ 0 ... nrows*ncols-1 ]
*/

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
    for(int i = 0; i < filas*columnas; i++)
        //Se coloca el valor del iterador como contenido
        //ya que es puramente ilustrativo
        insert<int>(matrix,i/columnas,i%columnas,i);
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
    for(int i = 0; i < filas*columnas; i++)
        //Se coloca como contenido el resultado de enviar
        //el valor del iterador a nuestra función para
        //obtener una letra mayúscula. Es suficiente, ya que
        //es un proceso ilustrativo.
        insert<char>(matrix3,i/columnas,i%columnas,create_letter(i));
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
