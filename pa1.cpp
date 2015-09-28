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
    Point ww(dim,arr);
    PointPtr p1 = new Point(dim, arr);
    PointPtr p2 = new Point(dim, arr2);
    PointPtr p3 = new Point(dim, arr3), p4 = new Point(dim, arr4);

    Cluster c1;
    c1.add(p1);
    c1.add(p2);
//    c1.add(p3);
//    c1.add(p4);
//    cout << endl << "c1\n" << c1;
//    c1.add(c1.remove(p4));
//    cout << endl << "c1\n" << c1;

    Cluster c2;
    c2.add(p3);
    c2.add(p4);
//    c2.add(c1.remove(p2));
//    cout << "c2\n" << c2;
//    cout<<c2;

    Cluster c22 = c1 + c2;
    cout << "c22\n" << c22;

/*    Cluster c22 = c1 + c2;
    c22 = c1 + c2;                      // Error when assigning c22
    cout << "c22\n" << c22;*/

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

