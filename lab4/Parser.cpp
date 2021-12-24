//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

// Error checks
bool ifInArray(string value, string array[], int size) {
    for (int i = 0; i < size; i++)
        if (array[i] == value)
            return true;
    return false;
}

bool invalidName(string name) {
    if (ifInArray(name, keyWordsList, NUM_KEYWORDS) || ifInArray(name, shapeTypesList, NUM_TYPES)) {
        cout << "error: invalid name" << endl;
        return true;
    }
    return false;
}

bool nameNameExists(string name) {
    GroupNode* curNode = gList->getHead();
    while (curNode) {
        if (curNode->getName() == name || curNode->getShapeList()->find(name)) {
            cout << "error: name " << name << " exists" << endl;
            return true;
        }
        curNode = curNode->getNext();
    }
    return false;
}

bool nameNotFound(string type, string name, bool node) {
    if (!node) {
        cout << "error: " << type << " " << name << " not found" << endl;
        return true;
    }
    return false;
}

void shape(stringstream & arguments) {
    string name, type;
    int x_loc, y_loc, x_sz, y_sz;
    arguments >> name >> type >> x_loc >> y_loc >> x_sz >> y_sz;

    if (invalidName(name)) return;
    if (nameNameExists(name)) return;

    ShapeNode* newShapeNode = new ShapeNode();
    Shape* newShape = new Shape(name, type, x_loc, y_loc, x_sz, y_sz);
    newShapeNode->setShape(newShape);

    gList->getHead()->getShapeList()->insert(newShapeNode);
    newShapeNode->print();
}

void group(stringstream & arguments) {
    string name;
    arguments >> name;

    if (invalidName(name)) return;
    if (nameNameExists(name)) return;

    GroupNode* newGroup = new GroupNode(name);
    gList->insert(newGroup);
    cout << name << ": group" << endl;
}

void move(stringstream & arguments) {
    string shapeName, groupName;
    arguments >> shapeName >> groupName;

    if (invalidName(shapeName) || invalidName(groupName)) return;

    // find shape
    GroupNode* srcGroupNode = nullptr;
    GroupNode* destGroupNode = nullptr;
    GroupNode* curGroupNode = gList->getHead();
    while (curGroupNode) {
        if (curGroupNode->getShapeList()->find(shapeName)) {
            srcGroupNode = curGroupNode;
        }
        if (curGroupNode->getName() == groupName) {
            destGroupNode = curGroupNode;
        }
        if (srcGroupNode && destGroupNode) break;
        curGroupNode = curGroupNode->getNext();
    }

    if (nameNotFound("shape", shapeName, (srcGroupNode))) return;
    if (nameNotFound("group", groupName, (destGroupNode))) return;

    ShapeNode* srcShapeNode = srcGroupNode->getShapeList()->remove(shapeName);
    destGroupNode->getShapeList()->insert(srcShapeNode);

    cout << "moved " << shapeName << " to " << groupName << endl;
}

void deleteN(stringstream & arguments) {
    string name;
    arguments >> name;

    if (invalidName(name)) return;

    // find shape
    GroupNode* curGroupNode = gList->getHead();
    while (curGroupNode) {
        ShapeNode* deleteShapeNode = curGroupNode->getShapeList()->remove(name);
        if (deleteShapeNode) {
            delete deleteShapeNode;
            cout << name << ": deleted" << endl;
            return;
        }

        if (curGroupNode->getName() == name) {
            GroupNode* deleteGroupNode = gList->remove(name);
            ShapeNode* moveHead = deleteGroupNode->getShapeList()->getHead();

            deleteGroupNode->getShapeList()->setHead(nullptr);
            delete deleteGroupNode;

            gList->getHead()->getShapeList()->insert(moveHead);
            cout << name << ": deleted" << endl;
            return;
        }
        curGroupNode = curGroupNode->getNext();
    }
    nameNotFound("shape", name, false);
}

void draw() {
    cout << "drawing:" << endl;
    gList->print();
}

int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the poo group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        command = "";
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here

        int commandIndex = -1;
        for (size_t i = 0; i < NUM_KEYWORDS; i++)
            if (command == keyWordsList[i])
                commandIndex = i;

        switch(commandIndex) {
            case 0:
                shape(lineStream);
                break;
            case 1:
                group(lineStream);
                break;
            case 2:
                move(lineStream);
                break;
            case 3:
                deleteN(lineStream);
                break;
            case 4:
                draw();
                break;
            default:
                cout << "Error: invalid command" << endl;
        }
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

