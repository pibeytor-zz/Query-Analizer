#ifndef INSERT_H
#define INSERT_H
#include "valor.h"
#include "campo.h"
#include <vector>
#include <iostream>
using namespace std;

class Insert
{
public:
    string tabla;
    vector<Campo>campos;
    vector<Valor>valores;
    Insert();
    Insert(string tabla,vector<Campo>campos,vector<Valor>valores);
    void printDebug();
};

#endif // INSERT_H
