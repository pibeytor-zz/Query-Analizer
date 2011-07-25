/* 
 * File:   Lexico.h
 * Author: userr
 *
 * Created on July 24, 2011, 10:30 PM
 */
#include "Token.h"
#include <vector>
#include <iostream>
using namespace std;

class Lexico {
public:
    vector<Token> tokens;
    int iterador;
    Lexico(string query);
    Lexico();
    void resetIterador();
    Token getToken();
    Token nextToken();
    bool quedanTokens();
};
