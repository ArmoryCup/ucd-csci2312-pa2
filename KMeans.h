//
// Created by kamil on 10/13/15.
//

#ifndef UCD_CSCI2312_PA2_KMEANS_H
#define UCD_CSCI2312_PA2_KMEANS_H

#include "Cluster.h"

namespace Clustering {
    class KMeans {

        Cluster point_space;
        PointPtr points;
        static double SCORE_DIFF_THRESHOLD;

    public:

        KMeans():point_space(){}
        KMeans(int k);

        double computeClusteringScore();

        // Getters & setters
        Cluster getM_cluster() const {
            return point_space;
        }
        void setM_cluster(Cluster m_cluster) {
            KMeans::point_space = m_cluster;
        }
    };
}

#endif //UCD_CSCI2312_PA2_KMEANS_H
