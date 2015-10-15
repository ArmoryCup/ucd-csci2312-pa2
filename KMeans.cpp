//
// Created by kamil on 10/13/15.
//

#include<iostream>
#include <fstream>
#include <sstream>
#include "KMeans.h"
#include "Cluster.h"
namespace Clustering{


    std::istream &operator>>(std::istream &istream, Clustering::KMeans &kMeans) {
        Cluster *c = new Clustering::Cluster();
        PointPtr newPoint;
        std::string line;
        int dimension;  // to hold a number of dimensions for a point
        char delim = Clustering::Point::POINT_VALUE_DELIM;      // Point delimeter
        while (getline(istream, line)) {
            dimension = 0;

            // count point delimeter in the line
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == delim) {
                    dimension++;
                }
            }

            std::stringstream lineStream(line);
            newPoint = new Point(dimension + 1);
            lineStream >> *newPoint;
            c->add(newPoint);
        }
        kMeans.m_cluster = c;
        return istream;
    }
}