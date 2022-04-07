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

        static int count_nodes_aux(NodeT<type>* tree){
            if(tree == NULL) return 0;
            return 1 + count_nodes_aux(tree->left) + count_nodes_aux(tree->right);
        }

        static void copy_tree(NodeT<type>* O, DS<type>** clone){
            if(O == NULL) return;
            (*clone)->insert(O->data);
            copy_tree(O->left, clone);
            copy_tree(O->right, clone);
        }

        static void extractNode(DS<type>* G, int id, NodeG<type>** node){
            NodeG<type>* graph = (NodeG<type>*) G->getRoot();
            while(graph != NULL){
                if(graph->id == id) break;
                graph = graph->next;
            }
            *node = graph;
        }

        static void insert_connections(DS<type>* G, int id, NodeSL<NodeG<type>*>* C){
            NodeG<type>* graph = (NodeG<type>*) G->getRoot();
            while(graph != NULL){
                if(graph->id == id){
                    graph->connections = C;
                    break;
                }
                graph = graph->next;
            }
        }

        static void define_connections_aux(DS<type>* G, int id, DS<int>* C){
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
            ref = matrix->extension();
            *rows = ref.n;
            *columns = ref.m;
        }
        static void extension(DS<type>* var, int* n){
            *n = var->extension();
        }

        static void insert(DS<type>* var, int row, int column, type value){
            DSM<type>* matrix = (DSM<type>*) var;
            ref.n = row; ref.m = column;
            matrix->insert(ref,value);
        }
        static void insert(DS<type>* var, type value){
            category cat = var->getCategory();
            switch(cat){
                case SINGLE_LINKED_LIST: {
                    DSSL<type>* SL = (DSSL<type>*) var;
                    SL->insert(value);
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    DSDL<type>* DL = (DSDL<type>*) var;
                    DL->insert(value);
                    break;
                }
                case BINARY_SEARCH_TREE: {
                    DST<type>* T = (DST<type>*) var;
                    T->insert(value);
                    break;
                }
            }
        }
        static void insert(DS<type>* var, int n, type value){
            category cat = var->getCategory();
            switch(cat){
                case ARRAY: {
                    DSA<type>* A = (DSA<type>*) var;
                    A->insert(n,value);
                    break;
                }
                case SINGLE_LINKED_LIST: {
                    DSSL<type>* SL = (DSSL<type>*) var;
                    SL->insert(n,value);
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    DSDL<type>* DL = (DSDL<type>*) var;
                    DL->insert(n,value);
                    break;
                }
                case GRAPH: {
                    DSG<type>* G = (DSG<type>*) var;
                    G->insert(n,value);
                    break;
                }
            }
        }

        static void extract(DS<type>* matrix, int row, int column, type* result){
            ref.n = row; ref.m = column;
            *result = matrix->extract(ref);
        }
        static void extract(DS<type>* var, int pos, type* res){
            *res = var->extract(pos);
        }

        static void reverse(DS<type>* var){
            var->reverse();
        }

        //Utilidades externas a la familia de clases 'DS'
        
        static void count_nodes(DS<type>* T, int* n){
            if(T->getCategory() == BINARY_SEARCH_TREE){
                NodeT<type>* tree = (NodeT<type>*) T->getRoot();
                *n = count_nodes_aux(tree);
            }else cout << "N/A\n";
        }

        static void define_connections(DS<type>* G, int M[5][4]){
            if(G->getCategory() == GRAPH){
                DS<int>* indices;
                create(&indices,SINGLE_LINKED_LIST);
                for(int i = 0; i < 5; i++){
                    for(int j = 1; j < 4; j++)
                        if(M[i][j] != -99) insert(indices,M[i][j]);
                    define_connections_aux(G,M[i][0],indices);
                    indices->destroy();
                }
                delete indices;
            }else cout << "N/A\n";
        }

        static void create_copy(DS<type>* original, DS<type>** clone){
            switch(original->getCategory()){
                case ARRAY: {
                    *clone = new DSA<type>();
                    int n = original->extension();
                    (*clone)->create(n);
                    for(int i = 0; i < n; i++)
                        (*clone)->insert(i, original->extract(i));
                    break;
                }
                case MATRIX: {
                    *clone = new DSM<type>();
                    Data dim = original->getDim();
                    (*clone)->create(dim);
                    for(int i = 0; i < dim.n*dim.m; i++){
                        ref.n = i/dim.m;
                        ref.m = i%dim.m;
                        (*clone)->insert(ref, original->extract(ref));
                    }
                    break;
                }
                case SINGLE_LINKED_LIST: {
                    *clone = new DSSL<type>();
                    (*clone)->create();
                    NodeSL<type>* SL = (NodeSL<type>*) original->getRoot();
                    while(SL != NULL){
                        (*clone)->insert(SL->data);
                        SL = SL->next;
                    }
                    (*clone)->reverse();
                    break;
                }
                case DOUBLE_LINKED_LIST: {
                    *clone = new DSDL<type>();
                    (*clone)->create();
                    NodeDL<type>* DL = (NodeDL<type>*) original->getRoot();
                    while(DL != NULL){
                        (*clone)->insert(DL->data);
                        DL = DL->next;
                    }
                    (*clone)->reverse();
                    break;
                }
                case BINARY_SEARCH_TREE: {
                    *clone = new DST<type>();
                    (*clone)->create();
                    NodeT<type>* T = (NodeT<type>*) original->getRoot();
                    copy_tree(T,clone);
                    break; 
                }
                case GRAPH: {
                    *clone = new DSG<type>();
                    (*clone)->create();
                    NodeG<type>* G = (NodeG<type>*) original->getRoot();
                    while(G != NULL){
                        (*clone)->insert(G->id,G->data);
                        NodeSL<NodeG<type>*>* O = G->connections;
                        DSSL<NodeG<type>*>* L = new DSSL<NodeG<type>*>();
                        L->create();
                        while(O != NULL){
                            L->insert(O->data);
                            O = O->next;
                        }
                        L->reverse();
                        insert(*clone,G->id,(NodeSL<NodeG<type>*>* ) L->getRoot());
                        G = G->next;
                        delete L;
                    }
                    break;
                }
            }
        }
};
