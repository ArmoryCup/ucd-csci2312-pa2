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

        class Centroid {                    // private inner/nested/member class
            PointPtr __centroid;
            int __dimension;
            bool isValid;
        public:
            Centroid(int d) :
                    __dimension(d),
                    __centroid(new Point(d)) { }

            ~Centroid() { delete __centroid; }

            const Point get() const {
                return *__centroid;
            }

            void set(const Point &point) {
                *__centroid = point;
            }

            const bool getValid() const {
                return isValid;
            }

            void setValid(bool v) {
                isValid = v;
            }
        };

        int m_PointDimension;               // number of dimensions of the point in the Cluster
        Centroid __centroid;                  // cluster's centroid


    public:
        Cluster();
        Cluster(int d) : m_PointDimension(d), __centroid(m_PointDimension), m_size(0),
                         points(nullptr) { } // default ctor

        Cluster(const Cluster &rhs); // copy ctor
        Cluster &operator=(const Cluster &); // assignment operator
        ~Cluster(); // dtor

        Point get__centroid() const;

        LNodePtr getPoints() const;

        const unsigned int getID() const {
            return idGenerator;
        }

        int getPointDimension() const {
            return Cluster::m_PointDimension;
        }

        void setPointDimension(int dim) {
            m_PointDimension = dim;
        }

        bool isCentroidValid() const;

        void setCentroidValid(bool b);

        void setCentroid(const Point &);

        void computeCentroid();

        int getM_size() const {
            return m_size;
        }

        void generateID(){ __id = idGenerator++; }

        void pickPoints(int k, PointPtr *pointArray);

        double intraClusterDistance() const;

        friend double interClusterDistance(const Cluster &c1, const Cluster &c2);

        int getClusterEdges() const;

        friend double interClusterEdges(const Cluster &c1, const Cluster &c2);

        void add(const PointPtr &);                 // add a point
        const PointPtr &remove(const PointPtr &); // remove a point and return it
        // so we can add it to another cluster



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


    private:
        bool isValid;                       // validate centroid
        int m_size;
        LNodePtr points;                    // node pointer to points to the points of the linked list
        static unsigned int idGenerator;
        unsigned int __id;

    public:
        static const char POINT_CLUSTER_ID_DELIM = ':';

        class Move {
            private:
                Cluster *_from, *_to;
                PointPtr _ptr;
            public:
                Move(PointPtr &ptr, Cluster *from, Cluster *to) : _ptr(ptr), _from(from), _to(to) { }

                void perform() {
                    _to->add(_from->remove(_ptr));
                    _to->setCentroidValid(false);
                    _from->setCentroidValid(false);
                }
            };
    };
}
#endif //PA2_CLUSTER_H
