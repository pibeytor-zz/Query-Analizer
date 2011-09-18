#ifndef SELECT_H
#define SELECT_H
#include "parse/campo.h"
#include "parse/tabla.h"
#include "parse/validacion.h"
#include "arbol.h"
#include <vector>
#include <iostream>
using namespace std;
class Select : Arbol
{
public:
    vector<Campo>campos;
    vector<Tabla>tablas;
    vector<Validacion>validaciones;
    vector<string>operadores_logicos;
    vector<Campo>groupBy;
    Select(vector<Campo>campos,vector<Tabla>tablas,vector<Validacion>validaciones,vector<string>operadores_logicos,vector<Campo>groupBy);
    void printDebug();
    void ejecutar(StorageManagerM* smm);
};

#endif // SELECT_H
