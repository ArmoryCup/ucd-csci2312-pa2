#include <vector>
#include <forward_list>
#include <unordered_map>

#include "Point.h"

#ifndef PA2_CLUSTER_H
#define PA2_CLUSTER_H

namespace Clustering {


    class Cluster {
        class Centroid {                    // private inner/nested/member class
            Point __centroid;
            int __dimension;
            bool isValid;
        public:
            Centroid(int d) :
                    __dimension(d),
                    __centroid(d) { }

            const Point get() const {
                return __centroid;
            }

            void set(const Point &point) {
                __centroid = point;
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
        Cluster() : m_PointDimension(0), __centroid(0), m_size(0) {
            generateID();
             }
        Cluster(unsigned int d) : m_PointDimension(d), __centroid(m_PointDimension), m_size(0)
                          { generateID(); }

        Cluster(const Cluster &rhs);                    // copy ctor
        Cluster &operator=(const Cluster &);            // assignment operator
        ~Cluster(); // dtor

        bool isCentroidValid() const;
        void setCentroidValid(bool b);
        void setCentroid(const Point &);
        void computeCentroid();
        unsigned int numberImported();
        unsigned int numberFailed();

        unsigned int CantorFunction(unsigned int id1, unsigned int id2){
        }

        int getM_size() const { return m_size; }
        Point get__centroid() const;
        std::forward_list<Point> getPoints() const;

        const unsigned int getID() const {
            return idGenerator;
        }

        int getPointDimension() const { return m_PointDimension; }

        void setPointDimension(unsigned int dim) { m_PointDimension = dim; }

        void generateID() { __id = idGenerator++; }
        void pickPoints(int k, std::vector<Point> &);
        double intraClusterDistance() const;

        friend double interClusterDistance(const Cluster &c1, const Cluster &c2);
        int getClusterEdges() const;
        friend double interClusterEdges(const Cluster &c1, const Cluster &c2);

        void add(const Point &);                 // add a point
        const Point &remove(const Point &);   // remove a point and return it
        // so we can add it to another cluster

        bool contains(const Point &);

        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference

        Cluster &operator+=(const Point &rhs); // add point
        Cluster &operator-=(const Point &rhs); // remove point
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator+(const Cluster &lhs, const Point &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Point &rhs);
        friend std::ostream &operator<<(std::ostream &os, const Clustering::Cluster &c1);
        friend std::istream &operator>>(std::istream &os, Clustering::Cluster &c1);


        Point &operator[](const unsigned int &index) {
            if (index >= m_size)
                throw OutOfBoundEx("Cluster[]", index);

            auto it = points.begin();
            unsigned  int i = index;
            while( i > 0){
                i--;
                it++;
            }
            return *it;
        }



    private:
        int m_size;
        std::forward_list<Point> points;                    // node pointer to points to the points of the linked list
        unsigned int __id;
        static std::unordered_map<unsigned int, double> m_map;
        static unsigned int idGenerator;
        static unsigned int numbImported, numbFailed;

    public:
        static const char POINT_CLUSTER_ID_DELIM = ':';

        class Move {

        private:
            Cluster *_from, *_to;
            Point _pt;
        public:
            Move(Point &p, Cluster &from, Cluster &to) : _pt(p), _from(&from), _to(&to) { }

            void  perform() {
                _from->remove(_pt);
                _to->add(_pt);
                _to->setCentroidValid(false);
                _from->setCentroidValid(false);
            }
        };
    };
}
#endif //PA2_CLUSTER_H
