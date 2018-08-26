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
		int fechavuelo;
		int fechacompra;
		int hrcompra;

public:
		void setCodigo(string codigoIn);
		void setRuta(string rutaIn);
		void setIdcomprador(string idCompradorIn);
		void setNombre(string nombreIn);
		void setFechavuelo(int fechavueloIn);
		void setFechacompra(int fechacompraIn);
		void setHrcompra(int hrcompraIn);
		string getCodigo();
		string getRuta();
		string getIdComprador();
		string getNombre();
		int getFechavuelo();
		int getFechacompra();
		int getHrcompra();
};

#include "venta.hxx"
#endif
