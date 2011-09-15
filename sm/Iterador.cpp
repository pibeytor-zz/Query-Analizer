#include "Iterador.h"




Iterador::Iterador(){
    this->cont=0;
}
Iterador::Iterador(unsigned int c) {
    this->cont=c;
}

void Iterador::Open(unsigned int BlockID){
     Metadata md(BlockID);
    this->bIDDatos= md.getEspacioDisponible();
    cont=0;
}

unsigned char* Iterador::getNext(){
   Registro buffer;

    if(this->bIDDatos==0)
    {
        return NULL;
    }
    Data b(this->bIDDatos);
    while(b.getCantRegActivos()==0)
    {

       if(b.getSig() == 0)
        {
           return NULL;
        }
       else
       {
           Data b(b.getSig());
       }

    }
    if(cont<b.getCantRegActivos())
    {
        buffer = b.selectRecord(cont);
        cont++;

        return buffer.getContentReg();
    }
    else
    {
        cont=0;
        if(b.getSig()==0)
            return NULL;

        this->bIDDatos=b.getSig();
        return getNext();
    }
}


