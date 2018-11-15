#ifndef _GRAFO_H
#define _GRAFO_H

#include "Vertice.h"
#include <set>
#include <iostream>
#include <queue>
#include <stack>


template < class T >
struct VertComparator
{
	bool operator()(const Vertex<T>* a, const Vertex<T>* b ) const
	{
		return a->GetData() < b->GetData();
	}
};
template < class T >
class Graph
{
protected:
std::set<Vertex<T>*, VertComparator<T> > vertexs;
bool type;
public:
Graph();
Graph(bool type);
~Graph() = default;
void addVertex(T data);
void eraseEdge(Vertex<T> *V1, Vertex<T> *v2);
Vertex<T>* findVertex(T data);
void addEdge(T data, T data2, unsigned long cost);
void eraseVertex(T data );
void flatTravel();
void resetVisited();
void DepthfirstSearch(T begin);
void depthFirstSearch(T begin);
void Breadthfirstsearch(T begin);
void breadthfirstsearch(T begin);
bool isPath(T begin);
void EulerPath(Vertex<T>* V);
unsigned int getinGrade(Vertex<T>* v );
void rmEdge(Vertex<T>* v1, Vertex<T>* v2);
void reAddEdge(Vertex<T>* v1, Vertex<T>* v2);
bool validNext(Vertex<T>* v1, Vertex<T>* v2);
unsigned int numberOfConectedComponents(Vertex<T>* v1);
std::set<Vertex<T>*, VertComparator<T> > GetConectedComponents(Vertex<T>* v1);
unsigned int DFCount(Vertex<T>* v );
void resetValue();
void dijkstra(T begin, T end);
void resetEdgeVisited();
};
#include "Grafo.hxx"

#endif
