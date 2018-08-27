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
		int cantVentas;
		list<Venta*> ventasAg;

public:
		void setNombre(string nombreIn);
		void setPass(string passIn);
		void setVentas(list<Venta*> ventasIn);
		void setCantventas(int cantVentasIn);
		string getNombre();
		string getPass();
		list<Venta*>& getVentas();
		int getCantVentas();
};

#include "agencia.hxx"
#endif
