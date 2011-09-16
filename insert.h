#ifndef INSERT_H
#define INSERT_H
#include "parse/valor.h"
#include "parse/campo.h"
#include "arbol.h"
#include <vector>
#include <iostream>
using namespace std;

class Insert : Arbol
{
public:
    string tabla;
    vector<Campo>campos;
    vector<Valor>valores;
    Insert();
    Insert(string tabla,vector<Campo>campos,vector<Valor>valores);
    void printDebug();
    void ejecutar();
};

#endif // INSERT_H
