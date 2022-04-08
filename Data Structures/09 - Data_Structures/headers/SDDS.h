enum category {ARRAY,MATRIX,SINGLE_LINKED_LIST,DOUBLE_LINKED_LIST,BINARY_SEARCH_TREE,GRAPH};

typedef struct Data{
    int n;
    int m;
    Data(){}
} Data;

template <typename type>
struct Node{
    type data;
};

template <typename type>
struct NodeSL: Node<type>{
    type data;
    NodeSL<type>* next;
};

template <typename type>
struct NodeDL: Node<type>{
    type data;
    NodeDL<type>* prev;
    NodeDL<type>* next;
};

template <typename type>
struct NodeT: Node<type>{
    type data;
    NodeT<type>* parent;
    NodeT<type>* left;
    NodeT<type>* right;
};

template <typename type>
struct NodeG: Node<type>{
    bool entry;
    int id;
    type data;
    NodeSL<NodeG<type>*>* connections;
    NodeG<type>* next;
};

#include "DS.h"
#include "static/DSA.h"
#include "static/DSM.h"
#include "dynamic/DSSL.h"
#include "dynamic/DSDL.h"
#include "dynamic/DST.h"
#include "dynamic/DSG.h"

template <typename type>
class SDDS{
    private:
        static Data ref;

        static void insert_aux(insertable<type>* var, type value){
            var->insert(value);
        }

        static void insert_pos_aux(positionable<type>* var, int n, type value){
            var->insert(n, value);
        }

        static void extract_aux(positionable<type>* var, int pos, type* res){
            *res = var->extract(pos);
        }

        static void extension_aux(measurable* var, int* n){
            *n = var->extension();
        }

        static void reverse_aux(reversible* var){
            var->reverse();
        }

        static void copy_tree(NodeT<type>* O, DST<type>** clone){
            if(O == NULL) return;
            (*clone)->insert(O->data);
            copy_tree(O->left, clone);
            copy_tree(O->right, clone);
        }

        static void extractNode(DS<type>* G, int id, NodeG<type>** node){
            NodeG<type>* graph = (NodeG<type>*) ( (DSG<type>*) G )->getRoot();
            while(graph != NULL){
                if(graph->id == id) break;
                graph = graph->next;
            }
            *node = graph;
        }

        static void insert_connections(DS<type>* G, int id, NodeSL<NodeG<type>*>* C){
            NodeG<type>* graph = (NodeG<type>*) ( (DSG<type>*) G )->getRoot();
            while(graph != NULL){
                if(graph->id == id){
                    graph->connections = C;
                    break;
                }
                graph = graph->next;
            }
        }

    public:
        static void destroy(DS<type>* var){
            var->destroy();
        }
        static void search(DS<type>* var, type value, bool* res){
            *res = var->search(value);
        }
        static void count(DS<type>* var, type value, int* res){
            *res = var->count(value);
        }
        static void show(DS<type>* var, bool verbose){
            var->show(verbose);
        }

        static void create(DS<type>** var, int n, category cat){
            DSA<type>* array = new DSA<type>();
            array->create(n);
            *var = array;
        }
        static void create(DS<type>** var, int nrows, int ncols, category cat){
            DSM<type>* matrix = new DSM<type>();
            ref.n = nrows;
            ref.m = ncols;
            matrix->create(ref);
            *var = matrix;
        }
        static void create(DS<type>** var, category cat){
            switch(cat){
                case SINGLE_LINKED_LIST: {
                    DSSL<type>* SL = new DSSL<type>();
                    SL->create();
                    *var = SL;
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    DSDL<type>* DL = new DSDL<type>();
                    DL->create();
                    *var = DL;
                    break;
                }
                case BINARY_SEARCH_TREE: {
                    DST<type>* T = new DST<type>();
                    T->create();
                    *var = T;
                    break;
                }
                case GRAPH: {
                    DSG<type>* G = new DSG<type>();
                    G->create();
                    *var = G;
                    break;
                }
            }
        }

        static void extension(DS<type>* matrix, int* rows, int* columns){
            ref = ( ( DSM<type>* ) matrix )->extension();
            *rows = ref.n;
            *columns = ref.m;
        }
        static void extension(DS<type>* var, int* n){
            category cat = var->getCategory();
            switch(cat){
                case ARRAY: {
                    extension_aux( ((DSA<type>*) var), n);
                    break;
                }
                case SINGLE_LINKED_LIST: {
                    extension_aux( ((DSSL<type>*) var), n);
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    extension_aux( ((DSDL<type>*) var), n);
                    break;
                }
                case BINARY_SEARCH_TREE: {
                    extension_aux( ((DST<type>*) var), n);
                    break;
                }
                case GRAPH: {
                    extension_aux( ((DSG<type>*) var), n);
                    break;
                }
            }
        }

