template <typename T>
class DSSL: public dynamicDS<T>,insertable<T>,measurable,positionable<T>,reversible {
    private:
        NodeSL<T>* L;

        void* createNode() override {
            return malloc(sizeof(NodeSL<T>));
        }

    public:
        category getCategory() override {
            return SINGLE_LINKED_LIST;
        }
        void destroy() override {
            NodeSL<T>* temp;
            while(L != NULL){
                temp = L;
                L = L->next;
                free(temp);
            }
        }
        bool search(T value) override {
            bool ans = false;
            NodeSL<T>* Lcopy = L;
            while(Lcopy != NULL){
                if(Lcopy->data == value){
                    ans = true;
                    break;
                }
                Lcopy = Lcopy->next;
            }
            return ans;
        }
        int count(T value) override {
            int cont = 0;
            NodeSL<T>* Lcopy = L;
            while(Lcopy != NULL){
                if(Lcopy->data == value) cont++;
                Lcopy = Lcopy->next;
            }
            return cont;
        }
        void show(bool verbose) override {
            if(L == NULL){
                cout << "La lista está vacía.\n";
                return;
            }
            NodeSL<T>* Lcopy = L;
            if(verbose){
                int index = 1;
                while(Lcopy != NULL){
                    cout << "Element #" << index << " is: " << Lcopy->data << "\n";
                    index++;
                    Lcopy = Lcopy->next;
                }       
            }else{
                while(Lcopy != NULL){
                    cout << Lcopy->data << " -> ";
                    Lcopy = Lcopy->next;
                }
                cout << "NULL\n";
            }
        }

        Node<T>* getRoot(){
            return L;
        }
        void create() override {
            L = NULL;
        }

        void insert(T value) override {
            //Se asume inserción al inicio de la lista
            NodeSL<T>* temp = (NodeSL<T>*) createNode();
            temp->data = value;
            if(L == NULL) temp->next = NULL;
            else          temp->next = L;
            L = temp;
        }
        
        int extension() override {
            int cont = 0;
            NodeSL<T>* Lcopy = L;
            while(Lcopy != NULL){
                cont++;
                Lcopy = Lcopy->next;
            }
            return cont;
        }
        
        void insert(int pos, T value) override {
            //Se asume pre-validación de una posición válida
            NodeSL<T>* temp = (NodeSL<T>*) createNode();
            temp->data = value;

            NodeSL<T>* Lcopy = L;
            for(int i = 0; i < pos-1; i++) Lcopy = Lcopy->next;

            temp->next = Lcopy->next;
            Lcopy->next = temp;
        }
        T extract(int pos) override {
            //Se asume pre-validación de una posición válida
            NodeSL<T>* Lcopy = L;
            for(int i = 0; i < pos; i++) Lcopy = Lcopy->next;
            return Lcopy->data;
        }

        void reverse() override {
            NodeSL<T>* new_one = NULL;
            NodeSL<T>* Lcopy = L;
            NodeSL<T>* temp;
            while(Lcopy != NULL){
                temp = (NodeSL<T>*) createNode();
                temp->data = Lcopy->data;
                if(new_one == NULL) temp->next = NULL;
                else                temp->next = new_one;
                new_one = temp;
                Lcopy = Lcopy->next;
            }
            destroy();
            L = new_one;
        }
};
