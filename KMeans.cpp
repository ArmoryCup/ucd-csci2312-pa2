//
// Created by kamil on 10/13/15.
//

#include<iostream>
#include <fstream>
#include <sstream>
#include "KMeans.h"
#include "Cluster.h"

using namespace std;
namespace Clustering {

    KMeans::KMeans(int k) {
        PointPtr cents[5];
        Cluster c[k];
        fstream csv("CSV.txt", std::ios::in);
        if (csv.is_open()) {
            csv >> point_space;
        }
        csv.close();

        LNodePtr n = point_space.getPoints();
        int i = 0;
        for (LNodePtr curr = n; curr != nullptr; curr = curr->next) {
            cents[i] = curr->p;
            i++;
        }
        cout << point_space;
        int numbOfPoints = point_space.getM_size();

        // pick random points from point_space and set them as initial centroids for the k clusters
        for (int j = 0; j < k; ++j) {
            c[j].pickPoints(numbOfPoints, cents);
        }


        // create k-1 cluster empty cluster
        Cluster emptyCluster;
        double score, scoreDiff;

        bool flag = false;
        int s = 0;
        while(!flag){

            double min = c[s].get__centroid().distanceTo(*cents[s]);
            double max = c[s+1].get__centroid().distanceTo(*cents[s]);
            cout << min << " " << max;

            s++;
            flag = true;
        }

    }



}