#ifndef VALIDACION_H
#define VALIDACION_H
#include <string>
using namespace std;
class Validacion
{
public:
    string exp_izq,operador,exp_der,tipo;
    Validacion();
    Validacion(string exp_izq,string operador,string exp_der,string tipo);
};

#endif // VALIDACION_H
