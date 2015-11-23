//
// Created by kamil on 10/13/15.
//

#ifndef UCD_CSCI2312_PA2_KMEANS_H
#define UCD_CSCI2312_PA2_KMEANS_H

#include <vector>
#include "Cluster.h"

namespace Clustering {

    template <int k, int dim>
    class KMeans {
        Cluster<Point<double, dim>, dim> m_cluster;
        std::vector<Cluster<Point<double, dim>, dim>> point_space;
        unsigned int __k;
        unsigned int m_kPointDim;

    public:
        const double SCORE_DIFF_THRESHOLD = 5;
        KMeans();
        KMeans(unsigned int, unsigned int);

        void start();
        void loadPoints(std::string);
        void movePonts();
        void displayResult();
        double computeClusteringScore();

        void writeToFile(std::string fileName);


    };
}

#include "KMeans.cpp"
#endif //UCD_CSCI2312_PA2_KMEANS_H
