template <typename type>
class DSDL: public DS<type>{
    private:
        NodeDL<type>* L;

        void* createNode() override {
            return malloc(sizeof(NodeDL<type>));
        }
    public:
        Node<type>* getRoot(){
            return L;
        }
        category getCategory() override {
            return DOUBLE_LINKED_LIST;
        }
        void create() override {
            L = NULL;
        }
        int extension() override {
            int cont = 0;
            NodeDL<type>* Lcopy = L;
            while(Lcopy != NULL){
                cont++;
                Lcopy = Lcopy->next;
            }
            return cont;
        }
        void insert(type value) override {
            //Se asume inserción al inicio de la lista
            NodeDL<type>* temp = (NodeDL<type>*) createNode();
            temp->data = value;
            temp->prev = NULL;
            if(L == NULL) temp->next = NULL;
            else{
                L->prev = temp;
                temp->next = L;
            }
            L = temp;
        }
        void insert(int pos, type value) override {
            //Se asume pre-validación de una posición válida
            NodeDL<type>* temp = (NodeDL<type>*) createNode();
            temp->data = value;

            NodeDL<type>* Lcopy = L;
            for(int i = 0; i < pos-1; i++) Lcopy = Lcopy->next;

            temp->prev = Lcopy;
            temp->next = Lcopy->next;
            Lcopy->next->prev = temp;
            Lcopy->next       = temp;
        }
        type extract(int pos) override {
            //Se asume pre-validación de una posición válida
            NodeDL<type>* Lcopy = L;
            for(int i = 0; i < pos; i++) Lcopy = Lcopy->next;
            return Lcopy->data;
        }
        void destroy() override {
            NodeDL<type>* temp;
            while(L != NULL){
                temp = L;
                L = L->next;
                free(temp);
            }
        }
        bool search(type value) override {
            bool ans = false;
            NodeDL<type>* Lcopy = L;
            while(Lcopy != NULL){
                if(Lcopy->data == value){
                    ans = true;
                    break;
                }
                Lcopy = Lcopy->next;
            }
            return ans;
        }
        int count(type value) override {
            int cont = 0;
            NodeDL<type>* Lcopy = L;
            while(Lcopy != NULL){
                if(Lcopy->data == value) cont++;
                Lcopy = Lcopy->next;
            }
            return cont;
        }
        void reverse() override {
            NodeDL<type>* new_one = NULL;
            NodeDL<type>* Lcopy = L;
            NodeDL<type>* temp;
            while(Lcopy != NULL){
                temp = (NodeDL<type>*) createNode();
                temp->data = Lcopy->data;
                temp->prev = NULL;
                if(new_one == NULL) temp->next = NULL;
                else{
                    new_one->prev = temp;
                    temp->next = new_one;
                }
                new_one = temp;
                Lcopy = Lcopy->next;
            }
            destroy();
            L = new_one;
        }
        void show(bool verbose) override {
            if(L == NULL){
                cout << "La lista está vacía.\n";
                return;
            }
            NodeDL<type>* Lcopy = L;
            if(verbose){
                int index = 1;
                while(Lcopy != NULL){
                    cout << "Element #" << index << " is: " << Lcopy->data << "\n";
                    index++;
                    Lcopy = Lcopy->next;
                }       
            }else{
                while(Lcopy != NULL){
                    cout << Lcopy->data << " <-> ";
                    Lcopy = Lcopy->next;
                }
                cout << "NULL\n";
            }
        }
};
