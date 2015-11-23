#include <iostream>
#include <fstream>
#include <sstream>
#include "Cluster.h"
#include "Exceptions.h"

namespace Clustering {

    template<typename C, int d>
    unsigned int Cluster<C, d>::idGenerator = 0;
    template<typename C, int d>
    unsigned int Cluster<C, d>::numbImported = 0;

    template<typename C, int d>
    unsigned int Cluster<C, d>::numbFailed = 0;




    template<typename P, int dim>
    Cluster<P, dim>::Cluster(const Cluster<P, dim> &rhs) : __centroid(rhs.__centroid) {
        m_size = rhs.m_size;
        m_PointDimension = rhs.m_PointDimension;
        points = rhs.points;
        __id = rhs.__id;
//        generateID();
    }

    template<typename P, int dim>
    void Cluster<P, dim>::add(const P &pt) {
        if (points.empty()) {
            points.push_front(pt);
        }
        else if (pt < *points.begin()) {
            points.push_front(pt);
            m_size++;
            return;
        }

        else {
            auto curr = points.begin();
            auto prev = curr;
            for (auto next = ++curr; next != points.end(); next++) {
                if (*next > pt)
                    break;
                else {
                    prev = next;
                }
            }
            points.insert_after(prev, pt);
        }
        m_size++;
    }

    template<typename P, int dim>
    Cluster<P, dim> &Cluster<P, dim>::operator=(const Cluster<P, dim> &rhs) {
        if (this == &rhs) {
            return *this;
        }
        else {
            points.clear();
            points = rhs.points;
            m_size = rhs.m_size;
            m_PointDimension = rhs.m_PointDimension;
            return *this;
        }
    }


    // dtor
    template<typename P, int dim>
    Cluster<P, dim>::~Cluster() {
//        idGenerator --;
        points.clear();
    }

    template<typename P, int dim>
    const P &Cluster<P, dim>::remove(const P &point) {
//        if (points.empty()) {
//            throw RemoveFromEmptyEx("Remove function");
//        }
        bool found = false;
        for (auto i = points.begin(); i != points.end(); i++) {
            if (*i == point) {
                points.remove(*i);
                found = true;
                m_size--;
                break;
            }
        }
        if (found == false)
            std::cout << "\nPoint was not removed. Point was not found!\n";


        return point;
    }

    template<typename P, int dim>
    const Cluster<P, dim> operator+(const Cluster<P, dim> &lhs, const Cluster<P, dim> &rhs) {
        Cluster<P, dim> tempCluster;

        std::forward_list<P> tempPoints1 = lhs.points, tempPoints2 = rhs.points;
        tempPoints1.merge(tempPoints2);

        tempPoints1.unique();
        for (auto it = tempPoints1.begin(); it != tempPoints1.end(); it++) {
            tempCluster.add(*it);
        }

        return tempCluster;
    }

    template<typename P, int dim>
    const Cluster<P, dim> operator-(const Cluster<P, dim> &lhs, const Cluster<P, dim> &rhs) {

        std::forward_list<P> tempPoints1 = lhs.points, tempPoints2 = rhs.points;
        tempPoints1.unique();
        tempPoints2.unique();

        auto it2 = tempPoints2.begin();

        Cluster<P, dim> intersect;
        while (it2 != tempPoints2.end()) {
            auto it1 = tempPoints1.begin();
            while (it1 != tempPoints1.end()) {
                if (*it2 == *it1) {
                    intersect.add(*it1);
                }
                it1++;
            }
            it2++;
        }
        if (intersect.points.empty())
            std::cout << "No Interseption.\n";
        else
            return intersect;
    }

    template<typename P, int dim>
    bool operator==(const Cluster<P, dim> &lhs, const Cluster<P, dim> &rhs) {
        bool equal = false;
        if (lhs.points == rhs.points) {
            equal = true;
            return equal;
        }
        return equal;
    }

    template<typename P, int dim>
    Cluster<P,dim> &Cluster<P,dim>::operator+=(const P &rhs) {
        P newPoint = rhs;
        add(newPoint);
        return *this;
    }

