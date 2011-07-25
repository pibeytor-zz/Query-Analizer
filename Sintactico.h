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
    bool analizarSelect(Lexico *lexico);
    void resetIterador();
    Token getToken();
    Token nextToken();
    bool quedanTokens();

    bool S();
    bool select();
    bool from();
    bool where();
    bool campos();
    bool listaDeCampos();
    bool tablas();
    bool validaciones();
    bool validacion();
    bool expIzq();
    bool expDer();
    bool campo();
    bool tabla();
    bool opLogico();
    bool opRel();
};