        static void insert(DS<type>* matrix, int row, int column, type value){
            ref.n = row; ref.m = column;
            ( ( DSM<type>* ) matrix )->insert(ref,value);
        }
        static void insert(DS<type>* var, type value){
            category cat = var->getCategory();
            switch(cat){
                case SINGLE_LINKED_LIST: {
                    insert_aux( ((DSSL<type>*) var), value);
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    insert_aux( ((DSDL<type>*) var), value);
                    break;
                }
                case BINARY_SEARCH_TREE: {
                    insert_aux( ((DST<type>*) var), value);
                    break;
                }
            }
        }
        static void insert(DS<type>* var, int n, type value){
            category cat = var->getCategory();
            switch(cat){
                case ARRAY: {
                    insert_pos_aux( ((DSA<type>*) var), n, value);
                    break;
                }
                case SINGLE_LINKED_LIST: {
                    insert_pos_aux( ((DSSL<type>*) var), n, value);
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    insert_pos_aux( ((DSDL<type>*) var), n, value);
                    break;
                }
                case GRAPH: {
                    insert_pos_aux( ((DSG<type>*) var), n, value);
                    break;
                }
            }
        }

        static void extract(DS<type>* matrix, int row, int column, type* result){
            ref.n = row; ref.m = column;
            *result = ( ( DSM<type>* ) matrix )->extract(ref);
        }
        static void extract(DS<type>* var, int pos, type* res){
            category cat = var->getCategory();
            switch(cat){
                case ARRAY: {
                    extract_aux( ((DSA<type>*) var), pos, res);
                    break;
                }
                case SINGLE_LINKED_LIST: {
                    extract_aux( ((DSSL<type>*) var), pos, res);
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    extract_aux( ((DSDL<type>*) var), pos, res);
                    break;
                }
                case GRAPH: {
                    extract_aux( ((DSG<type>*) var), pos, res);
                    break;
                }
            }
        }

        static void reverse(DS<type>* var){
            category cat = var->getCategory();
            switch(cat){
                case ARRAY: {
                    reverse_aux( ((DSA<type>*) var) );
                    break;
                }
                case SINGLE_LINKED_LIST: {
                    reverse_aux( ((DSSL<type>*) var) );
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    reverse_aux( ((DSDL<type>*) var) );
                    break;
                }
            }
        }

        //Utilidades externas a la familia de clases 'DS'

        static void define_connections(DS<type>* G, int id, DS<int>* C){
            DSSL<NodeG<int>*>* graph_nodes = new DSSL<NodeG<int>*>();
            NodeG<int>* temp;
            DSSL<int>* L = (DSSL<int>*) C;
            for(int i= 0; i < L->extension(); i++){
                extractNode(G,L->extract(i),&temp);
                graph_nodes->insert(temp);
            }
            insert_connections(G,id, (NodeSL<NodeG<int>*>*) graph_nodes->getRoot());
            delete graph_nodes;
        }

        static void create_copy(DS<type>* original, DS<type>** clone){
            switch(original->getCategory()){
                case ARRAY: {
                    *clone = new DSA<type>();
                    int n;
                    extension_aux( ((DSA<type>*) original), &n);
                    ((DSA<type>*) *clone)->create(n);
                    for(int i = 0; i < n; i++){
                        int v;
                        extract_aux(((DSA<type>*) original),i,&v);
                        insert_pos_aux(((DSA<type>*) *clone),i,v);
                    }
                    break;
                }
                case MATRIX: {
                    *clone = new DSM<type>();
                    Data dim = ((DSM<type>*) original)->extension();
                    ((DSM<type>*) *clone)->create(dim);
                    for(int i = 0; i < dim.n*dim.m; i++){
                        ref.n = i/dim.m;
                        ref.m = i%dim.m;
                        ((DSM<type>*) *clone)->insert(ref, ((DSM<type>*) original)->extract(ref));
                    }
                    break;
                }
                case SINGLE_LINKED_LIST: {
                    *clone = new DSSL<type>();
                    ((DSSL<type>*) *clone)->create();
                    NodeSL<type>* SL = (NodeSL<type>*) ((DSSL<type>*) original)->getRoot();
                    while(SL != NULL){
                        insert_aux( ((DSSL<type>*) *clone), SL->data);
                        SL = SL->next;
                    }
                    reverse_aux( ((DSSL<type>*) *clone) );
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    *clone = new DSDL<type>();
                    ((DSDL<type>*) *clone)->create();
                    NodeDL<type>* DL = (NodeDL<type>*) ((DSDL<type>*) original)->getRoot();
                    while(DL != NULL){
                        insert_aux( ((DSDL<type>*) *clone), DL->data);
                        DL = DL->next;
                    }
                    reverse_aux( ((DSDL<type>*) *clone) );
                    break;
                }
                case BINARY_SEARCH_TREE: {
                    *clone = new DST<type>();
                    ((DST<type>*) *clone)->create();
                    NodeT<type>* T = (NodeT<type>*) ((DST<type>*) original)->getRoot();
                    copy_tree(T, (DST<type>**) clone);
                    break; 
                }
                case GRAPH: {
                    *clone = new DSG<type>();
                    ((DSG<type>*) *clone)->create();
                    NodeG<type>* G = (NodeG<type>*) ((DSG<type>*) original)->getRoot();
                    while(G != NULL){
                        insert_pos_aux( ((DSG<type>*) *clone), G->id, G->data);
                        NodeSL<NodeG<type>*>* O = G->connections;
                        DSSL<NodeG<type>*>* L = new DSSL<NodeG<type>*>();
                        L->create();
                        while(O != NULL){
                            L->insert(O->data);
                            O = O->next;
                        }
                        L->reverse();
                        insert_connections(*clone,G->id,(NodeSL<NodeG<type>*>* ) L->getRoot());
                        G = G->next;
                        delete L;
                    }
                    break;
                }
            }
        }
};
