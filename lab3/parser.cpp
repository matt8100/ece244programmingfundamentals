//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
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

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

bool ifInArray(string value, string array[], int start, int size) {
    for (int i = start; i < size; i++)
        if (array[i] == value)
            return true;
    return false;
}

void maxShapes(stringstream & arguments) {
    int size = 0;
    arguments >> size;

    // check if argument invalid
    if ((arguments.fail() && !arguments.eof()) || (arguments.rdbuf()->in_avail() && arguments.peek() != ' ' )) {
        cout << "Error: invalid argument" << endl;
        return;
    }

    // remove all trailing whitespace
    while (arguments.rdbuf()->in_avail() > 0){
        if (arguments.peek() != ' ')
            break;
        arguments.ignore();
    }

    // check if value invalid
    if (size < 0) {
        cout << "Error: invalid value" << endl;
        return;
    }

    // check if extraneous arguments exist
    if (arguments.rdbuf()->in_avail()) {
        cout << "Error: too many arguments" << endl;
        return;
    }

    // check if missing arguments
    if(arguments.fail() && arguments.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

    shapeCount = 0;
    // check if shapesArray already exists
    if (max_shapes) {
        for (int i = 0; i < max_shapes; i++) {
            delete shapesArray[i];
            shapesArray[i] = NULL;
        }    
        delete shapesArray;
        shapesArray = NULL;
    }

    max_shapes = size;

    shapesArray = new Shape*[max_shapes];
    for (int i = 0; i < max_shapes; i++)
        shapesArray[i] = NULL;
    cout << "New database: max shapes is " << max_shapes << endl;
}

void create(stringstream & arguments) {
    string name, type;
    int x_loc = 0, x_sz = 0, y_loc = 0, y_sz = 0;
    arguments >> name >> type >> x_loc >> y_loc >> x_sz >> y_sz;

    // check if argument invalid
    if ((arguments.fail() && !arguments.eof()) || (arguments.rdbuf()->in_avail() && arguments.peek() != ' ' )) {
        cout << "Error: invalid argument" << endl;
        return;
    }

    // remove all trailing whitespace
    while (arguments.rdbuf()->in_avail() > 0){
        if (arguments.peek() != ' ')
            break;
        arguments.ignore();
    }

    // check if name is reserved keyword
    if (ifInArray(name, keyWordsList, 0, NUM_KEYWORDS) || ifInArray(name, shapeTypesList, 0, NUM_TYPES)) {
        cout << "Error: invalid shape name" << endl;
        return;
    }

    // the index of the shape to be created
    int i = 0;
    // find empty spot in array
    for (; i < max_shapes; i++) {
        if (i == shapeCount)
            goto newShape;
        if (shapesArray[i]->getName() == name) {
            cout << "Error: shape " << name << " exists" << endl;
            return;
        }
    }

    if (name.empty())
        goto emptyName;
    // only runs if for loop ends without finding empty spot
    cout << "Error: shape array is full" << endl;
    return;

    newShape:
    // check if shape type is an allowed type
    if (!type.empty() && !ifInArray(type, shapeTypesList, 0, NUM_TYPES)) {
        cout << "Error: invalid shape type" << endl;
        return;
    }

    // check if value invalid
    if ((x_loc && x_loc < 0) || (y_loc && y_loc < 0) || (x_sz && x_sz < 0) || (y_sz && y_sz < 0) || (type == "circle" && (x_sz && y_sz) && (x_sz != y_sz))) {
        cout << "Error: invalid value" << endl;
        return;
    }

    // check if extraneous arguments exist
    if (arguments.rdbuf()->in_avail()) {
        cout << "Error: too many arguments" << endl;
        return;
    }

    emptyName:
    // check if missing arguments
    if(arguments.fail() && arguments.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

    shapesArray[i] = new Shape(name, type, x_loc, x_sz, y_loc, y_sz);
    shapeCount++;
    cout << "Created " << name << ": "
        << type << " "
        << x_loc << " "
        << y_loc << " "
        << x_sz << " "
        << y_sz << " "
        << endl;
}

void move(stringstream & arguments) {
    string name;
    int x_loc = 0, y_loc = 0;
    arguments >> name >> x_loc >> y_loc;

    // check if argument invalid
    if ((arguments.fail() && !arguments.eof()) || (arguments.rdbuf()->in_avail() && arguments.peek() != ' ' )) {
        cout << "Error: invalid argument" << endl;
        return;
    }

    // remove all trailing whitespace
    while (arguments.rdbuf()->in_avail() > 0){
        if (arguments.peek() != ' ')
            break;
        arguments.ignore();
    }
    
    // check if name is reserved keyword
    if (ifInArray(name, keyWordsList, 0, NUM_KEYWORDS) || ifInArray(name, shapeTypesList, 0, NUM_TYPES)) {
        cout << "Error: invalid shape name" << endl;
        return;
    }

    // the index of the shape to be moved
    int i = 0;
    // shape search
    for (; i < max_shapes; i++) {
        if (!shapesArray[i])
            break;
        if (shapesArray[i]->getName() == name) 
            goto shapeFound;
    }

    // only runs if for loop does not find shape
    if (name.empty())
        goto emptyName;
    cout << "Error: shape " << name << " not found" << endl;
    return;

    shapeFound:
    // check if value invalid
    if ((x_loc && x_loc < 0) || (y_loc && y_loc < 0)) {
        cout << "Error: invalid value" << endl;
        return;
    }

    // check if extraneous arguments exist
    if (arguments.rdbuf()->in_avail()) {
        cout << "Error: too many arguments" << endl;
        return;
    }

    emptyName:
    // check if missing arguments
    if(arguments.fail() && arguments.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

    shapesArray[i]->setXlocation(x_loc);
    shapesArray[i]->setYlocation(y_loc);

    cout << "Moved " << name << " to " << x_loc << " " << y_loc << endl;
}

void rotate(stringstream & arguments) {
    string name;
    int angle = 0;
    arguments >> name >> angle;

    // check if argument invalid
    if ((arguments.fail() && !arguments.eof()) || (arguments.rdbuf()->in_avail() && arguments.peek() != ' ' )) {
        cout << "Error: invalid argument" << endl;
        return;
    }

    // remove all trailing whitespace
    while (arguments.rdbuf()->in_avail() > 0){
        if (arguments.peek() != ' ')
            break;
        arguments.ignore();
    }

    // check if name is reserved keyword
    if (ifInArray(name, keyWordsList, 0, NUM_KEYWORDS) || ifInArray(name, shapeTypesList, 0, NUM_TYPES)) {
        cout << "Error: invalid shape name" << endl;
        return;
    }

    // the index of the shape to be rotated
    int i = 0;
    // shape search
    for (; i < max_shapes; i++) {
        if (!shapesArray[i])
            break;
        if (shapesArray[i]->getName() == name) 
            goto shapeFound;
    }

    // only runs if for loop does not find shape
    if (name.empty())
        goto emptyName;
    cout << "Error: shape " << name << " not found" << endl;
    return;

    shapeFound:
    // check if value invalid
    if ((angle && angle < 0) || (angle && angle > 360)) {
        cout << "Error: invalid value" << endl;
        return;
    }

    // check if extraneous arguments exist
    if (arguments.rdbuf()->in_avail()) {
        cout << "Error: too many arguments" << endl;
        return;
    }

    emptyName:
    // check if missing arguments
    if(arguments.fail() && arguments.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

    shapesArray[i]->setRotate(angle);
    cout << "Rotated " << name << " by " << angle << " degrees" << endl;
}

void draw(stringstream & arguments) {
    string name;
    arguments >> name;

    // check if argument invalid
    if ((arguments.fail() && !arguments.eof()) || (arguments.rdbuf()->in_avail() && arguments.peek() != ' ' )) {
        cout << "Error: invalid argument" << endl;
        return;
    }

    // remove all trailing whitespace
    while (arguments.rdbuf()->in_avail() > 0){
        if (arguments.peek() != ' ')
            break;
        arguments.ignore();
    }

    // the index of the shape to be drawn
    int i = 0;

    if (ifInArray(name, keyWordsList, 1, NUM_KEYWORDS || ifInArray(name, shapeTypesList, 0, NUM_TYPES))) {
        cout << "Error: invalid shape name" << endl;
        return;
    }

    if (name == "all")
        goto shapeFound;

    // shape search
    for (; i < max_shapes; i++) {
        if (!shapesArray[i])
            break;
        if (shapesArray[i]->getName() == name) 
            goto shapeFound;
    }

    // only runs if for loop does not find shape
    if (name.empty())
        goto emptyName;
    cout << "Error: shape " << name << " not found" << endl;
    return;

    shapeFound:
    // check if extraneous arguments exist
    if (arguments.rdbuf()->in_avail()) {
        cout << "Error: too many arguments" << endl;
        return;
    }

    emptyName:
    // check if missing arguments
    if(arguments.fail() && arguments.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

    if (name == "all") {
        cout << "Drew all shapes" << endl;
        for (int i = 0; i < shapeCount; i++)
            if (shapesArray[i])
                shapesArray[i]->draw();
    }
    else {
        cout << "Drew ";
        shapesArray[i]->draw();
    }
}

void deleteShape(stringstream & arguments) {
    string name;
    arguments >> name;

    // check if argument invalid
    if ((arguments.fail() && !arguments.eof()) || (arguments.rdbuf()->in_avail() && arguments.peek() != ' ' )) {
        cout << "Error: invalid argument" << endl;
        return;
    }

    // remove all trailing whitespace
    while (arguments.rdbuf()->in_avail() > 0){
        if (arguments.peek() != ' ')
            break;
        arguments.ignore();
    }

    // the index of the shape to be drawn
    int i = 0;

    if (ifInArray(name, keyWordsList, 1, NUM_KEYWORDS || ifInArray(name, shapeTypesList, 0, NUM_TYPES))) {
        cout << "Error: invalid shape name" << endl;
        return;
    }

    if (name == "all")
        goto shapeFound;

    // shape search
    for (; i < max_shapes; i++) {
        if (!shapesArray[i])
            break;
        if (shapesArray[i]->getName() == name) 
            goto shapeFound;
    }

    // only runs if for loop does not find shape
    if (name.empty())
        goto emptyName;
    cout << "Error: shape " << name << " not found" << endl;
    return;

    shapeFound:
    // check if extraneous arguments exist
    if (arguments.rdbuf()->in_avail()) {
        cout << "Error: too many arguments" << endl;
        return;
    }

    emptyName:
    // check if missing arguments
    if(arguments.fail() && arguments.eof()) {
        cout << "Error: too few arguments" << endl;
        return;
    }

    if (name == "all") {
        for (int i = 0; i < shapeCount; i++) {
            delete shapesArray[i];
            shapesArray[i] = NULL;
        }
        shapeCount = 0;
        cout << "Deleted: all shapes" << endl;
    } else {
        delete shapesArray[i];
        shapesArray[i] = NULL;
        cout << "Deleted shape " << name << endl;
    }
}

int main() {

    string line;
    string command;
    max_shapes = 0;
    
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

        int commandIndex = 0;
        for (size_t i = 0; i < NUM_KEYWORDS; i++)
            if (command == keyWordsList[i])
                commandIndex = i;
        
        switch(commandIndex) {
            case 1:
                maxShapes(lineStream);
                break;
            case 2:
                create(lineStream);
                break;
            case 3:
                move(lineStream);
                break;
            case 4:
                rotate(lineStream);
                break;
            case 5:
                draw(lineStream);
                break;
            case 6:
                deleteShape(lineStream);
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

