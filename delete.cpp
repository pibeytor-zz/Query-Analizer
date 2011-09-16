#include "delete.h"

Delete::Delete()
{
}

Delete::Delete(string tabla,vector<Validacion>validaciones)
{
    this->tabla=tabla;
    this->validaciones=validaciones;
}

void Delete::printDebug()
{
    cout<<"-------------"<<endl;
    cout<<"Debug delete:"<<endl;
    cout<<"Tabla:"<<endl;
    cout<<tabla<<endl;
    cout<<"Validaciones"<<endl;
    for(int i=0;i<(int)validaciones.size();i++)
        cout<<validaciones[i].exp_izq<<","<<validaciones[i].operador<<","<<validaciones[i].exp_der<<","<<validaciones[i].tipo<<endl;
    cout<<"-------------"<<endl;
}

void Delete::ejecutar()
{
    printDebug();

    cout<<eval(Field((char)'f'),validaciones[0].exp_der,validaciones[0].tipo);
}
