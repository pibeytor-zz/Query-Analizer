#ifndef ITERADORORDENADO_H
#define ITERADORORDENADO_H
#include "Metadata.h"
#include "Registro.h"
#include "Iterador.h"
#include <vector>

class IteradorOrdenado
{
public:

    unsigned int cont;
    unsigned int bIDDatos;
    vector<Registro> ordenados;

    IteradorOrdenado();
    IteradorOrdenado(int c);
    void Open(unsigned int blockID, char parametros[]);
    Registro getNext();
    void Close();
};

#endif // ITERADORORDENADO_H
