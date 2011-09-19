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

void Insert::ejecutar(StorageManagerM* smm)
{
    //printDebug();

    //Buscacion de la tabla
    Table *table=smm->getTabla(tabla);
    if(table->nombre=="")
    {
        cout<<"La tabla no existe"<<endl;
        return;
    }

    //Buscacion de campos
    vector<int>campos_a_proyectar;
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

    //Validacion de match campo<->valores
    if(campos.size()!=valores.size())
    {
        cout<<"La cantidad de campos y valores no es la misma."<<endl;
        return;
    }
    int j=0;
    for(int i=0;i<campos_a_proyectar.size();i++)
    {
        if(valores[j].tipo!=table->info_fields[i].tipo)
        {
            cout<<"Los tipos de valores no corresponen."<<endl;
            return;
        }
    }

    //Creacion de campos rellenados con el valor default
    vector<Field*> fields;
    for(int i=0;i<table->info_fields.size();i++)
        fields.push_back(table->info_fields[i].valor_default);
    //Seteacion de valores de los campos
    j=0;
    for(int i=0;i<campos_a_proyectar.size();i++)
    {
        if(valores[j].tipo=="entero")
            fields[campos_a_proyectar[i]]=new Field(getInt(valores[j].valor));
        if(valores[j].tipo=="varchar")
            fields[campos_a_proyectar[i]]=new Field((string)getString(valores[j].valor));
        if(valores[j].tipo=="char")
            fields[campos_a_proyectar[i]]=new Field((char)getChar(valores[j].valor));
        if(valores[j].tipo=="booleano")
            fields[campos_a_proyectar[i]]=new Field(getBool(valores[j].valor));
        j++;
    }
    //Insertacion de registro
    Reccord* reg=new Reccord(fields);
    table->insertReccord(reg);
    cout<<"Registro insertdo con exito."<<endl;
}
