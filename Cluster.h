#include <vector>
#include <forward_list>
#include <unordered_map>

#include "Point.h"
#include "Exceptions.h"

#ifndef PA2_CLUSTER_H
#define PA2_CLUSTER_H

namespace Clustering {

    template<typename P, int dim>
    class Cluster;


    template<typename P, int dim>
    std::ostream &operator<<(std::ostream &os, const Cluster<P, dim> &c1);


    template<typename P, int dim>
    class Cluster {

        int m_PointDimension;
        Point<double,dim> __centroid;
        bool valid;


    public:
        class Move;

        Cluster() : m_PointDimension(0), m_size(0) {
            generateID();
        }

//        Cluster(unsigned int d) : m_PointDimension(d), __centroid(m_PointDimension), m_size(0) { generateID(); }
        Cluster(const Cluster &rhs);                    // copy ctor
        Cluster &operator=(const Cluster &);            // assignment operator
        ~Cluster(); // dtor

        bool isCentroidValid() const;
        void setCentroidValid(bool b);
        void setCentroid(const P &);
        void computeCentroid();
        unsigned int numberImported();
        unsigned int numberFailed();
        unsigned int cantorFunction(unsigned int id1, unsigned int id2);

        int getM_size() const { return m_size; }
        P get__centroid() const;
        std::forward_list<P> getPoints() const;

        const unsigned int getID() const {
            return idGenerator;
        }

        int getPointDimension() const { return m_PointDimension; }
        void setPointDimension(unsigned int i_dim) { m_PointDimension = i_dim; }
        void generateID() { __id = idGenerator++; }

        void pickPoints(int k, std::vector<P> &);
        double intraClusterDistance() const;


        template<typename C, int d>
        friend double interClusterDistance(const Cluster<C, d> &c1, const Cluster<C, d> &c2);

        int getClusterEdges() const;

        template<typename C, int d>
        friend double interClusterEdges(const Cluster<C, d> &c1, const Cluster<C, d> &c2);

        void add(const P &);                 // add a point
        const P &remove(const P &);         // remove a point and return it
                                            // so we can add it to another cluster

        bool contains(const P &);
        void loadToMap();


        Cluster<P, dim> &operator+=(const Cluster<P, dim> &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference

        Cluster<P, dim> &operator+=(const P &rhs); // add point
        Cluster<P, dim> &operator-=(const P &rhs); // remove point

        template<typename C, int d>
        friend bool operator==(const Cluster<C, d> &lhs, const Cluster<C, d> &rhs);

        template<typename C, int d>
        friend const Cluster operator+(const Cluster<C, d> &lhs, const Cluster<C, d> &rhs);

        template<typename C, int d>
        friend const Cluster<C, d> operator-(const Cluster<C, d> &lhs, const Cluster<C, d> &rhs);

        template<typename C, int d>
        friend const Cluster<C, d> operator+(const Cluster<C, d> &lhs, const P &rhs);

        template<typename C, int d>
        friend const Cluster operator-(const Cluster<C, d> &lhs, const P &rhs);

        friend std::ostream &operator<< <>(std::ostream &os, const Cluster &);

        template<typename C, int d>
        friend std::istream &operator>>(std::istream &os, Cluster<C, d> &c1);


        P &operator[](const unsigned int &index) {
            if (index >= m_size)
                throw OutOfBoundEx("Cluster[]", index);

            auto it = points.begin();
            unsigned int i = index;
            while (i > 0) {
                i--;
                it++;
            }
            return *it;
        }

        struct Keys { // key {p1, p2}
            P p1, p2;
            Keys(const P &dp1, const P &dp2) :
                    p1(dp1), p2(dp2)
            {}
        };

        struct Hash { // hash functor
            std::size_t operator()(const Keys &key) const {
                unsigned int pID1 = key.p1.getID();
                unsigned int pID2 = key.p2.getID();

                if (pID1 > pID2) std::swap(pID1, pID2);

                return std::hash<std::size_t>()((pID1 + pID2) * (pID1 + pID2 + 1) / 2 + pID2);
            }
        };

        struct DPKeyEqual { // equality functor (implements transitivity)
            bool operator()(const Keys &lhs, const Keys &rhs) const { // note the const
                return (lhs.p1.getID() == rhs.p1.getID() && lhs.p2.getID() == rhs.p2.getID()) ||
                       (lhs.p1.getID() == rhs.p2.getID() && lhs.p2.getID() == rhs.p1.getID());
            }
        };

        void loadToMap(Cluster<P, dim> &);

        typedef std::unordered_map<Keys, double, Hash, DPKeyEqual> myMap;


    private:
        int m_size;
        std::forward_list<P> points;                    // node pointer to points to the points of the linked list
        unsigned int __id;
        static myMap m_distances;

        static unsigned int idGenerator;
        static unsigned int numbImported, numbFailed;

    public:
        class Move {
        public:
            friend class Cluster;

            Move(P &point, Cluster &from, Cluster &to) : _pt(point), _from(&from), _to(&to) { }

            void perform() {
                _from->remove(_pt);
                _to->add(_pt);
                _to->setCentroidValid(false);
                _from->setCentroidValid(false);
            }

        private:
            Cluster *_from, *_to;
            P _pt;
        };

        static const char POINT_CLUSTER_ID_DELIM = ':';
    };
}

#include "Cluster.cpp"

#endif //PA2_CLUSTER_H
