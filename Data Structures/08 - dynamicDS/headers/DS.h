template <typename type>
class DS{
    private:
        virtual void* createNode() = 0;
    public:
        virtual Node<type>* getRoot() = 0;
        virtual category getCategory() = 0;
        virtual void create() = 0;
        virtual int extension() = 0;
        virtual void insert(type value) = 0;
        virtual void insert(int pos, type value) = 0;
        virtual type extract(int pos) = 0;
        virtual void destroy() = 0;
        virtual bool search(type value) = 0;
        virtual int count(type value) = 0;
        virtual void reverse() = 0;
        virtual void show(bool verbose) = 0;
};
