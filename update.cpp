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
        if(asignaciones[j].valor.tipo!=table->info_fields[campos_a_proyectar[i]].tipo)
        {
            cout<<"Los tipos de valores no corresponen."<<endl;
            return;
        }
        j++;
    }

    //Creacion de campos rellenados con NULL
    Reccord* reg=table->selectReccord(0);
    //Seteacion de valores de los campos
    j=0;
    for(int i=0;i<campos_a_proyectar.size();i++)
    {
        if(asignaciones[j].valor.tipo=="entero")
            reg->fields[campos_a_proyectar[i]]=new Field(getInt(asignaciones[j].valor.valor));
        if(asignaciones[j].valor.tipo=="varchar")
            reg->fields[campos_a_proyectar[i]]=new Field((string)getString(asignaciones[j].valor.valor));
        if(asignaciones[j].valor.tipo=="char")
            reg->fields[campos_a_proyectar[i]]=new Field((char)getChar(asignaciones[j].valor.valor));
        if(asignaciones[j].valor.tipo=="booleano")
            reg->fields[campos_a_proyectar[i]]=new Field(getBool(asignaciones[j].valor.valor));
        j++;
    }
    //Updatacion de registro
    table->updateReccord(0,reg);
    cout<<"Registro insertdo con exito."<<endl;
}
