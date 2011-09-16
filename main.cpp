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
    Field field1("varchar");
    InfoField info1("varchar","nombre",false,false,field1);
    vector<InfoField>info;
    info.push_back(info1);
    Table tab("tabla1",info);

    vector<Field> fields;
    fields.push_back(Field ((string)"string"));

            Reccord reg(fields);
           tab.insertReccord(reg);

           vector<Field> fields2;
           fields2.push_back(Field ((string)"string22"));
           Reccord reg2(fields2);
          tab.insertReccord(reg2);

           Iterator it;
           it.open(tab);
          // Reccord r=it.getNext().fields;
          // cout<<r.fields[0].varchar;
          // r=it.getNext().fields;
          // cout<<r.fields[0].varchar;
          // r=it.getNext().fields;
         //  cout<<r.fields[0].varchar;

           while(it.actual<it.tabla.reccords.size())
           {
               Reccord r=it.getNext();
               cout<<r.fields[0].varchar;
           }
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
        semantico.ejecutarSentencia();
    }

    return 0;
}
