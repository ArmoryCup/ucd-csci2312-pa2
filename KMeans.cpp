//
// Created by kamil on 10/13/15.
//

#include<iostream>
#include <fstream>
#include <cmath>
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

    void KMeans::firstMove(PointPtr *point) {
        const double MIN = 100;
        int min = MIN;
        double distance = 0;
        int clusterEl, numbOfPoints = point_space[0].getM_size();
        int numbOfClusters = __k;

//        cout << "\t\t\t\t\tFIRST_MAIN LOOP\n";

        PointPtr tmp = NULL;
        int cl = 0;
        for (int l = 0; l < numbOfPoints; ++l) {
            min = MIN;
            for (int i = 0; i < numbOfClusters; ++i) {

                distance = point[l]->distanceTo(point_space[i].get__centroid());
//                    cout << "point[" << l << "] --> " << *point[l] << "   dist(c[" << i << "]: " << distance <<
//                    endl;
                if (distance < min) {
                    min = distance;
                    clusterEl = i;
                }
            }

            for (int j = 0; j < numbOfClusters; ++j) {
                if (*point[l] == point_space[j].get__centroid()) {
                    tmp = point[l];
                    cl = j;
                }
            }

//                cout << "\nc[" << clusterEl << "] nMin " << min << " <-- " << *point[l] << endl;
//                cout << "point_space[" << clusterEl << "].centr <-- " << point_space[clusterEl].get__centroid() <<
//                endl << endl;
            if (point_space[cl].get__centroid() != *point[l] &&
                point_space[cl].get__centroid() != point_space[0].get__centroid()) {
                Cluster::Move move(point[l], &point_space[0], &point_space[clusterEl]);
                move.perform();
//                    cout << "point is moved successfull.\n\n";
            }

        }
        displayResult();
    }


    void Clustering::KMeans::movePonts(PointPtr *point) {
        const double MIN = 100;
        double score = 0, oldScore = 0, scoreDiff = 0, distance = 0, min = MIN;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;

        int clusterEl, numbOfPoints = point_space[0].getM_size();
        int numbOfClusters = __k;


        cout << "\t\t\t\t\tMAIN LOOP\n";
        while (scoreDiff > SCORE_DIFF_THRESHOLD) {
            oldScore = MIN;
            cout << "OLDSCORE " << oldScore << endl << endl;

            for (int j = 0; j < numbOfClusters; ++j) {
                min = MIN;


                for (int l = 0; l < numbOfPoints; ++l) {
                    min = MIN;
                    for (int i = 0; i < numbOfClusters; ++i) {
                        distance = point[l]->distanceTo(point_space[i].get__centroid());
                        cout << "point[" << l << "] --> " << *point[l] << "   dist(c[" << i << "]: " << distance <<
                        endl;
                        if (distance < min) {
                            min = distance;
                            clusterEl = i;
                        }
                    }
//                    cout <<"MIN "<<min<<endl;
                    cout << "\nc[" << clusterEl << "] nMin " << min << " <-- " << *point[l] << endl;
                    cout << "point_space[" << clusterEl << "].centr <-- " <<
                    point_space[clusterEl].get__centroid() <<
                    endl << endl;
                    if (point_space[j].get__centroid() != *point[l]) {
                        Cluster::Move move(point[l], &point_space[j], &point_space[clusterEl]);
                        move.perform();
                        cout << "point is moved successfull.\n";
                    }

                }
            }

            // compute and set centroid to valid
            // if centroid is invalid
            for (int i = 0; i < numbOfClusters; ++i) {
                if (!point_space[i].isCentroidValid()) {
                    point_space[i].computeCentroid();
                    cout << "NEW Centroid " << point_space[i].get__centroid() << endl;
                }
            }

            score = computeClusteringScore();
            cout << "Score: " << score << endl;

            oldScore = score;

            scoreDiff = std::abs(score - oldScore);
            cout << "ScoreDiff: " << scoreDiff << endl;

        }
    }

    double KMeans::computeClusteringScore() {
        int numOfPoints = point_space[0].getM_size();
        double d_In, d_Out;
        int p_In, p_Out;
        double betaCV;

        int sum = 0;

        cout << "\n computeClusteringScore  Begin\n";

        // calculate the sum of the inter-cluster distances
        // and the number of distinct (intra-) cluster edges
        for (int i = 0; i < __k; ++i) {
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
        cout << "BETA " << betaCV << endl;
        cout << "\nEnd computeClusteringScore\n";
        return betaCV;
    }

    void KMeans::start() {
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
            PointPtr p = point_space->remove(initCentroid[j]);
//                point_space[j].setCentroid((*initCentroid[j]));
            point_space[j].setCentroid(*p);
            point_space[j].setPointDimension(dim);
//            cout << "c[" << j << "].centroid: " << point_space[j].get__centroid() << endl;
        }

        cout << "******************FIRSTmovePoint(points)**********************\n\n";
        firstMove(points);
//            cout << "******************movePoint(points)**********************\n\n";
//
//            movePonts(points);
        cout << "****************************************\n";

        cout << "BBBB";


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
}