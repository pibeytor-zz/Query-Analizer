#ifndef ITERATOR_H
#define ITERATOR_H
#include "smm.h"
class iterator
{
public:
    int actual;
    Table tabla;
    iterator();
    void open(Tabla tab);
    Reccord getNext();


};

#endif // ITERATOR_H
