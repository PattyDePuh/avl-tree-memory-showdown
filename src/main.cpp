/* Source-Datei main.cpp */

#include "header.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <time.h>
//Folgende Argumente werden erwartet:
// - l in 2^l - 1
// - der Typus des Speicher-Layouts
// - die Anzahl Such-Iterationen für die Zeiterfassung
// - Seed
int main(int argc, char** argv){

    //Variablen aus Parameter
    Layout m_type;
    unsigned int anzahl_elemente;
    unsigned int anzahl_such_iterationen;
    unsigned int seed;
    int blockheight;


  	anzahl_elemente = pow(2, atoi(argv[1])) - 1;
  	anzahl_such_iterationen = atoi(argv[3]);
  	seed = atoi(argv[4]);
        if (!strcmp(argv[2], "RANDOM"))
          m_type = RANDOM;
        else if (!strcmp(argv[2], "SORTED"))
          m_type = SORTED;
        else if (!strcmp(argv[2], "LAYERS"))
          m_type = LAYERS;
        else if (!strcmp(argv[2], "EMDEBOAS")) {
          m_type = EMDEBOAS;
          blockheight = atoi(argv[5]);
        }
        else{
          std::cerr << "Fehler: '" << argv[2] << "' ist kein gültiger Typ" << std::endl;
          return 2;
        }

        srand(seed);

        // input numbers (sorted)
        unsigned int numbers[anzahl_elemente];
        for (int i = 0; i < anzahl_elemente; i++) {
          numbers[i] = i;
        }

  	//Generiere den Baum
  	Node* my_tree = generate_tree(anzahl_elemente, m_type, numbers, blockheight);

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
  	double gesamtzeit = (double)(end_zeit - start_zeit) / CLOCKS_PER_SEC;
  	double zeit_pro_such = gesamtzeit / anzahl_such_iterationen;

  	//Ausgabe
        std::cerr << "#numbers" << " " << "#iterations" << " " << "layout" << " " << "runtime";
        if (m_type == EMDEBOAS) std::cerr << " " << "blockheight";
        std::cerr << std::endl;
  	std::cout << anzahl_elemente << " " << anzahl_such_iterationen << " " << argv[2] << " " << gesamtzeit;
        if (m_type == EMDEBOAS) std::cout << " " << blockheight;
        std::cout << std::endl;

  return 0;
}
