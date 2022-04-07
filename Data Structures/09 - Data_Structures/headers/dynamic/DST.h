template <typename type>
class DST: public dynamicDS<type>,insertable<type>,measurable {
    private:
        NodeT<type>* T;

        void* createNode() override {
            return malloc(sizeof(NodeT<type>));
        }

        int height(NodeT<type>* tree){
            if(tree == NULL) return 0;
            return max( 1 + height(tree->left) , 1 + height(tree->right) );
        }
        void insert_aux(NodeT<type>* tree, NodeT<type>* node){
            if(node->data <= tree->data)
                if(tree->left == NULL){
                    node->parent = tree;
                    tree->left = node;
                }else insert_aux(tree->left,node);
            else
                if(tree->right == NULL){
                    node->parent = tree;
                    tree->right = node;
                }else insert_aux(tree->right,node);
        }
        void destroy_aux(NodeT<type>* tree){
            if(tree == NULL) return;
            destroy_aux(tree->left);
            destroy_aux(tree->right);
            free(tree);
        }
        bool search_aux(NodeT<type>* tree, type value){
            if(tree == NULL) return false;
            if(tree->data == value) return true;
            return search_aux(tree->left,value) || search_aux(tree->right,value);
        }
        int count_aux(NodeT<type>* tree, type value){
            if(tree == NULL) return 0;
            return ((tree->data == value)?1:0) + count_aux(tree->left,value) + count_aux(tree->right,value);
        }
        void show_aux(NodeT<type>* tree){
            if(tree == NULL){ cout << " NULL "; return; }
            cout << "[ " << tree->data << " ";
            show_aux(tree->left);
            show_aux(tree->right);
            cout << "]";
        }
        void show_aux_verbose(NodeT<type>* tree, int cont){
            if(tree == NULL){
                cout << string(cont,'\t') << "Hijo nulo.\n";
                return;
            }
            cout << string(cont,'\t') << "Padre: " << tree->data << ".\n";
            cout << string(cont,'\t') << "Hijo izquierdo:\n";
            show_aux_verbose(tree->left,cont+1);
            cout << string(cont,'\t') << "Hijo derecho:\n";
            show_aux_verbose(tree->right,cont+1);
        }

    public:
        category getCategory() override {
            return BINARY_SEARCH_TREE;
        }
        void destroy() override {
            destroy_aux(T);
            T == NULL;
        }
        bool search(type value) override {
            return search_aux(T,value);
        }
        int count(type value) override {
            return count_aux(T,value);
        }
        void show(bool verbose) override {
            //Se implementa recorrido Pre-Order
            if(T == NULL){
                cout << "El árbol está vacío.\n";
                return;
            }
            if(verbose) show_aux_verbose(T,0);
            else{ show_aux(T); cout << "\n"; }
        }

        Node<type>* getRoot(){
            return T;
        }
        void create() override {
            T = NULL;
        }

        void insert(type value) override {
            //Se asume Binary Search Tree
            NodeT<type>* temp = (NodeT<type>*) createNode();
            temp->data = value;
            temp->left   = NULL;
            temp->right  = NULL;
            if(T == NULL){
                temp->parent = NULL;
                T = temp;
            }else insert_aux(T,temp);
        }

        int extension() override {
            return height(T);
        }
};
