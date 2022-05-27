#include "point.h"

class FEMNode{
    private:
        int ID;
        Point* P;

    public:
        FEMNode(){}
        FEMNode(int identifier, Point* punto){
            ID = identifier;
            P = punto;
        }

        void set_ID(int identifier){
            ID = identifier;
        }
        void set_Point(Point* punto){
            P = punto;
        }
        int get_ID(){
            return ID;
        }
        Point* get_Point(){
            return P;
        }
};