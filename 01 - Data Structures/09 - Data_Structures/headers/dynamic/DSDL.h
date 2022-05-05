/*
    Implementación para una lista enlazada doble.

    Se define la implementación como independiente del tipo de dato
    a almacenar mediante el uso de template.
*/
template <typename T>
class DSDL: public dynamicDS<T>,public insertable<T>,public measurable,public positionable<T>,public reversible {
    private:
        NodeDL<T>* L;

        void* createNode() override {
            return malloc(sizeof(NodeDL<T>));
        }

    public:
        category getCategory() override {
            return DOUBLE_LINKED_LIST;
        }
        void destroy() override {
            NodeDL<T>* temp;
            while(L != NULL){
                temp = L;
                L = L->next;
                free(temp);
            }
        }
        bool search(T value) override {
            bool ans = false;
            NodeDL<T>* Lcopy = L;
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
            NodeDL<T>* Lcopy = L;
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
            NodeDL<T>* Lcopy = L;
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

        Node<T>* getRoot(){
            return L;
        }
        void create() override {
            L = NULL;
        }

        void insert(T value) override {
            //Se asume inserción al inicio de la lista
            NodeDL<T>* temp = (NodeDL<T>*) createNode();
            temp->data = value;
            temp->prev = NULL;
            if(L == NULL) temp->next = NULL;
            else{
                L->prev = temp;
                temp->next = L;
            }
            L = temp;
        }

        int extension() override {
            int cont = 0;
            NodeDL<T>* Lcopy = L;
            while(Lcopy != NULL){
                cont++;
                Lcopy = Lcopy->next;
            }
            return cont;
        }

        void insert(int pos, T value) override {
            //Se asume pre-validación de una posición válida
            NodeDL<T>* temp = (NodeDL<T>*) createNode();
            temp->data = value;

            NodeDL<T>* Lcopy = L;
            for(int i = 0; i < pos-1; i++) Lcopy = Lcopy->next;

            temp->prev = Lcopy;
            temp->next = Lcopy->next;
            Lcopy->next->prev = temp;
            Lcopy->next       = temp;
        }
        T extract(int pos) override {
            //Se asume pre-validación de una posición válida
            NodeDL<T>* Lcopy = L;
            for(int i = 0; i < pos; i++) Lcopy = Lcopy->next;
            return Lcopy->data;
        }

        void reverse() override {
            NodeDL<T>* new_one = NULL;
            NodeDL<T>* Lcopy = L;
            NodeDL<T>* temp;
            while(Lcopy != NULL){
                temp = (NodeDL<T>*) createNode();
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
};
