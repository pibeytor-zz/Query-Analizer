#include "update.h"

Update::Update()
{
}

Update::Update(string tabla,vector<Asignacion>asignaciones,vector<Validacion>validaciones,vector<string>operadores_logicos)
{
    this->tabla=tabla;
    this->asignaciones=asignaciones;
    this->validaciones=validaciones;
    this->operadores_logicos=operadores_logicos;
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

void Update::ejecutar(StorageManagerM* smm)
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
    for(int i=0;i<asignaciones.size();i++)
    {
        int pos=table->getPosicionCampo(asignaciones[i].campo);
        if(pos==-1)
        {
            cout<<"No existe el campo"<<endl;
            return;
        }
        campos_a_proyectar.push_back(pos);
    }
    //Validacion de match campo<->valores
    int j=0;
    for(int i=0;i<campos_a_proyectar.size();i++)
    {
        if(asignaciones[j].valor.tipo!=table->info_fields[campos_a_proyectar[i]].tipo && asignaciones[j].valor.tipo!="null")
        {
            cout<<"Los tipos de valores no corresponen."<<endl;
            return;
        }
        j++;
    }

    for(int i=0;i<(int)table->reccords.size();i++)
    {
        Reccord* reg=new Reccord(table->selectReccord(i)->fields);

        //Verificacion de validaciones
        if(!where(validaciones,operadores_logicos,table,reg))
            continue;
        //Creacion de campos rellenados con NULL
        //Seteacion de valores de los campos
        j=0;
        for(int k=0;k<campos_a_proyectar.size();k++)
        {
            if(asignaciones[j].valor.tipo=="null")
                reg->fields[campos_a_proyectar[k]]=new Field();
            if(asignaciones[j].valor.tipo=="entero")
                reg->fields[campos_a_proyectar[k]]=new Field(getInt(asignaciones[j].valor.valor));
            if(asignaciones[j].valor.tipo=="varchar")
                reg->fields[campos_a_proyectar[k]]=new Field((string)getString(asignaciones[j].valor.valor));
            if(asignaciones[j].valor.tipo=="char")
                reg->fields[campos_a_proyectar[k]]=new Field((char)getChar(asignaciones[j].valor.valor));
            if(asignaciones[j].valor.tipo=="booleano")
                reg->fields[campos_a_proyectar[k]]=new Field(getBool(asignaciones[j].valor.valor));
            j++;
        }
        //Validacion de acepacion de nulls
        bool null_invalido=false;
        for(int j=0;j<table->info_fields.size();j++)
            if((!(table->info_fields[j].acepta_null)) && reg->fields[j]->tipo=="null")
                null_invalido=true;
        if(null_invalido)
        {
            cout<<"Advertencia: el registro #"<<i<<" no se actualizado porque contiene nulls invalidos."<<endl;
            continue;
        }
        //Validacion de PKs
        bool pk_valido=cumplePK(reg,table,i);
        if(!pk_valido)
        {
            cout<<"Error: existe una violacion de PKs."<<endl;
            return;
        }
        //Updatacion de registros
        table->updateReccord(i,reg);
    }
    cout<<"Registros actualizados exitosamente."<<endl;
}
