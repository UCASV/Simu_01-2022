/*
    Clase utilizada para representar un punto bidimensional
    mediante sus coordenadas en el plano cartesiano.
*/
class Point{
    private:
        /*
            Los atributos privados son las coordenadas X e Y
            que conforman el punto.
        */
        float x_coordinate;
        float y_coordinate;

    public:
        /********** Constructores ************/
        /*
            Se proveen dos constructores:
            - Uno genérico que no inicializa los atributos.
            - Uno que recibe datos para inicializar los atributos.
        */
        Point(){}
        Point(int x, int y){
            x_coordinate = x;
            y_coordinate = y;
        }
        
        /********* Setters y Getters para los atributos *************/
        void set_x(float x){
            x_coordinate = x;
        }
        void set_y(float y){
            y_coordinate = y;
        }
        float get_x(){
            return x_coordinate;
        }
        float get_y(){
            return y_coordinate;
        }
};