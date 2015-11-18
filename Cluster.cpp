#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>

#include "Point.h"
#include "Cluster.h"
#include "Exceptions.h"

using namespace std;
namespace Clustering {

    unsigned int Cluster::idGenerator = 0;
    unsigned int Cluster::numbImported = 0;
    unsigned int Cluster::numbFailed = 0;


    Cluster::Cluster(const Cluster &rhs) : __centroid(rhs.__centroid) {
        m_size = rhs.m_size;
        m_PointDimension = rhs.m_PointDimension;
        points = rhs.points;
        __id = rhs.__id;
//        generateID();
    }

    void Cluster::add(const Point &pt) {
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


    Cluster &Cluster::operator=(const Cluster &rhs) {
        if (this == &rhs) {
            return *this;
        }
        else {
            points.clear();
            points = rhs.points;
            m_size = rhs.m_size;
            m_PointDimension = rhs.m_PointDimension;
//            __id= rhs.__id;
            return *this;
        }
    }


    // dtor
    Cluster::~Cluster() {
//        idGenerator --;
        points.clear();
    }


    const Point &Cluster::remove(const Point &point) {
        if (points.empty())
            throw RemoveFromEmptyEx("Remove function");

        bool found = false;
        for (auto i = points.begin(); i != points.end(); i++) {
            if (*i == point) {
//                temp = *i;
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


    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {
        Cluster tempCluster;

        std::forward_list<Point> tempPoints1 = lhs.points, tempPoints2 = rhs.points;
        tempPoints1.merge(tempPoints2);

        tempPoints1.unique();
        for (auto it = tempPoints1.begin(); it != tempPoints1.end(); it++) {
            tempCluster.add(*it);
        }

        return tempCluster;
    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {

        std::forward_list<Point> tempPoints1 = lhs.points, tempPoints2 = rhs.points;
        tempPoints1.unique();
        tempPoints2.unique();

        auto it2 = tempPoints2.begin();

        Cluster intersect;
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
            cout << "No Interseption.\n";
        else
            return intersect;
    }

    bool operator==(const Cluster &lhs, const Cluster &rhs) {
        bool equal = false;
        if (lhs.points == rhs.points) {
            equal = true;
            return equal;
        }
        return equal;
    }

    Cluster &Cluster::operator+=(const Point &rhs) {
        Point newPoint = rhs;
        add(newPoint);
        return *this;
    }

    Cluster &Cluster::operator-=(const Point &rhs) {
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


    Cluster &Cluster::operator+=(const Cluster &rhs) {
        if (points == rhs.points)
            return *this;
        else {
            Cluster temp = *this + rhs;
            *this = temp;
            return *this;
        }
    }


    Cluster &Cluster::operator-=(const Cluster &rhs) {
        if (points == rhs.points)
            return *this;
        else {
            std::forward_list<Point> tempPoints1 = this->points, tempPoints2 = rhs.points,
                    tempPoint3;
            tempPoints1.unique();
            tempPoints2.unique();

            auto it2 = tempPoints2.begin();

            Cluster temp;
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


    const Cluster operator+(const Cluster &lhs, const Point &rhs) {
        Cluster newCluster;
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

    const Cluster operator-(const Cluster &lhs, const Point &rhs) {
        Cluster newCluster;
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

    std::ostream &operator<<(std::ostream &os, const Cluster &c1) {
        if (c1.points.empty())
            throw RemoveFromEmptyEx("cout<<");

        int i = 0;
        for (auto it = c1.points.begin(); it != c1.points.end(); it++) {
//            os << i << ") " << *it << " " << Cluster::POINT_CLUSTER_ID_DELIM << " " << c1.__id << "\n";
            os << *it << " " << Cluster::POINT_CLUSTER_ID_DELIM << " " << c1.__id << "\n";

            i++;
        }

    }

    bool Cluster::contains(const Point &point) {
        for (auto it = points.begin(); it != points.end(); it++) {
            int i;
            if (*it == point)
                return true;
        }
        return false;
    }

    std::istream &operator>>(std::istream &istream, Cluster &c1) {
        std::string line;
        int dimension;  // to hold a number of dimensions for a point
        char delim = Clustering::Point::POINT_VALUE_DELIM;      // Point delimeter
        while (getline(istream, line)) {
            dimension = 1;

            // get point's dimenstion by counting the delimeter in the line
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == delim) {
                    dimension++;
                }
            }

            try {

                stringstream lineStream(line);
                Point newPoint(dimension);

                lineStream >> newPoint;
                c1.add(newPoint);
                Cluster::numbImported++;

            } catch (DimensionalityMismatchEx &dimErr) {
                cout << "Error: Dimensionality mismatch " << dimErr << endl;
                Cluster::numbFailed++;
            }
        }
        return istream;
    }

    void Cluster::computeCentroid() {
        if (points.empty())
            throw RemoveFromEmptyEx("ComputeCentroid");

        int dim = m_PointDimension;
        Point ptr(dim);
        for (auto curr = points.begin(); curr != points.end(); curr++) {
            ptr += *curr;
//             cout << ptr;
        }
        (ptr) / static_cast<double>(m_size);
        __centroid.set(ptr);
        __centroid.setValid(true);
//         cout << "\nComputeCentroid " << get__centroid() << endl;
    }

    unsigned int Cluster::numberImported() {
        numbImported++;
        return numbImported;
    }

    unsigned int Cluster::numberFailed() {
        numbFailed++;
        return numbFailed;
    }

    forward_list<Point> Cluster::getPoints() const {
        return points;
    }

    Point Cluster::get__centroid() const {
        return __centroid.get();
    }

    void Cluster::setCentroid(const Point &point) {

        __centroid.set(point);
        __centroid.setValid(true);
    }

//    void Cluster::pickPoints(int k, PointPtr *pointArray) {
    void Cluster::pickPoints(int k, std::vector<Point> &pointArray) {

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

    double Cluster::intraClusterDistance() const {
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

    double interClusterDistance(const Cluster &c1, const Cluster &c2) {
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

    int Cluster::getClusterEdges() const {
        return (m_size * (m_size - 1) / 2);
    }

    double interClusterEdges(const Cluster &c1, const Cluster &c2) {

        int size = c1.m_size + c2.m_size;
        int numEdge = (size * (size - 1) / 2);
        return size;
    }

    bool Cluster::isCentroidValid() const {
        return __centroid.getValid();
    }

    void Cluster::setCentroidValid(bool b) {
        this->__centroid.setValid(b);
    }

}
