//
// Created by kamil on 10/13/15.
//

#include<iostream>
#include <fstream>
#include <cmath>
#include <forward_list>
#include "KMeans.h"

using namespace std;
namespace Clustering {

    template<int k, int dim>
    KMeans<k, dim>::KMeans(unsigned int i_k, unsigned int pointDim) {
        __k = i_k;
        m_kPointDim = pointDim;
        m_cluster.setPointDimension(pointDim);
    }

    template<int k, int dim>
    KMeans<k, dim>::KMeans() {
        __k = k;
        m_kPointDim = dim;
        m_cluster.setPointDimension(dim);
    }

    template<int k, int dim>
    void KMeans<k, dim>::loadPoints(string textFile) {
        std::fstream csv(textFile.c_str(), std::ios::in);
        if (csv.is_open()) {
            csv >> m_cluster;
        }
        csv.close();
        int numRead = m_cluster.numberImported(),
                numFailed = m_cluster.numberFailed();

        std::cout << numRead << " points were read successfull\n";
        std::cout << numFailed << " points were not read due to dimensionality mismatches\n";
//        cout << "Load p\n";
//        cout << m_cluster;
//        point_space.push_back(m_cluster);
    }

    template<int k, int dim>
    void KMeans<k, dim>::movePonts() {
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

                // run from the end side
                int i = (numb - 1);
                // loop through all  k cluster's points
                while (i >= 0) {

//                    Point<double,dim> currP = point_space[l][i];

//                    pID = i;
//                    cout << "\nc[" << l << "].currP[" << i << "] --> " << currP << endl;

                    // find the nearest cluster to the point
                    min = MIN;
                    for (unsigned int j = 0; j < __k; ++j) {
//                        distance = currP.distanceTo(point_space[j].get__centroid());
                        distance = point_space[l][i].distanceTo(point_space[j].get__centroid());

//                        cout << "currP --> " << point_space[l][i] << "   dist(c[" << j << "]: " << distance << endl;
                        if (min > distance) {
                            min = distance;
                            clusterId = j;
                        }
                    }

//                    if (point_space[l].get__centroid() != currP) {
                    if (point_space[l].get__centroid() != point_space[l][i]) {

//                        typename Cluster<Point<double, dim>, dim>::Move move(currP, point_space[l], point_space[clusterId]);
                        typename Cluster<Point<double, dim>, dim>::Move move(point_space[l][i], point_space[l], point_space[clusterId]);
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

    template<int k, int dim>
    double KMeans<k, dim>::computeClusteringScore() {
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

    template<int k, int dim>
    void KMeans<k, dim>::start() {

        std::vector<Point<double, dim>> initCentroid;
        cout << "---------------------";
        cout << "\nPick & Init\n";
        cout <<"---------------------\n\n";

        m_cluster.pickPoints(__k, initCentroid);
        for (unsigned int i = 0; i < __k; ++i) {
            Cluster<Point<double,dim>,dim> tempCluster;

            tempCluster.setCentroid(initCentroid[i]);
            point_space.push_back(tempCluster);

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

//        cout << "END_MOVEPOINT\n";
//        cout << "---------------------";

        displayResult();
//

    }

    template<int k, int dim>
    void KMeans<k, dim>::displayResult() {
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

    template<int k, int dim>
    void KMeans<k, dim>::writeToFile(std::string fileName) {
        std::fstream saveToFile(fileName.c_str(), std::ios::out);
        if (saveToFile.is_open()) {
            for (unsigned int i = 0; i < __k; ++i) {
                saveToFile << point_space[i];

            }
        }
        saveToFile.close();
    }

}