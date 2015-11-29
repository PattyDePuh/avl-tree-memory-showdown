/* Source-Datei tree_generator.cpp */

#include <cstdlib>
#include <cmath>
#include <math.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "header.hpp"

Node* data;
long index = 0;
long myblockheight;

void recursiveRandom(Node** actualElement, unsigned long* numbers, std::vector<long>& freeIndex, long startIndex, long endIndex) {
  *actualElement = data + freeIndex.back();
  freeIndex.pop_back();
  (*actualElement)->value = numbers[startIndex + (endIndex - startIndex) / 2];
  //std::cout << "von " << startIndex << " bis " << endIndex << " Zahl " << (*actualElement)->value << std::endl;
  if (startIndex != endIndex) {
    recursiveRandom(&((*actualElement)->left_son), numbers, freeIndex, startIndex, startIndex + (endIndex - startIndex) / 2 - 1);
    recursiveRandom(&((*actualElement)->right_son), numbers, freeIndex, startIndex + (endIndex - startIndex) / 2 + 1, endIndex);
  }
}

Node* generate_random_tree(unsigned long size, unsigned long* numbers){
  // build list of all indices
  std::vector<long> indexlist;
  for (long i = 0; i < size; i++) {
    indexlist.push_back(i);
  }
  // build random list from all indices
  std::vector<long> freeIndex;
  for (long i = 0; i < size; i++) {
    long rnd = rand() % indexlist.size();
    freeIndex.push_back(indexlist.at(rnd));
    indexlist.erase(indexlist.begin() + rnd);
  }

  Node* root;
  recursiveRandom(&root, numbers, freeIndex, 0, size - 1);

  /*
  for (long i = 0; i < size; i++) {
    std::cout << i << ": " << data + i << " " << data[i].value << " left:" << data[i].left_son << " right:" << data[i].right_son << std::endl;
  }
  */

  return root;
}

void recursiveSorted(Node** actualElement, unsigned long* numbers, long startIndex, long endIndex) {
  *actualElement = data + startIndex + (endIndex - startIndex) / 2;
  (*actualElement)->value = numbers[startIndex + (endIndex - startIndex) / 2];
  //std::cout << "von " << startIndex << " bis " << endIndex << " Zahl " << (*actualElement)->value << std::endl;
  if (startIndex != endIndex) {
    recursiveSorted(&((*actualElement)->left_son), numbers, startIndex, startIndex + (endIndex - startIndex) / 2 - 1);
    recursiveSorted(&((*actualElement)->right_son), numbers, startIndex + (endIndex - startIndex) / 2 + 1, endIndex);
  }
}

Node* generate_sorted_tree(unsigned long size, unsigned long* numbers) {
  Node* root;
  recursiveSorted(&root, numbers, 0, size - 1);

  /*
  for (long i = 0; i < size; i++) {
    std::cout << i << ": " << data + i << " " << data[i].value << " left:" << data[i].left_son << " right:" << data[i].right_son << std::endl;
  }
  */

  return root;
}

void recursiveLayers(Node** actualElement, unsigned long* numbers, long startIndex, long endIndex, long offset) {
  *actualElement = data + offset - 1;
  (*actualElement)->value = numbers[startIndex + (endIndex - startIndex) / 2];
  //std::cout << "von " << startIndex << " bis " << endIndex << " Zahl " << (*actualElement)->value << std::endl;
  if (startIndex != endIndex) {
    recursiveLayers(&((*actualElement)->left_son), numbers, startIndex, startIndex + (endIndex - startIndex) / 2 - 1, offset * 2);
    recursiveLayers(&((*actualElement)->right_son), numbers, startIndex + (endIndex - startIndex) / 2 + 1, endIndex, offset * 2 + 1);
  }
}

Node* generate_layers_tree(unsigned long size, unsigned long* numbers) {
  Node* root;
  recursiveLayers(&root, numbers, 0, size - 1, 1);

  /*
  for (long i = 0; i < size; i++) {
    std::cout << i << ": " << data + i << " " << data[i].value << " left:" << data[i].left_son << " right:" << data[i].right_son << std::endl;
  }
  */

  return root;
}

