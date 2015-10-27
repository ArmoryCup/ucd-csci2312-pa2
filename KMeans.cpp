//
// Created by kamil on 10/13/15.
//

#include<iostream>
#include <fstream>
#include <cstdlib>
#include "KMeans.h"
#include "Cluster.h"
<<<<<<< HEAD
#include "Point.h"
=======
>>>>>>> origin/master

using namespace std;
namespace Clustering {

<<<<<<< HEAD

    KMeans::KMeans(int k) {
        __k = k;
        loadPoints();

        const int PICKPOINT = 6;

        c = new Cluster[k];
        int numbOfPoints = point_space.getM_size();
        int pointDim = point_space.getPointDimension();
        Point *cents[numbOfPoints];
        Point p[numbOfPoints];
        int i = 0;
        for (LNodePtr curr = point_space.getPoints(); curr != nullptr; curr = curr->next) {
            cents[i] = curr->p;
            p[i] = *curr->p;
//            cout << "cents " << *cents[i] << endl;
            i++;
        }

        Cluster centroids[k];

        // pick random points for centroids
        for (int i = 0; i < k; ++i) {
            c[i].setPointDimension(pointDim);
            c[i].pickPoints(PICKPOINT, cents);
            cout << "getCentroid " << c[i].get__centroid() << endl;
        }

        Cluster emptyCluster;
        double score, scoreDiff;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;


        double max = 1000;
        double min = max;
        int cluster;
        double distance;
        int numbOfClusters = __k;
        /**
        *
        * loop until scoreDiff < SCORE_DIFF_THRESHOLD
   loop through all clusters
       loop through all points
           find the min distance(point, centroid)
           if centroid not of current cluster
               perform move(point, current, other)
   loop through all clusters
       if centroid invalid
           compute and set valid to true
   compute new clustering score
   compute absolute difference and set scoreDiff
        * */
        int point = 0;
        for (int index = 0; index < numbOfClusters; index++) {
            min = 100;
            for (int j = 0; j < numbOfPoints; j++) {

                distance = cents[j]->distanceTo(c[index].get__centroid());
                if (*cents[j] != c[index].get__centroid()) {
                cout << "cents["<<j<<"] : " << *cents[j]<<endl;
                cout << "c["<<index<<"].Centroid : " << c[index].get__centroid()<<endl;
                cout <<"Distance( c["<<index<<"], cents["<<j<<"] ) is " << distance<<endl;
                if (distance < min) {
                        min = distance;
                        point = j;
                        cout <<"MIN "<<min<<endl;
                    }

                }
            }
            PointPtr p = cents[point];
            Cluster::Move m(p, &point_space, &c[index]);
            m.perform();
            if (c[index].isCentroidValid() == false){
                c[index].computeCentroid();
                c[index].setCentroidValid(true);
            }

        }
//        movePonts(*cents);
        displayResult();
        cout << "======================\n";



//        c[cluster].computeCentroid();
//        for (int n = 0; n < numbOfClusters; ++n) {
//            cout<<"PP "<< c[n].getPointDimension()<<endl;
//            if (c[n].isCentroidValid() == false) {
//                c[n].computeCentroid();
//            }
//        }
//        for (int j = 0; j < numbOfPoints; ++j) {
//            min = max;
//            for (int l = 0; l < numbOfClusters; ++l) {
//                distance = cents[j]->distanceTo(c[l].get__centroid());
//                if (distance < min) {
//                    min = distance;
//                    cluster = l;
//                }
//            }
//            Cluster::Move m(cents[j], &point_space, &c[cluster]);
//            m.perform();
//        }

    }

    void KMeans::loadPoints() {
        std::fstream csv("test.csv", std::ios::in);
        if (csv.is_open()) {
            csv >> point_space;
        }
//        cout << point_space << endl;
        csv.close();
    }

