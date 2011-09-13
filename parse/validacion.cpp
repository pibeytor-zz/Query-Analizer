#include "validacion.h"

Validacion::Validacion()
{
}

Validacion::Validacion(string exp_izq,string operador,string exp_der,string tipo)
{
    this->exp_izq=exp_izq;
    this->operador=operador;
    this->exp_der=exp_der;
    this->tipo=tipo;
}
