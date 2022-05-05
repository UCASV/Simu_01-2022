#include <iostream>
#include <string>

using namespace std;

#include "headers/staticDS.h"

/*
    La clase Arrays se ha definido exclusivamente con
    métodos y atributos estáticos, ya que se ha concebido
    como una clase utilitaria.

    C++ requiere, para los atributos estáticos, que se
    realice, antes del proceso, una asignación para que
    se genere el espacio de memoria correspondiente.

    En este escenario, ref es de tipo Data, que es una struct,
    y es un atributo estático de la clase Arrays, por lo que
    comenzamos por asignarle un struct vacío.

    La sintaxis de esta asignación es:

            <tipo> <Clase>::<atributo> = <valor_nulo>;

    Para el caso:
        - <tipo> es Data.
        - Clase es Arrays.
        - <atributo> es ref.
        - <valor_nulo>, por ser un struct, requiere una
          instanciación vacía de la misma haciendo uso
          de un constructor genérico.

    Por último, dado que Arrays es un template, es necesario
    realizar esta instanciación establecienco el "meta-parámetro";
    sin embargo, ya que el proceso no ha comenzado aún no está
    definido el tipo de dato concreto a utilizar, por lo que
    se "acarrea" el template.
*/
template <typename type>
Data Arrays<type>::ref = Data();

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
    //Conjunto de variables auxiliares que se utilizarán
    //en el proceso ilustrativo.
    int n = 5, f = 3, c = 4, val;
    int n2, f2, c2, cont;
    bool bval;
    char cval;

    /*
        A partir de este momento, toda operación con estructuras
        de datos estáticas se hará a través de la clase utilitaria
        Arrays.

        Para hacer el proceso completamente transparente al "cliente",
        que en este caso es el proceso ilustrativo de main, se trabaja
        haciendo uso de una clase genérica llamada simplemente Array.

        El "cliente" no deberá preocuparse por las diferecias de uso
        e implementación entre arreglos unidimensionales y bidimensionales,
        la clase utilitaria se encargará de todo esto.

        Como Arrays es un template, para su uso deberá especificarse el
        tipo de dato a utilizar mediante un "meta-parámetro".
    */

    /*
        Toda estructura estática se maneja mediante un objeto Array,
        que generaliza el concepto, dejando el detalle de diferenciación
        y de implementación a la clase utilitaria Arrays.

        Todos los objetos serán creados en Arrays mediante el operador
        'new', el cual devuelve un puntero al objeto creado, por ende,
        todos los Array se manejan por dirección, y se declaran acá
        los respectivos punteros.
    */

    //Se preparan punteros para dos Array de enteros que se manejarán
    //unidimensionalmente. El segundo es exclusivo para la prueba del
    //proceso de creación de copia.
    Array<int>* array; Array<int>* array2;
    //Se preparan punteros para dos Array de caracteres que se manejarán
    //bidimensionalmente. El segundo es exclusivo para la prueba del
    //proceso de creación de copia.
    Array<char>* matrix; Array<char>* matrix2;

    cout << "Probando creación de arreglo de enteros... ";
    //Quemado a 5 posiciones ya que es solo para
    //propósitos ilustrativos
    /*
        El objeto Array será creado en Arrays, pero para poder tener acceso
        a la asignación correspondiente, el puntero local debe enviarse
        **por referencia** usando el operador de dirección '&'.
    */
    Arrays<int>::create(&array, n);
    cout << "OK\n";

    cout << "Probando inserción en arreglo de enteros... ";
    Arrays<int>::insert(array,2,5); //Se inserta un 5 en la posición 2
    cout << "OK\n";

    cout << "Mostrando valor insertado...\n";
    /*
        Para mantener una perspectiva estricta en el uso de la clase
        utilitaria, en el caso de operaciones que proveen un resultado
        también se delega la asignación a Arrays, requiriendo entonces el
        envío **por referencia** de la variable en la que queremos guardar
        el resultado.

        Esto aplica a todas las operaciones de Arrays que generan resultados
        de algún tipo, y se verá reflejado en todas las instrucciones a
        continuación que utilicen operaciones de esta naturaleza.

        Esto puede ser opcional dependiendo de la implementación,
        permitiendo que la asignación sea local y que la clase utilitaria sí
        retorne datos.
    */
    Arrays<int>::extract(array,2,&val); //Se extrae el dato de la posición 2 y se almacena en val
    cout << "El valor insertado es: " << val << "\n";

    cout << "Probando eliminación de arreglo de enteros... ";
    Arrays<int>::destroy(array);
    cout << "OK\n";

    cout << "Creando nuevo arreglo de enteros... ";
    Arrays<int>::create(&array,n+3);
    cout << "OK\n";

    cout << "Probando inserción en nuevo arreglo de enteros... ";
    Arrays<int>::insert(array,5,15); //Se inserta un 15 en la posición 5
    cout << "OK\n";

    cout << "Mostrando nuevo valor insertado...\n";
    Arrays<int>::extract(array,5,&val); //Se extrae el dato de la posición 5 y se almacena en val
    cout << "El valor insertado es: " << val << "\n";

    cout << "Obteniendo dimensiones del arreglo de enteros...\n";
    //Para el caso de un arreglo, getDim retorna su longitud
    Arrays<int>::getDim(array,&n2);
    cout << "La longitud del arreglo es: " << n2 << "\n";

    cout << "Llenando arreglo de enteros con valores... ";
    for(int i = 0; i < n2; i++)
        //Se coloca directamente el valor del iterador
        //ya que es puramente ilustrativo
        Arrays<int>::insert(array,i,i); //Se coloca el valor i en la posición i
    cout << "OK\n";

    cout << "Mostrando el arreglo de enteros...\n";
    Arrays<int>::show(array,false); //false indica que no se necesita modo VERBOSE

    cout << "Probando inversión del arreglo de enteros... ";
    Arrays<int>::reverse(array);
    cout << "OK\n";

    cout << "Mostrando el arreglo invertido...\n";
    Arrays<int>::show(array,false);

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    Arrays<int>::search(array,4,&bval); //Se busca el 4 y el resultado se almacena en bval, se sabe que 4 sí está en el arreglo
    cout << "Resultado de búsqueda de dato existente: " << bval << "\n";
    Arrays<int>::search(array,54,&bval); //Se busca el 54 y el resultado se almacena en bval, se sabe que 54 no está en el arreglo
    cout << "Resultado de búsqueda de dato no existente: " << bval << "\n";

    cout << "Mostrando el arreglo de enteros en modo VERBOSE...\n";
    Arrays<int>::show(array,true); //true indica la ejecución del modo VERBOSE
    
    cout << "Probando creación de copia del arreglo de enteros... ";
    //array se envía **por valor**, ya que en Arrays sólo se utilizará su contenido
    //arra2 se envía **por referencia**, ya que necesito acceso local a la asignación que Arrays ejecutará
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
    Arrays<int>::count(array2,0,&cont); //Se cuentan las ocurrencias del 0 y el resultado se almacena en cont
    cout << "El resultado del conteo es: " << cont << "\n";

    cout << "\n======================================\n\n";

    cout << "Probando creación de matriz de caracteres... ";
    //Quemado a 3 filas y 4 columnas ya que es solo para
    //propósitos ilustrativos
    /*
        El objeto Array será creado en Arrays, pero para poder tener acceso
        a la asignación correspondiente, el puntero local debe enviarse
        **por referencia** usando el operador de dirección '&'.

        Para el cliente, este proceso es de la misma naturaleza que la creción
        de un arreglo, ya que todo el detalle se ha delegado a la clase Arrays.
    */
    Arrays<char>::create(&matrix,f,c);
    cout << "OK\n";

    cout << "Probando inserción en matriz de caracteres... ";
    Arrays<char>::insert(matrix,2,2,'H'); //Se inserta una 'H' en la celda (2,2)
    cout << "OK\n";

    cout << "Mostrando valor insertado...\n";
    Arrays<char>::extract(matrix,2,2,&cval); //Se extrae el dato de la celda (2,2) y se almacena en cval
    cout << "El valor insertado es: " << cval << "\n";

    cout << "Probando eliminación de matriz de caracteres... ";
    Arrays<char>::destroy(matrix);
    cout << "OK\n";

    cout << "Creando nueva matriz de caracteres... ";
    Arrays<char>::create(&matrix,f+3,c+3);
    cout << "OK\n";

    cout << "Probando inserción en nueva matriz de caracteres... ";
    Arrays<char>::insert(matrix,5,5,'K'); //Se inserta una 'K' en la celda (5,5)
    cout << "OK\n";

    cout << "Mostrando nuevo valor insertado...\n";
    Arrays<char>::extract(matrix,5,5,&cval); //Se extrae el dato de la celda (5,5) y se almacena en cval
    cout << "El valor insertado es: " << cval << "\n";

    cout << "Obteniendo dimensiones de la matriz de caracteres...\n";
    //Para el caso de una matriz, getDim retorna número de filas y número de
    //columnas
    Arrays<char>::getDim(matrix,&f2,&c2);
    cout << "Las dimensiones de la matriz son: " << f2 << "x" << c2 << "\n";

    cout << "Llenando matriz de caracteres con valores... ";
    //Se utiliza el recorrido de matriz mediante un sólo iterador
    //La lógica de este proceso se explica en los archivos del chapter "05 - array2Dv2"
    //y también en el archivo local "headers/Array2D.h"
    for(int i = 0; i < f2*c2; i++)
        //Se almacena la letra mayúscula obtenida al enviar el valor del iterador
        //a nuestra función create_letter en la celda (i/c2,i%c2)
        //Nuevamente, esto es sólo para propósitos ilustrativos
        Arrays<char>::insert(matrix,i/c2,i%c2,create_letter(i));
    cout << "OK\n";

    cout << "Mostrando la matriz de caracteres...\n";
    Arrays<char>::show(matrix,false); //false indica que no se necesita modo VERBOSE

    cout << "Probando inversión (reverso) de una matriz de caracteres...\n";
    Arrays<char>::reverse(matrix); //esto es solo para mostrar que es un proceso no válido

    cout << "Mostrando resultados de búsqueda de dato existente y dato no existente...\n";
    //Se busca la letra generada a partir del número 4 y el resultado se almacena en bval, se sabe que dicha letra sí está en la matriz
    Arrays<char>::search(matrix,create_letter(4),&bval);
    cout << "Resultado de búsqueda de dato existente: " << bval << "\n";
    Arrays<char>::search(matrix,'#',&bval); //Se busca el '#' y el resultado se almacena en bval, se sabe que '#' no está en la matriz
    cout << "Resultado de búsqueda de dato no existente: " << bval << "\n";

    cout << "Mostrando el arreglo de enteros en modo VERBOSE...\n";
    Arrays<char>::show(matrix,true); //true indica la ejecución del modo VERBOSE
    
    cout << "Probando creación de copia de la matriz de caracteres... ";
    //matrix se envía **por valor**, ya que en Arrays sólo se utilizará su contenido
    //matrix2 se envía **por referencia**, ya que necesito acceso local a la asignación que Arrays ejecutará
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
    Arrays<char>::count(matrix2,(char) 0,&cont); //Se cuentan las ocurrencias del 0 convertido a caracter y el resultado se almacena en cont
    cout << "El resultado del conteo es: " << cont << "\n";

    //Se eliminan todos los objetos creados
    //Esto es para liberar la memoria asignada al programa
    delete array;
    delete array2;
    delete matrix;
    delete matrix2;
    
    return 0;
}
