/*
 * File:   main.cpp
 * Author: userr
 *
 * Created on July 24, 2011, 8:02 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

#include "Sintactico.h"


/*
 *
 */

int main(int argc, char *argv[])
{
    for(;;)
    {
        //Captura de sentencia SQL
        cout<<"\n> ";
        string query="";
        std::getline(std::cin, query);
        if(query=="salir")
            break;

        //Analisis lexico
        Lexico *l=new Lexico(query);
        l->printTokens();
        if(!l->correcto())
        {
            cout<<"Lexico incorrecto, la sentencia no pudo ejecutar."<<endl;
            continue;
        }

        //Analisis sintactico
        Sintactico s;
        if(s.analizar(l))
            cout<<"Sintaxis correcta"<<endl;
        else
            cout<<"Sintaxis incorrecta"<<endl;
    }
    return 0;
}
