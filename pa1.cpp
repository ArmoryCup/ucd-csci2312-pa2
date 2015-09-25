#include <iostream>
//#include "Point.h"
#include "Cluster.h"

using namespace std;
using namespace Clustering;


int main(void) {


    const int dim = 4;
    double arr[dim] = {1, 1, 1, 1};
    double arr2[dim] = {2, 2, 2, 2};
    double arr3[dim] = {3, 3, 3, 3};

    Point p1(dim, arr);
    Point p2(dim, arr2);
    Point p3(dim, arr3), p4(p1);
    Cluster c1;
    c1.add(&p1);
    c1.add(&p2);
    c1.add(&p3);


    cout <<"\nC2";
    Cluster c2(c1);

//    cout <<"\nC3";
//    Cluster c3(c2);
    return 0;

}

