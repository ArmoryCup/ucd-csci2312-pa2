#include <iostream>
//#include "Point.h"
#include "Cluster.h"

using namespace std;
using namespace Clustering;


int main(void) {


    const int dim = 2;
    double arr[dim] = {1, 1};
    double arr2[dim] = {2, 2};
    double arr3[dim] = {3, 3};
    double arr4[dim] = {4, 4};

    Point p1(dim, arr);
    Point p2(dim, arr2);
    Point p3(dim, arr3), p4(dim, arr4);
    Cluster c1;
    c1.add(&p1);
    c1.add(&p2);
    Cluster c2 ;

    c2.add(&p3);
    c2.add(&p4);
    Cluster c22 = c1+c1;
    cout << "c22\n"<<c22;
//    Cluster c3= c1+c2;
//    cout << c3;
//    cout <<"\nC3";
//    Cluster c3(c2);
//    cout <<c3;
//
//    cout <<"\nC4";
//    Cluster c4;
//    c4 = c1;
    return 0;

}

