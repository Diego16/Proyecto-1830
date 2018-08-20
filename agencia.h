#ifndef __AGENCIA__H__
#define __AGENCIA__H__
#include <list>
#include <string.h>
#include "venta.h"

using namespace std;


class Agencia {

private:
		string nombre;
		string pass;
		list<Venta*> ventasAg;

public:
		void setNombre(string nombreIn);
		void setPass(string passIn);
		void setVentas(list<Venta*> ventasIn);
		string getNombre();
		string getPass();
		list<Venta*>& getVentas();
};

#include "agencia.hxx"
#endif
