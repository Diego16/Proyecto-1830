#ifndef __VUELO__H__
#define __VUELO__H__
#include <string.h>
#include "venta.h"
#include "ruta.h"

using namespace std;


class Vuelo {

private:
		Ruta* ruta;
		list<Venta*> vendidos;
		int fecha;
		int disponibles;

public:
		void setRuta(Ruta* rutaIn);
		void setVendidos(list<Venta*> vendidosIn);
		void setFecha(int fechaIn);
		void setDisponibles(int disponiblesIn);
		Ruta* getRuta();
		list<Venta*> getVendidos();
		int getFecha();
		int getDisponibles();
};

#include "vuelo.hxx"
#endif
