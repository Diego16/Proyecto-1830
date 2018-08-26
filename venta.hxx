#ifndef __VENTA__HPP__
#define __VENTA__HPP__
#include <string.h>

using namespace std;

void Venta::setCodigo(string codigoIn)
{
		codigo = codigoIn;
}
void Venta::setRuta(string rutaIn)
{
		ruta = rutaIn;
}
void Venta::setIdcomprador(string idCompradorIn)
{
		idComprador = idCompradorIn;
}
void Venta::setNombre(string nombreIn)
{
		nombre = nombreIn;
}
void Venta::setFechavuelo(int fechavueloIn)
{
		fechavuelo = fechavueloIn;
}
void Venta::setFechacompra(int fechacompraIn)
{
		fechacompra = fechacompraIn;
}
void Venta::setHrcompra(int hrcompraIn)
{
		hrcompra = hrcompraIn;
}
string Venta::getCodigo()
{
		return codigo;
}
string Venta::getRuta()
{
		return ruta;
}
string Venta::getIdComprador()
{
		return idComprador;
}
string Venta::getNombre()
{
		return nombre;
}
int Venta::getFechavuelo()
{
		return fechavuelo;
}
int Venta::getFechacompra()
{
		return fechacompra;
}
int Venta::getHrcompra()
{
		return hrcompra;
}

#endif
