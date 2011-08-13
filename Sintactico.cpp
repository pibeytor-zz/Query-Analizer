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
    t=nextToken();
    //etc...
    //TODO
    return true;
}
