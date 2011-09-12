#include "select.h"

Select::Select(vector<Campo>campos,vector<Tabla>tablas,vector<Validacion>validaciones,vector<string>operadores_logicos)
{
    this->campos=campos;
    this->tablas=tablas;
    this->validaciones=validaciones;
    this->operadores_logicos=operadores_logicos;
}

void Select::printDebug()
{
    cout<<"-------------"<<endl;
    cout<<"Debug Select:"<<endl;
    cout<<"Campos:"<<endl;
    for(int i=0;i<(int)campos.size();i++)
        cout<<campos[i].campo<<","<<campos[i].tabla<<endl;
    cout<<"Tablas:"<<endl;
    for(int i=0;i<(int)tablas.size();i++)
        cout<<tablas[i].tabla<<","<<tablas[i].alias<<endl;
    cout<<"Validaciones:"<<endl;
    for(int i=0;i<(int)validaciones.size();i++)
        cout<<validaciones[i].exp_izq<<","<<validaciones[i].operador<<","<<validaciones[i].exp_der<<","<<validaciones[i].tipo<<endl;
    cout<<"Operadores logicos:"<<endl;
    for(int i=0;i<(int)operadores_logicos.size();i++)
        cout<<operadores_logicos[i]<<endl;
    cout<<"-------------"<<endl;
}
