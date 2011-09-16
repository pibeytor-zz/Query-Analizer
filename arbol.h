#ifndef ARBOL_H
#define ARBOL_H

#include "smm/smm.h"

class Arbol
{
public:
    Arbol();
    int compare(Field f,int valor)
    {
        if(f.tipo!="entero")
            return -2;
        if(f.entero<valor)
            return -1;
        if(f.entero>valor)
            return 1;
        return 0;
    }

    int compare(Field f,bool valor)
    {
        if(f.tipo!="booleano")
            return -2;
        if(f.booleano==valor)
            return 0;
        return -1;
    }
    int compare(Field f,char valor)
    {
        if(f.tipo!="caracter")
            return -2;
        if(f.caracter<valor)
            return -1;
        if(f.caracter>valor)
            return 1;
        return 0;
    }
    int compare(Field f,string valor)
    {
        if(f.tipo!="varchar")
            return -2;
        if(f.varchar==valor)
            return 0;
        return -1;
    }
};

#endif // ARBOL_H