Node* getSubTreePlace() {
  Node* p = data + index;
  index += pow(2, myblockheight) - 1;
  return p;
}

Node* recursiveEmdeboas(Node* actualElement, unsigned long* numbers, long startIndex, long endIndex, long offset, long subdepth, long size, long depth) {
  actualElement += offset - 1;
  actualElement->value = numbers[startIndex + (endIndex - startIndex) / 2];
  //std::cout << actualElement << " " << actualElement->value << " depth:" << depth << " subdepth:" << subdepth <<std::endl;

  if (startIndex != endIndex) {
    Node* nl;
    Node* nr;

    if (subdepth + 1 < myblockheight) {
      long newloffset = offset * 2;
      long newroffset = offset * 2 + 1;
      nl = recursiveEmdeboas(actualElement, numbers, startIndex, startIndex + (endIndex - startIndex) / 2 - 1, newloffset, subdepth + 1, size, depth + 1);
      nr = recursiveEmdeboas(actualElement, numbers, startIndex + (endIndex - startIndex) / 2 + 1, endIndex, newroffset, subdepth + 1, size, depth + 1);
    }
    else {
      //std::cout << "new subtree" << std::endl;
      nl = recursiveEmdeboas(getSubTreePlace(), numbers, startIndex, (startIndex + (endIndex - startIndex) / 2) - 1, 1, 0, size, depth + 1);
      nr = recursiveEmdeboas(getSubTreePlace(), numbers, (startIndex + (endIndex - startIndex) / 2) + 1, endIndex, 1, 0, size, depth + 1);
    }

    actualElement->left_son = nl;
    actualElement->right_son = nr;
  }

  return actualElement;
}

Node* generate_emdeboas_tree(unsigned long size, unsigned long* numbers) {
  Node* root;

  //std::cout << "size:" << sizeof(Node*) << std::endl;
  //std::cout << "#level:" << log2(size + 1) << std::endl;

  root = recursiveEmdeboas(getSubTreePlace(), numbers, 0, size - 1, 1, 0, size, 0);

  for (long i = 0; i < size; i++) {
    //std::cout << i << ": " << data + i << " " << data[i].value << " left:" << data[i].left_son << " right:" << data[i].right_son << std::endl;
  }

  return root;
}

//Generiert einen Baum mit 'size' Elongrägen und 'mem_type' Speicherlayout.
Node* generate_tree(unsigned long size, enum Layout mem_type, unsigned long* numbers, long blockheight){
  myblockheight = blockheight;
  data = new Node[size];
  for (long i = 0; i < size; i++) {
    data[i].value = -1;
    data[i].left_son = 0;
    data[i].right_son = 0;
  }

	//Zuerst im switch-case die mem_types unterscheiden und dann separat generieren
        switch (mem_type) {
          case RANDOM:
            return generate_random_tree(size, numbers);
          case SORTED:
            return generate_sorted_tree(size, numbers);
          case LAYERS:
            return generate_layers_tree(size, numbers);
          case EMDEBOAS:
            return generate_emdeboas_tree(size, numbers);
        }
	return NULL;
}


//Suche im 'tree' nach dem Schlüssel 'key'
bool search_in_tree(Node* tree, unsigned long key){
	//Steige in den Baum oben ein.
	Node* focus = tree;

	//Solange der im Knoten nicht der gewünschte Wert ist. DO:
	while (focus->value != key){
		// Vergleiche die Schlüssel und entscheide dich 
		// für einen Knoten-Sohn, brich ab, wenn der
		// Verweis zum Sohn leer ist.
		if(key < focus->value){
			if(focus->left_son == NULL)
				return false;
			else
				focus = focus->left_son;
		}else{
			if(focus->right_son == NULL)
				return false;
			else
				focus = focus->right_son;
		}
	}

	return true;
}
