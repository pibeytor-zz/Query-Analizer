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
    Token t=getToken();
    if(t.lexema!="select" || t.tipo!="palabra reservada")
        return false;

    t=nextToken();

    if(!Campo())
        return false;

    return true;
}

bool Sintactico::Campo()
{
    Token t=getToken();
    int pos_temp=getIterador();
    bool correcto=true;
    if(t.tipo!="puntuacion" && t.lexema!="*")
        correcto=false;
    t=nextToken();
    if(t.tipo!="puntuacion" && t.lexema!=",")
        correcto=false;
    t=nextToken();
    if(t.tipo!="id")
        correcto=false;
    t=nextToken();
    if(correcto==true)
        return true;

    correcto=true;
    setIterador(pos_temp);
    t=getToken();
    if(t.tipo!="id")
        correcto=false;
    t=nextToken();
    if(t.tipo!="puntuacion" && t.lexema!=",")
        correcto=false;
    t=nextToken();
    if(t.tipo!="id")
        correcto=false;
    t=nextToken();
    return correcto;
}
