template <typename type>
class DSG: public DS<type>{
    private:
        NodeG<type>* G;

        void* createNode() override {
            return malloc(sizeof(NodeG<type>));
        }
    public:
        Node<type>* getRoot(){
            return G;
        }
        category getCategory() override {
            return GRAPH;
        }
        void create() override {
            G = NULL;
        }
        int extension() override {
            int cont = 0;
            NodeG<type>* Gcopy = G;
            while(Gcopy != NULL){
                cont++;
                Gcopy = Gcopy->next;
            }
            //Se puede añadir contar el número de aristas
            return cont;
        }
        void insert(type value) override {
            cout << "N/A\n";
        }
        void insert(int id, type value) override {
            //La posición en el listado principal no es relevante.
            //Por simplicidad se inserta al inicio.
            NodeG<type>* temp = (NodeG<type>*) createNode();
            temp->entry = false;
            temp->id = id;
            temp->data = value;
            temp->connections = NULL;
            if(G == NULL){
                temp->entry = true;
                temp->next = NULL;
            }else temp->next = G;
            G = temp;
        }
        type extract(int id) override {
            NodeG<type>* Gcopy = G;
            while(Gcopy != NULL){
                if(Gcopy->id == id) break;
                Gcopy = Gcopy->next;
            }
            return Gcopy->data;
        }
        void destroy() override {
            NodeG<type>* temp;
            NodeSL<NodeG<type>*>* L;
            NodeSL<NodeG<type>*>* tempL;
            while(G != NULL){
                temp = G;
                L = temp->connections;
                while(L != NULL){
                    tempL = L;
                    L = L->next;
                    free(tempL);
                }
                G = G->next;
                free(temp);
            }
        }
        bool search(type value) override {
            bool ans = false;
            NodeG<type>* Gcopy = G;
            while(Gcopy != NULL){
                if(Gcopy->data == value){
                    ans = true;
                    break;
                }
                Gcopy = Gcopy->next;
            }
            return ans;
        }
        int count(type value) override {
            cout << "N/A\n";
        }
        void reverse() override {
            cout << "N/A\n";
        }
        void show(bool verbose) override {
            if(G == NULL){
                cout << "El grafo está vacío.\n";
                return;
            }
            NodeG<type>* Gcopy = G;
            NodeSL<NodeG<type>*>* L;
            if(verbose)
                while(Gcopy != NULL){
                    cout << "Nodo #" << Gcopy->id << ":\n\tDatos: " << Gcopy->data << "\n\tConexiones:\n";
                    L = Gcopy->connections;
                    int index = 1;
                    while(L != NULL){
                        cout << "\tConexión #" << index << " corresponde al Nodo #" << L->data->id << "\n";
                        index++;
                        L = L->next;
                    }
                    Gcopy = Gcopy->next;
                }
            else{
                while(Gcopy != NULL){
                    cout << "( " << Gcopy->id << " , " << Gcopy->data << " , [ ";
                    L = Gcopy->connections;
                    while(L != NULL){
                        cout << L->data->id << "->";
                        L = L->next;
                    }
                    cout << "NULL ] )" << " -> ";
                    Gcopy = Gcopy->next;
                }
                cout << "NULL\n";
            }
        }
};
