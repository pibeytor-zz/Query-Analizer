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

#include "parse/semantico.h"
#include "sm/StorageManager.h"

int main()
{
    StorageManagerM *smm=new StorageManagerM;
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
        //l->printTokens();
        if(!l->correcto())
        {
            cout<<"Lexico incorrecto, la sentencia no pudo ejecutar."<<endl;
            continue;
        }

        //Analisis sintactico
        Sintactico sintactico;
        if(!sintactico.analizar(l))
        {
            cout<<"Sintaxis incorrecta"<<endl;
            continue;
        }
        Semantico semantico(sintactico);
        semantico.ejecutarSentencia(smm);
    }

    return 0;
}
