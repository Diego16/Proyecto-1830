#ifndef __VUELO__HPP__
#define __VUELO__HPP__


using namespace std;

void Vuelo::setRuta(Ruta* rutaIn)
{
		ruta = rutaIn;
}
void Vuelo::setVendidos(list<Venta*> vendidosIn)
{
		vendidos = vendidosIn;
}
void Vuelo::setFecha(int fechaIn)
{
		fecha = fechaIn;
}
void Vuelo::setDisponibles(int disponiblesIn)
{
		disponibles = disponiblesIn;
}
Ruta* Vuelo::getRuta()
{
		return ruta;
}
list<Venta*> Vuelo::getVendidos()
{
		return vendidos;
}
int Vuelo::getFecha()
{
		return fecha;
}
int Vuelo::getDisponibles()
{
		return disponibles;
}

#endif
