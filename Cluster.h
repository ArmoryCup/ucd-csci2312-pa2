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
        int getM_size() const {
            return m_size;
        }

        Cluster() : m_size(0), points(nullptr) { } // default ctor
        Cluster(const Cluster &); // copy ctor
        Cluster &operator=(const Cluster &); // assignment operator
        ~Cluster(); // dtor

        int getSize() {
            return m_size;
        }

        void add(const PointPtr &); // add a point
        const PointPtr &remove(const PointPtr &); // remove a point and return it so we can add it to another cluster

        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference

        Cluster &operator+=(const Point &rhs); // add point
        Cluster &operator-=(const Point &rhs); // remove point

        friend bool operator==(const Cluster &lhs, const Cluster &rhs);

        friend std::ostream &operator<<(std::ostream &os, const Clustering::Cluster &c1);
        friend std::istream &operator>>(std::istream &os, Clustering::Cluster &c1);

        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);

    };
}
#endif //PA2_CLUSTER_H
