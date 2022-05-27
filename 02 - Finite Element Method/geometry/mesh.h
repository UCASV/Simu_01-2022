#include "element.h"

enum parameter {DENSITY,SPECIFIC_HEAT,THERMAL_CONDUCTIVITY,HEAT_SOURCE,DIRICHLET_VALUE,NEUMANN_VALUE,INITIAL_TEMPERATURE,TIME_STEP,INITIAL_TIME,FINAL_TIME};
enum quantity {NUM_NODES,NUM_ELEMENTS,NUM_DIRICHLET_BCs,NUM_NEUMANN_BCs};
enum condition {DIRICHLET,NEUMANN};

class Mesh{
    private:
        DS<float>* parameters;
        DS<int>* quantities;
        DS<FEMNode*>* nodes;
        DS<Element*>* elements;
        DS<FEMNode*>* dirichlet_conditions;
        DS<FEMNode*>* neumann_conditions;

    public:
        Mesh(){
            SDDS<float>::create(&parameters,10,ARRAY);
            SDDS<int>::create(&quantities,4,ARRAY);
        }

        ~Mesh(){
            SDDS<float>::destroy(parameters);
            SDDS<int>::destroy(quantities);
            SDDS<FEMNode*>::destroy(nodes);
            SDDS<Element*>::destroy(elements);
            SDDS<FEMNode*>::destroy(dirichlet_conditions);
            SDDS<FEMNode*>::destroy(neumann_conditions);
        }

        void init_geometry(){
            int n;
            SDDS<int>::extract(quantities,NUM_NODES,&n);
            SDDS<FEMNode*>::create(&nodes,n,ARRAY);
            SDDS<int>::extract(quantities,NUM_ELEMENTS,&n);
            SDDS<Element*>::create(&elements,n,ARRAY);
            SDDS<int>::extract(quantities,NUM_DIRICHLET_BCs,&n);
            SDDS<FEMNode*>::create(&dirichlet_conditions,n,ARRAY);
            SDDS<int>::extract(quantities,NUM_NEUMANN_BCs,&n);
            SDDS<FEMNode*>::create(&neumann_conditions,n,ARRAY);
        }

        void set_parameters(float rho, float Cp, float k, float Q, float Td, float Tn, float initial_T, float delta_t, float t_0, float t_f){
            SDDS<float>::insert(parameters,DENSITY,rho);
            SDDS<float>::insert(parameters,SPECIFIC_HEAT,Cp);
            SDDS<float>::insert(parameters,THERMAL_CONDUCTIVITY,k);
            SDDS<float>::insert(parameters,HEAT_SOURCE,Q);
            SDDS<float>::insert(parameters,DIRICHLET_VALUE,Td);
            SDDS<float>::insert(parameters,NEUMANN_VALUE,Tn);
            SDDS<float>::insert(parameters,INITIAL_TEMPERATURE,initial_T);
            SDDS<float>::insert(parameters,TIME_STEP,delta_t);
            SDDS<float>::insert(parameters,INITIAL_TIME,t_0);
            SDDS<float>::insert(parameters,FINAL_TIME,t_f);
        }
        float get_parameter(parameter indicator){
            float param;
            SDDS<float>::extract(parameters,indicator,&param);
            return param;
        }

        void set_quantities(int nnodes, int nelems, int ndirichlet, int nneumann){
            SDDS<int>::insert(quantities,NUM_NODES,nnodes);
            SDDS<int>::insert(quantities,NUM_ELEMENTS,nelems);
            SDDS<int>::insert(quantities,NUM_DIRICHLET_BCs,ndirichlet);
            SDDS<int>::insert(quantities,NUM_NEUMANN_BCs,nneumann);
        }
        int get_quantity(quantity indicator){
            int qty;
            SDDS<int>::extract(quantities,indicator,&qty);
            return qty;
        }

        void add_node(FEMNode* node){
            SDDS<FEMNode*>::insert(nodes,node);
        }
        FEMNode* get_node(int ID){
            int n;
            SDDS<int>::extract(quantities,NUM_NODES,&n);
            for(int i = 0; i < n; i++){
                FEMNode* node;
                SDDS<FEMNode*>::extract(nodes,i,&node);
                if(node->get_ID() == ID) return node;
            }
        }

        void add_element(Element* elem){
            SDDS<Element*>::insert(elements,elem);
        }
        Element* get_element(int ID){
            int n;
            SDDS<int>::extract(quantities,NUM_ELEMENTS,&n);
            for(int i = 0; i < n; i++){
                Element* elem;
                SDDS<Element*>::extract(elements,i,&elem);
                if(elem->get_ID() == ID) return elem;
            }
        }

        void add_dirichlet_cond(FEMNode* node,int i){
            SDDS<FEMNode*>::insert(dirichlet_conditions,i,node);
        }

        void add_neumann_cond(FEMNode* node,int i){
            SDDS<FEMNode*>::insert(neumann_conditions,i,node);
        }

        void get_condition_indices(DS<int>* indices, condition mode){
            int n;
            DS<FEMNode*>* conditions;

            switch(mode){
                case DIRICHLET: {
                    SDDS<int>::extract(quantities,NUM_DIRICHLET_BCs,&n);
                    conditions = dirichlet_conditions;
                    break;
                }
                case NEUMANN: {
                    SDDS<int>::extract(quantities,NUM_NEUMANN_BCs,&n);
                    conditions = neumann_conditions;
                    break;
                }
            }

            FEMNode* node;
            for(int i = 0; i < n; i++){
                SDDS<FEMNode*>::extract(conditions,i,&node);
                SDDS<int>::insert(indices,i,node->get_ID());
            }
        }
};