/*
 * File:   Sintactico.cpp
 * Author: userr
 *
 * Created on July 24, 2011, 10:51 PM
 */

#include "Sintactico.h"

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

bool Sintactico::analizarSelect(Lexico *lexico)
{
    this->lexico=lexico;
    return S();
}

bool Sintactico::S()
{
    int iterador=getIterador();
    Token t=getToken();

    if(!select())
        return false;
    t=nextToken();
    if(!from())
        return false;
    t=nextToken();

    iterador=getIterador();
    if(!where())
        setIterador(iterador);
    else
        t=nextToken();
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
        t=nextToken();
        if(t.tipo=="puntuacion" && t.lexema==",")
        {
            t=nextToken();
            if(listaDeCampos())
            {
                return true;
            }
        }
    }

    //campo
    setIterador(iterador);
    t=getToken();
    if(!campo())
        return false;
    return true;
}

bool Sintactico::campo()
{
    int iterador=getIterador();
    bool flag=true;
    //id . id
    Token t=getToken();
    if(t.tipo!="id")
        flag=false;
    t=nextToken();
    if(t.tipo!="puntuacion" || t.lexema!=".")
        flag=false;
    t=nextToken();
    if(t.tipo!="id")
        flag=false;
    if(flag)
        return true;
    //id
    setIterador(iterador);
    t=getToken();
    if(t.tipo!="id")
        return false;
    return true;
}

bool Sintactico::listaDeTablas()
{
    int iterador=getIterador();

    //tabla , listaDeTabla
    Token t=getToken();
    if(tabla())
    {
        t=nextToken();
        if(t.tipo=="puntuacion" && t.lexema==",")
        {
            t=nextToken();
            if(listaDeTablas())
            {
                return true;
            }
        }
    }

    //campo
    setIterador(iterador);
    t=getToken();
    if(!tabla())
        return false;
    return true;
}

bool Sintactico::tabla()
{
    int iterador=getIterador();
    bool flag=true;
    //id . id
    Token t=getToken();
    if(t.tipo!="id")
        flag=false;
    if(t.tipo!="puntuacion" || t.lexema!=".")
        flag=false;
    if(t.tipo!="id")
        flag=false;
    if(flag)
        return true;

    //id
    setIterador(iterador);
    t=getToken();
    if(t.tipo!="id")
        return false;
    return true;
}

bool Sintactico::listaDeValidaciones()
{
    int iterador=getIterador();

    //tabla , listaDeTabla
    Token t=getToken();
    if(validacion())
    {
        t=nextToken();
        if(opLogico())
        {
            t=nextToken();
            if(listaDeValidaciones())
            {
                return true;
            }
        }
    }

    //campo
    setIterador(iterador);
    t=getToken();
    if(!validacion())
        return false;
    return true;
}

bool Sintactico::validacion()
{
    Token t=getToken();
    if(!expIzq())
        return false;
    t=nextToken();
    if(!opRel())
        return false;
    t=nextToken();
    if(!expDer())
        return false;
    return true;
}

bool Sintactico::opLogico()
{
    Token t=getToken();
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
    if(t.tipo!="entero" && t.tipo!="decimal" && t.tipo!="char" && t.tipo!="varchar" && t.tipo!="booleano")
        return false;
    return true;
}