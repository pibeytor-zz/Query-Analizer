#ifndef DELETE_H
#define DELETE_H
#include "parse/validacion.h"
#include "arbol.h"
#include <vector>
#include <iostream>
using namespace std;
class Delete : Arbol
{
public:
    string tabla;
    vector<Validacion>validaciones;
    Delete();
    Delete(string tabla,vector<Validacion>validaciones);
    void printDebug();
    void ejecutar();
};

#endif // DELETE_H
