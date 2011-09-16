#include "iterator.h"

iterator::iterator()
{

}
void iterator::open(Table tab)
{
    this->tabla=tab;
    this->actual=0;
}
Reccord iterator::getNext()
{
    Reccord r=this->tabla.reccords[this->actual];
    this->actual++;
    return r;
}
