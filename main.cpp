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

#include "parse/sintactico.h"
#include "sm/StorageManager.h"

int main()
{
    StorageManager sm;
    sm.createTableSpace("MiBdd","1.0","clave",40);
    InfoMDC imdc;
    imdc.tipo_campo=1;
    strcpy(imdc.nombre_campo,"campo");
    imdc.size=sizeof(short);
    imdc.nulls=false;
    imdc.PK=false;
    strcpy(imdc.DEFAULT,"mi default");

    InfoMDC imdc2;
    imdc2.tipo_campo=1;
    strcpy(imdc2.nombre_campo,"campo");
    imdc2.size=sizeof(short);
    imdc2.nulls=false;
    imdc2.PK=false;
    strcpy(imdc2.DEFAULT,"mi default");

    InfoMDC arr_imdc[2];
    arr_imdc[0]=imdc;
    arr_imdc[1]=imdc2;

    sm.createTable("tabla",2,arr_imdc);

    SystemBlock sb;
    sb.escribir();
    sb.acomodarPrimerLibre();
    cout<<sb.getFree();
    /*
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
        Sintactico s;
        if(s.analizar(l))
            cout<<"Sintaxis correcta"<<endl;
        else
            cout<<"Sintaxis incorrecta"<<endl;
    }
    */
    return 0;
}
