#ifndef __RUTA__HPP__
#define __RUTA__HPP__
#include <string.h>

using namespace std;
void Ruta::setCodigo(string codigoIn)
{
		codigo = codigoIn;
}
void Ruta::setDia(string diaIn)
{
		dia = diaIn;
}
void Ruta::setOrigen(string origenIn)
{
		origen = origenIn;
}
void Ruta::setDestino(string destinoIn)
{
		destino = destinoIn;
}
void Ruta::setHrsalida(string hrsalidaIn)
{
		hrsalida = hrsalidaIn;
}
void Ruta::setDuracion(int duracionIn)
{
		duracion = duracionIn;
}
void Ruta::setSillas(int sillasIn)
{
		sillas = sillasIn;
}
void Ruta::setCosto(int costosillaIn)
{
		costosilla = costosillaIn;
}
string Ruta::getCodigo()
{
		return codigo;
}
string Ruta::getDia()
{
		return dia;
}
string Ruta::getOrigen()
{
		return origen;
}
string Ruta::getDestino()
{
		return destino;
}
string Ruta::getHrsalida()
{
		return hrsalida;
}
int Ruta::getDuracion()
{
		return duracion;
}
int Ruta::getSillas()
{
		return sillas;
}
int Ruta::getCosto()
{
		return costosilla;
}
#endif
