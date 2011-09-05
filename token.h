#ifndef TOKEN_H
#define TOKEN_H

/*
 * File:   Token.h
 * Author: userr
 *
 * Created on July 24, 2011, 9:24 PM
 */
#include <string>
using namespace std;

class Token {
public:
    string tipo;
    string lexema;
    Token(string tipo,string lexema);
};

#endif // TOKEN_H
