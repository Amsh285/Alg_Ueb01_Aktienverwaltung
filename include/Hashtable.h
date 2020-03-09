#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "../ShareContainer.h"
#include <string>


class Hashtable
{
    public:
        Hashtable(int);
        virtual ~Hashtable();
        void Insert(ShareContainer*, std::string);
        int Search(std::string);
        void Delete(std::string);
        ShareContainer* getShare(int);



    private:
        bool isPrime(int);
        bool isEmpty(int);
        int CalculateIndex(int);
        int Find(std::string);


        int tableSize;
        ShareContainer** ContainerTable;  // double pointer
                                            // a pointer of type ShareContainer points to an array of pointers

};

#endif // HASHTABLE_H
