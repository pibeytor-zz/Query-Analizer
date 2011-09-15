#include "IteradorOrdenado.h"

IteradorOrdenado::IteradorOrdenado()
{
    this->cont = 0;
    //this->ordenados = 0;

}

IteradorOrdenado::IteradorOrdenado(int c){
    this->cont = c;
    //this->ordenados = 0;
}

void IteradorOrdenado::Open(unsigned int blockID, char parametros[]){

   /* Iterador it, it2;
    Registro b1, b2;
    Registro bvalor1, bvalor2, r;
    bool flagReg;


    it = new Iterador(blockID);
    it2 = new Iterador(blockID);

    b1 = new Registro();
    b2 = new Registro();

    it.Open(blockID);
    it2.Open(blockID);

    while(b1 = it.getNext() != NULL){

        while(b2 = it2.getNext() != NULL){

            flagReg = true;

            for(int i=0; i<sizeof(parametros); i++){

                bvalor1 = r.readCampo(i, blockID);
                bvalor2 = r.readCampo(i, blockID);

                switch(r/*.getFieldType(parametros[i], bIDMD)){

                case 'string':
                    if((string)bvalor1 == (string)bvalor2){

                        continue;

                    }

                    else{

                        if((string)bvalor1 < (string)bvalor2){

                            flagReg = false;
                            break;

                        }

                   }
                }

                if(flagReg == true){

                    ordenados.insert(b1);                //arreglo.add(b1);

                }

                else{

                    ordenados.insert(b2);                //arreglo.add(b2);

                }
            }

        }
    }
}

IteradorOrdenado::getNext(){

    //Registro r;

    if(this->bIDDatos==0)
    {
        return NULL;
    }
    Data b= new Data(this->bIDDatos);
    while(b.getCantRegActivos()==0)
    {
        b= new Data(b.getSig());

        if(b==NULL)
        {
            return NULL;
        }

    }
    if(cont<b.getCantRegActivos())
    {
        buffer = b.selectRecord(cont);
        cont++;
        return buffer;
    }
    else
    {
        cont=0;
        if(b.getSig()==0)
            return NULL;

        this->bIDDatos=b.getSig();
        return getNext();
    }

    /*if(r >= sizeof(ordenados)){

           return NULL;

       }

       else{

           return ordenados[r];
           r++;

       }*/

}

void IteradorOrdenado::Close(){

    ordenados.clear();

}
