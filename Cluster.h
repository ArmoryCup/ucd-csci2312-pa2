#include <stddef.h>
#include "Point.h"

#ifndef PA2_CLUSTER_H
#define PA2_CLUSTER_H


namespace Clustering {

    typedef Point *PointPtr;
    typedef struct Node *NodePtr;

    struct Node {
        PointPtr pointer;
        Node *next;
    };

    class Cluster {

    public:
        Cluster() : m_size(0), m_points(nullptr) { } // default ctor
        Cluster(int, NodePtr link);
        Cluster(const Cluster &); // copy ctor


        Cluster &operator=(const Cluster &); // assignment operator
        ~Cluster(); // dtor

        void add(const PointPtr &); // add a point
        PointPtr &remove(const PointPtr &); // remove a point and return it so we can add it to another cluster

    private:
        NodePtr m_points; // array of pointers to Point
        size_t m_size;
    };
}
#endif //PA2_CLUSTER_H
