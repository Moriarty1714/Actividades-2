#include "Grafo.h"

//2.  Constructor  a  partir  de  la  lista  de  arcos  el GraphD(std::vector<edge> )
GraphD::GraphD(std::vector<edge> el) {
	
	for (int i{ 0 }; i < el.size(); i++) {
		g[el[i].first] = std::vector<vertex>().insert((vertex)el[i].second);
	}
}

GraphD::~GraphD() {

}

//3.  Inserta  el  arco  si  no  existe
void  GraphD::Insert(edge) {

}

//4.  Borra  el  arco  si  existe 
void  GraphD::Remove(edge) {

}

//7.  Imprime  por  pantalla  la  lista  de  los  arcos  representando  al  grafo 
void  GraphD::Print() {

}