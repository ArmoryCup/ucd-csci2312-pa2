//
// Created by kamil on 10/13/15.
//

#ifndef UCD_CSCI2312_PA2_KMEANS_H
#define UCD_CSCI2312_PA2_KMEANS_H

#include "Cluster.h"

namespace Clustering {
    class KMeans {
        int dim;
        Cluster point_space;
        Cluster *c;
        int __k;

    public:
        const double SCORE_DIFF_THRESHOLD = 100;
        KMeans(int k);

        void pickPoints(int k, PointPtr *pointArray);

        Cluster getM_cluster() const {
            return point_space;
        }

        void setM_cluster(Cluster m_cluster) {
            KMeans::point_space = m_cluster;
        }

        void loadPoints();
        void movePonts(PointPtr cents);
        void displayResult();
    };
}

#endif //UCD_CSCI2312_PA2_KMEANS_H
