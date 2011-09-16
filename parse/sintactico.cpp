/*
 * File:   Sintactico.cpp
 * Author: userr
 *
 * Created on July 24, 2011, 10:51 PM
 */

#include "sintactico.h"

void Sintactico::limpiarVariables()
{
    //Select* arbol_select;
    arbol_campos.clear();
    //Campo arbol_campo;
    arbol_tablas.clear();
    //Tabla arbol_tabla;
    arbol_validaciones.clear();
    //Validacion arbol_validacion;
    arbol_operadores.clear();
    //string arbol_operador;
    arbol_asignaciones.clear();
    //Asignacion arbol_asignacion;
    arbol_valores.clear();
    //Valor arbol_valor;
}

void Sintactico::resetIterador()
{
    lexico->resetIterador();
}
int Sintactico::getIterador()
{
    return lexico->getIterador();
}

void Sintactico::setIterador(int iterador)
{
    lexico->setIterador(iterador);
}

Token Sintactico::getToken()
{
    return lexico->getToken();
}

Token Sintactico::nextToken()
{
    return lexico->nextToken();
}

bool Sintactico::quedanTokens()
{
    return lexico->quedanTokens();
}

bool Sintactico::analizar(Lexico *lexico)
{
    this->lexico=lexico;
    Token t=getToken();
    if(t.tipo=="palabra reservada" && t.lexema=="select")
    {
        bool correcta=analizarSelect();
        if(correcta)
        {
            tipo_sentencia="select";
            return true;
        }
        return false;
    }
    limpiarVariables();
    if(t.tipo=="palabra reservada" && t.lexema=="update")
    {
        bool correcta=analizarUpdate();
        if(correcta)
        {
            tipo_sentencia="update";
            return true;
        }
        return false;
    }
    limpiarVariables();
    if(t.tipo=="palabra reservada" && t.lexema=="delete")
    {
        bool correcta=analizarDelete();
        if(correcta)
        {
            tipo_sentencia="delete";
            return true;
        }
        return false;
    }
    limpiarVariables();
    if(t.tipo=="palabra reservada" && t.lexema=="insert")
    {
        bool correcta=analizarInsert();
        if(correcta)
        {
            tipo_sentencia="insert";
            return true;
        }
        return false;
    }
    return false;
}

bool Sintactico::analizarSelect()
{
    int iterador=getIterador();
    Token t=getToken();

    if(!select())
        return false;
    vector<Campo>lista_campos_temp=arbol_campos;
    arbol_campos.clear();
    t=nextToken();
    if(!from())
        return false;
    t=nextToken();

    iterador=getIterador();
    if(!where())
        setIterador(iterador);
    else
        t=nextToken();

    iterador=getIterador();
    if(!groupBy())
        setIterador(iterador);
    else
        t=nextToken();
    arbol_select=new Select(lista_campos_temp,arbol_tablas,arbol_validaciones,arbol_operadores,arbol_campos);//semantico
    return !quedanTokens();
}

bool Sintactico::select()
{
    int iterador=getIterador();
    bool flag=true;

    //select <lista de campos>
    Token t=getToken();
    if(t.tipo!="palabra reservada" || t.lexema!="select")
        flag=false;
    t=nextToken();
    if(!listaDeCampos())
        flag=false;
    if(flag)
        return true;

    //select *
    setIterador(iterador);
    t=getToken();
    if(t.tipo!="palabra reservada" || t.lexema!="select")
        return false;
    t=nextToken();
    if(t.tipo!="puntuacion" || t.lexema!="*")
        return false;
    arbol_campos.push_back(Campo("*",""));
    return true;
}

bool Sintactico::from()
{
    Token t=getToken();
    if(t.tipo!="palabra reservada" || t.lexema!="from")
        return false;
    t=nextToken();
    if(!listaDeTablas())
        return false;
    return true;
}

bool Sintactico::where()
{
    Token t=getToken();
    if(t.tipo!="palabra reservada" || t.lexema!="where")
        return false;
    t=nextToken();
    if(!listaDeValidaciones())
        return false;
    return true;
}

bool Sintactico::listaDeCampos()
{
    int iterador=getIterador();

    //campo , listaDeCampos
    Token t=getToken();
    if(campo())
    {
        Campo campo_temp=arbol_campo;
        t=nextToken();
        if(t.tipo=="puntuacion" && t.lexema==",")
        {
            t=nextToken();
            if(listaDeCampos())
            {
                arbol_campos.insert(arbol_campos.begin(),campo_temp);
                return true;
            }
        }
    }

    //campo
    arbol_campos.clear();
    setIterador(iterador);
    t=getToken();
    if(!campo())
        return false;
    arbol_campos.push_back(arbol_campo);
    return true;
}

