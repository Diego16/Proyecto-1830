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
int ingresos;
int devoluciones;
int ganacias;
int cancelados;
int cambiados;
list<Venta*> ventasAg;
list<Vuelo*> vuelosAg;

public:
void setNombre(string nombreIn);
void setPass(string passIn);
void setVentas(list<Venta*> ventasIn);
void setVuelos(list<Vuelo*> vuelosIn);
void setCantventas(int cantVentasIn);
void setIngresos(int ingresosIn);
void setDevoluciones(int devolucionesIn);
void setGanancias(int gananciasIn);
void setCancelados(int canceladosIn);
void setCambiados(int cambiadosIn);
string getNombre();
string getPass();
list<Venta*>& getVentas();
list<Vuelo*>& getVuelos();
int getCantVentas();
int getIngresos();
int getDevoluciones();
int getGanancias();
int getCancelados();
int getCambiados();
};

#include "agencia.hxx"
#endif
