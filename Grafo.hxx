#ifndef _GRAFO_HXX
#define _GRAFO_HXX

#include "Grafo.h"
//=========================================================================
template < class T >
Graph<T>::Graph()
{
}
//=========================================================================
template < class T >
Graph<T>::Graph(bool type) : type(type)
{
}
//=========================================================================
template < class T >
void Graph<T>::addVertex(T data)
{
	this->vertexs.insert(new Vertex<T>(data));
}
//=========================================================================
template < class T >
void Graph<T>::addEdge(T data, T data2, unsigned long cost)
{
	Vertex<T>* v1 = this->findVertex(data);
	Vertex<T>* v2 = this->findVertex(data2);

	if(v1 != nullptr && v2 != nullptr)
	{

		typename std::set<Vertex<T>*, VertComparator<T> >::iterator it;
		if(this->type)
		{

			it = this->vertexs.find(v1);
			if( it != this->vertexs.end())
			{
				it = this->vertexs.find(v2);
				if(it != this->vertexs.end())
				{
					v1->addAdjacents(cost, v2);
				}
			}
		}
		else
		{

			it = this->vertexs.find(v1);

			if( it != this->vertexs.end())
			{
				it = this->vertexs.find(v2);
				if(it != this->vertexs.end())
				{
					v1->addAdjacents(cost, v2);
					v2->addAdjacents(cost, v1);
				}
			}
		}
	}
}
//=========================================================================
template < class T >
void Graph<T>::eraseEdge(Vertex<T> *V1, Vertex<T> *v2)
{
	V1->eraseEdge(v2);
}
//=========================================================================
template < class T >
void Graph<T>::eraseVertex(T data )
{
	Vertex<T>* v2 = this->findVertex(data);
	if(v2 != nullptr)
	{
		for(typename std::set<Vertex<T>*>::iterator it1 = this->vertexs.begin(); it1 != this->vertexs.end(); it1++)
		{
			(*it1)->eraseEdge(v2);
		}
		Vertex<T> *aux = v2;
		this->vertexs.erase(v2);
		delete aux;
	}
}
//=========================================================================
template < class T >
Vertex<T>* Graph<T>::findVertex(T data)
{
	typename std::set<Vertex<T>*>::iterator it;
	bool ya = false;
	for(it = this->vertexs.begin(); it != this->vertexs.end() && !ya; it++)
	{
		if((*it)->data == data )
		{
			ya = true;
		}
	}
	if(ya)
	{
		--it;
		return (*it);
	}
	return nullptr;
}
//=========================================================================
template < class T >
void Graph<T>::flatTravel(){
	typename std::set<Vertex<T>*>::iterator it;
	std::cout<<std::endl;
	for(it = this->vertexs.begin(); it != this->vertexs.end(); it++) {
		std::cout<<(*it)->data<<" -> ";
	}
	std::cout<<std::endl;
}
//=========================================================================
template < class T >
void Graph<T>::resetVisited(){
	typename std::set<Vertex<T>*>::iterator it;
	for(it = this->vertexs.begin(); it != this->vertexs.end(); it++) {
		(*it)->setVisited(false);
	}
}
//=========================================================================
template < class T >
void Graph<T>::DepthfirstSearch(T begin){
	Vertex<T>* aux = this->findVertex(begin);
	if(aux != nullptr) {
		if(!aux->getVisited()) {
			aux->setVisited(true);
			std::cout<<aux->GetData()<<" ";

			if(!aux->GetAdjacents().empty()) {
				typename std::multimap<Vertex<T>*, Edge* > aux2 = aux->GetAdjacents();
				for(typename std::multimap<Vertex<T>*, Edge* >::iterator it  = aux2.begin(); it != aux2.end(); it++) {
					this->DepthfirstSearch((it->first)->GetData());
				}
			}
		}
	}
}
//=========================================================================
template < class T >
void Graph<T>::depthFirstSearch(T begin){
	this->DepthfirstSearch(begin);
	this->resetVisited();
}
//=========================================================================
template < class T >
void Graph<T>::Breadthfirstsearch(T begin){
	std::queue<Vertex<T>*> q;
	if(this->findVertex(begin) != nullptr) {
		q.push(this->findVertex(begin));
		this->findVertex(begin)->setVisited(true);
		while(!q.empty()) {

			typename std::multimap<Vertex<T>*, Edge* > aux2 = q.front()->GetAdjacents();
			for(typename std::multimap<Vertex<T>*, Edge* >::iterator it  = aux2.begin(); it != aux2.end(); it++) {
				if((it->first)->getVisited() == false ) {
					q.push(it->first);
					(it->first)->setVisited(true);
				}
			}
			std::cout<<q.front()->GetData()<<" ";
			q.pop();
		}
	}
}
//=========================================================================
template < class T >
void Graph<T>::breadthfirstsearch(T begin){
	this->Breadthfirstsearch(begin);
	this->resetVisited();
}
//=========================================================================
template < class T >
bool Graph<T>::isPath(T begin){
	unsigned int impar = 0;
	int dif = 0;
	if(this->type ) {
		std::queue<Vertex<T>*> q;
		if(this->findVertex(begin) != nullptr) {
			std::set<Vertex<T>*, VertComparator<T> > aux = this->GetConectedComponents(this->findVertex(begin));
			unsigned int inGrade = 0;
			unsigned int outGrade = 0;
			int res = 0;
			unsigned int mayor = 0;
			for(typename std::set<Vertex<T>*, VertComparator<T> >::iterator it1 = aux.begin(); it1 != aux.end(); it1++) {
				inGrade =  this->getinGrade(*it1);
				outGrade = (*it1)->GetAdjacents().size();
				res = inGrade - outGrade;
				if( res < 0) {
					res *= -1;
				}
				if(res == 1) {
					impar++;
					q.push(*it1);
				}
				if(res > 1) {
					mayor++;
				}
			}
			if(mayor > 0) {
				return false;
			}else{
				if(impar > 2) {
					return false;
				}else{
					if(impar >= 1) {
						this->EulerPath(q.front());
						this->resetVisited();
						this->resetEdgeVisited();
						return true;
					}else{
						return false;
					}
				}
			}
		}
	}else{
		std::queue<Vertex<T>*> q;
		std::queue<Vertex<T>*> v;
		if(this->findVertex(begin) != nullptr) {
			q.push(this->findVertex(begin));
			this->findVertex(begin)->setVisited(true);
			while(!q.empty()) {
				typename std::multimap<Vertex<T>*, Edge* > aux2 = q.front()->GetAdjacents();
				for(typename std::multimap<Vertex<T>*, Edge* >::iterator it  = aux2.begin(); it != aux2.end(); it++) {
					if((it->first)->getVisited() == false ) {
						q.push(it->first);
						(it->first)->setVisited(true);
					}
				}
				if(q.front()->getGrade() % 2 != 0) {
					impar++;
					v.push(q.front());
				}
				q.pop();
			}
		}
		if(impar > 0 && impar <= 2) {
			this->EulerPath(v.front());
			this->resetEdgeVisited();
			this->resetVisited();
			return true;
		}else if(impar == 0 ) {
			this->EulerPath(this->findVertex(begin));
			this->resetEdgeVisited();
			this->resetVisited();
			return true;
		}
	}
	return false;
}
//=========================================================================
template < class T >
unsigned int Graph<T>::getinGrade(Vertex<T>* v ){
	typename std::set<Vertex<T>*>::iterator it;
	unsigned int cont = 0;
	for(it = this->vertexs.begin(); it != this->vertexs.end(); it++) {
		if ((*it)->exist(v)) {
			cont++;
		}
	}
	return cont;
}
//=========================================================================
template < class T >
void Graph<T>::EulerPath(Vertex<T>* V){
	std::multimap<Vertex<T>*, Edge* > adjacents = V->GetAdjacents();

	for(typename std::multimap<Vertex<T>*, Edge* >::iterator it = adjacents.begin(); it != adjacents.end(); it++) {

		if(!V->ExistEdge(it->first) && this->validNext(V,it->first)) {
			std::cout<<V->GetData()<<" - "<<(it->first)->GetData()<<", ";
			this->rmEdge(V,it->first);
			this->EulerPath(it->first);
		}
	}
}
//=========================================================================
template < class T >
void Graph<T>::rmEdge(Vertex<T>* v1, Vertex<T>* v2){
	typename std::set<Vertex<T>*>::iterator it  = this->vertexs.find(v1);
	typename std::set<Vertex<T>*>::iterator it1 = this->vertexs.find(v2);
	if(it != this->vertexs.end() && it1 != this->vertexs.end()) {
		(*it)->rmEdge(v2);
		if(!this->type)
			(*it1)->rmEdge(v1);
	}
}
//=========================================================================
template < class T >
void Graph<T>::reAddEdge(Vertex<T>* v1, Vertex<T>* v2){
	typename std::set<Vertex<T>*>::iterator it  = this->vertexs.find(v1);
	typename std::set<Vertex<T>*>::iterator it1 = this->vertexs.find(v2);
	if(it != this->vertexs.end() && it1 != this->vertexs.end()) {
		(*it)->reAddEdge(v2);
		if(!this->type)
			(*it1)->reAddEdge(v1);
	}
}
//=========================================================================
template < class T >
bool Graph<T>::validNext(Vertex<T>* v1, Vertex<T>* v2){
	if(v1->NumberOfNonVisitedVertexs() == 1) {
		return true;
	}
	this->resetVisited();
	unsigned int a =  this->DFCount(v1);
	this->resetVisited();
	this->rmEdge(v1, v2);
	unsigned int b = this->DFCount(v1);
	this->reAddEdge(v1,v2);
	return (a > b) ? false : true;
}
//=========================================================================
template < class T >
unsigned int Graph<T>::numberOfConectedComponents(Vertex<T>* v1){
	std::queue<Vertex<T>*> iqueue;
	iqueue.push(v1);
	v1->visited = true;
	unsigned int cont = 0;
	while(!iqueue.empty()) {
		cont++;
		std::multimap<Vertex<T>*, Edge* > adjacents = iqueue.front()->GetAdjacents();
		for(typename std::multimap<Vertex<T>*, Edge* >::iterator it = adjacents.begin(); it != adjacents.end(); it++) {
			if(!(it->first)->visited) {
				iqueue.push(it->first);
				(it->first)->visited = true;
			}
		}
		typename std::set<Vertex<T>*>::iterator it1;
		for(it1 = this->vertexs.begin(); it1 != this->vertexs.end(); it1++) {
			if(!(*it1)->visited && (*it1)->HasAdjacent(iqueue.front())) {
				iqueue.push(*it1);
				(*it1)->visited = true;
			}
		}
		iqueue.pop();
	}
	this->resetVisited();
	return cont;
}
//=========================================================================
template < class T >
unsigned int Graph<T>::DFCount(Vertex<T>* v ){
	v->setVisited(true);
	unsigned int cont = 1;
	std::multimap<Vertex<T>*, Edge* > adjacents = v->GetAdjacents();
	for(typename std::multimap<Vertex<T>*, Edge* >::iterator it = adjacents.begin(); it != adjacents.end(); it++) {
		if( !(it->second)->visited && !(it->first)->visited   ) {
			cont += this->DFCount(it->first);
		}
	}
	return cont;
}
//=========================================================================
template <class T>
void Graph<T>::dijkstra(T begin, T end){
	this->resetValue();
	std::priority_queue<Vertex<T>*, std::vector<Vertex<T>*>, VertComparator<T> > queue;
	std::multimap<Vertex<T>*, Vertex<T>*> print;
	Vertex<T> *v= this->findVertex(begin);
	v->setValue(0);
	queue.push(v);
	while(!queue.empty()) {
		Vertex<T> *u=queue.top();
		queue.pop();
		std::multimap<Vertex<T>*, Edge* > aux=u->GetAdjacents();
		typename std::multimap<Vertex<T>*, Edge* >::iterator it=aux.begin();
		for(; it!=aux.end(); it++) {
			if(u->getValue()+ (it->second)->weigth < it->first->getValue()) {
				print.insert(std::pair<Vertex<T>*,Vertex<T>*>(it->first,u));
				it->first->setValue(u->getValue()+  (it->second)->weigth);
				print.find(it->first)->second=u;
				queue.push(it->first);
			}
		}
	}
	std::stack<T> track;
	track.push(end);
	if(this->findVertex(end)->getValue() != 9999) {
		while(track.top()!=begin) {
			typename std::multimap<Vertex<T> *, Vertex<T> *>::iterator it=print.begin();
			for(; it!=print.end(); it++) {
				if(it->first->GetData()==track.top()) {
					track.push(it->second->GetData());
					break;
				}
			}
		}
		while(!track.empty()) {
			std::cout<<track.top()<<", ";
			track.pop();
		}
	}
	std::cout<<std::endl;
	this->resetEdgeVisited();
}
//=========================================================================
template<class T>
void Graph<T>::resetValue(){
	typename std::set<Vertex<T> *>::iterator it = this->vertexs.begin();
	for(; it!=this->vertexs.end(); it++) {
		(*it)->setValue(9999);
	}
}
//=========================================================================
template<class T>
void Graph<T>::resetEdgeVisited(){
	typename std::set<Vertex<T>*>::iterator it;
	for(it = this->vertexs.begin(); it != this->vertexs.end(); it++) {
		(*it)->resetVisited();
	}
}
//=========================================================================
template<class T>
std::set<Vertex<T>*, VertComparator<T> > Graph<T>::GetConectedComponents(Vertex<T>* v1){
	std::queue<Vertex<T>*> iqueue;
	iqueue.push(v1);
	v1->visited = true;
	std::set<Vertex<T>*, VertComparator<T> > auxestruct;
	while(!iqueue.empty()) {
		auxestruct.insert(iqueue.front());
		std::multimap<Vertex<T>*, Edge* > adjacents = iqueue.front()->GetAdjacents();
		for(typename std::multimap<Vertex<T>*, Edge* >::iterator it = adjacents.begin(); it != adjacents.end(); it++) {
			if(!(it->first)->visited) {
				iqueue.push(it->first);
				(it->first)->visited = true;
			}
		}
		typename std::set<Vertex<T>*>::iterator it1;
		for(it1 = this->vertexs.begin(); it1 != this->vertexs.end(); it1++) {
			if(!(*it1)->visited && (*it1)->HasAdjacent(iqueue.front())) {
				iqueue.push(*it1);
				(*it1)->visited = true;
			}
		}
		iqueue.pop();
	}
	this->resetVisited();
	return auxestruct;
}
#endif
