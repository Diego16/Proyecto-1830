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
void Venta::setFechavuelo(string fechavueloIn)
{
	fechavuelo = fechavueloIn;
}
void Venta::setFechacompra(string fechacompraIn)
{
	fechacompra = fechacompraIn;
}
void Venta::setHrcompra(string hrcompraIn)
{
	hrcompra = hrcompraIn;
}
void Venta::setEstado(string estadoIn)
{
	estado = estadoIn;
}
void Venta::setValor(int valorIn)
{
	valor = valorIn;
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
string Venta::getFechavuelo()
{
	return fechavuelo;
}
string Venta::getFechacompra()
{
	return fechacompra;
}
string Venta::getHrcompra()
{
	return hrcompra;
}
string Venta::getEstado()
{
	return estado;
}
int Venta::getValor()
{
	return valor;
}
#endif
