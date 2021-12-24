//
//  Triangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
using namespace std;

#include "Shape.h"

// This class implements the triangle Shape objects.
// ECE244 Student: Write the definition of the class here.
class Triangle : Shape {
private:
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
public:
    // Constructor
    Triangle (string n, float xcent, float ycent, float vx1, float vy1, float vx2, float vy2, float vx3, float vy3);
    
    // Destructor
    virtual ~Triangle();
    
    // Accessor
    float getX1() const;
    float getY1() const;
    float getX2() const;
    float getY2() const;
    float getX3() const;
    float getY3() const;
    // Mutator
    void setY1(float n);
    void setX2(float n);
    void setY2(float n);
    void setX3(float n);
    void setY3(float n);
    void setX1(float n);
    
    // Utility methods
    virtual void draw() const;
    
    virtual float computeArea() const;
    
    virtual Shape* clone() const;
};

#endif /* Triangle_h */


