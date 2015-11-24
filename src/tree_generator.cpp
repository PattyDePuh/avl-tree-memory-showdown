/* Source-Datei tree_generator.cpp */

#include <cstdlib>
#include <math.h>
#include <vector>
#include <iostream>

#include "header.hpp"

void recursiveShit(Node* actualElement, unsigned int* numbers, std::vector<int>& freeIndex, int startIndex, int endIndex, Node* data) {
  actualElement = data + freeIndex.back();
  freeIndex.pop_back();
  actualElement->value = numbers[startIndex + (endIndex - startIndex) / 2];
  //std::cout << "von " << startIndex << " bis " << endIndex << " Zahl " << actualElement->value << std::endl;
  if (startIndex != endIndex) {
    recursiveShit(actualElement->left_son, numbers, freeIndex, startIndex, startIndex + (endIndex - startIndex) / 2 - 1, data);
    recursiveShit(actualElement->right_son, numbers, freeIndex, startIndex + (endIndex - startIndex) / 2 + 1, endIndex, data);
  }
}

Node* generate_random_tree(unsigned int size, unsigned int* numbers){
  Node data[size];

  // build list of all indices
  std::vector<int> indexlist;
  for (int i = 0; i < size; i++) {
    indexlist.push_back(i);
  }
  // build random list from all indices
  std::vector<int> freeIndex;
  for (int i = 0; i < size; i++) {
    int rnd = rand() % indexlist.size();
    freeIndex.push_back(indexlist.at(rnd));
    indexlist.erase(indexlist.begin() + rnd);
  }

  Node* root = data + freeIndex.back();
  freeIndex.pop_back();
  root->value = numbers[size / 2];
  recursiveShit(root->left_son, numbers, freeIndex, 0, size / 2 - 1, data);
  recursiveShit(root->right_son, numbers, freeIndex, size / 2 + 1, size - 1, data);

  for (int i = 0; i < size; i++) {
    std::cout << i << ": " << data[i].value << std::endl;
  }

  return root;
}

Node* generate_sorted_tree(unsigned int size){}
Node* generate_layers_tree(unsigned int size){}
Node* generate_emdeboas_tree(unsigned int size){}

//Generiert einen Baum mit 'size' Einträgen und 'mem_type' Speicherlayout.
Node* generate_tree(unsigned int size, enum Layout mem_type, unsigned int* numbers){
	//Zuerst im switch-case die mem_types unterscheiden und dann separat generieren
        switch (mem_type) {
          case RANDOM:
            return generate_random_tree(size, numbers);
          case SORTED:
            return generate_sorted_tree(size);
          case LAYERS:
            return generate_layers_tree(size);
          case EMDEBOAS:
            return generate_emdeboas_tree(size);
        }
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
