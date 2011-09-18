#include "iterator.h"

Iterator::Iterator()
{

}
void Iterator::open(Table *tab)
{
    this->tabla=tab;
    this->actual=0;
}
Reccord* Iterator::getNext()
{

    Reccord* r=this->tabla->reccords[this->actual];
    this->actual++;
    return r;
}
