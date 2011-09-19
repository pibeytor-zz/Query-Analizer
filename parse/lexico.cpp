/*
 * File:   Lexico.cpp
 * Author: userr
 *
 * Created on July 24, 2011, 10:30 PM
 */

#include "lexico.h"

Lexico::Lexico(string query)
{
    palabras_reservadas.push_back("select");
    palabras_reservadas.push_back("from");
    palabras_reservadas.push_back("where");
    palabras_reservadas.push_back("insert");
    palabras_reservadas.push_back("into");
    palabras_reservadas.push_back("on");
    palabras_reservadas.push_back("values");
    palabras_reservadas.push_back("delete");
    palabras_reservadas.push_back("update");
    palabras_reservadas.push_back("set");
    palabras_reservadas.push_back("null");
    palabras_reservadas.push_back("as");
    palabras_reservadas.push_back("group");
    palabras_reservadas.push_back("by");

    puntuacion.push_back("(");
    puntuacion.push_back(")");
    puntuacion.push_back(",");
    puntuacion.push_back(".");
    puntuacion.push_back("*");

    operadores_relacionales.push_back("=");
    operadores_relacionales.push_back("!=");
    operadores_relacionales.push_back("<");
    operadores_relacionales.push_back(">");
    operadores_relacionales.push_back("<=");
    operadores_relacionales.push_back(">=");

    operadores_logicos.push_back("and");
    operadores_logicos.push_back("or");

    generarTokens(query);
}

bool Lexico::esCaracterAscii(char c)
{
    if((c>=65&&c<=90) || (c>=97&&c<=122))
        return true;
    false;
}

bool Lexico::esNumeroAscii(char c)
{
    if(c>=48&&c<=57)
        return true;
    return false;
}

int Lexico::getLength(string a)
{
    int res;
    for(res=0;a[res]!='\0';res++);
    return res;
}
bool Lexico::unsensitiveCompare(string a,string b)
{
    if(getLength(a)!=getLength(b))
        return false;
    for(int i=0;i<getLength(a);i++)
        if(a[i]!=b[i] && a[i]!=b[i]-32)
            return false;
    return true;
}

bool Lexico::esDecimal(string a)
{
    int i;
    for(i=0;i<getLength(a);i++)
        if(!esNumeroAscii(a[i]))
            break;
    if(a[i]!='.')
        return false;
    i++;
    for(;i<getLength(a);i++)
        if(!esNumeroAscii(a[i]))
            return false;
    return true;
}

bool Lexico::esEntero(string a)
{
    for(int i=0;i<getLength(a);i++)
        if(!esNumeroAscii(a[i]))
            return false;
    return true;
}

bool Lexico::esId(string a)
{
    int i;
    //si comienza con un numero
    if(esNumeroAscii(a[0]))
        return false;
    for(i=0;i<getLength(a);i++)
        if(!esCaracterAscii(a[i])&&!esNumeroAscii(a[i])&&a[i]!='_')
            return false;
    return true;
}

Token Lexico::getTipo(string lexema)
{
    if(unsensitiveCompare(lexema,"null"))
        return Token("null","null");
    if(unsensitiveCompare(lexema,"true"))
        return Token("booleano","true");
    if(unsensitiveCompare(lexema,"false"))
        return Token("booleano","false");
    for(int i=0;i<palabras_reservadas.size();i++)
        if(unsensitiveCompare(lexema,palabras_reservadas[i]))
                return Token("palabra reservada",palabras_reservadas[i]);
    for(int i=0;i<operadores_logicos.size();i++)
        if(unsensitiveCompare(lexema,operadores_logicos[i]))
                return Token("operador logico",lexema);
    for(int i=0;i<puntuacion.size();i++)
        if(lexema==puntuacion[i])
                return Token("puntuacion",lexema);
    for(int i=0;i<operadores_relacionales.size();i++)
        if(lexema==operadores_relacionales[i])
                return Token("operador relacional",lexema);
    if(lexema[0]=='\"' && lexema[getLength(lexema)-1]=='\"')
        return Token("varchar",lexema);
    if(lexema[0]=='\'' && lexema[getLength(lexema)-1]=='\'' &&((getLength(lexema)==3 && lexema[1]!='\\')||(getLength(lexema)==4 && lexema[1]=='\\')))
        return Token("char",lexema);
    if(esDecimal(lexema))
        return Token("decimal",lexema);
    if(esEntero(lexema))
        return Token("entero",lexema);
    if(esId(lexema))
        return Token("id",lexema);

    return Token("error",lexema);
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
    return getToken();
}

void Lexico::setIterador(int iterador)
{
    this->iterador=iterador;
}

int Lexico::getIterador()
{
    return iterador;
}

bool Lexico::quedanTokens()
{
    return iterador<tokens.size();
}

void Lexico::printTokens()
{
    for(int i=0;i<tokens.size();i++)
        cout<<tokens[i].lexema<<","<<tokens[i].tipo<<endl;
}

bool Lexico::correcto()
{
    for(int i=0;i<tokens.size();i++)
        if(tokens[i].tipo=="error")
        {
            cout<<"Error: \""<<tokens[i].lexema<<"\" es un token inválido."<<endl;
            return false;
        }
    return true;
}

bool Lexico::generarTokens(string query)
{
    tokens.clear();
    resetIterador();
    string temp="";
    for(int i=0;i<query.length();i++)
    {
        if(query[i]==' '||i==query.length()-1)
        {
            if(i==query.length()-1)
                temp+=query[i];
            tokens.push_back(getTipo(temp));
            temp="";
        }
        else
            temp+=query[i];
    }
}
