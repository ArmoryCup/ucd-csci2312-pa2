//
// Created by kamil on 10/13/15.
//

#include<iostream>
#include <fstream>
#include <cmath>
#include <forward_list>
#include <cstdlib>
#include "KMeans.h"
#include "Cluster.h"
#include "Point.h"

using namespace std;
namespace Clustering {


    KMeans::KMeans(unsigned int k, unsigned int pointDim)  {
        __k = k;
        m_kPointDim = pointDim;
        m_cluster.setPointDimension(pointDim);
    }

    void KMeans::loadPoints(string textFile) {
        std::fstream csv(textFile.c_str(), std::ios::in);
        if (csv.is_open()) {
            csv >> m_cluster;
        }
        csv.close();
//        cout << "**********************************SIZE " << m_cluster.getM_size()<<endl;

//        cout << "Load p\n";
//        cout << m_cluster;
//        point_space.push_back(m_cluster);
    }

    void KMeans::movePonts() {
        const double MIN = 100;
        int min = MIN;
        double distance = 0;

        double score = 0, prevScore, scoreDiff = 0;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;
        int clusterId = 0;

        prevScore = MIN;
        int pointDim = point_space[0].getPointDimension();
        while (scoreDiff > SCORE_DIFF_THRESHOLD) {
//            cout << "OLDSCORE " << prevScore << endl;
//            cout << "MovePoint() START\n\n";
//            cout << "Points size " << point_space[0].getM_size() << " \n";
//            cout << point_space[0];
//            cout << endl;

//            cout << "********************Current Centroids********************\n";
//            for (int k = 0; k < __k; ++k) {
//                cout << point_space[k].get__centroid() << endl;
//            }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            // loop through all clusters
            for (unsigned int l = 0; l < __k; ++l) {
                int numb = point_space[l].getM_size();
                int pID = 0;
//                cout << "\n******************CLUSTER SWITCH******************\n";

                int i = (numb -1);
                // loop through all  k cluster's points
                while (i >= 0) {

                    Point currP = point_space[l][i];
                    pID = i;
//                    cout << "\nc[" << l << "].currP[" << i << "] --> " << currP << endl;

                    // find the nearest cluster to the point
                    min = MIN;
                    for (unsigned int j = 0; j < __k; ++j) {
                        distance = currP.distanceTo(point_space[j].get__centroid());
//                        cout << "currP --> " << currP << "   dist(c[" << j << "]: " << distance << endl;
                        if (min > distance) {
                            min = distance;
                            clusterId = j;
                        }
                    }

                    if (point_space[l].get__centroid() != currP) {
                        Cluster::Move move(currP, point_space[l], point_space[clusterId]);
                        move.perform();
//                        cout << "Point is moved to c[" << clusterId << "]\n";
                    }
                    i--;
                }
            }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /*loop through all clusters
                if centroid invalid
                    compute and set valid to true */

//            cout << "\nComputing centroids";
//            cout << "\n***********************************************\n";
            for (unsigned int c = 0; c < __k; ++c) {
                if (point_space[c].isCentroidValid() == false) {
                    point_space[c].computeCentroid();
                    point_space[c].setCentroidValid(true);
//                    cout << "NEW CENTROID " << point_space[c].get__centroid() << endl;
                }
            }
//            cout << "\nCOMPUTING CLUSTER SCORE\n";
//            cout << "*************************\n";
            score = computeClusteringScore();
            scoreDiff = std::abs((score - prevScore));
            prevScore = score;
//            cout << "\nSCORE: " << score << endl;
//            cout << "SCOREDIFF: " << scoreDiff << endl << endl;
        }
    }


    double KMeans::computeClusteringScore() {
        double d_In, d_Out, betaCV;
        d_In = d_Out = betaCV = 0;
        int p_In, p_Out;
        p_In = p_Out = 0;

        // calculate the sum of the inter-cluster distances
        // and the number of distinct (intra-) cluster edges
        for (unsigned int i = 0; i < __k; ++i) {
            d_In += point_space[i].intraClusterDistance();
            p_In += point_space[i].getClusterEdges();
//            cout << "point_space[" << i << "]_d_In: " << d_In << endl;
//            cout << "point_space[" << i << "]_p_In: " << p_In << endl;

        }

        // calculate the sum of the inter-cluster distances
        // and  the number of the distinct inter-cluster edge
        for (unsigned int i = 0; i < __k; ++i) {
            for (unsigned int j = 1; j < __k; ++j) {
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

        std::vector<Point> initCentroid;
        cout << "---------------------";
//        cout << "\nPick & Init\n";
//        cout <<"---------------------\n\n";

        m_cluster.pickPoints(__k, initCentroid);
        for (unsigned int i = 0; i < __k; ++i) {
            Cluster t(m_kPointDim);

            t.setCentroid(initCentroid[i]);

            point_space.push_back(t);
//            cout << "POISP " << point_space[i].get__centroid();
//            cout << endl;
        }
        point_space[0] = m_cluster;


        m_cluster.~Cluster();

//        cout << "END___Pick & Init\n";
//        cout << "---------------------\n\n";
//        cout << "---------------------";
//        cout << "\nMOVE() BEGIN\n";
        movePonts();

        cout << "END_MOVEPOINT\n";
        cout << "---------------------";

        displayResult();
//
//        // deallocate all clusters
        deleteClusters(point_space);

    }

    void KMeans::displayResult() {
        for (unsigned int n = 0; n < __k; ++n) {
            if (point_space[n].getPoints().empty()) {
                cout << "Error! The function displayResult can not display anything. Clusters do not have points\n";
                return;
            }

            cout << "\nc[" << n << "] has \n";
            cout << point_space[n];
//                cout << "centroid: " << point_space[n].get__centroid() << endl;
        }
    }

    void KMeans::deleteClusters(std::vector<Cluster> cArray) {
        cArray.clear();
    }

    void KMeans::writeToFile(std::string fileName){
        std::fstream saveToFile(fileName.c_str(), std::ios::out);
        if (saveToFile.is_open()) {
            for (unsigned int i = 0; i < __k; ++i) {
                saveToFile << point_space[i];

            }
        }
        saveToFile.close();
    }

}