bool Sintactico::campo()
{
    //semantico
    string campo_temp="",tabla_temp="";
    //sintactico
    int iterador=getIterador();
    bool flag=true;
    //id . id
    Token t=getToken();
    tabla_temp=t.lexema;
    if(t.tipo!="id")
        flag=false;
    t=nextToken();
    if(t.tipo!="puntuacion" || t.lexema!=".")
        flag=false;
    t=nextToken();
    campo_temp=t.lexema;
    if(t.tipo!="id")
        flag=false;
    if(flag)
    {
        arbol_campo=Campo(campo_temp,tabla_temp);
        return true;
    }
    //id
    campo_temp=tabla_temp="";
    setIterador(iterador);
    t=getToken();
    campo_temp=t.lexema;
    if(t.tipo!="id")
        return false;
    arbol_campo=Campo(campo_temp,tabla_temp);
    return true;
}

bool Sintactico::listaDeTablas()
{
    int iterador=getIterador();

    //tabla , listaDeTabla
    Token t=getToken();
    if(tabla())
    {
        Tabla tabla_temp=arbol_tabla;
        t=nextToken();
        if(t.tipo=="puntuacion" && t.lexema==",")
        {
            t=nextToken();
            if(listaDeTablas())
            {
                arbol_tablas.insert(arbol_tablas.begin(),tabla_temp);
                return true;
            }
        }
    }

    //tabla
    arbol_tablas.clear();
    setIterador(iterador);
    t=getToken();
    if(!tabla())
        return false;
    arbol_tablas.push_back(arbol_tabla);
    return true;
}

bool Sintactico::tabla()
{
    //semantico
    string tabla_temp="",alias_temp="";
    //sintactico
    int iterador=getIterador();
    bool flag=true;
    //id . id
    Token t=getToken();
    tabla_temp=t.lexema;
    if(t.tipo!="id")
        flag=false;
    t=nextToken();
    if(t.tipo!="palabra reservada" || t.lexema!="as")
        flag=false;
    t=nextToken();
    alias_temp=t.lexema;
    if(t.tipo!="id")
        flag=false;
    if(flag)
    {
        arbol_tabla=Tabla(tabla_temp,alias_temp);
        return true;
    }

    //id
    tabla_temp=alias_temp="";
    setIterador(iterador);
    t=getToken();
    tabla_temp=t.lexema;
    if(t.tipo!="id")
        return false;
    arbol_tabla=Tabla(tabla_temp,alias_temp);
    return true;
}

bool Sintactico::listaDeValidaciones()
{
    int iterador=getIterador();

    //tabla , listaDeTabla
    Token t=getToken();
    if(validacion())
    {
        Validacion validacion_temp=arbol_validacion;
        t=nextToken();
        if(opLogico())
        {
            string operador_temp=arbol_operador;
            t=nextToken();
            if(listaDeValidaciones())
            {
                arbol_validaciones.insert(arbol_validaciones.begin(),validacion_temp);
                arbol_operadores.insert(arbol_operadores.begin(),operador_temp);
                return true;
            }
        }
    }

    //campo
    arbol_validaciones.clear();
    setIterador(iterador);
    t=getToken();
    if(!validacion())
        return false;
    arbol_validaciones.push_back(arbol_validacion);
    return true;
}

bool Sintactico::validacion()
{
    //semantica
    string tipo_temp="";
    //sintactico
    Token t=getToken();
    string exp_izq_temp="",operador_temp="",exp_der_temp="";
    exp_izq_temp=t.lexema;
    if(!expIzq())
        return false;
    t=nextToken();
    operador_temp=t.lexema;
    if(!opRel())
        return false;
    t=nextToken();
    tipo_temp=t.tipo;
    exp_der_temp=t.lexema;
    if(!expDer())
        return false;
    arbol_validacion=Validacion(exp_izq_temp,operador_temp,exp_der_temp,tipo_temp);
    return true;
}

bool Sintactico::opLogico()
{
    Token t=getToken();
    arbol_operador=t.lexema;
    if(t.tipo=="operador logico")
        return true;
    return false;
}

bool Sintactico::expIzq()
{
    Token t=getToken();
    if(!campo())
        return false;
    return true;
}

bool Sintactico::expDer()
{
    int iterador=getIterador();
    bool flag=true;

    //campo
    Token t=getToken();
    if(!campo())
        flag=false;
    if(flag)
        return true;

    //valor
    setIterador(iterador);
    t=getToken();
    if(!valor())
        return false;
    return true;
}

bool Sintactico::opRel()
{
    Token t=getToken();
    if(t.tipo!="operador relacional")
        return false;
    if(t.lexema!="=" && t.lexema!="!=" && t.lexema!="<" && t.lexema!=">" && t.lexema!="<=" && t.lexema!=">=")
        return false;
    return true;
}

bool Sintactico::valor()
{
    Token t=getToken();
    arbol_valor=Valor(t.lexema,t.tipo);
    if(t.tipo!="entero" && t.tipo!="decimal" && t.tipo!="char" && t.tipo!="varchar" && t.tipo!="booleano")
        return false;
    return true;
}

