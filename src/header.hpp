/* Header-Datei header.hpp */

#ifndef HEADER_HPP
#define HEADER_HPP

typedef struct s_Node Node;

//Knotenstruktur des Baumes
struct s_Node{
	Node * father;
	Node * left_son;
	Node * right_son;
	unsigned int value;
};

//Die verschiedenen Varianten des Speicher Layouts.
enum Layout {RANDOM, SORTED, LAYERS, EMDEBOAS};

//
//Funktionen
//

//Generiert einen Baum mit 'size' Einträgen und 'mem_type' Speicherlayout.
//
Node* generate_tree(unsigned int size, enum Layout mem_type, unsigned int* numbers);

//Suche im 'tree' nach dem Schlüssel 'key'
//@return: die Suchzeit in Millisekunden zurück 
// ODER -1, wenn der Schlüssel nicht gefunden wird.
bool search_in_tree(Node* tree, unsigned int key);

#endif