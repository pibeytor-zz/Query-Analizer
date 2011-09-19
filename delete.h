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
    vector<string>operadores_logicos;
    Delete();
    Delete(string tabla,vector<Validacion>validaciones,vector<string>operadores_logicos);
    void printDebug();
    void ejecutar(StorageManagerM* smm);
};

#endif // DELETE_H
