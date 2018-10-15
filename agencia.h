#ifndef __AGENCIA__H__
#define __AGENCIA__H__
#include <list>
#include <string.h>
#include "venta.h"
#include "vuelo.h"

using namespace std;


class Agencia {

private:
		string nombre;
		string pass;
		int cantVentas;
		int devoluciones;
		int ganancias;
		list<Venta*> ventasAg;
		list<Vuelo*> vuelosAg;

public:
		void setNombre(string nombreIn);
		void setPass(string passIn);
		void setVentas(list<Venta*> ventasIn);
		void setVuelos(list<Vuelo*> vuelosIn);
		void setCantventas(int cantVentasIn);
		string getNombre();
		string getPass();
		list<Venta*>& getVentas();
		list<Vuelo*>& getVuelos();
		int getCantVentas();
};

#include "agencia.hxx"
#endif
