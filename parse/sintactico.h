#ifndef SINTACTICO_H
#define SINTACTICO_H

/*
 * File:   Sintactico.h
 * Author: userr
 *
 * Created on July 24, 2011, 10:51 PM
 */
#include "lexico.h"
#include "select.h"
#include "insert.h"
#include "update.h"
#include "delete.h"
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

    //Analizar
    Select* arbol_select;
    Insert* arbol_insert;
    Update* arbol_update;
    Delete* arbol_delete;

    vector<Campo> arbol_campos;
    Campo arbol_campo;
    vector<Tabla> arbol_tablas;
    Tabla arbol_tabla;
    vector<Validacion> arbol_validaciones;
    Validacion arbol_validacion;
    vector<string> arbol_operadores;
    string arbol_operador;
    vector<Asignacion>arbol_asignaciones;
    Asignacion arbol_asignacion;
    vector<Valor>arbol_valores;
    Valor arbol_valor;

    void limpiarVariables();
    bool analizar(Lexico *lexico);

    //Select
    bool analizarSelect();
    bool select();
    bool from();
    bool where();
    bool listaDeCampos();
    bool campo();
    bool tabla();
    bool listaDeTablas();
    bool listaDeValidaciones();
    bool validacion();
    bool expIzq();
    bool expDer();
    bool opRel();
    bool opLogico();
    bool valor();

    //Update
    bool analizarUpdate();
    bool listaDeAsignaciones();
    bool asignacion();

    //Delete
    bool analizarDelete();

    //Insert
    bool analizarInsert();
    bool listaDeValores();
};
#endif // SINTACTICO_H
