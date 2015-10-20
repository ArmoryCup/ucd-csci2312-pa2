//
// Created by kamil on 10/13/15.
//

#include<iostream>
#include <fstream>
#include <sstream>
#include "KMeans.h"
#include "Cluster.h"
using namespace std;
namespace Clustering{

    KMeans::KMeans(int k){
        PointPtr cents[5];
        fstream csv("CSV.txt", std::ios::in);
        if (csv.is_open()) {
            csv>> point_space;
        }
        csv.close();
        Cluster c[k];
        LNodePtr n = point_space.getPoints();
        int i = 0;
        for(LNodePtr curr = n; curr!= nullptr; curr = curr->next){
            cents[i] = curr->p;
            i++;
        }
                cout << point_space;
        int numbOfPoints = point_space.getM_size();

        for (int j = 0; j < k; ++j) {
            point_space.pickPoints(4,c[j],cents);
        }
    }

}