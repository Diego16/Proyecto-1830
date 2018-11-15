#ifndef VERTICE_GRAFO_H
#define VERTICE_GRAFO_H

#include "Grafo.h"
#include <map>
#include <iostream>


template < class T >
class Graph;

struct Edge {
	unsigned long weigth;
	bool visited;
	Edge(unsigned long weigth, bool visited) : weigth(weigth), visited(visited){
	}
};
template < class T >

class Vertex
{
friend class Graph<T>;
protected:
T data;
std::multimap<Vertex<T>*, Edge* > adjacents;
bool visited;
int value;

public:
Vertex();
Vertex(T& data );
~Vertex() = default;
void addAdjacents(unsigned long cost,  Vertex<T>* vert);
void eraseEdge(Vertex<T>*vert);
T GetData() const;
void PrintEdges();
bool getVisited();
void setVisited(bool v);
unsigned int getGrade();
bool exist(Vertex<T>* v );
std::multimap<Vertex<T>*, Edge* > GetAdjacents();
template<T> friend bool operator == (const Vertex<T> &v1, const Vertex<T> &v2);
template<T> friend bool operator != (const Vertex<T> &v1, const Vertex<T> &v2);
template<T> friend bool operator < (const Vertex<T> &v1, const Vertex<T> &v2);
template<T> friend bool operator > (const Vertex<T> &v1, const Vertex<T> &v2);
template<T> friend bool operator >= (const Vertex<T> &v1, const Vertex<T> &v2);
template<T> friend bool operator <= (const Vertex<T> &v1, const Vertex<T> &v2);
template<T> friend bool operator != (const Vertex<T> &v1, const Vertex<T> &v2);
template<T> friend std ::ostream& operator << (std::ostream &o, const Vertex<T> &v1);
void resetVisited();
void rmEdge(Vertex<T>* v);
void reAddEdge(Vertex<T>* v);
bool ExistEdge(Vertex<T>* v);
bool HasAdjacent(Vertex<T>* v);
unsigned int NumberOfNonVisitedVertexs();
int getValue();
void setValue(int value);
int getDist(Vertex<T> *t);
bool allAdy();
};

#include "Vertice.hxx"

#endif
