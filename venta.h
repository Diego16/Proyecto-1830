#ifndef __VENTA__H__
#define __VENTA__H__
#include <string.h>
#include "agencia.h"

using namespace std;


class Venta {

private:
		string agencia;
		string codigo;
		string vuelo;
		string idComprador;
		string nombre;
		int fechavuelo;
		int fechacompra;
		int hrcompra;

public:
		void setAgencia(string agenciaIn);
		void setCodigo(string codigoIn);
		void setVuelo(string vueloIn);
		void setIdcomprador(string idCompradorIn);
		void setNombre(string nombreIn);
		void setFechavuelo(int fechavueloIn);
		void setFechacimpra(int fechacompraIn);
		void setHrcompra(int hrcompraIn);
		string getAgencia();
		string getCodigo();
		string getVuelo();
		string getIdComprador();
		string getNombre();
		int getFechavuelo();
		int getFechacompra();
		int getHrcompra();
};

// #include "venta.hpp"
#endif
