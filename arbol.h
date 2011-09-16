#ifndef ARBOL_H
#define ARBOL_H

#include "smm/smm.h"
#include "parse/valor.h"
#include <cstdlib>

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
    int compare(Field f,string valor,string tipo)
    {
        if(f.tipo!=tipo)
            return -2;
        if(tipo=="varchar")
        {
            if(f.varchar==getString(valor))
                return 0;
            return -1;
        }
        if(tipo=="booleano")
        {
            if(f.booleano==getBool(valor))
                return 0;
            return -1;
        }
        if(tipo=="entero")
        {
            if(f.entero<getInt(valor))
                return -1;
            if(f.entero>getInt(valor))
                return 1;
            return 0;
        }
        if(tipo=="char")
        {
            if(f.caracter<getChar(valor))
                return -1;
            if(f.caracter>getChar(valor))
                return 1;
            return 0;
        }
        return -3;
    }
    string getString(string valor)
    {
        string resultado="";
        for(int i=1;i<valor.length()-1;i++)
        {
            resultado+=valor[i];
        }
        return resultado;
    }
    int getInt(string valor)
    {
        return atoi(valor.c_str());
    }
    bool getBool(string valor)
    {
        return valor=="true";
    }
    char getChar(string valor)
    {
        return valor[1];
    }
};

#endif // ARBOL_H
