#include "select.h"

Select::Select(vector<Campo>campos,vector<Tabla>tablas,vector<Validacion>validaciones,vector<string>operadores_logicos,vector<Campo>groupBy)
{
    this->campos=campos;
    this->tablas=tablas;
    this->validaciones=validaciones;
    this->operadores_logicos=operadores_logicos;
    this->groupBy=groupBy;
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
    cout<<"Group by:"<<endl;
    for(int i=0;i<(int)groupBy.size();i++)
        cout<<groupBy[i].campo<<","<<groupBy[i].tabla<<endl;
    cout<<"-------------"<<endl;
}
bool contains(vector<int>enteros,int entero)
{
    for(int i=0;i<enteros.size();i++)
        if(enteros[i]==entero)
            return true;
    return false;
}

void Select::ejecutar(StorageManagerM* smm)
{
    //printDebug();

    //Buscacion de la tabla
    Table *table=smm->getTabla(this->tablas[0].tabla);
    if(table->nombre=="")
    {
        cout<<"La tabla no existe"<<endl;
        return;
    }

    //Buscacion de campos
    vector<int>campos_a_proyectar;
    if(campos[0].campo=="*")
    {
        for(int i=0;i<table->info_fields.size();i++)
            campos_a_proyectar.push_back(i);
    }else
    {
        for(int i=0;i<campos.size();i++)
        {
            int pos=table->getPosicionCampo(campos[i].campo);
            if(pos==-1)
            {
                cout<<"No existe el campo"<<endl;
                return;
            }
            campos_a_proyectar.push_back(pos);
        }
    }

    //Recorrido de campos con el iterador
    Iterator it;
    it.open(table);

    for(int i=0;i<table->info_fields.size();i++)
        if(contains(campos_a_proyectar,i))
            cout<<table->info_fields[i].nombre<<"\t";

    cout<<endl;

    while(it.actual<it.tabla->reccords.size())
    {
        Reccord* r=it.getNext();

        for(int i=0;i<it.tabla->info_fields.size();i++)
        {
            if(contains(campos_a_proyectar,i))
            {
                if(r->fields[i]->tipo=="entero")
                    cout<<r->fields[i]->entero;
                if(r->fields[i]->tipo=="varchar")
                    cout<<r->fields[i]->varchar;
                if(r->fields[i]->tipo=="char")
                    cout<<r->fields[i]->caracter;
                if(r->fields[i]->tipo=="booleano")
                    cout<<r->fields[i]->booleano;
                if(r->fields[i]->tipo=="NULL")
                    cout<<"NULL";
                cout<<"\t";
            }
        }
        cout<<endl;
    }
}
