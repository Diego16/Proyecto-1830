#ifndef __VENTA__H__
#define __VENTA__H__
#include <string.h>

using namespace std;


class Venta {

private:
string codigo;
string ruta;
string idComprador;
string nombre;
string fechavuelo;
string fechacompra;
string hrcompra;
string estado;
int valor;

public:
void setCodigo(string codigoIn);
void setRuta(string rutaIn);
void setIdcomprador(string idCompradorIn);
void setNombre(string nombreIn);
void setFechavuelo(string fechavueloIn);
void setFechacompra(string fechacompraIn);
void setHrcompra(string hrcompraIn);
void setEstado(string estadoIn);
void setValor(int valorIn);
string getCodigo();
string getRuta();
string getIdComprador();
string getNombre();
string getFechavuelo();
string getFechacompra();
string getHrcompra();
string getEstado();
int getValor();
};

#include "venta.hxx"
#endif