bool Sintactico::groupBy()
{
    //group by <lista de campos>
    Token t=getToken();
    if(t.tipo!="palabra reservada" || t.lexema!="group")
        return false;
    t=nextToken();
    if(t.tipo!="palabra reservada" || t.lexema!="by")
        return false;
    t=nextToken();
    if(!listaDeCampos())
        return false;
    return true;
}

bool Sintactico::analizarUpdate()
{
    //semantica
    string tabla_temp="";
    //sintactico
    Token t=getToken();
    if(t.tipo!="palabra reservada" || t.lexema!="update")
        return false;
    t=nextToken();
    tabla_temp=t.lexema;
    if(t.tipo!="id")
        return false;
    t=nextToken();
    if(t.tipo!="palabra reservada" || t.lexema!="set")
        return false;
    t=nextToken();
    if(!listaDeAsignaciones())
        return false;
    t=nextToken();
    int iterador=getIterador();
    if(!where())
        setIterador(iterador);
    else
        t=nextToken();
    arbol_update=new Update(tabla_temp,arbol_asignaciones,arbol_validaciones);
    return !quedanTokens();
}

bool Sintactico::listaDeAsignaciones()
{
    int iterador=getIterador();

    //asignacion listaDeCampos
    Token t=getToken();
    if(asignacion())
    {
        Asignacion asignacion_temp=arbol_asignacion;
        t=nextToken();
        if(listaDeAsignaciones())
        {
            arbol_asignaciones.insert(arbol_asignaciones.begin(),asignacion_temp);
            return true;
        }
    }

    //asignacion
    arbol_asignaciones.clear();
    setIterador(iterador);
    t=getToken();
    if(!asignacion())
        return false;
    arbol_asignaciones.push_back(arbol_asignacion);
    return true;
}

bool Sintactico::asignacion()
{
    string campo_temp="",valor_temp="",tipo_temp="";
    Token t=getToken();
    campo_temp=t.lexema;
    if(!campo())
        return false;
    t=nextToken();
    if(t.tipo!="operador relacional" || t.lexema!="=")
        return false;
    t=nextToken();
    valor_temp=t.lexema;
    tipo_temp=t.tipo;
    if(!valor())
        return false;
    arbol_asignacion=Asignacion(campo_temp,Valor(valor_temp,tipo_temp));
    return true;
}

bool Sintactico::analizarDelete()
{
    string tabla_temp="";
    Token t=getToken();
    if(t.tipo!="palabra reservada" && t.lexema!="delete")
        return false;
    t=nextToken();
    if(t.tipo!="palabra reservada" && t.lexema!="from")
        return false;
    t=nextToken();
    tabla_temp=t.lexema;
    if(!tabla())
        return false;
    t=nextToken();
    int iterador=getIterador();
    if(!where())
        setIterador(iterador);
    else
        t=nextToken();
    arbol_delete=new Delete(tabla_temp,arbol_validaciones);
    return !quedanTokens();
}

bool Sintactico::analizarInsert()
{
    //semantico
    string tabla_temp="";
    //sintactico
    Token t=getToken();

    if(t.tipo!="palabra reservada" && t.lexema!="insert")
        return false;
    t=nextToken();
    if(t.tipo!="palabra reservada" && t.lexema!="into")
        return false;
    t=nextToken();
    tabla_temp=t.lexema;
    if(!tabla())
        return false;
    t=nextToken();
    if(t.tipo!="palabra reservada" && t.lexema!="on")
        return false;
    t=nextToken();
    if(t.tipo!="puntuacion" && t.lexema!="(")
        return false;
    t=nextToken();
    if(!listaDeCampos())
        return false;
    t=nextToken();
    if(t.tipo!="puntuacion" && t.lexema!=")")
        return false;
    t=nextToken();
    if(t.tipo!="palabra reservada" && t.lexema!="values")
        return false;
    t=nextToken();
    if(t.tipo!="puntuacion" && t.lexema!="(")
        return false;
    t=nextToken();
    if(!listaDeValores())
        return false;
    t=nextToken();
    if(t.tipo!="puntuacion" && t.lexema!=")")
        return false;
    t=nextToken();
    arbol_insert=new Insert(tabla_temp,arbol_campos,arbol_valores);
    return !quedanTokens();
}

bool Sintactico::listaDeValores()
{
    int iterador=getIterador();

    //valor , listaDeValores
    Token t=getToken();
    if(valor())
    {
        Valor valor_temp=arbol_valor;
        t=nextToken();
        if(t.tipo=="puntuacion" && t.lexema==",")
        {
            t=nextToken();
            if(listaDeValores())
            {
                arbol_valores.insert(arbol_valores.begin(),valor_temp);
                return true;
            }
        }
    }

    //campo
    arbol_valores.clear();
    setIterador(iterador);
    t=getToken();
    if(!valor())
        return false;
    arbol_valores.push_back(arbol_valor);
    return true;
}
