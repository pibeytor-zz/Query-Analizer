#ifndef UPDATE_H
#define UPDATE_H
#include <vector>
#include "asignacion.h"
#include "validacion.h"
#include <iostream>
class Update
{
public:
    string tabla;
    vector<Asignacion>asignaciones;
    vector<Validacion>validaciones;
    Update();
    Update(string tabla,vector<Asignacion>asignaciones,vector<Validacion>validaciones);
    void printDebug();
};

#endif // UPDATE_H
