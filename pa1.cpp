#include <iostream>
#include <fstream>
#include <sstream>
#include "Cluster.h"

using namespace std;
using namespace Clustering;


int main(void) {

    std::string s;
    double d[5];
    fstream in;
    int i=0;
    double v;
    in.open("CSV.txt", ios::in);
    Point p(5);
    if(in.fail()){
        cout << "Error";
    }else{
        while(getline(in, s)){
            cout << s << endl;
            v = (double)s;
            cout << "Value: "<<v<<endl;
            }
        }

in.close();



    const int dim = 2;
    double arr[dim] = {1, 1};
    double arr2[dim] = {2, 2};
    double arr3[dim] = {3, 3};
    double arr4[dim] = {4, 4};
    double arr5[dim] = {5.7, 5};
    double arr6[dim] = {6, 6}, arr7[dim] = {7, 2};
    PointPtr p1 = new Point(dim, arr);
    PointPtr p2 = new Point(dim, arr2);
    PointPtr p3 = new Point(dim, arr3);
    PointPtr p4 = new Point(dim, arr4);
    PointPtr p5 = new Point(dim, arr5);
    PointPtr p6 = new Point(dim, arr6), p7 = new Point(dim, arr7);



    int newSize = 3;
//    PointPtr z1 = new Point(newSize, generateRand(newSize));
//    PointPtr z2 = new Point(newSize, generateRand(newSize));
//    PointPtr z3 = new Point(newSize, generateRand(newSize));
//    PointPtr z4 = new Point(newSize, generateRand(newSize));
//    PointPtr z5 = new Point(newSize, generateRand(newSize));
//    PointPtr z6 = new Point(newSize, generateRand(newSize));
//    PointPtr z7 = new Point(newSize, generateRand(newSize));
//    PointPtr z8 = new Point(newSize, generateRand(newSize));
//    c2.add(z5);
//    c2.add(z1);
//    c2.add(z6);
//    c2.add(z7);
//    c2.add(z2);
//    c2.add(z5);
//    c2.add(z1);

//    double a[dim] = {1, 1};
//    double b[dim] = {3, 3};
//    Point p(dim, a);
//    Point pp(dim, b);
//
//    Cluster c1;
//    c1.add(p1);
//    c1.add(p3);
//    c1.add(p4);
//
//    Cluster c2;
//    c2.add(p4);
//    c2.add(p5);
//    c2.add(p7);
//    cout << "C1: " << c1;
//    cout << "C2: " << c2;
//    cout << "----------------------------------\n";
//
////    PointPtr ptr = c1.remove(p5);
////    c2.add(c1.remove(p5));                                    ERROR!
//    cout << "C2: " << c2;
//    cout << "----------------------------------\n";
//
//    Cluster c3=c1+c2;
//     ;
//    cout << "\t\t\t\t\t\t\tc3 = c1+c2:\n";
//    cout <<c3;
//    cout << "----------------------------------\n";
//    cout << "\t\t\t\t\t\t\tc3 = c1-c2\n";
//    c3 =c2-c1;
//    c3 = (c1 + c2) - (c1 - c2) - (c2 - c1);
//    cout <<c3;
//    cout << "----------------------------------\n";
//    cout << "\t\t\t\t\t\t\t c1==c2\n";
//    Cluster c4(c1);
//    if(c1==c4)
//        cout<<"True\n";
//    cout << "----------------------------------\n";
//    cout << "\t\t\t\t\t\t\t c1+=c2\n";
//    c2+=c1;
//    cout<<"C1: " << c1<<endl;
//    cout << "----------------------------------\n";
//    cout << "\t\t\t\t\t\t\t c1+=pp\n";
//    c1+=pp;
//    cout<<"C1: " << c1<<endl;
//    cout << "----------------------------------\n";
//
//    cout << "Point " << p << " " << pp << endl;
//
//    cout << "BEFORE \n" << c1;
//    c1 += pp;
//    c1 += p;
//    cout << "Added: \n" << c1;
//    c1-=p;
//    c1 -= pp;
//    cout << "\nAfter \n" << c1;
//    cout << "----------------------------------\n";
//
//
    return 0;

}

