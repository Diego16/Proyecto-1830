#ifndef VERTICE_GRAFO_HXX
#define VERTICE_GRAFO_HXX

#include "Vertice.h"

//=========================================================================
template < class T >
Vertex<T>::Vertex(){

}
//=========================================================================
template < class T >
Vertex<T>::Vertex(T& data) : data(data), visited(false), value(0){

}
//=========================================================================
template < class T >
void Vertex<T>::addAdjacents(unsigned long cost,  Vertex<T>* vert){
	Edge* aux  = new Edge(cost,false);
	this->adjacents.insert(std::pair<Vertex<T>*, Edge* >(vert,aux) );
}
//=========================================================================
template < class T >
bool operator == (const Vertex<T> &v1, const Vertex<T> &v2){
	return v1.data == v2.data;
}
//=========================================================================
template < class T >
bool operator != (const Vertex<T> &v1, const Vertex<T> &v2){
	return v1.data != v2.data;
}
//=========================================================================
template < class T >
bool operator < (const Vertex<T> &v1, const Vertex<T> &v2){
	return v1.data < v2.data;
}
//=========================================================================
template < class T >
bool operator > (const Vertex<T> &v1, const Vertex<T> &v2){
	return v1.data > v2.data;
}
//=========================================================================
template < class T >
bool operator >= (const Vertex<T> &v1, const Vertex<T>&v2){
	return v1.data >= v2.data;
}
//=========================================================================
template < class T >
bool operator <= (const Vertex<T> &v1, const Vertex<T> &v2){
	return v1.data <= v2.data;
}
//=========================================================================
template < class T >
std::ostream& operator << (std::ostream &o, const Vertex<T> &v1){
	return o << v1.data;
}
//=========================================================================
template < class T >
void Vertex<T>::eraseEdge(Vertex<T>*vert){
	typename std::multimap<Vertex<T>*, Edge* >::iterator it;
	it = this->adjacents.find(vert);
	if(it != this->adjacents.end()) {
		this->adjacents.erase(it);
	}
}
//=========================================================================
template < class T >
T Vertex<T>::GetData() const {
	return this->data;
}
//=========================================================================
template < class T >
void Vertex<T>::PrintEdges(){
	typename std::multimap<Vertex<T>*, Edge* >::iterator it;
	for(it = this->adjacents.begin(); it != this->adjacents.end(); it++) {
		std::cout<<"Nombre:"<<(it->first)->data<<", Afinidad: "<<(it->second)->weigth<<std::endl;
	}
}
//=========================================================================
template < class T >
bool Vertex<T>::getVisited(){
	return this->visited;
}
//=========================================================================
template < class T >
void Vertex<T>::setVisited(bool v){
	this->visited = v;
}
//=========================================================================
template < class T >
std::multimap<Vertex<T>*, Edge* > Vertex<T>::GetAdjacents(){
	return this->adjacents;
}
//=========================================================================
template < class T >
unsigned int Vertex<T>::getGrade(){
	return this->adjacents.size();
}
//=========================================================================
template < class T >
bool Vertex<T>::exist(Vertex<T>* v ){
	typename std::multimap<Vertex<T>*,Edge*>::iterator it  = this->adjacents.find(v);
	if(it != this->adjacents.end()) {
		return true;
	}
	return false;
}
//=========================================================================
template < class T >
void Vertex<T>::resetVisited(){
	typename std::multimap<Vertex<T>*,Edge*>::iterator it;
	for(it = this->adjacents.begin(); it != this->adjacents.end(); it++) {
		(it->second)->visited = false;
	}
}
//=========================================================================
template < class T >
void Vertex<T>::rmEdge(Vertex<T>* v){
	bool band = false;
	std::pair <typename std::multimap<Vertex<T>*, Edge*>::iterator, typename std::multimap<Vertex<T>*, Edge*>::iterator> ret;
	ret = this->adjacents.equal_range(v);
	for (typename std::multimap<Vertex<T>*, Edge*>::iterator it=ret.first; it!=ret.second; ++it) {
		if( !(it->second)->visited && !band) {
			(it->second)->visited = true;
			band = true;
		}
	}


}
//=========================================================================
template < class T >
void Vertex<T>::reAddEdge(Vertex<T>* v){
	bool band = false;
	std::pair <typename std::multimap<Vertex<T>*, Edge*>::iterator, typename std::multimap<Vertex<T>*, Edge*>::iterator> ret;
	ret = this->adjacents.equal_range(v);
	for (typename std::multimap<Vertex<T>*, Edge*>::iterator it=ret.first; it!=ret.second; ++it) {
		if( (it->second)->visited && !band ) {
			(it->second)->visited = false;
			band = true;
		}
	}
}
//=========================================================================
template < class T >
bool Vertex<T>::ExistEdge(Vertex<T>* v){
	bool band = false;
	std::pair <typename std::multimap<Vertex<T>*, Edge*>::iterator, typename std::multimap<Vertex<T>*, Edge*>::iterator> ret;
	ret = this->adjacents.equal_range(v);
	for (typename std::multimap<Vertex<T>*, Edge*>::iterator it=ret.first; it!=ret.second; ++it) {
		if( (it->second)->visited == false && !band ) {
			band = true;
		}
	}
	return !band;
}
//=========================================================================
template < class T >
unsigned int Vertex<T>::NumberOfNonVisitedVertexs(){
	unsigned int cont = 0;
	typename std::multimap<Vertex<T>*,Edge*>::iterator it;
	for(it = this->adjacents.begin(); it != this->adjacents.end(); it++) {
		if(!(it->second)->visited ) {
			cont++;
		}
	}
	return cont;
}
//=========================================================================
template < class T >
bool Vertex<T>::HasAdjacent(Vertex<T>* v){
	typename std::multimap<Vertex<T>*, Edge* >::iterator it   = this->adjacents.find(v);
	if(it != this->adjacents.end()) {
		return true;
	}else{
		return false;
	}
}
//=========================================================================
template<class T>
int Vertex<T>::getValue(){
	return this->value;
}
//=========================================================================
template<class T>
void Vertex<T>::setValue(int value){
	this->value= value;
}
//=========================================================================
template<class T>
int Vertex<T>::getDist(Vertex<T> *t){
	return this->ady.find(t)->second;
}
//=========================================================================
template<class T>
bool Vertex<T>::allAdy(){
	bool x=true;
	typename std::multimap<Vertex<T> *, int>::iterator it=this->ady.begin();
	for(; it!=this->ady.end(); it++) {
		if(it->first->getVisited()==false) {
			x=false;
		}
	}
	return x;
}
//=========================================================================
#endif
