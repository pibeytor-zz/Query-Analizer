#ifndef UPDATE_H
#define UPDATE_H
#include <vector>
#include "parse/asignacion.h"
#include "parse/validacion.h"
#include "arbol.h"
#include <iostream>
class Update : Arbol
{
public:
    string tabla;
    vector<Asignacion>asignaciones;
    vector<Validacion>validaciones;
    Update();
    Update(string tabla,vector<Asignacion>asignaciones,vector<Validacion>validaciones);
    void printDebug();
    void ejecutar(StorageManagerM* smm);
};

#endif // UPDATE_H
