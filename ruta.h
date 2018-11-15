#ifndef __RUTA__H__
#define __RUTA__H__
#include <stack>
#include <queue>
#include <string.h>

using namespace std;


class Ruta {

protected:
string codigo;
string dia;
string origen;
string destino;
string hrsalida;
int duracion;
int sillas;
int costosilla;

public:
void setCodigo(string codigoIn);
void setDia(string diaIn);
void setOrigen(string origenIn);
void setDestino(string destinoIn);
void setHrsalida(string horsalidaIn);
void setDuracion(int duracionIn);
void setSillas(int sillasIn);
void setCosto(int costosillaIn);
string getCodigo();
string getDia();
string getOrigen();
string getDestino();
string getHrsalida();
int getDuracion();
int getSillas();
int getCosto();
friend ostream& operator << (ostream &o, const Ruta* rt);
};

#include "ruta.hxx"
#endif
