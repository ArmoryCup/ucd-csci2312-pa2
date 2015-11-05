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

    void KMeans::movePonts() {
        const double MIN = 100;
        int min = MIN;
        double distance = 0;

        double score = 0, prevScore, scoreDiff = 0;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;
        int clusterId = 0;

        prevScore = MIN;
        while (scoreDiff > SCORE_DIFF_THRESHOLD) {
            cout << "OLDSCORE " << prevScore << endl << endl;

            LNodePtr currNode = NULL;
            PointPtr currP = NULL;

            // loop through all clusters
            for (int l = 0; l < __k; ++l) {
                int numb = point_space[l].getM_size();
                currNode = point_space[l].getPoints();

                // loop through all  k cluster's points
                for (int i = 0; i < numb; ++i) {
                    currP = currNode->p;
//                    cout << "\nc[" << l << "].currP --> " << *currP << endl;

                    min = MIN;
                    for (int j = 0; j < __k; ++j) {
                        distance = currP->distanceTo(point_space[j].get__centroid());
//                        cout << "currP --> " << *currP << "   dist(c[" << j << "]: " << distance <<
//                        endl;
                        if (min > distance) {
                            min = distance;
                            clusterId = j;
                        }
                    }
                    if (currNode->next != NULL)
                        currNode = currNode->next;
//                    cout << "\nc[" << clusterId << "] nMin " << min << " <-- " << *currP << endl << endl;

                    if (point_space[l].get__centroid() != *currP) {
                        Cluster::Move m(currP, &point_space[l], &point_space[clusterId]);
                        m.perform();
                    }
                }
            }

            /*loop through all clusters
                if centroid invalid
                    compute and set valid to true */
            for (int c = 0; c < __k; ++c) {
                if (point_space[c].isCentroidValid() == false) {
                    point_space[c].computeCentroid();
                    point_space[c].setCentroidValid(true);
//                    cout << "NEW CENTROID "<<point_space[c].get__centroid() << endl;
                }

            }
//            cout << "\nCOMPUTING CLUSTER SCORE\n";
//            cout << "*************************\n";
            score = computeClusteringScore();
//            cout<<"point_space[0].get__centroid() " << point_space[0].get__centroid()<<endl; // <<< NOT WORKING------------------------------
            scoreDiff = std::abs((score - prevScore));
            prevScore = score;
//            cout << "\nSCORE: " << score << endl;
//            cout << "SCOREDIFF: " << scoreDiff << endl << endl;
        }
    }


    double KMeans::computeClusteringScore() {
        double d_In, d_Out, betaCV;
        d_In = d_Out = betaCV= 0;
        int p_In, p_Out;
        p_In = p_Out = 0;

        // calculate the sum of the inter-cluster distances
        // and the number of distinct (intra-) cluster edges
        for (int i = 0; i < __k; ++i) {
            d_In += point_space[i].intraClusterDistance();
            p_In += point_space[i].getClusterEdges();
//            cout << "point_space[" << i << "]_d_In: " << d_In << endl;
//            cout << "point_space[" << i << "]_p_In: " << p_In << endl;

        }

        // calculate the sum of the inter-cluster distances
        // and  the number of the distinct inter-cluster edge
        for (int i = 0; i < __k; ++i) {
            for (int j = 1; j < __k; ++j) {
                d_Out += interClusterDistance(point_space[i], point_space[j]);
                p_Out += interClusterEdges(point_space[i], point_space[j]);
            }
        }
        betaCV = (d_In / p_In) / (d_Out / p_Out);
//        cout << "d_In " << d_In << " d_Out " << d_Out << " p_In " << p_In << " p_Out " << p_Out << endl;
//        cout << "BETA " << betaCV << endl;
//        cout << "\nEnd computeClusteringScore\n";
        return betaCV;
    }

    void KMeans::start() {
        int numbOfPoints = point_space[0].getM_size();
        PointPtr initCentroid[__k];         // initial centroid for k cluster


        // set initial centroids for k clusters
        point_space->pickPoints(__k, initCentroid);
        int dim = point_space[0].getPointDimension();

//        for (int j = 0; j < __k; ++j) {
//            PointPtr p = point_space->remove(initCentroid[j]);
//            point_space[j].setCentroid(*p);
////            point_space[j].add(p);
//            point_space[j].setPointDimension(dim);
//            cout << "c[" << j << "].centroid: " << point_space[j].get__centroid() << endl;
//        }

        for (int j = 0; j < __k; ++j) {
            point_space[j].setCentroid((*initCentroid[j]));
            point_space[j].setPointDimension(dim);
//            cout << "c[" << j << "].centroid: " << point_space[j].get__centroid() << endl;
        }

        movePonts();
        displayResult();

        // deallocate all clusters
        deleteClusters(point_space);

    }

    void KMeans::displayResult() {
        if (point_space[0].getPoints() == nullptr) {
            cout << "Error! The function displayResult can not display anything. Clusters do not have points\n";
        }
        else {
            for (int n = 0; n < __k; ++n) {
//                cout << "\nc[" << n << "] has \n";
                cout << point_space[n];
//                cout << "centroid: " << point_space[n].get__centroid() << endl;
            }

        }
    }

    void KMeans::deleteClusters(Cluster *clusterArr) {
        for (int i = 0; i < __k; ++i) {
            clusterArr[i].~Cluster();
        }
    }
}