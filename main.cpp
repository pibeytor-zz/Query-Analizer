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
        cout<<"\n> ";
        string query="";
        std::getline(std::cin, query);
        if(query=="salir")
            break;
        Lexico *l=new Lexico(query);
        Sintactico s;
        if(s.analizarSelect(l))
            cout<<"Sintaxis correcta"<<endl;
        else
            cout<<"Sintaxis incorrecta"<<endl;
    }
    return 0;
}