    template<typename P, int dim>
    Cluster<P, dim> &Cluster<P, dim>::operator-=(const P &rhs) {
        bool found = false;
        for (auto it = points.begin(); it != points.end(); it++) {
            if (*it == rhs) {
                remove(rhs);
                found = true;
            }
        }
        if (!found)
            std::cout << "\nPoint was not removed by op - r(-=)\n";
        return *this;
    }

    template<typename P, int dim>
    Cluster<P, dim> &Cluster<P, dim>::operator+=(const Cluster<P, dim> &rhs) {
        if (points == rhs.points)
            return *this;
        else {
            Cluster<P, dim> temp = *this + rhs;
            *this = temp;
            return *this;
        }
    }

    template<typename P, int dim>
    Cluster<P, dim> &Cluster<P, dim>::operator-=(const Cluster<P, dim> &rhs) {
        if (points == rhs.points)
            return *this;
        else {
            std::forward_list<P> tempPoints1 = this->points, tempPoints2 = rhs.points,
                    tempPoint3;
            tempPoints1.unique();
            tempPoints2.unique();

            auto it2 = tempPoints2.begin();

            Cluster<P, dim> temp;
            tempPoint3 = tempPoints1;
            int size = 0;
            while (it2 != tempPoints2.end()) {
                auto it1 = tempPoints1.begin();
                while (it1 != tempPoints2.end()) {
                    if (*it2 == *it1) {
                        tempPoint3.remove(*it1);
                    }
                    it1++;
                }
                it2++;
            }

            for (auto it = tempPoint3.begin(); it != tempPoint3.end(); it++)
                temp.add(*it);
            *this = temp;
            return *this;
        }
    }

    template<typename P, int dim>
    const Cluster<P, dim> operator+(const Cluster<P, dim> &lhs, const P &rhs) {
        Cluster<P, dim> newCluster;
        if (lhs.points.empty()) {
            newCluster.add(rhs);
            return newCluster;

        } else {
            newCluster = lhs;
            for (auto it = lhs.points.begin(); it != lhs.points.end(); it++) {
                if (*it == rhs) {
                    break;
                }
            }
            newCluster.add(rhs);
        }
        return newCluster;
    }

    template<typename P, int dim>
    const Cluster<P, dim> operator-(const Cluster<P, dim> &lhs, const P &rhs) {
        Cluster<P, dim> newCluster;
        bool found = false;
        if (lhs.points.empty()) {
            return newCluster;

        } else {
            newCluster = lhs;
            for (auto it = lhs.points.begin(); it != lhs.points.end(); it++) {
                if (*it == rhs) {
                    found = true;
                    newCluster.remove(rhs);
                }
            }

            if (!found)
                std::cout << "\nError! Point is not contained in the cluster.\n";
        }
        return newCluster;
    }

    template<typename W, int dim>
    std::ostream &operator<<(std::ostream &os, const Cluster<W, dim> &c1) {
//        if (c1.points.empty())
//            throw RemoveFromEmptyEx("cout<<");

        int i = 0;
        for (auto it = c1.points.begin(); it != c1.points.end(); it++) {
            os << *it << " " << Cluster<W, dim>::POINT_CLUSTER_ID_DELIM << " " << c1.__id << "\n";
            i++;
        }

    }

    template<typename P, int dim>
    bool Cluster<P, dim>::contains(const P &point) {
        for (auto it = points.begin(); it != points.end(); it++) {
            int i;
            if (*it == point)
                return true;
        }
        return false;
    }

    template<typename W, int dim>
    std::istream &operator>>(std::istream &istream, Cluster<W, dim> &c1) {
        std::string line;
        int iDim = c1.getPointDimension();
        int dimension;  // to hold a number of dimensions for a point
        char delim = W::POINT_VALUE_DELIM;      // Point delimeter
        while (getline(istream, line)) {
            dimension = 1;

            // get point's dimenstion by counting the delimeter in the line
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == delim) {
                    dimension++;
                }
            }

            Point<double,dim> newPoint;

