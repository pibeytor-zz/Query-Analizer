#ifndef SELECT_H
#define SELECT_H
#include "parse/campo.h"
#include "parse/tabla.h"
#include "parse/validacion.h"
#include <vector>
#include <iostream>
using namespace std;
class Select
{
public:
    vector<Campo>campos;
    vector<Tabla>tablas;
    vector<Validacion>validaciones;
    vector<string>operadores_logicos;
    Select(vector<Campo>campos,vector<Tabla>tablas,vector<Validacion>validaciones,vector<string>operadores_logicos);
    void printDebug();
};

#endif // SELECT_H
