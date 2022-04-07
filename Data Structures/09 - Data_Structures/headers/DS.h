template <typename T>
class DS{
    public:
        virtual category getCategory() = 0;
        virtual void destroy() = 0;
        virtual bool search(T value) = 0;
        virtual int count(T value) = 0;
        virtual void show(bool verbose) = 0;
};

template <typename T>
class staticDS_1D: public DS<T>{
    public:
        virtual void create(int size) = 0;
};

template <typename T>
class staticDS_2D: public DS<T>{
    public:
        virtual void create(Data dim) = 0;
        virtual Data extension() = 0;
        virtual void insert(Data pos, T value) = 0;
        virtual T extract(Data pos) = 0;
};

template <typename T>
class dynamicDS: public DS<T>{
    private:
        virtual void* createNode() = 0;
    public:
        virtual Node<T>* getRoot() = 0;
        virtual void create() = 0;
};



template <typename T>
class insertable{
    public:
        virtual void insert(T value) = 0;
};

class measurable{
    public:
        virtual int extension() = 0;
};

template <typename T>
class positionable{
    public:
        virtual void insert(int pos, T value) = 0;
        virtual T extract(int pos) = 0;
};

class reversible{
    public:
        virtual void reverse() = 0;
};
