#include <vector>
#include <string>
using namespace std;

class Field
{
public:
        string tipo;//"varchar" "booleano" "entero" "caracter" "NULL"
	string varchar;
    bool booleano;
	int entero;
	char caracter;

    Field(string varchar)
	{
		this->varchar=varchar;
		tipo="varchar";
	}
    Field(bool booleano)
	{
		this->booleano=booleano;
		tipo="booleano";
	}
    Field(int entero)
	{
		this->entero=entero;
		tipo="entero";
	}
    Field(char caracter)
	{
                this->caracter=caracter;
                tipo="char";
	}
    Field()
    {
        tipo="NULL";
    }
};

class Reccord
{
    public:

        vector<Field*>fields;

        Reccord(vector<Field*>fields){
            this->fields=fields;
        }

        Field* getField(int id)
        {
            return this->fields[id];
        }

        void setField(int id,Field *field)
        {
            this->fields[id]=field;
        }
};

class InfoField
{
public:
	string tipo;
	string nombre;
	bool pk;
	bool acepta_null;
        Field* valor_default;

        InfoField(string tipo,string nombre,bool pk,bool acepta_null,Field* valor_default)
        {
            this->tipo=tipo;
            this->nombre=nombre;
            this->pk=pk;
            this->acepta_null=acepta_null;
            this->valor_default=valor_default;
        }
};

class Table
{
public:
	string nombre;
	vector<InfoField>info_fields;
        vector<Reccord*>reccords;

        Table()
        {

        }

        Table(string nombre,vector<InfoField>info_fields)
        {
            this->nombre=nombre;
            this->info_fields=info_fields;
        }

        void insertReccord(Reccord* reccord)
        {
            this->reccords.push_back(reccord);
        }
        void deleteReccord(int id)
        {
            this->reccords.erase(reccords.begin()+id);
        }
        void updateReccord(int id,Reccord* reccord)
        {
            this->reccords[id]=reccord;
        }
        Reccord* selectReccord(int id)
        {
            return this->reccords[id];
        }
        int getPosicionCampo(string campo)
        {
            for(int i=0;i<info_fields.size();i++)
                if(info_fields[i].nombre==campo)
                    return i;
            return -1;
        }
};

class StorageManagerM
{
public:
        vector<Table*>tables;

        StorageManagerM()
        {
            insertTable(getTablaEmpleado());
            insertTable(getTablaBono());
        }

        void insertTable(Table *tabla)
        {
            tables.push_back(tabla);
        }

        Table *getTabla(int id)
        {
            return tables[id];
        }

        Table *getTabla(string nombre)
        {
            for(int i=0;i<tables.size();i++)
                if(tables[i]->nombre==nombre)
                    return tables[i];
            return new Table("",vector<InfoField>());
        }

        Table *getTablaEmpleado()
        {
            //Definicion de infocampos
            vector<InfoField>info;
            info.push_back(InfoField("entero","codigo",false,false,new Field(0)));
            info.push_back(InfoField("varchar","nombre",false,false,new Field((string)"default")));
            info.push_back(InfoField("char","sexo",false,false,new Field()));
            info.push_back(InfoField("booleano","tiempo_completo",false,false,new Field(false)));

            //Creacion de tabla
            Table *tab=new Table("Empleado\0",info);

            //Insert reccords
            vector<Field*> fields;
            fields.push_back(new Field(10));
            fields.push_back(new Field((string)"Carlos"));
            fields.push_back(new Field((char)'m'));
            fields.push_back(new Field(true));
            Reccord* reg=new Reccord(fields);
            tab->insertReccord(reg);

            vector<Field*> fields2;
            fields2.push_back(new Field(11));
            fields2.push_back(new Field((string)"Maria"));
            fields2.push_back(new Field((char)'f'));
            fields2.push_back(new Field(false));
            Reccord* reg2=new Reccord(fields2);
            tab->insertReccord(reg2);

            return tab;
        }

        Table *getTablaBono()
        {
            //Definicion de infocampos
            vector<InfoField>info;
            info.push_back(InfoField("entero","codigo",false,false,new Field(0)));
            info.push_back(InfoField("entero","bono",false,false,new Field(0)));

            //Creacion de tabla
            Table *tab=new Table("Bono\0",info);

            //Insert reccords
            vector<Field*> fields;
            fields.push_back(new Field(10));
            fields.push_back(new Field(500));
            Reccord* reg=new Reccord(fields);
            tab->insertReccord(reg);

            vector<Field*> fields2;
            fields2.push_back(new Field(11));
            fields2.push_back(new Field(1000));
            Reccord* reg2=new Reccord(fields2);
            tab->insertReccord(reg2);

            vector<Field> fields3;
            fields3.push_back(Field(10));
            fields3.push_back(Field(700));
            Reccord* reg3=new Reccord(fields);
            tab->insertReccord(reg3);

            return tab;
        }
};
