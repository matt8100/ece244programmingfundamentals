//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below

#include "GroupList.h"
#include "GroupNode.h"

GroupList::GroupList() {
  head = nullptr;
}

GroupList::~GroupList() {
  if (!head) return; // empty list
  GroupNode* curNode = head;
  GroupNode* nextNode;

  while (curNode) {
    nextNode = curNode->getNext(); // save next node
    delete curNode; // delete current node
    curNode = nextNode; // advance current node
  }
}

GroupNode* GroupList::getHead() const {
  return head;
}
 
void GroupList::setHead(GroupNode* ptr) {
  head = ptr;
}

void GroupList::insert(GroupNode* s) {
  if (!s) return; 
  if (!head) { // empty list; insert as head
    head = s;
    return;
  }

  GroupNode* curNode = head;
  while (curNode->getNext()) curNode = curNode->getNext(); // advance to end of list
  curNode->setNext(s);
}

GroupNode* GroupList::remove(string name) {
  GroupNode* prevNode = nullptr;
  GroupNode* curNode = head;
  while (curNode) {
    if (curNode->getName() == name) {
      if (prevNode)
        prevNode->setNext(curNode->getNext());
      else
        head = curNode->getNext();
      return curNode;
    }
    prevNode = curNode;
    curNode = curNode->getNext();
  }
  return nullptr;
}

void GroupList::print() const {
  GroupNode* curNode = head;
  while (curNode) {
    curNode->print();
    curNode = curNode->getNext();
  }
}