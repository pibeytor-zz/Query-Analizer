#include <vector>
#include <string>
using namespace std;

class Field
{
public:
	string tipo;//"varchar" "booleano" "entero" "caracter"
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
    Field(){}
};

class Reccord
{
    public:

        vector<Field>fields;

        Reccord(vector<Field>fields){
            this->fields=fields;
        }

        Field getField(int id)
        {
            return this->fields[id];
        }

        void setField(int id,Field field)
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
        Field valor_default;

        InfoField(string tipo,string nombre,bool pk,bool acepta_null,Field valor_default)
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
	vector<Reccord>reccords;

        Table()
        {

        }

        Table(string nombre,vector<InfoField>info_fields)
        {
            this->nombre=nombre;
            this->info_fields=info_fields;
        }

        void insertReccord(Reccord reccord)
        {
            this->reccords.push_back(reccord);
        }
        void deleteReccord(int id)
        {
            this->reccords.erase(reccords.begin()+id);
        }
        void updateReccord(int id,Reccord reccord)
        {
            this->reccords[id]=reccord;
        }
        Reccord selectReccord(int id)
        {
            return this->reccords[id];
        }
};

class StorageManagerM
{
public:
	vector<Table>table;

        StorageManagerM();
        void insertTable(Table tabla);
        Table getTabla(int id);
};
