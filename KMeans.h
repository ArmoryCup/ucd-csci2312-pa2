//
// Created by kamil on 10/13/15.
//

#ifndef UCD_CSCI2312_PA2_KMEANS_H
#define UCD_CSCI2312_PA2_KMEANS_H

#include "Cluster.h"

namespace Clustering {
    class KMeans {

        Cluster *m_cluster;

    public:
        KMeans():m_cluster(){}
        friend std::istream &operator>>(std::istream &os, KMeans &kMeans);


        Cluster *getM_cluster() const {
            return m_cluster;
        }

        void setM_cluster(Cluster *m_cluster) {
            KMeans::m_cluster = m_cluster;
        }
    };
}

#endif //UCD_CSCI2312_PA2_KMEANS_H
