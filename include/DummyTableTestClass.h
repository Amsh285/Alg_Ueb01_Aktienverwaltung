#ifndef DUMMYTABLETESTCLASS_H
#define DUMMYTABLETESTCLASS_H


class DummyTableTestClass
{
    public:
        DummyTableTestClass();
        virtual ~DummyTableTestClass();
        void Insert(int);
        int getIndex(int);
        void Delete(int);

    protected:

    private:
        int Array[50];
};

#endif // DUMMYTABLETESTCLASS_H
