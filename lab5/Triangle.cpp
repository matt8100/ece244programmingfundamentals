//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

// Constructor
Triangle::Triangle(string n, float xcent, float ycent, float vx1, float vy1, float vx2, float vy2, float vx3, float vy3): Shape(n, xcent, ycent) {
  x1 = vx1;
  y1 = vy1;
  x2 = vx2;
  y2 = vy2;
  x3 = vx3;
  y3 = vy3;
}

// Destructor
Triangle::~Triangle() {

}

// Accessor
float Triangle::getX1() const {
  return x1;
}
float Triangle::getY1() const {
  return y1;
}
float Triangle::getX2() const {
  return x2;
}
float Triangle::getY2() const {
  return y2;
}
float Triangle::getX3() const {
  return x3;
}
float Triangle::getY3() const {
  return y3;
}

// Mutator
void Triangle::setX1(float n) {
  x1 = n;
}
void Triangle::setY1(float n) {
  y1 = n;
}
void Triangle::setX2(float n) {
  x2 = n;
}
void Triangle::setY2(float n) {
  y2 = n;
}
void Triangle::setX3(float n) {
  x3 = n;
}
void Triangle::setY3(float n) {
  y3 = n;
}

// Utility methods
void Triangle::draw() const {
  // Set floating point printing to fixed point with 2 decimals
  cout << std::fixed;
  cout << std::setprecision(2);
  
  // Print the information
  cout << "triangle: " << name << " "
        << x_centre << " " << y_centre
        << " " << x1 << " " << y1
        << " " << x2 << " " << y2
        << " " << x3 << " " << y3
        << " " << computeArea()
        << endl;
}

float Triangle::computeArea() const {
  return 0.5*abs((x1-x3)*(y2-y1) - (x1-x2)*(y3-y1));
}

Shape* Triangle::clone() const {
  return (new Triangle(*this));
}