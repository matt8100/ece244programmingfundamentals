// Main program 

#include <iostream>

using namespace std;

#include "squared.h"
#include "squareRoot.h"

int main () {

    int myNumber, myNumberSquared; 
    float myNumberSquareRoot;

    cout << "Please enter a number, pretty please: ";
    cin >> myNumber;

    myNumberSquared = squared (myNumber);
    myNumberSquareRoot = squareRoot (myNumber);


    cout << "The square of " << myNumber << " is: "
         << myNumberSquared << endl;

    cout << "The square root of " << myNumber << " is: "
         << myNumberSquareRoot << endl << endl;

    return (0);
}

