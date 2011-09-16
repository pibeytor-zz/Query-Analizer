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
		tipo="caracter";
	}
};

class Reccord
{
	vector<Field>fields;

        Reccord(vector<Field>fields);
        Field getField(int id);
        void setField(int id,Field field);
};

class InfoField
{
	string tipo;
	string nombre;
	bool pk;
	bool acepta_null;
        Field valor_default;

        InfoField(string tipo,string nombre,bool pk,bool acepta_null,Field valor_default);
};

class Table
{
	string nombre;
	vector<InfoField>info_fields;
	vector<Reccord>reccords;

        Table(string nombre,vector<InfoField>info_fields);
        void insertReccord(Reccord reccord);
        void deleteReccord(int id);
        void updateReccord(int id,Reccord reccord);
        Reccord selectReccord(int id);
};

class StorageManagerM
{
	vector<Table>table;

        StorageManagerM();
        void insertTable(Table tabla);
        Tabla getTabla(int id);
};
