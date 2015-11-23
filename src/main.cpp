/* Source-Datei main.cpp */

#include "header.hpp"
#include <cstdlib>
#include <iostream>
#include <time.h>
//Folgende Argumente werden erwartet:
// - die Anzahl Elemente, die in den Baum rein sollen.
// - der Typus des Speicher-Layouts
// - die Anzahl Such-Iterationen für die Zeiterfassung
int main(int argc, char** argv){

    //Variablen aus Parameter
    Layout m_type;
    unsigned int anzahl_elemente;
    unsigned int anzahl_such_iterationen;


  	anzahl_elemente = atoi(argv[1]);
  	anzahl_such_iterationen = atoi(argv[3]);
  	if (argv[2] == "RANDOM")
	  	m_type = RANDOM;
	else if (argv[2] == "SORTED")
        m_type = SORTED;
    else if (argv[2] == "LAYERS")
        m_type = LAYERS;
    else if (argv[2] == "EMDEBOAS")
        m_type = EMDEBOAS;
	else{
	   std::cerr << "Fehler: '" << argv[2] << "' ist kein gültiger Typ" << std::endl;
	   return 2;
  	}
  	//Generiere den Baum
  	Node* my_tree = generate_tree(anzahl_elemente, m_type);

  	//Verwende immer den selben Seed (#Comparable)
  	//ToDo!!!

  	//Beginne Messung der Such-Laufzeit
  	//Starte Zeit
	clock_t start_zeit = clock();
  	for(int i = 0; i < anzahl_such_iterationen; i++){
  		unsigned int random = rand() % anzahl_elemente;
  		if(search_in_tree(my_tree, random)){
  			continue;
  		}else{
  			std::cerr << "Schlüssel '" << random << "' konnte nicht gefunden werden!" << std::endl;
  		}
  	}
  	//Stoppe Zeit
  	clock_t end_zeit = clock();

  	//Zeitdifferenz
  	long gesamtzeit = (long)(((double)(end_zeit - start_zeit) / CLOCKS_PER_SEC)*1000);
  	long zeit_pro_such = gesamtzeit / anzahl_such_iterationen;

  	//Ausgabe
  	std::cout << gesamtzeit << " " << zeit_pro_such << std::endl;

  return 0;
}
