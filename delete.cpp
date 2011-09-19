#include "delete.h"

Delete::Delete()
{
}

Delete::Delete(string tabla,vector<Validacion>validaciones,vector<string>operadores_logicos)
{
    this->tabla=tabla;
    this->validaciones=validaciones;
    this->operadores_logicos=operadores_logicos;
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

void Delete::ejecutar(StorageManagerM* smm)
{
    //printDebug();

    //Buscacion de la tabla
    Table *table=smm->getTabla(tabla);
    if(table->nombre=="")
    {
        cout<<"La tabla no existe"<<endl;
        return;
    }
    //Buscacion de registros a borrar
    vector<int>registros_a_borrar;
    for(int i=0;(int)i<table->reccords.size();i++)
    {
        if(where(validaciones,operadores_logicos,table,table->selectReccord(i)))
            registros_a_borrar.push_back(i);
    }
    //Borracion de registros de abajo hacia arriba para no interferir en los indices
    for(int i=(int)table->reccords.size()-1;i>=0;i--)
    {
        if(contains(registros_a_borrar,i))
            table->deleteReccord(i);
    }
    cout<<"Registros borrados exitosamente";
}