            try {
                std::stringstream lineStream(line);

                lineStream >> newPoint;
                c1.add(newPoint);
                Cluster<W, dim>::numbImported++;

            } catch (DimensionalityMismatchEx &dimErr) {
                std::cout << "Error: Dimensionality mismatch " << dimErr << std::endl;
                Cluster<W, dim>::numbFailed++;
                W::rewindIdGen();
            }
        }
        return istream;
    }

    template<typename P, int d>
    void Cluster<P, d>::computeCentroid() {
//        if (points.empty())
//            throw RemoveFromEmptyEx("ComputeCentroid");

        int dim = m_PointDimension;
        P ptr;
//        ptr.setDimenstion(dim);
        for (auto curr = points.begin(); curr != points.end(); curr++) {
            ptr += *curr;
//             cout << ptr;
        }
        (ptr) / static_cast<double>(m_size);
        __centroid = ptr;
//        __centroid.setValid(true);
        valid = true;
//         cout << "\nComputeCentroid " << get__centroid() << endl;
    }

    template<typename P, int dim>
    unsigned int Cluster<P, dim>::numberImported() {
        numbImported++;
        return numbImported;
    }

    template<typename P, int dim>
    unsigned int Cluster<P, dim>::numberFailed() {
        numbFailed++;
        return numbFailed;
    }

    template<typename P, int dim>
    std::forward_list<P> Cluster<P, dim>::getPoints() const {
        return points;
    }
    template<typename P, int dim>
    P Cluster<P, dim>::get__centroid() const {
//        return __centroid.get();
        return  __centroid;
    }

    template<typename W, int dim>
    void Cluster<W, dim>::setCentroid(const W &point) {
//
//        __centroid.set(point);
//        __centroid.setValid(true);
        __centroid = point;
        valid = true;

    }

    template<typename P, int dim>
    void Cluster<P, dim>::pickPoints(int k, std::vector<P> &pointArray) {

        auto curr = points.begin();
        int temp = m_size / k;
        int dist = 0;

        for (int i = 0; i < k; ++i) {
            for (int j = 1; j < dist; ++j) {
                curr++;
            }
            pointArray.push_back(*curr);
            dist += temp;
            curr = points.begin();
        }
    }

    template<typename P, int dim>
    double Cluster<P, dim>::intraClusterDistance() const {
        double sum = 0;

        if (points.empty())
            return 0;

        auto curr1 = points.begin(), curr2 = points.begin();
        curr2++;

        while (curr1 != points.end()) {
            while (curr2 != points.end()) {
                sum += curr1->distanceTo(*curr2);
                curr2++;
            }
            curr1++;


        }
        return (sum / 2);
    }

    template<typename P, int dim>
    double interClusterDistance(const Cluster<P, dim> &c1, const Cluster<P, dim> &c2) {
        double sum = 0;

        auto currC1 = c1.points.begin(), currC1n = c1.points.begin();
        currC1n++;
        auto currC2 = c2.points.begin(), currC2n = c2.points.begin();
        currC2n++;

        while (currC1 != c1.points.end()) {
            while (currC2 != c2.points.end()) {
                sum += currC1->distanceTo(*currC2);
                currC2++;
            }
            currC2 = c2.points.begin();
            currC1++;
        }
        return (sum / 2);
    }

    template<typename P, int dim>
    int Cluster<P, dim>::getClusterEdges() const {
        return (m_size * (m_size - 1) / 2);
    }

    template<typename P, int dim>
    double interClusterEdges(const Cluster<P, dim> &c1, const Cluster<P, dim> &c2) {
        int size = c1.m_size + c2.m_size;
        int numEdge = (size * (size - 1) / 2);
        return size;
    }

    template<typename P, int dim>
    bool Cluster<P, dim>::isCentroidValid() const {
        return valid;
//        return __centroid.getValid();
    }

    template<typename P, int dim>
    void Cluster<P, dim>::setCentroidValid(bool b) {
        valid = b;
//        this->__centroid.setValid(b);
    }

    template<typename P, int dim>
    unsigned int Cluster<P, dim>::CantorFunction(unsigned int id1, unsigned int id2) {
        return ((id1 + id2) * (id1 + id2 + 1) + id2) / 2 + id2;
    }
}
