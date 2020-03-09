#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "../ShareContainer.h"


class Hashtable
{
    public:
        Hashtable(int);
        virtual ~Hashtable();
        void Insert(ShareContainer*);
        int Search(int);
        void Delete(int);




    protected:

    private:
        bool isPrime(int);
        bool isEmpty(int);
        int CalculateIndex(int);
        int Find(int);


        int tableSize;
        ShareContainer** ContainerTable;  // double pointer
                                            // a pointer of type ShareContainer points to an array of pointers

};

#endif // HASHTABLE_H
