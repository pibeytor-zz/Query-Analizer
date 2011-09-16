#ifndef SEMANTICO_H
#define SEMANTICO_H
#include "sintactico.h"

class Semantico
{
    string tipo_sentencia;
    Select* arbol_select;
    Insert* arbol_insert;
    Update* arbol_update;
    Delete* arbol_delete;
public:
    Semantico(Sintactico sintactico);
    void ejecutarSentencia();
};

#endif // SEMANTICO_H