    void KMeans::displayResult() {
        int numbOfClusters = __k;
        if (c[0].getPoints() == nullptr) {
            cout << "Error! The function displayResult can not display anything. Clusters do not have points\n";
        }
        else {
            for (int n = 0; n < numbOfClusters; ++n) {

                cout << "\nc[" << n << "] has \n";
                cout << c[n];
                cout << "centroid: " << c[n].get__centroid() << endl;
            }
        }
    }
}


void Clustering::KMeans::movePonts(PointPtr cents) {
    Cluster emptyCluster;
    double score, scoreDiff;
    scoreDiff = SCORE_DIFF_THRESHOLD + 1;


    double max = 1000;
    double min = max;
    int cluster;
    double distance;
    int numbOfClusters = __k;
    /**
    *
    * loop until scoreDiff < SCORE_DIFF_THRESHOLD
loop through all clusters
   loop through all points
       find the min distance(point, centroid)
       if centroid not of current cluster
           perform move(point, current, other)
loop through all clusters
   if centroid invalid
       compute and set valid to true
compute new clustering score
compute absolute difference and set scoreDiff
    * */
    int point = 0;
    int numbOfPoints = __k;
    for (int index = 0; index < numbOfClusters; index++) {
        min = 100;
        for (int j = 0; j < numbOfPoints; j++) {
            distance = cents[j].distanceTo(c[index].get__centroid());
//            if (cents[j] != c[index].get__centroid()) {
                cout << "cents["<<j<<"] : " << cents[j]<<endl;
                cout << "c["<<index<<"].Centroid : " << c[index].get__centroid()<<endl;
                cout <<"Distance( c["<<index<<"], cents["<<j<<"] ) is " << distance<<endl;
                if (distance < min) {
                    min = distance;
                    point = j;
                    cout <<"MIN "<<min<<endl;

            }

        }
        PointPtr p = &cents[point];
        Cluster::Move m(p, &point_space, &c[index]);
        m.perform();
        if (c[index].isCentroidValid() == false){
            c[index].computeCentroid();
            c[index].setCentroidValid(true);
        }

    }
//    displayResult();
    cout << "======================\n";
}
//    void KMeans::movePonts(Point* cents) {
//
//        Cluster emptyCluster;
//        double score, scoreDiff;
//        scoreDiff = SCORE_DIFF_THRESHOLD + 1;
//
//
//        double max = 1000;
//        double min = max;
//        int cluster;
//        double distance;
//        int numbOfPoints = point_space.getM_size();
//        int numbOfClusters = __k;
//        PointPtr ptr;
//        for (int j = 0; j < numbOfPoints; ++j) {
//            min = max;
//            for (int l = 0; l < numbOfClusters; ++l) {
//                 ptr = &cents[j];
//                distance = cents[j].distanceTo(c[l].get__centroid());
//                if (distance < min) {
//                    min = distance;
//                    cluster = l;
//                }
//            }
//            Cluster::Move m(&ptr, &point_space, &c[cluster]);
//            m.perform();
//        }
//    }
=======
    KMeans::KMeans(int k) {
        PointPtr cents[5];
        Cluster c[k];
        fstream csv("CSV.txt", std::ios::in);
        if (csv.is_open()) {
            csv >> point_space;
        }
        csv.close();

        LNodePtr n = point_space.getPoints();
        int i = 0;
        for (LNodePtr curr = n; curr != nullptr; curr = curr->next) {
            cents[i] = curr->p;
            i++;
        }
        cout << point_space;
        int numbOfPoints = point_space.getM_size();

        // pick random points from point_space and set them as initial centroids for the k clusters
        for (int j = 0; j < k; ++j) {
            c[j].pickPoints(numbOfPoints, cents);
        }


        // create k-1 cluster empty cluster
        Cluster emptyCluster;
        double score, scoreDiff;

        bool flag = false;
        int s = 0;
        while(!flag){

            double min = c[s].get__centroid().distanceTo(*cents[s]);
            double max = c[s+1].get__centroid().distanceTo(*cents[s]);
            cout << min << " " << max;

            s++;
            flag = true;
        }

    }



}
>>>>>>> origin/master
