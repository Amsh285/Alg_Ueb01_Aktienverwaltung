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
        bool Delete(std::string);
        int Find(std::string);
        Share* getShare(int);

    private:
        bool isEmpty(int);

        int tableSize;
        ShareContainer** ContainerTable;  // double pointer
                                            // a pointer of type ShareContainer points to an array of pointers

};

#endif // HASHTABLE_H
