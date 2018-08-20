#ifndef __AGENCIA__HPP__
#define __AGENCIA__HPP__
#include <list>
#include <string.h>
#include "venta.h"
#include "agencia.h"

using namespace std;
void Agencia::setNombre(string nombreIn)
{
		nombre = nombreIn;
}
void Agencia::setPass(string passIn)
{
		pass = passIn;
}
void Agencia::setVentas(list<Venta*> ventasIn)
{
		ventasAg = ventasIn;
}
string Agencia::getNombre()
{
		return nombre;
}
string Agencia::getPass()
{
		return pass;
}
list<Venta*>& Agencia::getVentas()
{
		return ventasAg;
}
#endif