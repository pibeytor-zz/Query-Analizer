#ifndef SELECT_H
#define SELECT_H
#include "campo.h"
#include "tabla.h"
#include "validacion.h"
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
