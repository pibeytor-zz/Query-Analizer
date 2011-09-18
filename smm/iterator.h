#ifndef ITERATOR_H
#define ITERATOR_H
#include "smm.h"
class Iterator
{
public:
    int actual;
    Table *tabla;
    Iterator();
    void open(Table *tab);
    Reccord* getNext();


};

#endif // ITERATOR_H
