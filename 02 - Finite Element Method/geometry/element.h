#include "mesh_node.h"

class Element{
    private:
        int ID;
        DS<FEMNode*>* nodes;

    public:
        Element(){
            SDDS<FEMNode*>::create(&nodes,3,ARRAY);
        }
        Element(int identifier, FEMNode* node1, FEMNode* node2, FEMNode* node3){
            ID = identifier;
            SDDS<FEMNode*>::create(&nodes,3,ARRAY);
            SDDS<FEMNode*>::insert(nodes,0,node1);
            SDDS<FEMNode*>::insert(nodes,1,node2);
            SDDS<FEMNode*>::insert(nodes,2,node3);
        }

        ~Element(){
            SDDS<FEMNode*>::destroy(nodes);
        }

        void set_ID(int identifier){
            ID = identifier;
        }
        void set_Node(FEMNode* node,int index){
            SDDS<FEMNode*>::insert(nodes,index,node);
        }
        int get_ID(){
            return ID;
        }
        FEMNode* get_Node(int index){
            FEMNode* res;
            SDDS<FEMNode*>::extract(nodes,index,&res);
            return res;
        }
};