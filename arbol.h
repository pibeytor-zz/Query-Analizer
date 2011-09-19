#ifndef ARBOL_H
#define ARBOL_H

#include "smm/iterator.h"
#include "parse/valor.h"
#include "parse/validacion.h"
#include <cstdlib>

class Arbol
{
public:
    Arbol();
    int eval(Field* f,string valor,string tipo)
    {
        if(f->tipo!=tipo)
            return -2;
        if(tipo=="varchar")
        {
            if(f->varchar==getString(valor))
                return 0;
            return -1;
        }
        if(tipo=="booleano")
        {
            if(f->booleano==getBool(valor))
                return 0;
            return -1;
        }
        if(tipo=="entero")
        {
            if(f->entero<getInt(valor))
                return -1;
            if(f->entero>getInt(valor))
                return 1;
            return 0;
        }
        if(tipo=="char")
        {
            if(f->caracter<getChar(valor))
                return -1;
            if(f->caracter>getChar(valor))
                return 1;
            return 0;
        }
        return -3;
    }

    int eval(Field* f,Field* f2)
    {
        if(f->tipo!=f2->tipo)
            return -2;
        if(f->tipo=="varchar")
        {
            if(f->varchar==f2->varchar)
                return 0;
            return -1;
        }
        if(f->tipo=="booleano")
        {
            if(f->booleano==f2->booleano)
                return 0;
            return -1;
        }
        if(f->tipo=="entero")
        {
            if(f->entero<f2->entero)
                return -1;
            if(f->entero>f2->entero)
                return 1;
            return 0;
        }
        if(f->tipo=="char")
        {
            if(f->caracter<f2->caracter)
                return -1;
            if(f->caracter>f2->caracter)
                return 1;
            return 0;
        }
        return -3;
    }

    string getString(string valor)
    {
        string resultado="";
        for(int i=1;i<valor.length()-1;i++)
        {
            resultado+=valor[i];
        }
        return resultado;
    }
    int getInt(string valor)
    {
        return atoi(valor.c_str());
    }
    bool getBool(string valor)
    {
        return valor=="true";
    }
    char getChar(string valor)
    {
        return valor[1];
    }
    bool contains(vector<int>enteros,int entero)
    {
        for(int i=0;i<enteros.size();i++)
            if(enteros[i]==entero)
                return true;
        return false;
    }
    bool verificarValidacion(Validacion validacion,Table*table,Reccord *reccord)
    {
        for(int i=0;i<(int)table->info_fields.size();i++)
        {
            if(table->info_fields[i].nombre==validacion.exp_izq)
                if(!eval(reccord->fields[i],validacion.exp_der,reccord->fields[i]->tipo)==0)
                    return false;
        }
        return true;
    }
    bool where(vector<Validacion>validaciones,vector<string>operadores_logicos,Table*table,Reccord *reccord)
    {
        bool resultado=true;
        for(int i=0;i<(int)validaciones.size();i++)
        {
            Validacion v=validaciones[i];
            bool actual=verificarValidacion(v,table,reccord);
            if(i!=0)
            {
                if(operadores_logicos[i-1]=="and")
                    resultado=resultado&&actual;
                else
                    resultado=resultado||actual;
            }else
                resultado=actual;
        }
        return resultado;
    }
    bool cumplePK(Reccord *r,Reccord *rtabla,vector<InfoField>ifs)
    {
        int i;
        for(i=0;i<ifs.size();i++)
            if( ifs[i].pk && eval(r->fields[i],rtabla->fields[i])!=0 )
                    return true;
        return false;
    }
    bool cumplePK(Reccord *r, Table *table,int ignorarme)
    {
        for(int i=0;i<table->reccords.size();i++)
        {
            if(i==ignorarme)
                continue;
            if(!cumplePK(r,table->reccords[i],table->info_fields))
                return false;
        }
        return true;
    }
};

#endif // ARBOL_H
