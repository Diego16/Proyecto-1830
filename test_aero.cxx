#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <chrono>
#include <locale>
#include <list>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h> //For tab-comletion Installation: sudo apt-get install libreadline-dev
#include <readline/readline.h> //For tab-completion Installation: sudo apt-get install libreadline-dev
#include "table_printer.h" //Taken from https://github.com/dattanchu/bprinter under MIT License
#include "agencia.h"
#include "venta.h"
#include "ruta.h"
#include "vuelo.h"

using namespace std;
using BPrinter::TablePrinter;

// Vocabulary for tab-completion
std::vector<std::string> vocabulary{"report", "inventory", "login", "money", "help", "flights", "sell", "cancel", "consolidate", "logout", "exit"};
//Funciones componente 1
bool validateSession(string cmdInput, string input, list<Agencia*> &tAgencias);
bool selling(string idRuta, string fechaV, list<Vuelo*> &tVuelos, list<Ruta*> &tRutas, list<Venta*> &tVentas, Agencia* &vendedora);
void inventory(list<Venta*> &tVentas, list<Ruta*> &tRutas, list<Vuelo*> &tVuelos);
void availability(string input,string input1,list<Vuelo*> &tVuelos);
//Funciones componente 2
bool cancelSell(string idVenta, list<Ruta*> &tRutas, list<Vuelo*> &tVuelos, Agencia* &vendedora);
bool consolidate(list<Venta*> &tVentas, list<Ruta*> &tRutas, list<Vuelo*> &tVuelos);
void finances(Agencia* &vendedora);
//Funciones auxiliares
bool loadAgencies(string nombreArchivo, list<Agencia*> &tAgencias);
bool loadFlights(string nombreArchivo, list<Ruta*> &tRutas);
bool loadSells(string nombreArchivo, list<Vuelo*> &tVuelos, list<Ruta*> &tRutas, list<Venta*> &tVentas, list<Agencia*> &tAgencias);
void updateStates(list<Ruta*> &tRutas, list<Vuelo*> &tVuelos, Agencia* &vendedora);
Vuelo* checkVuelo(string Lfecha, Ruta* Lruta, list<Vuelo*> &tVuelos);
Vuelo* findVuelo(string Lfecha, Ruta* Lruta, list<Vuelo*> &tVuelos);
Ruta* findRuta(string Lcode, list<Ruta*> &tRutas);
Agencia* findAgencia(string Lname, list<Agencia*> &tAgencias);
vector<string> tokenizer(string toTokenize, char token);
//Funciones tab-completion taken from https://github.com/eliben/code-for-blog/blob/master/2016/readline-samples/readline-complete-simple.cpp under public domain usage
char* completion_generator(const char* text, int state);
char** completer(const char* text, int start, int end);
//Función pricipal
int main(int argc, char* argv[])
{
	list<Ruta*> tRutas;
	list<Agencia*> tAgencias;
	list<Venta*> tVentas;
	list<Vuelo*> tVuelos;
	Agencia* user = new Agencia();
	bool logged = false;
	string cmdInput = " ", input = " ", input1 = " ";
	char* buff;
	char command[300]={' '};
	rl_attempted_completion_function = completer;
	if(argc<4||argc>4)
	{
		cerr << "Uso: " << argv[0] << " flightsX.txt " << " ticketsX.txt " << " passwordsX.txt " << endl;
		return 1;
	}
	loadFlights(argv[1],tRutas);
	loadAgencies(argv[3],tAgencias);
	loadSells(argv[2],tVuelos,tRutas,tVentas,tAgencias);
	for(list<Agencia*>::iterator it = tAgencias.begin(); it!=tAgencias.end(); it++)
		updateStates(tRutas,tVuelos, (*it));
	while ((buff = readline("$ ")) != nullptr)
	{
		if (strlen(buff) > 0) {
			add_history(buff);
			strcpy(command,buff);
		}
		free(buff);
		int cantCmd = 0;
		char* cmdList[10];
		char* piece;
		piece = strtok(command, " ");
		while (piece != NULL)
		{
			cmdList[cantCmd] = piece;
			cantCmd++;
			piece = strtok(NULL, " ");
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
					inventory(user->getVentas(),tRutas,tVuelos);
				}
				else if(cmdInput=="money")
				{
					finances(user);
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
		else if(strcmp(cmdList[0],"cancel")==0 && logged)
		{
			if (cantCmd==2)
			{
				input = cmdList[1];
				if(cancelSell(input,tRutas,tVuelos, user))
					cout<<">>> La venta "<< input<< " fue cancelada exitosamente"<<endl;
				else
					cout<<"+++ La venta "<< input<< " no fue cancelada, verifique el codigo y vuelva a intentar"<<endl;
			}
			else
				cout << "** Parametros invalidos **" << endl;
		}
		else if(strcmp(cmdList[0],"consolidate")==0 && logged)
		{
			if(cantCmd==1)
				consolidate(user->getVentas(),tRutas,tVuelos);
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
					cout << "=== login <id_agencia>" << endl << "==== Activa la sesión de la agencia seleccionada en la aplicación" << endl;
				if(cmdInput=="exit")
					cout << "=== exit" << endl << "==== Termina la ejecucion de la aplicacion." << endl;
			}
			else
				cout << "** Parametros invalidos **" << endl;
		}
		else if(strcmp(cmdList[0],"help")==0 && logged)
		{
			if (cantCmd==1)
				cout << endl << "Comandos disponibles: " << endl << "   report flights" << endl << "   report inventory" << endl << "   report money" << endl << "   sell" << endl << "   cancel" << endl << "   consolidate" << endl << "   logout" << endl << "   exit" << endl;
			else if (cantCmd>=2)
			{
				cmdInput = cmdList[1];
				input = cmdList[2];
				if(cmdInput=="report"&&input=="flights")
					cout << "=== report flights [origen] [fecha]" << endl << "==== Reporte de vuelos con sillas disponibles. Se puede filtrar por ciudad de origen o fecha del vuelo" << endl;
				if(cmdInput=="report"&&input=="inventory")
					cout << "=== report inventory" << endl << "==== Reporte de todos los vuelos vendidos, cambiados o cancelados por la agencia" << endl;
				if(cmdInput=="report"&&input=="money")
					cout << "=== report money" << endl << "==== Reporte del estado financiero de la agencia" << endl;
				if(cmdInput=="sell")
					cout << "=== sell <id_vuelo> <fecha>" << endl << "==== Permite la venta del vuelo seleccionado en la fecha especificada en caso de ser posible" << endl;
				if(cmdInput=="cancel")
					cout << "=== cancel <id_vuelo>" << endl << "==== Cancela la venta del vuelo seleccionado" << endl;
				if(cmdInput=="consolidate")
					cout << "=== consolidate" << endl << "==== Elimina las transacciones de vuelos realizados" << endl;
				if(cmdInput=="logout")
					cout << "=== logout" << endl << "==== Termina la sesión de la agencia logueada en la aplicación" << endl;
				if(cmdInput=="exit")
					cout << "=== exit" << endl << "==== Termina la ejecucion de la aplicacion." << endl;
			}
			else
				cout << "** Parametros invalidos **" << endl;
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
bool selling(string idRuta, string fechaV, list<Vuelo*> &tVuelos, list<Ruta*> &tRutas, list<Venta*> &tVentas, Agencia* &vendedora)
{
	Venta* newSell = new Venta();
	Vuelo* aux = new Vuelo();
	char fecha[10], hora[6];
	int cant=0;
	string ID = " ", nombre = " ";
	aux = checkVuelo(fechaV,findRuta(idRuta,tRutas),tVuelos);
	if(aux->getDisponibles()==-1)
		cout << "La venta no fue registrada -> no hay sillas disponibles" << endl;
	else if(aux->getDisponibles()==-2)
		cout << "La venta no fue registrada -> la ruta no existe" << endl;
	else
	{
		using chrono::system_clock;
		time_t tt = system_clock::to_time_t (system_clock::now());
		strftime(fecha,sizeof(fecha),"%Y%m%d", localtime(&tt));
		strftime(hora,sizeof(hora),"%H%M", localtime(&tt));
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
		newSell->setEstado("VIGENTE");
		newSell->setValor(findRuta(idRuta,tRutas)->getCosto());
		vendedora->getVentas().push_back(newSell);
		cant = vendedora->getCantVentas() + 1;
		vendedora->setCantventas(cant);
		vendedora->setIngresos(vendedora->getIngresos()+newSell->getValor());
		tVentas.push_back(newSell);
		aux->getVendidos().push_back(newSell);
		cout << "La venta fue registrada correctamente" << endl;
		return true;
	}
	return false;
}
void inventory(list<Venta*> &tVentas, list<Ruta*> &tRutas, list<Vuelo*> &tVuelos)
{
	int fecha1 = 0, fecha2 = 0;
	TablePrinter tp(&cout);
	tp.AddColumn("CODIGO  ",10);
	tp.AddColumn("RUTA ", 6);
	tp.AddColumn("ID_Comprador  ", 16);
	tp.AddColumn("NOMBRE              ", 35);
	tp.AddColumn("FECHA VUELO ", 13);
	tp.AddColumn("FECHA COMPRA ", 14);
	tp.AddColumn("HORA COMPRA ", 13);
	tp.AddColumn("ESTADO  ", 10);
	tp.PrintHeader();
	for(list<Venta*>::iterator it = tVentas.begin(); it!=tVentas.end(); it++)
	{
		tp << (*it)->getCodigo() << (*it)->getRuta() << (*it)->getIdComprador() << (*it)->getNombre() << (*it)->getFechavuelo() << (*it)->getFechacompra() << (*it)->getHrcompra() << (*it)->getEstado();
	}
	tp.PrintFooter();
}
void availability(string input,string input1,list<Vuelo*> &tVuelos)
{
	char aux = input[0];
	TablePrinter tp(&cout);
	tp.AddColumn("RUTA ", 6);
	tp.AddColumn("ORIGEN     ",16);
	tp.AddColumn("DESTINO    ",15);
	tp.AddColumn("FECHA   ", 11);
	tp.AddColumn("SILLAS",6);
	tp.PrintHeader();
	if(input=="N"&&input1=="N")
	{
		for(list<Vuelo*>::iterator it = tVuelos.begin(); it!=tVuelos.end(); it++)
		{
			tp << (*it)->getRuta()->getCodigo() << (*it)->getRuta()->getOrigen() << (*it)->getRuta()->getDestino() << (*it)->getFecha() << (*it)->getDisponibles();
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
					tp << (*it)->getRuta()->getCodigo() << (*it)->getRuta()->getOrigen() << (*it)->getRuta()->getDestino() << (*it)->getFecha() << (*it)->getDisponibles();
				}
			}
		}
		else
		{
			for(list<Vuelo*>::iterator it = tVuelos.begin(); it!=tVuelos.end(); it++)
			{
				if(input==(*it)->getRuta()->getOrigen())
				{
					tp << (*it)->getRuta()->getCodigo() << (*it)->getRuta()->getOrigen() << (*it)->getRuta()->getDestino() << (*it)->getFecha() << (*it)->getDisponibles();
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
					tp << (*it)->getRuta()->getCodigo() << (*it)->getRuta()->getOrigen() << (*it)->getRuta()->getDestino() << (*it)->getFecha() << (*it)->getDisponibles();
				}
			}
		}
		else
		{
			for(list<Vuelo*>::iterator it = tVuelos.begin(); it!=tVuelos.end(); it++)
			{
				if(input==(*it)->getRuta()->getOrigen()&&input1==(*it)->getFecha())
				{
					tp << (*it)->getRuta()->getCodigo() << (*it)->getRuta()->getOrigen() << (*it)->getRuta()->getDestino() << (*it)->getFecha() << (*it)->getDisponibles();
				}
			}
		}
	}
	tp.PrintFooter();
}
bool cancelSell(string idVenta, list<Ruta*> &tRutas, list<Vuelo*> &tVuelos, Agencia* &vendedora)
{
	Vuelo* auxV = new Vuelo();
	bool res=false;
	for(list<Venta*>::iterator it = vendedora->getVentas().begin(); it!=vendedora->getVentas().end(); it++)
	{
		if((*it)->getCodigo()==idVenta)
		{
			if((*it)->getEstado()=="VIGENTE")
			{
				auxV=findVuelo((*it)->getFechavuelo(),findRuta((*it)->getRuta(),tRutas),tVuelos);
				auxV->setDisponibles(auxV->getDisponibles()+1);
				vendedora->setCancelados(vendedora->getCancelados()+1);
				vendedora->setDevoluciones(vendedora->getDevoluciones()-((*it)->getValor()*0.85));
			}
			(*it)->setEstado("CANCELADO");
			res=true;
		}
	}
	return res;
}
bool consolidate(list<Venta*> &tVentas, list<Ruta*> &tRutas, list<Vuelo*> &tVuelos)
{
	char fecha[10];
	string fec;
	using chrono::system_clock;
	time_t tt = system_clock::to_time_t (system_clock::now());
	strftime(fecha,sizeof(fecha),"%Y%m%d", localtime(&tt));
	fec=fecha;
	for(list<Venta*>::iterator it = tVentas.begin(); it!=tVentas.end(); it++)
	{
		if(stoi((*it)->getFechavuelo())<stoi(fec))
		{
			it=tVentas.erase(it);
		}
	}
	inventory(tVentas,tRutas,tVuelos);
}
void finances(Agencia* &vendedora)
{
	TablePrinter tp1(&cout);
	tp1.AddColumn("INGRESOS",20);
	tp1.AddColumn("DEVOLUCIONES",20);
	tp1.AddColumn("GANANCIAS",20);
	tp1.AddColumn("CANCELACIONES",20);
	tp1.AddColumn("CAMBIOS",20);
	tp1.PrintHeader();
	tp1 << vendedora->getIngresos() << vendedora->getDevoluciones() << vendedora->getIngresos() + vendedora->getDevoluciones() << vendedora->getCancelados() << vendedora->getCambiados();
	tp1.PrintFooter();
	TablePrinter tp2(&cout);
	tp2.AddColumn("CODIGO  ",10);
	tp2.AddColumn("RUTA ", 6);
	tp2.AddColumn("VALOR  ", 10);
	tp2.AddColumn("ESTADO  ", 10);
	tp2.PrintHeader();
	for(list<Venta*>::iterator it = vendedora->getVentas().begin(); it!=vendedora->getVentas().end(); it++)
	{
		tp2 << (*it)->getCodigo() << (*it)->getRuta() << (*it)->getValor() << (*it)->getEstado();
	}
	tp2.PrintFooter();
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
			newAgency->setIngresos(0);
			newAgency->setDevoluciones(0);
			newAgency->setGanancias(0);
			newAgency->setCancelados(0);
			newAgency->setCambiados(0);
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
			newSell->setValor(findRuta(newSell->getRuta(),tRutas)->getCosto());
			newSell->setEstado("VIGENTE");
			aux = checkVuelo(newSell->getFechavuelo(),findRuta(newSell->getRuta(),tRutas),tVuelos);
			tokenizedLine[6].resize(tokenizedLine[6].size() - 5);
			Aaux = findAgencia(tokenizedLine[6],tAgencias);
			if(aux->getDisponibles()==-1)
				fallosSeat++;
			else if(aux->getDisponibles()==-2)
				fallosExist++;
			else if(Aaux->getNombre()=="0")
				fallosAgency++;
			else
			{
				cant = Aaux->getCantVentas() + 1;
				Aaux->setCantventas(cant);
				Aaux->getVentas().push_back(newSell);
				tVentas.push_back(newSell);
				aux->getVendidos().push_back(newSell);
				Aaux->getVuelos().push_back(aux);
			}
		}
	}
	else
		return false;
	myfile.close();
	if(fallosSeat>0)
		cerr << "+++ No se registraron " << fallosSeat << " ventas, los vuelos no tenian sillas disponibles" << endl;
	if(fallosExist>0)
		cerr << "+++ No se registraron " << fallosExist << " ventas, la ruta no existe" << endl;
	if(fallosAgency>0)
		cerr << "+++ No se registraron " << fallosAgency << " ventas, la agencia no existe" << endl;
	return true;
}
void updateStates(list<Ruta*> &tRutas, list<Vuelo*> &tVuelos, Agencia* &vendedora)
{
	int fecha1 = 0, fecha2 = 0;
	Vuelo* auxV = new Vuelo();
	for(list<Venta*>::iterator it = vendedora->getVentas().begin(); it!=vendedora->getVentas().end(); it++)
		for(list<Venta*>::iterator itI = vendedora->getVentas().begin(); itI!=vendedora->getVentas().end(); itI++)
		{
			if((*it)->getCodigo()==(*itI)->getCodigo())
			{
				if((*it)->getEstado()=="CANCELADO")
					break;
				fecha1 = stoi((*it)->getFechacompra());
				fecha2 = stoi((*itI)->getFechacompra());
				if(fecha1<fecha2 && (*itI)->getEstado()!="CAMBIO")
				{
					int diff=0;
					(*it)->setEstado("CAMBIO");
					(*itI)->setEstado("VIGENTE");
					auxV=findVuelo((*it)->getFechavuelo(),findRuta((*it)->getRuta(),tRutas),tVuelos);
					auxV->setDisponibles(auxV->getDisponibles()+1);
					auxV=findVuelo((*itI)->getFechavuelo(),findRuta((*itI)->getRuta(),tRutas),tVuelos);
					auxV->setDisponibles(auxV->getDisponibles()-1);
					vendedora->setCambiados(vendedora->getCambiados()+1);
					diff=(*it)->getValor()-(*itI)->getValor();
					if(diff<0)
					{
						(*itI)->setValor((*itI)->getValor()+diff);
						vendedora->setDevoluciones(vendedora->getDevoluciones()+diff);
					}
					else
					{
						(*itI)->setValor((*itI)->getValor()+diff);
						vendedora->setIngresos(vendedora->getIngresos()+diff);
					}
					break;
				}
			}
		}
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
Vuelo* findVuelo(string Lfecha, Ruta* Lruta, list<Vuelo*> &tVuelos)
{
	for(list<Vuelo*>::iterator it = tVuelos.begin(); it!=tVuelos.end(); it++)
	{
		if((*it)->getRuta()==Lruta&&(*it)->getFecha()==Lfecha)
		{
			return *it;
		}
	}
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
char* completion_generator(const char* text, int state)
{
	// This function is called with state=0 the first time; subsequent calls are
	// with a nonzero state. state=0 can be used to perform one-time
	// initialization for this completion session.
	static std::vector<std::string> matches;
	static size_t match_index = 0;

	if (state == 0) {
		// During initialization, compute the actual matches for 'text' and keep
		// them in a static vector.
		matches.clear();
		match_index = 0;

		// Collect a vector of matches: vocabulary words that begin with text.
		std::string textstr = std::string(text);
		for (auto word : vocabulary) {
			if (word.size() >= textstr.size() &&
			    word.compare(0, textstr.size(), textstr) == 0) {
				matches.push_back(word);
			}
		}
	}

	if (match_index >= matches.size()) {
		// We return nullptr to notify the caller no more matches are available.
		return nullptr;
	} else {
		// Return a malloc'd char* for the match. The caller frees it.
		return strdup(matches[match_index++].c_str());
	}
}
char** completer(const char* text, int start, int end)
{
	// Don't do filename completion even if our generator finds no matches.
	rl_attempted_completion_over = 1;

	// Note: returning nullptr here will make readline use the default filename
	// completer.
	return rl_completion_matches(text, completion_generator);
}
