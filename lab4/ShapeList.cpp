//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below

#include "ShapeList.h"
#include "ShapeNode.h"
#include "Shape.h"

ShapeList::ShapeList() {
  head = nullptr;
}

ShapeList::~ShapeList() {
  if (!head) return; // empty list
  ShapeNode* curNode = head;
  ShapeNode* nextNode;

  while (curNode) {
    nextNode = curNode->getNext(); // save next node
    delete curNode; // delete current node
    curNode = nextNode; // advance current node
  }
}

ShapeNode* ShapeList::getHead() const {
  return head;
}

void ShapeList::setHead(ShapeNode* ptr) {
  head = ptr;
}

ShapeNode* ShapeList::find(string name) const {
  ShapeNode* curNode = head;
  while (curNode) {
    if (curNode->getShape()->getName() == name) return curNode;
    curNode = curNode->getNext();
  }
  return nullptr;
}

void ShapeList::insert(ShapeNode* s) {
  if (!s) return; 
  if (!head) { // empty list; insert as head
    head = s;
    return;
  }

  ShapeNode* curNode = head;
  while (curNode->getNext()) curNode = curNode->getNext(); // advance to end of list
  curNode->setNext(s);
}

ShapeNode* ShapeList::remove(string name) {
  ShapeNode* prevNode = nullptr;
  ShapeNode* curNode = head;
  while (curNode) {
    if (curNode->getShape()->getName() == name) {
      if (prevNode)
        prevNode->setNext(curNode->getNext());
      else
        head = curNode->getNext();
      curNode->setNext(nullptr);
      return curNode;
    }
    prevNode = curNode;
    curNode = curNode->getNext();
  }
  return nullptr;
}

void ShapeList::print() const {
  ShapeNode* curNode = head;
  while (curNode) {
    curNode->print();
    curNode = curNode->getNext();
  }
}