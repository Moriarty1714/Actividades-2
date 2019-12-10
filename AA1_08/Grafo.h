#pragma once
#include <map>
#include <forward_list>
#include <vector>


typedef  int    vertex;
typedef  std::pair<int, int>  edge; //Nodo al nodo

class  GraphD
{
private:


public:
	std::map<vertex, std::vector<vertex>>  g; 

	//2. Constructor a partir de la lista de arcos el
	GraphD(std::vector<edge> el);
	~GraphD();

	//3.  Inserta  el  arco  si  no  existe
	void  Insert(edge);

	//4.  Borra  el  arco  si  existe 
	void  Remove(edge);

	//7.  Imprime  por  pantalla  la  lista  de  los  arcos  representando  al  grafo 
	void  Print();

};