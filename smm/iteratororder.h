#ifndef ITERATORORDER_H
#define ITERATORORDER_H
#include "smm.h"
#include "iterator.h"

class iteratororder
{
public:

    iteratororder();
    void open(Table tab);
    Reccord getNext();
};

#endif // ITERATORORDER_H
