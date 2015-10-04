#include <iostream>
//#include "Point.h"
#include "Cluster.h"

using namespace std;
using namespace Clustering;

int v(int &v){
    int *a = new int(v);
    return *a;
}

int main(void) {


    const int dim = 2;
    double arr[dim] = {1, 1};
    double arr2[dim] = {2, 2};
    double arr3[dim] = {3, 3};
    double arr4[dim] = {4, 4};
    double arr5[dim] = {5, 5};
    double arr6[dim] = {6, 6}, arr7[dim] = {7,7};
    PointPtr p1 = new Point(dim, arr);
    PointPtr p2 = new Point(dim, arr2);
    PointPtr p3 = new Point(dim, arr3);
    PointPtr p4 = new Point(dim, arr4);
    PointPtr p5 = new Point(dim, arr5);
    PointPtr p6 = new Point(dim, arr6), p7 = new Point(dim, arr7);;

    Cluster c1;
    c1.add(p6);
    c1.add(p2);
    c1.add(p1);
cout << c1;

    Cluster c2;
    c2.add(p5);
    c2.add(p2);
    c2.add(p6);

    double a[dim] ={1,1};
    double b[dim] = {2,2};
    Point p(dim, a);
    Point pp(dim, b);

//    Cluster w;
//    w=c2-=c1;
//    cout <<"Size: "<<w.getM_size() <<"\nC2" << endl<< w;



    return 0;

}

