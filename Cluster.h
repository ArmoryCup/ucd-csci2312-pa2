#include <stddef.h>
#include "Point.h"

#ifndef PA2_CLUSTER_H
#define PA2_CLUSTER_H


namespace Clustering {

    typedef Point *PointPtr;
    typedef struct LNode *LNodePtr;

    struct LNode {
        PointPtr p;
        LNode *next;
    };

    class Cluster {

        LNodePtr points; // node pointer to points to the points of the linked list
        int m_size;
    public:
        Cluster() : m_size(0), points(nullptr) { } // default ctor

        Cluster(const Cluster &); // copy ctor

        Cluster &operator=(const Cluster &); // assignment operator

        ~Cluster(); // dtor

        void add(const PointPtr &); // add a point
        PointPtr &remove(const PointPtr &); // remove a point and return it so we can add it to another cluster

        friend bool operator==(const Cluster &lhs, const Cluster &rhs);

        friend std::ostream &operator<<(std::ostream &os, const Clustering::Cluster &c1);
        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);


    };
}
#endif //PA2_CLUSTER_H
