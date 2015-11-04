//
// Created by kamil on 10/13/15.
//

#ifndef UCD_CSCI2312_PA2_KMEANS_H
#define UCD_CSCI2312_PA2_KMEANS_H

#include "Cluster.h"

namespace Clustering {
    class KMeans {
        Cluster *point_space;
        int __k;

    public:
        const double SCORE_DIFF_THRESHOLD = 0.001;
        KMeans(int k);

        void firstMove(PointPtr *);

        Cluster getM_cluster() const {
            return *point_space;
        }

        void setM_cluster(Cluster m_cluster) {
            KMeans::point_space = &m_cluster;
        }
        void start();
        void loadPoints(std::string);
        void movePonts(PointPtr *);
        void displayResult();
        double computeClusteringScore();
    };
}

#endif //UCD_CSCI2312_PA2_KMEANS_H
