#include <iostream>
#include <cstring>
#include <ctime>
#include <list>
#include <vector>
#include <fstream>
#include "agencia.h"
#include "venta.h"
#include "ruta.h"
#include "vuelo.h"
using namespace std;
//Funciones auxiliares
bool loadAgencies(string nombreArchivo, list<Agencia*> &tAgencias);
bool loadFlights(string nombreArchivo, list<Ruta*> &tRutas);
bool loadSells(string nombreArchivo, list<Vuelo*> &tVuelos, list<Ruta*> &tRutas, list<Venta*> &tVentas, list<Agencia*> &tAgencias);
bool selling(string idRuta, string fechaV, list<Vuelo*> &tVuelos, list<Ruta*> &tRutas, list<Venta*> &tVentas, Agencia* &vendedora);
void inventory(list<Venta*> &tVentas);
void availability(string input,string input1,list<Vuelo*> &tVuelos);
bool validateSession(string cmdInput, string input, list<Agencia*> &tAgencias);
Vuelo* checkVuelo(string Lfecha, Ruta* Lruta, list<Vuelo*> &tVuelos);
Ruta* findRuta(string Lcode, list<Ruta*> &tRutas);
Agencia* findAgencia(string Lname, list<Agencia*> &tAgencias);
vector<string> tokenizer(string toTokenize, char token);
//Función pricipal
int main(int argc, char* argv[])
{
		list<Ruta*> tRutas;
		list<Agencia*> tAgencias;
		list<Venta*> tVentas;
		list<Vuelo*> tVuelos;
		Agencia* user = new Agencia();
		bool on = true, logged = false;
		string cmdInput = " ", input = " ", input1 = " ";
		char command[300] = {' '};
		if(argc<4||argc>4)
		{
				cerr << "Uso: " << argv[0] << " flightsX.txt " << " ticketsX.txt " << " passwordsX.txt " << endl;
				return 1;
		}
		loadFlights(argv[1],tRutas);
		loadAgencies(argv[3],tAgencias);
		loadSells(argv[2],tVuelos,tRutas,tVentas,tAgencias);
		while(on)
		{
				cout << "$ ";
				cin.clear();
				cin.sync();
				cin.getline(command,300);
				char* piece;
				char* cmdList[10];
				int cantCmd = 0;
				piece = strtok (command," ");
				while (piece != NULL)
				{
						cmdList[cantCmd] = piece;
						cantCmd++;
						piece = strtok (NULL, " ");
				}
				if (strcmp(cmdList[0],"login")==0 && !logged)
				{
						if (cantCmd==2)
						{
								cmdInput = cmdList[1];
								cout << "Contraseña: ";
								cin.clear();
								cin.sync();
								getline(cin,input);
								logged = validateSession(cmdInput,input,tAgencias);
								if(!logged)
										cout << "* Usuario o contraseña incorrectos, intente de nuevo *" << endl;
								else
								{
										cout << ">>> Sesion iniciada para " << cmdInput << endl;
										user = findAgencia(cmdInput,tAgencias);
								}
						}
						else
								cout << "** Parametros invalidos **" << endl;
				}
				else if(strcmp(cmdList[0],"report")==0 && logged)
				{
						if (cantCmd>=2)
						{
								cmdInput = cmdList[1];
								if(cmdInput=="flights")
								{
										if(cantCmd==3)
										{
												input = cmdList[2];
												input1 = "N";
										}
										else if(cantCmd==4)
										{
												input = cmdList[2];
												input1 = cmdList[3];
										}
										else
										{
												input = "N";
												input1 = "N";
										}
										availability(input,input1,tVuelos);
								}
								else if(cmdInput=="inventory")
								{
										inventory(user->getVentas());
								}
								else
										cout << "** Parametros invalidos **" << endl;
						}
						else
								cout << "** Parametros invalidos **" << endl;
				}
				else if(strcmp(cmdList[0],"sell")==0 && logged)
				{
						if (cantCmd==3)
						{
								input = cmdList[1];
								input1 = cmdList[2];
								selling(input,input1,tVuelos,tRutas,tVentas,user);
						}
						else
								cout << "** Parametros invalidos **" << endl;
				}
				else if(strcmp(cmdList[0],"help")==0 && !logged)
				{
						if (cantCmd==1)
								cout << endl << "Comandos disponibles: " << endl << "   login" << endl << "   exit" << endl;
						else if (cantCmd==2)
						{
								cmdInput = cmdList[1];
								if(cmdInput=="login")
										cout << "===login <id_agencia>" << endl << "==== Activa la sesión de la agencia seleccionada en la aplicación" << endl;
								if(cmdInput=="exit")
										cout << "===exit" << endl << "==== Termina la ejecucion de la aplicacion." << endl;
						}
				}
				else if(strcmp(cmdList[0],"help")==0 && logged)
				{
						if (cantCmd==1)
								cout << endl << "Comandos disponibles: " << endl << "   report flights" << endl << "   report inventory" << endl << "   sell" << endl << "   logout" << endl << "   exit" << endl;
						else if (cantCmd>=2)
						{
								cmdInput = cmdList[1];
								input = cmdList[2];
								if(cmdInput=="report"&&input=="flights")
										cout << "=== report flights [origen] [fecha]" << endl << "==== Reporte de vuelos con sillas disponibles. Se puede filtrar por ciudad de origen o fecha del vuelo" << endl;
								if(cmdInput=="report"&&input=="inventory")
										cout << "=== report inventory" << endl << "==== Reporte de todos los vuelos vendidos, cambiados o cancelados por la agencia" << endl;
								if(cmdInput=="sell")
										cout << "=== sell <id_vuelo> <fecha>" << endl << "==== Permite la venta del vuelo seleccionado en la fecha especificada en caso de ser posible" << endl;
								if(cmdInput=="logout")
										cout << "=== logout" << endl << "==== Termina la sesión de la agencia logueada en la aplicación" << endl;
								if(cmdInput=="exit")
										cout << "=== exit" << endl << "==== Termina la ejecucion de la aplicacion." << endl;
						}
				}
				else if(strcmp(cmdList[0],"exit")==0)
						return 0;
				else if(strcmp(cmdList[0],"logout")==0)
						logged = false;
				else if(strcmp(cmdList[0],"login")!=0 && !logged)
						cout << "*** Por favor ingrese su usuario y contraseña para continuar ***" << endl;
				else
						cout << "*** Comando no valido ***" << endl;
		}
		return 0;
}

