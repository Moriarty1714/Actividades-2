#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

#include "Clasesh.h"

#include "C:\Users\marti\Desktop\ENTI\Programmació\rapidxml.hpp"
#include "C:\Users\marti\Desktop\ENTI\Programmació\rapidxml_iterators.hpp"
#include "C:\Users\marti\Desktop\ENTI\Programmació\rapidxml_print.hpp"
#include "C:\Users\marti\Desktop\ENTI\Programmació\rapidxml_utils.hpp"

//AA1

int main() {
	
	std::map<std::string, Enemigo > oleada;

	rapidxml::xml_document<> doc;	//Creem un document perque llegeixi el .xml.
	std::ifstream file("config.xml");	//Li diem quin arxiu volem obrir.
	std::stringstream buffer;	//Creem un stringstream per guardar la info del .xml.		???
	buffer << file.rdbuf(); //Volquem la info al buffer.
	file.close();	//Tanquem el fitxer
	std::string content(buffer.str());	//	???
	doc.parse<0>(&content[0]);//	??? 
	rapidxml::xml_node<> *pNode = doc.first_node();	//creem un punter al document (com a primer node). Amb aquest recorrerem l'arbre.
	rapidxml::xml_attribute<> *pAttrib = doc.first_attribute();




	return 0;
}