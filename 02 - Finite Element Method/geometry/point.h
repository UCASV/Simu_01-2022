class Point{
    private:
        float x_coordinate;
        float y_coordinate;

    public:
        Point(){}
        Point(int x, int y){
            x_coordinate = x;
            y_coordinate = y;
        }
        
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