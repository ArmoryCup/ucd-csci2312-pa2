#include "Cluster.h"

namespace Clustering {


    Cluster::Cluster(int size, NodePtr link);

//Cluster::Cluster(const Cluster &rhs) : size(rhs.size) {
//}
/*
Cluster &operator=(const Cluster &rhs) {
    if (this == &rhs)
        return *this;
    else {
        if (points != nullptr) {
            for (int i = 0; i < size; ++i) {
                delete points[i];
            }
            delete[] points;
        }

        this->size = rhs.size;
        this->capacity = rhs.capacity;

        this->points = new PointPtr[capacity];
        for (int i = 0; i < capacity; i++)
            this->points[i] = nullptr;
        for (int i = 0; i < size; i++)
            this->points[i] = new Point(rhs.points[i]);
    }

    return *this;
}*/

// dtor
    Cluster::~Cluster() {
    }

    void Cluster::add(Clustering::PointPtr const &ptr) {

    }
}