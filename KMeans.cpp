//
// Created by kamil on 10/13/15.
//

#include<iostream>
#include <fstream>
#include <cstdlib>
#include "KMeans.h"
#include "Cluster.h"
#include "Point.h"

using namespace std;
namespace Clustering {


    KMeans::KMeans(int k) {
        __k = k;
        point_space = new Cluster[k];
    }

    void KMeans::loadPoints(string textFile) {
        std::fstream csv(textFile.c_str(), std::ios::in);
        if (csv.is_open()) {
            csv >> point_space[0];
        }
        csv.close();
    }

    void KMeans::displayResult() {
        if (point_space[0].getPoints() == nullptr) {
            cout << "Error! The function displayResult can not display anything. Clusters do not have points\n";
        }
        else {
            for (int n = 0; n < __k; ++n) {

                cout << "\nc[" << n << "] has \n";
                cout << point_space[n];
                cout << "centroid: " << point_space[n].get__centroid() << endl;
            }

        }
    }

    // temporary function
    void KMeans::testPoint(PointPtr *point) {
        int numbPoints = point_space[0].getM_size();
        for (int l = 0; l < numbPoints; l++)
            cout << "point[" << l << "] " << *point[l] << endl;
    }

    void Clustering::KMeans::movePonts(PointPtr *point) {
        double score, scoreDiff, distance = 0, min = SCORE_DIFF_THRESHOLD;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;
        double r = 0;

        int clusterEl, pointEl, numbOfPoints = point_space[0].getM_size();
        PointPtr currentPoint = nullptr;
        int numbOfClusters = __k;
//        while (scoreDiff > SCORE_DIFF_THRESHOLD) {
            for (int j = 1; j < numbOfClusters; ++j) {
                min = SCORE_DIFF_THRESHOLD;
//            cout <<"c["<<j<<"].centroid " << point_space[j].get__centroid() << endl;
                for (int l = 0; l < numbOfPoints; ++l) {

//                cout << "point["<<l<<"] "<< *point[l] << endl;
                    distance = point[l]->distanceTo(point_space[j].get__centroid());
                    cout << "point[" << l << "] --> " << *point[l] << "   dist(c[" << j << "]: " << distance << endl;


                    if (distance < min) {
                        min = distance;
                        currentPoint = point[l];
                        pointEl = l;
                        clusterEl = j;
                    }
                    if(min == 0)
                        break;
                }
                cout << "\nc[" << j << "] nMin " << min << " <-- " << *point[pointEl] << endl;
                PointPtr ptr = point[pointEl];
                if (point_space[j].get__centroid() != *ptr) {
                    Cluster::Move move(ptr, &point_space[0], &point_space[clusterEl]);
                    move.perform();
                }

//                cout << "AAAAAAc[0] \n" << point_space[0] << endl;
//                cout << "AAAAAAcc[1] \n" << point_space[1] << endl;
//                cout << "AAAAAAcc[2] \n" << point_space[2] << endl;


            }

            // compute and set centroid to valid
            // if centroid is invalid
            for (int i = 0; i < numbOfClusters; ++i) {
                if (!point_space[i].isCentroidValid()) {
                    point_space[i].computeCentroid();
                }
            }
                displayResult();
//            score = computeClusteringScore();
//            cout << "Score: " << score << endl;
//        }
    }

    double KMeans::computeClusteringScore() {
        int numOfPoints = point_space[0].getM_size();
        double d_In, d_Out;
        int p_In, p_Out;
        double betaCV;

        int sum = 0;

        cout <<"\nBegin\n";

        // calculate the sum of the inter-cluster distances
        // and the number of distinct (intra-) cluster edges
        for (int i = 0; i < __k; ++i) {
            cout << "c[" << i << "]: " <<endl;
            d_In += point_space[i].intraClusterDistance();
            p_In += point_space[i].getClusterEdges();
        }

        // calculate the sum of the inter-cluster distances
        // and  the number of the distinct inter-cluster edge
        for (int i = 0; i < __k; ++i) {
            for (int j = 1; j < --__k; ++j) {
                d_Out += interClusterDistance(point_space[i], point_space[j]);
                p_Out += interClusterEdges(point_space[i], point_space[j]);
            }
        }

        betaCV = (d_In / p_In) / (d_Out / p_Out);

        cout << "\nEnd\n";
        return betaCV;
    }

    void KMeans::start(){
        int numbOfPoints = point_space[0].getM_size();
        PointPtr initCentroid[__k];         // initial centroid for k cluster

        // store all points to the pointer points from point_space
        PointPtr points[numbOfPoints];
        int i = 0;
        for (LNodePtr curr = point_space[0].getPoints(); curr != nullptr; curr = curr->next) {
            points[i] = curr->p;
//            cout << (i+1) << ") points " << *points[i] << endl;
            i++;
        }

        cout << "\nAAAA\n";
        // set initial centroids for k clusters
        point_space->pickPoints(__k, initCentroid);
        int dim = point_space[0].getPointDimension();
        for (int j = 0; j < __k; ++j) {
//            cout << "Centroid " << *initCentroid[j] << endl;
            point_space[j].setCentroid((*initCentroid[j]));
            point_space[j].setPointDimension(dim);
            cout << "c[" << j << "].centroid: " << point_space[j].get__centroid() << endl;
        }

        cout << "****************************************\n";

//        for (int l = 0; l < numbOfPoints; ++l) {
//            cout<< *points[l] << endl;
//        }
//            testPoint(points);
        movePonts(points);
        cout << "****************************************\n";

        cout << "BBBB";
    }
}