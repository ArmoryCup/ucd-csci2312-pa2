#include <iostream>
#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"
#include <fstream>
//#include "DimensionalityMismatchEx.h"
//#include "OutOfBoundEx.h"
//#include "RemoveFromEmptyEx.h"
#include "Exceptions.h"

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

void load(Cluster &cc) {
    fstream fs("test.csv", ios::in);
    if (fs.is_open()) {
        fs >> cc;
    }
//    cout << cc;
}

void print(Cluster &c) {
    cout << "size: " << c.getM_size() << "\n";
    cout << c;
}

void s() {
    const int k = 2;
    KMeans m(k, 2);
    m.loadPoints("tt.csv");
    m.start();
    m.writeToFile("output.csv");
}

int main(void) {

    s();

//    randP(10, 2);


//    std::vector<Cluster> point_space;
//
//    fstream fs("t.csv", ios::in);
//    if (fs.is_open()) {
//        Cluster cc;
//        fs >> cc;
//        point_space.push_back(cc);
//    }
//    cout << point_space[0];









//    cout << cluster;
//    cout << "Size: " << cluster.getM_size()<<endl;
//    cluster.computeCentroid();

    const int dim = 2;
    double arr1[dim] = {1, 1};
    double arr2[dim] = {2, 2};
    double arr3[dim] = {3, 3};
    double arr4[dim] = {4, 4};
    double arr5[dim] = {5, 5};
//
    try {


        Point p1(dim, arr1);
        Point p2(dim, arr2);
        Point p3(dim, arr3);
        Point p4(dim, arr4);
        Point p5(dim, arr5);

        Cluster c1;
        c1.add(p1);
        c1.add(p2);
        c1.add(p3);
        c1.add(p4);
//        Cluster::Move m(p1,c1,c1);
//        cout << "Before: \n"<<c1;
//
//        m.perform();
//        cout << "After\n"<<c1;

//        Cluster c2;
//        c2.add(p1);
//        c2.add(p2);
//        Cluster c3;
//        c3.add(p4);
//        c3.add(p5);
//        cout << c3;

//        std::vector<Cluster> vec;
//        //idgen 4
//        vec.push_back(c1); // 5
//        vec.push_back(c2); //6        Cluster::idGenerator--;
//        vec.push_back(c3); //7
//        vec.pop_back();


//        for (int i = 0; i < vec.size(); ++i) {
//            cout << vec[i];
//            cout << endl;
//        }


//        cout << c3;


//        Cluster cc = c1;
////        cc = cc - p5;
//        print(cc);

//        cout << c2;
//        c1.setCentroid(p2);
//        cout << c1;
//        cout << "Centr: " << c1.get__centroid() << endl;

//        cout << "-----------\n"<<c1;
//        cout << "-----------\n"<<c1;

//        c1.computeCentroid();

    } catch (DimensionalityMismatchEx &er) {
        cerr << "Error: Dimensionality mismatch " << er << endl;
    } catch (OutOfBoundEx &outBound) {
        cerr << "Error: Out of Bound exc - n " << outBound << endl;
    } catch (RemoveFromEmptyEx &r) {
        cerr << "Error: " << r << endl;
    }
//    Point pp1(3, arr);
//
//
//

//
//

//
//
//    Cluster c1;
//    c1.add(p1);
//    c1.add(p3);
//    c1.add(p4);
//    Cluster c2;
//    c2.add(p4);
//    c2.add(p3);
//
//    double dist = interClusterDistance(c1,c2);
//    cout << dist;
//    Cluster c = c1;
//    cout << c2;
//    cout << "C1:\n" << c1;
//    cout << "C2:\n" << c2;
//    cout << "----------------------------------\n";
//
////    PointPtr ptr = c1.remove(p5);
////    c2.add(c1.remove(p5));                                    ERROR!
//    cout << "C2: " << c2;
//    cout << "----------------------------------\n";
//
//    Cluster c3=c1+c2;
//    cout << "\t\t\t\t\t\t\tc3 = c1+c2:\n";
//    cout <<c3;
//    cout << "----------------------------------\n";
//    cout << "C1:\n" << c1;
//    cout << "C2:\n" << c2;
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

