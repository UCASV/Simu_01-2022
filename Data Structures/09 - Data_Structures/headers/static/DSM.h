/*
    Implementación para una estructura de datos estática biidimensional,
    es decir, para una matriz.

    Se define la implementación como independiente del tipo de
    dato a almacenar mediante el uso de template.
*/
template <typename T>
/*
    En C++, la implementación se maneja como una herencia,
    de modo que DSM hereda de staticDS_2D, ya que es la que provee
    su funcionalidad básica.

    El indicador de visibilidad 'public' indica que DSM tendrá
    acceso a todos los métodos de staticDS_2D manteniendo su
    visibilidad original.

    Dado que staticDS_2D es un template, debe indicarse
    el tipo de dato a utilizar mediante un "meta-parámetro". Sin
    embargo, el tipo de dato aún no ha sido definido, ya que DSM
    también es un template, por lo que el "meta-parámetro" es el
    tipo de dato genérico local <T>.
*/
class DSM: public staticDS_2D<T> {
    /*
        Como atributo privado local se manejará la matriz de datos tipo
        <T> como tal. Se declara un puntero doble ya que se manejará
        por dirección el bloque de memoria correspondiente.

        Recordando, la estructura en memoria corresponde a un arreglo
        principal de punteros simples, donde cada uno apunta a un arreglo
        que corresponde a una de las filas de la matriz:

        int** matriz -->  [ int* ]-[ int* ]-[ int* ]     //Arreglo principal
                             |        |        |
                             v        v        v
                          [ int ]  [ int ]  [ int ]
                          [ int ]  [ int ]  [ int ]
                          [ int ]  [ int ]  [ int ]

        Los otros atributos privados locales son el número de filas <nrows>
        y el número de columnas <ncols> de la matriz, como datos acompañantes
        para controlar procesos de recorrido.
    */
    private:
        T** matrix;
        int nrows, ncols;

    //Se procede a la implementación como tal de los métodos de la interfaz
    //override indica la respectiva sobreescritura de cada método
    public:
        /*
            Función que retorna la categoría de la matriz local.

            La función hace uso de la enumeración category
            definida en "SDDS.h".
        */
        category getCategory() override {
            //Se retorna MATRIX ya que localmente manejamos una matriz
            return MATRIX;
        }
        //TODO: Continuar la comentada desde aquí
        void destroy() override {
            for(int i = 0; i < nrows; i++)
                free(*(matrix+i));
            free(matrix);
        }
        bool search(T value) override {
            bool ans = false;
            for(int i = 0; i < nrows*ncols; i++)
                if(matrix[i/ncols][i%ncols] == value){
                    ans = true;
                    break;
                }
            return ans;
        }
        int count(T value) override {
            int cont = 0;
            for(int i = 0; i < nrows*ncols; i++)
                if(matrix[i/ncols][i%ncols] == value) cont++;
            return cont;
        }
        void show(bool verbose) override {
            if(verbose)
                for(int i = 0; i < nrows*ncols; i++)
                    cout << "Element in cell [ " << i/ncols+1 << ", " << i%ncols+1 << " ] is: " << matrix[i/ncols][i%ncols] << "\n";
            else{
                cout << "[\n";
                for(int i = 0; i < nrows; i++){
                    cout << "[ ";
                    for(int j = 0; j < ncols-1; j++)
                        cout << matrix[i][j] << ", ";
                    cout << matrix[i][ncols-1] << " ]\n";
                }
                cout << "]\n";
            }
        }

        void create(Data dim) override {
            nrows = dim.n;
            ncols = dim.m;
            matrix = (T**) malloc(sizeof(T*)*nrows);
            for(int i = 0; i < nrows; i++)
                *(matrix+i) = (T*) malloc(sizeof(T)*ncols);
        }
        Data extension() override {
            Data dim;
            dim.n = nrows; dim.m = ncols;
            return dim;
        }
        void insert(Data pos, T value) override {
            matrix[pos.n][pos.m] = value;
        }
        T extract(Data pos) override {
            return matrix[pos.n][pos.m];
        }
};
