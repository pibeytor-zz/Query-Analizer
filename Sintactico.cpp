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
    for(int i=0;i<lexico->tokens.size();i++)
        cout<<lexico->tokens[i].lexema<<endl;
    if(!select())
        return false;
    if(!from())
        return false;
    if(!where())
        return false;
    return !quedanTokens();
}

bool Sintactico::select()
{
    int i_temp=lexico->iterador;
    if(getToken().lexema=="SELECT")
        nextToken();
    else
    {
        lexico->iterador=i_temp;
        return false;
    }

    if(!campos())
    {
        lexico->iterador=i_temp;
        return false;
    }
    return true;
}

bool Sintactico::from()
{
    int i_temp=lexico->iterador;
    if(getToken().lexema=="FROM")
        nextToken();
    else
    {
        lexico->iterador=i_temp;
        return false;
    }

    if(!tablas())
    {
        lexico->iterador=i_temp;
        return false;
    }
    return true;
}

bool Sintactico::where()
{
    int i_temp=lexico->iterador;
    if(getToken().lexema=="WHERE")
        nextToken();
    else
    {
        lexico->iterador=i_temp;
        return true;
    }

    if(!validaciones())
    {
        lexico->iterador=i_temp;
        return false;
    }
    return true;
}

bool Sintactico::campos()
{
    int i_temp=lexico->iterador;
    nextToken();
    return true;
}

bool Sintactico::tablas()
{
    int i_temp=lexico->iterador;
    nextToken();
    return true;
}

bool Sintactico::validaciones()
{
    int i_temp=lexico->iterador;
    //nextToken();
    if(nextToken().lexema!="=")
    {
        lexico->iterador=i_temp;
        return false;
    }
    if(nextToken().lexema=="")
        return false;
    nextToken();
    return true;
}