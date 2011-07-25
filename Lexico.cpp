/* 
 * File:   Lexico.cpp
 * Author: userr
 * 
 * Created on July 24, 2011, 10:30 PM
 */

#include "Lexico.h"

Lexico::Lexico(string query)
{
    resetIterador();
    string temp="";
    for(int i=0;i<query.length();i++)
    {
        if(query[i]==' '||i==query.length()-1)
        {
            if(i==query.length()-1)
                temp+=query[i];
            tokens.push_back(Token("temp",temp));
            temp="";
        }
        else
            temp+=query[i];

    }
}

void Lexico::resetIterador()
{
    iterador=0;
}

Token Lexico::getToken()
{
    if(!quedanTokens())
        return Token("","");
    return tokens[iterador];
}

Token Lexico::nextToken()
{
    iterador++;
    if(!quedanTokens())
        return Token("","");
    return tokens[iterador];
}

bool Lexico::quedanTokens()
{
    return iterador<tokens.size();
}