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
string fecha;
int disponibles;

public:
void setRuta(Ruta* rutaIn);
void setVendidos(list<Venta*> vendidosIn);
void setFecha(string fechaIn);
void setDisponibles(int disponiblesIn);
Ruta* getRuta();
list<Venta*> getVendidos();
string getFecha();
int getDisponibles();
};

#include "vuelo.hxx"
#endif
