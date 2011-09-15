#ifndef ITERADOR_H
#define ITERADOR_H

#include "Registro.h"
#include "Metadata.h"
#include "Data.h"

class Iterador {
public:
    unsigned int cont;
    unsigned int bIDDatos;

    Iterador();
    Iterador(unsigned int c);
    void Open(unsigned int BlockID);
    unsigned char* getNext();
    void Close();


private:

};

#endif // ITERADOR_H
