#include "insert.h"

Insert::Insert()
{
}

Insert::Insert(string tabla,vector<Campo>campos,vector<Valor>valores)
{
    this->tabla=tabla;
    this->campos=campos;
    this->valores=valores;
}

void Insert::printDebug()
{
    cout<<"-------------"<<endl;
    cout<<"Debug insert:"<<endl;
    cout<<"Tabla:"<<endl;
    cout<<tabla<<endl;
    cout<<"Campos:"<<endl;
    for(int i=0;i<(int)campos.size();i++)
        cout<<campos[i].campo<<","<<campos[i].tabla<<endl;
    cout<<"Valores:"<<endl;
    for(int i=0;i<(int)valores.size();i++)
        cout<<valores[i].valor<<","<<valores[i].tipo<<endl;
    cout<<"-------------"<<endl;
}
