enum category {SINGLE_LINKED_LIST,DOUBLE_LINKED_LIST,BINARY_SEARCH_TREE,GRAPH};

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
#include "DSSL.h"
#include "DSDL.h"
#include "DST.h"
#include "DSG.h"

template <typename type>
class Dynamic_Structures{
    private:
        static int count_nodes(NodeT<type>* tree){
            if(tree == NULL) return 0;
            return 1 + count_nodes(tree->left) + count_nodes(tree->right);
        }
        static void copy_tree(NodeT<type>* O, DS<type>** clone){
            if(O == NULL) return;
            (*clone)->insert(O->data);
            copy_tree(O->left, clone);
            copy_tree(O->right, clone);
        }
        static void extract(DS<type>* G, int id, NodeG<type>** node){
            NodeG<type>* graph = (NodeG<type>*) G->getRoot();
            while(graph != NULL){
                if(graph->id == id) break;
                graph = graph->next;
            }
            *node = graph;
        }
        static void insert(DS<type>* G, int id, NodeSL<NodeG<type>*>* C){
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
            for(int i= 0; i < C->extension(); i++){
                extract(G,C->extract(i),&temp);
                graph_nodes->insert(temp);
            }
            insert(G,id, (NodeSL<NodeG<int>*>*) graph_nodes->getRoot());
            delete graph_nodes;
        }
    public:
        static void create(DS<type>** var, category cat){
            switch(cat){
                case SINGLE_LINKED_LIST:
                    *var = new DSSL<type>(); break;
                case DOUBLE_LINKED_LIST:
                    *var = new DSDL<type>(); break;
                case BINARY_SEARCH_TREE:
                    *var = new DST<type>();  break;
                case GRAPH:
                    *var = new DSG<type>(); break;
            }
            (*var)->create();
        }

        static void extension(DS<type>* var, int* n){
            *n = var->extension();
        }

        static void insert(DS<type>* var, type value){
            var->insert(value);
        }
        static void insert(DS<type>* var, int n, type value){
            var->insert(n,value);
        }

        static void extract(DS<type>* var, int pos, type* res){
            *res = var->extract(pos);
        }
        
        static void destroy(DS<type>* var){
            var->destroy();
        }

        static void search(DS<type>* var, type value, bool* res){
            *res = var->search(value);
        }

        static void count(DS<type>* var, type value, int* res){
            *res = var->count(value);
        }
        static void count(DS<type>* T, int* n){
            if(T->getCategory() == BINARY_SEARCH_TREE){
                NodeT<type>* tree = (NodeT<type>*) T->getRoot();
                *n = count_nodes(tree);
            }else cout << "N/A\n";
        }

        static void reverse(DS<type>* var){
            var->reverse();
        }

        static void show(DS<type>* var, bool verbose){
            var->show(verbose);
        }

        //Utilidades externas a la familia de clases 'DS'
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
