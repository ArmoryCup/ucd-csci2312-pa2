#include <iostream>
#include "Point.h"

using namespace std;


int main(void) {

    const int dim = 4;
    double arr[dim] = {3, 2, 3, 4}, arr2[dim] = {1, 1, 1, 1}, arr3[dim] = {1, 1, 2, 2};


    Point p1(dim, arr3);
    cout << "p1: " << p1 << endl;
    Point p2(dim, arr), p3(dim, arr2);
    cout << "p2: " << p2 << endl << endl;

    cout << p1 << "/" << 2 << " = " << (p1 *= 2) << endl;
    return 0;


}
