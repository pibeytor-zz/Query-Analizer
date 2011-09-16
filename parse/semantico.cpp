#include "semantico.h"

Semantico::Semantico(Sintactico sintactico)
{
    arbol_select=sintactico.arbol_select;
    arbol_insert=sintactico.arbol_insert;
    arbol_update=sintactico.arbol_update;
    arbol_delete=sintactico.arbol_delete;
    tipo_sentencia=sintactico.tipo_sentencia;
}

void Semantico::ejecutarSentencia()
{
    if(tipo_sentencia=="select")
        arbol_select->ejecutar();
    if(tipo_sentencia=="insert")
        arbol_insert->ejecutar();
    if(tipo_sentencia=="upate")
        arbol_update->ejecutar();
    if(tipo_sentencia=="delete")
        arbol_delete->ejecutar();
}
