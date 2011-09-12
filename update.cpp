#include "update.h"

Update::Update()
{
}

Update::Update(string tabla,vector<Asignacion>asignaciones,vector<Validacion>validaciones)
{
    this->tabla=tabla;
    this->asignaciones=asignaciones;
    this->validaciones=validaciones;
}

void Update::printDebug()
{
    cout<<"-------------"<<endl;
    cout<<"Debug update:"<<endl;
    cout<<"Tabla:"<<endl;
    cout<<tabla<<endl;
    cout<<"Asignaciones:"<<endl;
    for(int i=0;i<(int)asignaciones.size();i++)
        cout<<asignaciones[i].campo<<","<<asignaciones[i].valor.valor<<","<<asignaciones[i].valor.tipo<<endl;
    cout<<"Validaciones:"<<endl;
    for(int i=0;i<(int)validaciones.size();i++)
        cout<<validaciones[i].exp_izq<<","<<validaciones[i].operador<<","<<validaciones[i].exp_der<<","<<validaciones[i].tipo<<endl;
    cout<<"-------------"<<endl;
}
