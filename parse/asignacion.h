#ifndef ASIGNACION_H
#define ASIGNACION_H
#include "valor.h"
class Asignacion
{
public:
    string campo;
    Valor valor;
    Asignacion();
    Asignacion(string campo,Valor valor);
};

#endif // ASIGNACION_H
