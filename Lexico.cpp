/* 
 * File:   Lexico.cpp
 * Author: userr
 * 
 * Created on July 24, 2011, 10:30 PM
 */

#include "Lexico.h"

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
    if(a[0]<=57 && a[0]>=48)
        return false;
    for(i=0;i<getLength(a);i++)
        if(!esCaracterAscii(a[i])&&!esNumeroAscii(a[i]))
            return false;
    return true;
}

string Lexico::getTipo(string lexema)
{
    if(unsensitiveCompare(lexema,"true") || unsensitiveCompare(lexema,"false"))
        return "booleano";
    for(int i=0;i<palabras_reservadas.size();i++)
        if(unsensitiveCompare(lexema,palabras_reservadas[i]))
                return "palabra reservada";
    for(int i=0;i<operadores_logicos.size();i++)
        if(unsensitiveCompare(lexema,operadores_logicos[i]))
                return "operador logico";
    for(int i=0;i<puntuacion.size();i++)
        if(lexema==puntuacion[i])
                return "puntuacion";
    for(int i=0;i<operadores_relacionales.size();i++)
        if(lexema==operadores_relacionales[i])
                return "operador relacional";
    if(lexema[0]=='\"' && lexema[getLength(lexema)-1]=='\"')
        return "varchar";
    if(lexema[0]=='\'' && lexema[getLength(lexema)-1]=='\'' &&((getLength(lexema)==3 && lexema[1]!='\\')||(getLength(lexema)==4 && lexema[1]=='\\')))
        return "char";
    if(esDecimal(lexema))
        return "decimal";
    if(esEntero(lexema))
        return "entero";
    if(esId(lexema))
        return "id";
    
    return "error";
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
            tokens.push_back(Token(getTipo(temp),temp));
            temp="";
        }
        else
            temp+=query[i];
    }
}