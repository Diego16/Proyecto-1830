#include <iostream>
#include <string.h>
#include <list>
#include "agencia.h"
#include "venta.h"
#include "ruta.h"
using namespace std;
//Funciones auxiliares
bool validateSession(string cmdInput, string input, list<Agencia*> &tAgencias);
//Función pricipal
int main()
{
		list<Ruta*> tRutas;
		list<Agencia*> tAgencias;
		list<Venta*> tVentas;
		bool on = true, logged = false;
		string cmdInput = " ", input = " ";
		char command[300] = {' '};
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
