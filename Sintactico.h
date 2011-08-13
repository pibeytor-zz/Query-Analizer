/* 
 * File:   Sintactico.h
 * Author: userr
 *
 * Created on July 24, 2011, 10:51 PM
 */
#include "Lexico.h"
using namespace std;

class Sintactico {
public:
    Lexico *lexico;
    //manejo de iterador acutal
    void resetIterador();
    int getIterador();
    void setIterador(int iterador);
    //manejo de tokens actuales
    Token getToken();
    Token nextToken();
    bool quedanTokens();

    //TODO
    bool analizarSelect(Lexico *lexico);
    bool S();
};