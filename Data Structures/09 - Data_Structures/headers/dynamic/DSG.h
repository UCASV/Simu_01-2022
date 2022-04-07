template <typename T>
class DSG: public dynamicDS<T>,measurable,positionable<T> {
    private:
        NodeG<T>* G;

        void* createNode() override {
            return malloc(sizeof(NodeG<T>));
        }
    public:
        category getCategory() override {
            return GRAPH;
        }
        void destroy() override {
            NodeG<T>* temp;
            NodeSL<NodeG<T>*>* L;
            NodeSL<NodeG<T>*>* tempL;
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
        bool search(T value) override {
            bool ans = false;
            NodeG<T>* Gcopy = G;
            while(Gcopy != NULL){
                if(Gcopy->data == value){
                    ans = true;
                    break;
                }
                Gcopy = Gcopy->next;
            }
            return ans;
        }
        int count(T value) override {
            int cont = 0;
            NodeG<T>* Gcopy = G;
            while(Gcopy != NULL){
                if(Gcopy->data == value) cont++;
                Gcopy = Gcopy->next;
            }
            return cont;
        }
        void show(bool verbose) override {
            if(G == NULL){
                cout << "El grafo está vacío.\n";
                return;
            }
            NodeG<T>* Gcopy = G;
            NodeSL<NodeG<T>*>* L;
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

        Node<T>* getRoot(){
            return G;
        }
        void create() override {
            G = NULL;
        }
        
        int extension() override {
            int cont = 0;
            NodeG<T>* Gcopy = G;
            while(Gcopy != NULL){
                cont++;
                Gcopy = Gcopy->next;
            }
            //Se puede añadir contar el número de aristas
            return cont;
        }

        void insert(int id, T value) override {
            //La posición en el listado principal no es relevante.
            //Por simplicidad se inserta al inicio.
            NodeG<T>* temp = (NodeG<T>*) createNode();
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
        T extract(int id) override {
            NodeG<T>* Gcopy = G;
            while(Gcopy != NULL){
                if(Gcopy->id == id) break;
                Gcopy = Gcopy->next;
            }
            return Gcopy->data;
        }
};
