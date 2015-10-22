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
        LNodePtr points;                    // node pointer to points to the points of the linked list
        int m_size;
        int m_PointDimension;                 // number of dimensions of the point in the Cluster
        bool validCentroid;                   // validate a centroid

        static unsigned int __idGenerator;  // for use with __id
        PointPtr __centroid;
        unsigned int __id;

        static const char POINT_CLUSTER_ID_DELIM = ':';       // for use with operator<<

    public:
        Point get__centroid() const;

        Cluster() : m_size(0), points(nullptr) { } // default ctor
        Cluster(const Cluster &); // copy ctor
        Cluster &operator=(const Cluster &); // assignment operator
        ~Cluster(); // dtor

        class Move{
            PointPtr m_ptr;
            Cluster *m_from, *m_to;

            Move(PointPtr &ptr, Cluster *from, Cluster *to):m_ptr(ptr), m_from(from), m_to(to){}

            void perform(){
                m_to->add(m_from->remove(m_ptr));
                m_from->validCentroid = false;
                m_to->validCentroid = false;

            }

        };

        void pickPoints(int k, PointPtr *pointArray);


        // Getters and Setters
        LNodePtr getPoints() const{
            return points;
        }

        int getPointDimension() const {
            return Cluster::m_PointDimension;
        }

        void setPointDimension(int dim) {
            m_PointDimension = dim;
        }

        void setCentroid(const Point &);
        void computeCentroid();

        int getM_size() const {
            return m_size;
        }


        void add(const PointPtr &); // add a point
        const PointPtr &remove(const PointPtr &); // remove a point and return it so we can add it to another cluster

        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference

        Cluster &operator+=(const Point &rhs); // add point
        Cluster &operator-=(const Point &rhs); // remove point
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);

        friend std::ostream &operator<<(std::ostream &os, const Clustering::Cluster &c1);
        friend std::istream &operator>>(std::istream &os, Clustering::Cluster &c1);
    };
}
#endif //PA2_CLUSTER_H
