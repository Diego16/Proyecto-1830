#include <iostream>
#include <string.h>
#include <list>
#include <vector>
#include <fstream>
#include "agencia.h"
#include "venta.h"
#include "ruta.h"
#include "vuelo.h"
using namespace std;
//Funciones auxiliares
bool validateSession(string cmdInput, string input, list<Agencia*> &tAgencias);
bool loadAgencies(string nombreArchivo, list<Agencia*> &tAgencias);
bool loadFlights(string nombreArchivo, list<Ruta*> &tRutas);
bool loadSells(string nombreArchivo, list<Vuelo*> &tVuelos, list<Ruta*> &tRutas, list<Venta*> &tVentas);
vector<string> tokenizer(string toTokenize, char token);
Vuelo* checkVuelo(int Lfecha, Ruta* Lruta, list<Vuelo*> &tVuelos);
//Función pricipal
int main(int argc, char* argv[])
{
		list<Ruta*> tRutas;
		list<Agencia*> tAgencias;
		list<Venta*> tVentas;
		list<Vuelo*> tVuelos;
		bool on = true, logged = false;
		string cmdInput = " ", input = " ";
		char command[300] = {' '};
		if(argc<4||argc>4)
		{
				cerr << "Uso: " << argv[0] << " flightsX.txt " << " ticketsX.txt " << " passwordsX.txt " << endl;
				return 1;
		}
		loadFlights(argv[1],tRutas);
		loadSells(argv[2],tVuelos,tRutas,tVentas);
		loadAgencies(argv[3],tAgencias);
		while(on)
		{
				cout << "$ ";
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
								cin >> input;
								logged = validateSession(cmdInput,input,tAgencias);
								if(!logged)
								{
										cout << "Usuario o contraseña incorrectos, intente de nuevo" << endl;
								}
						}
						else
						{
								cout << "Parametros invalidos" << endl;
						}
				}
				else if(strcmp(cmdList[0],"")==0 && logged)
				{
						if (cantCmd==1)
						{

						}
						else
						{
								cout << "Parametros invalidos" << endl;
						}
				}
				else if(strcmp(cmdList[0],"help")==0 && !logged)
				{
						if (cantCmd==1)
						{
								cout << endl << "Comandos disponibles: " << endl << "   login" << endl << "   exit" << endl;
						}
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
						{
								cout << endl << "Comandos disponibles: " << endl << "   report flights" << endl << "   report inventory" << endl << "   sell" << endl << "   logout" << endl << "   exit" << endl;
						}
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
						on = false;
				else if(!logged)
						cout << "*** Por favor ingrese su usuario y contraseña para continuar ***" << endl;
				else
						cout << "*** Comando no valido ***" << endl;
		}
		return 0;
}

bool validateSession(string cmdInput, string input, list<Agencia*> &tAgencias)
{
		for(list<Agencia*>::iterator it = tAgencias.begin(); it!=tAgencias.end(); it++)
		{
				if((*it)->getNombre()==cmdInput && (*it)->getPass()==input)
				{
						return true;
				}
		}
		return false;
}
bool loadAgencies(string nombreArchivo, list<Agencia*> &tAgencias)
{
		bool success = false;
		string line;
		Agencia* newAgency;
		ifstream myfile(nombreArchivo.c_str());
		vector<string> tokenizedLine;
		if (myfile.is_open())
		{
				getline (myfile,line);
				int i = 0;
				while((myfile.peek()!=EOF))
				{
						getline (myfile,line);
						tokenizedLine = tokenizer(line, ';');
						newAgency->setNombre(tokenizedLine[1]);
						newAgency->setPass(tokenizedLine[0]);
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
		Ruta* newRoute;
		ifstream myfile(nombreArchivo.c_str());
		vector<string> tokenizedLine;
		if (myfile.is_open())
		{
				getline (myfile,line);
				int i = 0;
				while((myfile.peek()!=EOF))
				{
						getline (myfile,line);
						tokenizedLine = tokenizer(line, ';');
						newRoute->setCodigo(tokenizedLine[7]);
						newRoute->setDia(tokenizedLine[6]);
						newRoute->setOrigen(tokenizedLine[5]);
						newRoute->setDestino(tokenizedLine[4]);
						newRoute->setHrsalida(stoi(tokenizedLine[3]));
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
bool loadSells(string nombreArchivo, list<Vuelo*> &tVuelos, list<Ruta*> &tRutas, list<Venta*> &tVentas)
{
		bool success = false;
		string line;
		Venta* newSell;
		ifstream myfile(nombreArchivo.c_str());
		vector<string> tokenizedLine;
		if (myfile.is_open())
		{
				getline (myfile,line);
				int i = 0;
				while((myfile.peek()!=EOF))
				{
						getline (myfile,line);
						tokenizedLine = tokenizer(line, ';');
						newSell->setCodigo(tokenizedLine[6]);
						newSell->setRuta(tokenizedLine[5]);
						newSell->setIdcomprador(tokenizedLine[4]);
						newSell->setNombre(tokenizedLine[3]);
						newSell->setFechavuelo(stoi(tokenizedLine[2]));
						newSell->setFechacompra(stoi(tokenizedLine[1]));
						newSell->setHrcompra(stoi(tokenizedLine[0]));
						if(checkVuelo(newSell->getFechavuelo(),))//TODO: Implement a routes finder
						{

						}
						tVentas.push_back(newSell);
				}
		}
		else
				return false;
		myfile.close();
		return true;
}
Vuelo* checkVuelo(int Lfecha, Ruta* Lruta, list<Vuelo*> &tVuelos)
{
		Vuelo* aux;
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
								aux->setDisponibles(0);
								return aux;
						}
				}
		}
		//TODO:If fligth doesn't exist create a new one and return it
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
		aux.resize(aux.size() - 1);
		tokenizedLine.insert(tokenizedLine.begin(), aux );
		return tokenizedLine;
}
