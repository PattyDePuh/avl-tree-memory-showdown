/* Source-Datei tree_generator.cpp */

#include <cstdlib>
#include <math.h>

#include "header.hpp"

//Generiert einen Baum mit 'size' Einträgen und 'mem_type' Speicherlayout.
Node* generate_tree(unsigned int size, enum Layout mem_type){
	//ToDo:
	//Zuerst im switch-case die mem_types unterscheiden und dann separat generieren
	return NULL;
}


//Suche im 'tree' nach dem Schlüssel 'key'
bool search_in_tree(Node* tree, unsigned int key){
	//Steige in den Baum oben ein.
	Node focus = tree[0];

	//Solange der im Knoten nicht der gewünschte Wert ist. DO:
	while (focus.value != key){
		// Vergleiche die Schlüssel und entscheide dich 
		// für einen Knoten-Sohn, brich ab, wenn der
		// Verweis zum Sohn leer ist.
		if(key < focus.value){
			if(focus.left_son == NULL)
				return false;
			else
				focus = *(focus.left_son);
		}else{
			if(focus.right_son == NULL)
				return false;
			else
				focus = *(focus.left_son);
		}
	}

	return true;
}
