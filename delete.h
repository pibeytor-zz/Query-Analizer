#ifndef DELETE_H
#define DELETE_H
#include "parse/validacion.h"
#include <vector>
#include <iostream>
using namespace std;
class Delete
{
public:
    string tabla;
    vector<Validacion>validaciones;
    Delete();
    Delete(string tabla,vector<Validacion>validaciones);
    void printDebug();
};

#endif // DELETE_H
