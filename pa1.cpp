#include <iostream>
#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"
#include <fstream>

using namespace std;

using namespace Clustering;

void randP(int num, int dim) {
    double ran = rand() % 10;
    fstream out("t.csv", std::ios::out);
    for (int i = 0; i < num; ++i) {
        out << ran;
        for (int j = 1; j < dim; ++j) {
            out << ",";
            ran = rand() % 10;
            out << ran;
        }
        out << endl;

    }
}

void load(Cluster &cc){
    fstream fs("t.csv", ios::in);
    if(fs.is_open()){
        fs>>cc;
    }
//    cout << cc;
}
int main(void) {
    const int k = 3;

    KMeans m(k);
    m.loadPoints("test.csv");
    m.start();
//    m.loadPoints();
//    Cluster cc;
//    load(cc);
//    cout <<cc;
//    double sum = cc.intraClusterDistance();
//    cout <<"SUM "<< sum;

//    randP(5,2);













//    cout << cluster;
//    cout << "Size: " << cluster.getM_size()<<endl;
//    cluster.computeCentroid();


//    double arr3[dim] = {3, 3};
//    double arr4[dim] = {4, 4};
//    double arr5[dim] = {5.7, 5};
//    double arr6[dim] = {6, 6}, arr7[dim] = {7, 2};

//    const int dim = 2;
//    double arr[dim] = {1, 1};
//    double arr2[dim] = {2, 2};
//    PointPtr p1 = new Point(dim, arr);
//    PointPtr p2 = new Point(dim, arr2);
//
//    *p1+=*p2;
//    cout <<*p1<<endl;

//    PointPtr p3 = new Point(dim, arr3);
//    PointPtr p4 = new Point(dim, arr4);
//    PointPtr p5 = new Point(dim, arr5);
//    PointPtr p6 = new Point(dim, arr6), p7 = new Point(dim, arr7);

//    double a[2] = {1, 1};
//    double b[2] = {3, 3};
//    Point p(2, a);
//    Point pp(2, b);


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


    return 0;

}

