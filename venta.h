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

public:
		void setCodigo(string codigoIn);
		void setRuta(string rutaIn);
		void setIdcomprador(string idCompradorIn);
		void setNombre(string nombreIn);
		void setFechavuelo(string fechavueloIn);
		void setFechacompra(string fechacompraIn);
		void setHrcompra(string hrcompraIn);
		void setEstado(string estadoIn);
		string getCodigo();
		string getRuta();
		string getIdComprador();
		string getNombre();
		string getFechavuelo();
		string getFechacompra();
		string getHrcompra();
		string getEstado();
};

#include "venta.hxx"
#endif