bool loadAgencies(string nombreArchivo, list<Agencia*> &tAgencias)
{
		bool success = false;
		string line;
		ifstream myfile(nombreArchivo.c_str());
		vector<string> tokenizedLine;
		if (myfile.is_open())
		{
				int i = 0;
				while((myfile.peek()!=EOF))
				{
						Agencia* newAgency = new Agencia();
						getline (myfile,line);
						tokenizedLine = tokenizer(line, ';');
						newAgency->setNombre(tokenizedLine[1]);
						newAgency->setPass(tokenizedLine[0]);
						newAgency->setCantventas(0);
						tAgencias.push_back(newAgency);
				}
		}
		else
				return false;
		myfile.close();
		return true;
}
bool loadFlights(string nombreArchivo, list<Ruta*> &tRutas)
{
		bool success = false;
		string line;
		ifstream myfile(nombreArchivo.c_str());
		vector<string> tokenizedLine;
		if (myfile.is_open())
		{
				int i = 0;
				while((myfile.peek()!=EOF))
				{
						Ruta* newRoute = new Ruta();
						getline (myfile,line);
						tokenizedLine = tokenizer(line, ';');
						newRoute->setCodigo(tokenizedLine[7]);
						newRoute->setDia(tokenizedLine[6]);
						newRoute->setOrigen(tokenizedLine[5]);
						newRoute->setDestino(tokenizedLine[4]);
						newRoute->setHrsalida(tokenizedLine[3]);
						newRoute->setDuracion(stoi(tokenizedLine[2]));
						newRoute->setSillas(stoi(tokenizedLine[1]));
						newRoute->setCosto(stoi(tokenizedLine[0]));
						tRutas.push_back(newRoute);
				}
		}
		else
				return false;
		myfile.close();
		return true;
}
bool loadSells(string nombreArchivo, list<Vuelo*> &tVuelos, list<Ruta*> &tRutas, list<Venta*> &tVentas, list<Agencia*> &tAgencias)
{
		bool success = false;
		string line;
		ifstream myfile(nombreArchivo.c_str());
		vector<string> tokenizedLine;
		int fallosExist = 0, fallosSeat = 0, fallosAgency = 0;
		if (myfile.is_open())
		{
				int i = 0;
				while((myfile.peek()!=EOF))
				{
						Venta* newSell = new Venta();
						Vuelo* aux = new Vuelo();
						Agencia* Aaux = new Agencia();
						int cant = 0;
						getline (myfile,line);
						tokenizedLine = tokenizer(line, ';');
						newSell->setCodigo(tokenizedLine[6]);
						newSell->setRuta(tokenizedLine[5]);
						newSell->setIdcomprador(tokenizedLine[4]);
						newSell->setNombre(tokenizedLine[3]);
						newSell->setFechavuelo(tokenizedLine[2]);
						newSell->setFechacompra(tokenizedLine[1]);
						newSell->setHrcompra(tokenizedLine[0]);
						newSell->setEstado("VIGENTE");
						aux = checkVuelo(newSell->getFechavuelo(),findRuta(newSell->getRuta(),tRutas),tVuelos);
						if(aux->getDisponibles()==-1)
								fallosSeat++;
						else if(aux->getDisponibles()==-2)
								fallosExist++;
						tokenizedLine[6].resize(tokenizedLine[6].size() - 5);
						Aaux = findAgencia(tokenizedLine[6],tAgencias);
						if(Aaux->getNombre()=="0")
								fallosAgency++;
						else
						{
								cant = Aaux->getCantVentas() + 1;
								Aaux->setCantventas(cant);
								Aaux->getVentas().push_back(newSell);
								tVentas.push_back(newSell);
								aux->getVendidos().push_back(newSell);
						}
				}
		}
		else
				return false;
		myfile.close();
		if(fallosSeat>0)
				cerr << "No se registraron " << fallosSeat << " ventas, los vuelos no tenian sillas disponibles" << endl;
		if(fallosExist>0)
				cerr << "No se registraron " << fallosExist << " ventas, la ruta no existe" << endl;
		if(fallosAgency>0)
				cerr << "No se registraron " << fallosAgency << " ventas, la agencia no existe" << endl;
		return true;
}
bool selling(string idRuta, string fechaV, list<Vuelo*> &tVuelos, list<Ruta*> &tRutas, list<Venta*> &tVentas, Agencia* &vendedora)
{
		Venta* newSell = new Venta();
		Vuelo* aux = new Vuelo();
		string fecha = " ", hora = " ";
		string ID = " ", nombre = " ";
		time_t t = std::time(0);
		tm* now = std::localtime(&t);
		aux = checkVuelo(fechaV,findRuta(idRuta,tRutas),tVuelos);
		if(aux->getDisponibles()==-1)
				cout << "La venta no fue registrada -> no hay sillas disponibles" << endl;
		else if(aux->getDisponibles()==-2)
				cout << "La venta no fue registrada -> la ruta no existe" << endl;
		else
		{
				fecha = to_string(now->tm_year + 1900) + to_string(now->tm_mon + 1) + to_string(now->tm_mday);
				hora = to_string(now->tm_hour) + to_string(now->tm_min);
				cout << "Ingrese la identificacion del comprador: ";
				cin >> ID;
				cout << "Ingrese el nombre del comprador (apellidos, nombres): ";
				cin.clear();
				cin.sync();
				cin.ignore();
				getline(cin,nombre);
				newSell->setCodigo(vendedora->getNombre() + "_100" + to_string(vendedora->getCantVentas()));
				newSell->setRuta(idRuta);
				newSell->setIdcomprador(ID);
				newSell->setNombre(nombre);
				newSell->setFechavuelo(fechaV);
				newSell->setFechacompra(fecha);
				newSell->setHrcompra(hora);
				vendedora->getVentas().push_back(newSell);
				tVentas.push_back(newSell);
				aux->getVendidos().push_back(newSell);
				cout << "La venta fue registrada correctamente" << endl;
				return true;
		}
		return false;
}
void inventory(list<Venta*> &tVentas)
{
		int fecha1 = 0, fecha2 = 0;
		for(list<Venta*>::iterator it = tVentas.begin(); it!=tVentas.end(); it++)
				for(list<Venta*>::iterator itI = tVentas.begin(); itI!=tVentas.end(); itI++)
				{
						if((*it)->getCodigo()==(*itI)->getCodigo())
						{
								fecha1 = stoi((*it)->getFechacompra());
								fecha2 = stoi((*itI)->getFechacompra());
								if(fecha1<fecha2 && (*itI)->getEstado()!="CAMBIO")
								{
										(*it)->setEstado("CAMBIO");
										(*itI)->setEstado("VIGENTE");
										break;
								}
						}
				}
		cout << "CODIGO       RUTA     ID_Comprador         NOMBRE           FECHA VUELO    FECHA COMPRA    HORA COMPRA    ESTADO" << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
		for(list<Venta*>::iterator it = tVentas.begin(); it!=tVentas.end(); it++)
		{
				cout << (*it)->getCodigo() << "   " << (*it)->getRuta() << "    " << (*it)->getIdComprador() << "    " << (*it)->getNombre() << "    " << (*it)->getFechavuelo() << "   " << (*it)->getFechacompra() << "    " << (*it)->getHrcompra() << "    " << (*it)->getEstado() << endl;
				cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
		}
}
void availability(string input,string input1,list<Vuelo*> &tVuelos)
{
		char aux = input[0];
		cout << "RUTA     ORIGEN     DESTINO     FECHA     SILLAS    " << endl;
		cout << "-----------------------------------------------------" << endl;
		if(input=="N"&&input1=="N")
		{
				for(list<Vuelo*>::iterator it = tVuelos.begin(); it!=tVuelos.end(); it++)
				{
						cout << (*it)->getRuta()->getCodigo() << "    " << (*it)->getRuta()->getOrigen() << "    " << (*it)->getRuta()->getDestino() << "    " << (*it)->getFecha() << "    " << (*it)->getDisponibles() << endl;
						cout << "-----------------------------------------------------" << endl;
				}
		}
		else if(input1=="N")
		{
				if(aux=='2')
				{
						for(list<Vuelo*>::iterator it = tVuelos.begin(); it!=tVuelos.end(); it++)
						{
								if(input==(*it)->getFecha())
								{
										cout << (*it)->getRuta()->getCodigo() << "    " << (*it)->getRuta()->getOrigen() << "    " << (*it)->getRuta()->getDestino() << "    " << (*it)->getFecha() << "    " << (*it)->getDisponibles() << endl;
										cout << "-----------------------------------------------------" << endl;
								}
						}
				}
				else
				{
						for(list<Vuelo*>::iterator it = tVuelos.begin(); it!=tVuelos.end(); it++)
						{
								if(input==(*it)->getRuta()->getOrigen())
								{
										cout << (*it)->getRuta()->getCodigo() << "    " << (*it)->getRuta()->getOrigen() << "    " << (*it)->getRuta()->getDestino() << "    " << (*it)->getFecha() << "    " << (*it)->getDisponibles() << endl;
										cout << "-----------------------------------------------------" << endl;
								}
						}
				}
		}
		else
		{
				if(aux=='2')
				{
						for(list<Vuelo*>::iterator it = tVuelos.begin(); it!=tVuelos.end(); it++)
						{
								if(input==(*it)->getFecha()&&input1==(*it)->getRuta()->getOrigen())
								{
										cout << (*it)->getRuta()->getCodigo() << "    " << (*it)->getRuta()->getOrigen() << "    " << (*it)->getRuta()->getDestino() << "    " << (*it)->getFecha() << "    " << (*it)->getDisponibles() << endl;
										cout << "-----------------------------------------------------" << endl;
								}
						}
				}
				else
				{
						for(list<Vuelo*>::iterator it = tVuelos.begin(); it!=tVuelos.end(); it++)
						{
								if(input==(*it)->getRuta()->getOrigen()&&input1==(*it)->getFecha())
								{
										cout << (*it)->getRuta()->getCodigo() << "    " << (*it)->getRuta()->getOrigen() << "    " << (*it)->getRuta()->getDestino() << "    " << (*it)->getFecha() << "    " << (*it)->getDisponibles() << endl;
										cout << "-----------------------------------------------------" << endl;
								}
						}
				}
		}
}
bool validateSession(string cmdInput, string input, list<Agencia*> &tAgencias)
{
		for(list<Agencia*>::iterator it = tAgencias.begin(); it!=tAgencias.end(); it++)
		{
				if(((*it)->getNombre()==cmdInput) && ((*it)->getPass()==input))
				{
						return true;
				}
		}
		return false;
}
Vuelo* checkVuelo(string Lfecha, Ruta* Lruta, list<Vuelo*> &tVuelos)
{
		Vuelo* aux = new Vuelo();
		if(Lruta->getCodigo()=="0")
		{
				aux->setDisponibles(-2);
				return aux;
		}
		for(list<Vuelo*>::iterator it = tVuelos.begin(); it!=tVuelos.end(); it++)
		{
				if((*it)->getRuta()==Lruta&&(*it)->getFecha()==Lfecha)
				{
						if((*it)->getDisponibles()>0)
						{
								(*it)->setDisponibles((*it)->getDisponibles() - 1);
								return *it;
						}
						else
						{
								aux->setDisponibles(-1);
								return aux;
						}
				}
		}
		aux->setRuta(Lruta);
		aux->setFecha(Lfecha);
		aux->setDisponibles(Lruta->getSillas() - 1);
		tVuelos.push_back(aux);
		return aux;
}
Ruta* findRuta(string Lcode, list<Ruta*> &tRutas)
{
		Ruta* aux = new Ruta();
		for(list<Ruta*>::iterator it = tRutas.begin(); it!=tRutas.end(); it++)
		{
				if((*it)->getCodigo()==Lcode)
				{
						return *it;
				}
		}
		aux->setCodigo("0");
		return aux;
}
Agencia* findAgencia(string Lname, list<Agencia*> &tAgencias)
{
		Agencia* aux = new Agencia();
		for(list<Agencia*>::iterator it = tAgencias.begin(); it!=tAgencias.end(); it++)
		{
				if((*it)->getNombre()==Lname)
				{
						return *it;
				}
		}
		aux->setNombre("0");
		return aux;
}
vector<string> tokenizer(string toTokenize, char token)
{
		vector<string> tokenizedLine;
		string aux;
		int i = 0;
		while( i <= toTokenize.size())
		{
				if(toTokenize[i] == token)
				{
						i++;
						tokenizedLine.insert(tokenizedLine.begin(), aux );
						aux.clear();
				}
				aux += toTokenize[i];
				i++;
		}
		aux.resize(aux.size() - 2);
		tokenizedLine.insert(tokenizedLine.begin(), aux );
		return tokenizedLine;
}
