#ifndef LEXICO_H
#define LEXICO_H

/*
 * File:   Lexico.h
 * Author: userr
 *
 * Created on July 24, 2011, 10:30 PM
 */
#include "token.h"
#include <vector>
#include <iostream>
using namespace std;

class Lexico {
private:
    int iterador;
    vector<string> palabras_reservadas;
    vector<string> puntuacion;
    vector<string> operadores_relacionales;
    vector<string> operadores_logicos;
    vector<Token> tokens;
    //funciones basicas
    Token getTipo(string lexema);
    bool esEntero(string a);
    bool esDecimal(string a);
    bool esId(string a);
    bool generarTokens(string query);
    //operaciones sobre primitivos
    int getLength(string a);
    bool esCaracterAscii(char c);
    bool esNumeroAscii(char c);
    bool unsensitiveCompare(string a,string b);
public:
    //funciones basicas
    Lexico(string query);
    bool correcto();
    //manejo de iteradores
    void resetIterador();
    int getIterador();
    void setIterador(int iterador);
    //manejo de tokens
    Token getToken();
    Token nextToken();
    bool quedanTokens();
    void printTokens();
};
#endif // LEXICO_H
