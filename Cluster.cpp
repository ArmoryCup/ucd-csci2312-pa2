#include "Cluster.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Point.h"
#include <cstdlib>

using namespace std;
namespace Clustering {

    unsigned int Cluster::idGenerator = 1;
    Cluster::Cluster(): m_PointDimension(0), __centroid(0), m_size(0), points(nullptr){

    }

    Cluster::Cluster(const Cluster &rhs):__centroid(rhs.__centroid) {
        m_size = rhs.m_size;
        LNodePtr newNode;                    // to point to the new node
        LNodePtr curr = NULL;         // to move thorugh the lsit
        Point p(2);
        LNodePtr copy = rhs.points;
        this->points = NULL;
        while (copy) {
            // Allocate a new node and store ptr there.
            newNode = new LNode;

            newNode->p = copy->p;
            newNode->next = NULL;
            if (!points) {
                points = newNode;
            } else {
                curr = points;
                while (curr->next) {
                    curr = curr->next;
                }
                curr->next = newNode;
            }
            copy = copy->next;
        }
    }

    void Cluster::add(const PointPtr &ptr) {
        LNodePtr newNode;                // to point to the new node
        LNodePtr curr = NULL;         // to move through the list

        // Allocate a new node and store ptr there.
        newNode = new LNode;
        newNode->p = ptr;
        newNode->next = NULL;
        if (!points) {
            points = newNode;
        } else {
//            curr = points;
//            while (curr->next) {
//                curr = curr->next;
//            }
//            curr->next = newNode;

            newNode->next = points;
            points = newNode;
        }
        this->m_size++;

        // sort points in the list in lexicographic order
        int dimention = ptr->getDims();
        bool isLess = false;
        LNodePtr currNode = points, nextNode;
        PointPtr dup;
        while (currNode) {
            nextNode = currNode;
            while (nextNode->next != NULL) {

                for (int i = 0; i < dimention; ++i) {
                    if (currNode->p->getValue(i) > nextNode->next->p->getValue(i))
                        isLess = true;
                    else
                        isLess = false;
                    break;
                }
                if (isLess) {
                    dup = nextNode->next->p;
                    nextNode->next->p = currNode->p;
                    currNode->p = dup;

                    nextNode = nextNode->next;
                } else {
                    nextNode = nextNode->next;
                }
            }
            currNode = currNode->next;
        }
    }


    Cluster &Cluster::operator=(const Cluster &rhs) {
        if (this == &rhs)
            return *this;
        else {

            // delete all existing node
            while (points != NULL) {
                m_size--;
                LNodePtr delNode = points;
                points = points->next;
//                delete delNode->p;
                delete delNode;
            }

            LNodePtr newCurr = rhs.points;
            while (newCurr != NULL) {
                add(newCurr->p);
                newCurr = newCurr->next;
            }
            return *this;
        }
    }


    // dtor
    Cluster::~Cluster() {
        while (points != NULL) {
            LNodePtr delNode = points;
            points = points->next;
//            if (delNode->p != NULL)
//                delete delNode->p;
            delete delNode;
        }
//        cout << "Dereferencing\n";
    }

    const PointPtr &Cluster::remove(const PointPtr &ptr) {

        LNodePtr currNode, nextNode, delNode;
        static PointPtr pDel;
        currNode = points;

        while (currNode->next != NULL) {
            if (*currNode->p == *ptr) {
                delNode = points;
                pDel = currNode->p;
                points = currNode->next;
                currNode = currNode->next;
            } else {
                break;
            }
//
        }

        while (currNode->next != NULL) {
            if (currNode->next->p == ptr) {
                delNode = currNode->next;
                currNode->next = currNode->next->next;
                pDel = delNode->p;
                delete delNode;
                m_size--;
                return pDel;
            } else
                currNode = currNode->next;
        }
<<<<<<< HEAD
=======
        
>>>>>>> origin/master
        return pDel;
    }


    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {

        Cluster newCluster = lhs;
        LNodePtr newPoints = rhs.points;
        while (newPoints) {
            newCluster.add(newPoints->p);
            newCluster.m_size++;
            newPoints = newPoints->next;
        }

        LNodePtr currNode = newCluster.points, nextNode, dup;
        while (currNode) {
            nextNode = currNode;
            while (nextNode->next != NULL) {
                if (currNode->p == nextNode->next->p) {
                    dup = nextNode->next;
                    nextNode->next = nextNode->next->next;
                    delete dup;
                    newCluster.m_size--;
                } else {
                    nextNode = nextNode->next;
                }
            }
            currNode = currNode->next;
        }
        return newCluster;
    }

    bool operator==(const Cluster &lhs, const Cluster &rhs) {
        int size = lhs.points->p->getDims();
        LNodePtr lCurr = lhs.points;
        LNodePtr rCurr = rhs.points;

        PointPtr left, right;

        while (lCurr) {
            left = lCurr->p;
            right = rCurr->p;
            for (int i = 0; i < size; ++i) {
                if (left->getValue(i) == right->getValue(i)) {
                    return true;
                }
                else {
                    return false;
                    break;
                }
            }
            lCurr = lCurr->next;
            rCurr = rCurr->next;
        }
    }

    Cluster &Cluster::operator+=(const Point &rhs) {
        PointPtr newPoint = new Point(rhs);
        add(newPoint);
        return *this;
    }

    Cluster &Cluster::operator-=(const Point &rhs) {
        LNodePtr currNode, nextNode, delNode;
        int dim = points->p->getDims();
        bool isEqual = false;
        bool flag = false;
        currNode = points;
        while (currNode) {
            for (int i = 0; i < dim; ++i) {
                if (currNode->p->getValue(i) == rhs.getValue(i))
                    flag = true;
                else {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                delNode = points;
                points = points->next;
                currNode = points;
                m_size--;
                delete delNode->p;
                delete delNode;
            }
            else if (!flag)
                break;
            else
                currNode = currNode->next;

        }

        currNode = points;
        isEqual = false;
        while (currNode->next) {
            nextNode = currNode;

            for (int i = 0; i < dim; ++i) {
                if (nextNode->next->p->getValue(i) == rhs.getValue(i))
                    isEqual = true;
                else {
                    isEqual = false;
                    break;
                }
            }
            if (isEqual) {
                delNode = nextNode->next;
                nextNode->next = nextNode->next->next;
                m_size--;
                delete delNode->p;
                delete delNode;
            }

            else
                currNode = currNode->next;
        }

        return *this;
    }


    Cluster &Cluster::operator+=(const Cluster &rhs) {
        LNodePtr newPoints;

        newPoints = rhs.points;
        while (newPoints) {
            this->add(newPoints->p);
            newPoints = newPoints->next;
        }

        LNodePtr currNode = this->points, nextNode, dup;
        while (currNode) {
            nextNode = currNode;
            while (nextNode->next != NULL) {
                if (currNode->p == nextNode->next->p) {
                    dup = nextNode->next;
                    nextNode->next = nextNode->next->next;
                    delete dup;
                    this->m_size--;
                } else {
                    nextNode = nextNode->next;
                }
            }
            currNode = currNode->next;
        }


        return *this;
    }


    Cluster &Cluster::operator-=(const Cluster &rhs) {
        Cluster intersect;

        LNodePtr curr = this->points,
                rhsCurr = rhs.points;
        while (curr) {
            rhsCurr = rhs.points;
            while (rhsCurr) {
                if (curr->p == rhsCurr->p) {
                    intersect.add(rhsCurr->p);
//                    rhsCurr = rhsCurr->next;
                }
                rhsCurr = rhsCurr->next;
            }
            curr = curr->next;
        }

        *this = intersect;
        return *this;
    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {
        Cluster intersect;

        LNodePtr lhsCurr = lhs.points,
                rhsCurr = rhs.points;

        while (rhsCurr) {
            lhsCurr = lhs.points;
            while (lhsCurr) {
                if (rhsCurr->p == lhsCurr->p) {
                    intersect.add(lhsCurr->p);
                }
                lhsCurr = lhsCurr->next;
            }
            rhsCurr = rhsCurr->next;
        }
        if (intersect.points == NULL)
            cout << "Intersection is empty.\n";
        else
            return intersect;

    }

    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs) {
        Cluster newCluster = lhs;

        // delete all duplicated points in the linked list
        LNodePtr currNode = newCluster.points, nextNode, dup;
        while (currNode) {
            nextNode = currNode;
            while (nextNode->next != NULL) {
                if (currNode->p == nextNode->next->p) {
                    dup = nextNode->next;
                    nextNode->next = nextNode->next->next;
                    delete dup;
                    newCluster.m_size--;
                } else {
                    nextNode = nextNode->next;
                }
            }
            currNode = currNode->next;
        }

        PointPtr matched = NULL;
        // find the matched point with the point rhs, if there is no matches, add it to the list
        currNode = newCluster.points, nextNode = NULL;
        while (currNode) {
            if (currNode->p == rhs) {
                matched = currNode->p;
                //currNode = currNode->next;
                break;
            }
            else {
                currNode = currNode->next;
            }
        }

        if (matched != rhs)
            newCluster.add(rhs);

        return newCluster;
    }

    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs) {
        return Cluster();
    }

    std::ostream &operator<<(std::ostream &os, const Cluster &c1) {

        LNodePtr n = c1.points;
        os << *(n->p) << " " << Cluster::POINT_CLUSTER_ID_DELIM << " " << Cluster::idGenerator << "\n";
        while (n->next) {
            n = n->next;
            os << *(n->p) << " " << Cluster::POINT_CLUSTER_ID_DELIM << " " << Cluster::idGenerator  <<  "\n";
        }
//        os << std::endl;
    }

    std::istream &operator>>(std::istream &istream, Cluster &c1) {
        PointPtr newPoint;
        std::string line;
        int dimension;  // to hold a number of dimensions for a point
        char delim = Clustering::Point::POINT_VALUE_DELIM;      // Point delimeter
        while (getline(istream, line)) {
            dimension = 0;

            // get point's dimenstion by counting the delimeter in the line
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == delim) {
                    dimension++;
                }
            }

            stringstream lineStream(line);
            newPoint = new Point(dimension + 1);
            lineStream >> *newPoint;
            c1.setPointDimension(dimension+1);
            c1.add(newPoint);
        }
        return istream;
    }

<<<<<<< HEAD
    void Cluster::computeCentroid() {
        int dim = m_PointDimension;
        Point  ptr(dim);
        for (LNodePtr curr = points; curr != NULL; curr = curr->next) {
            ptr+= *curr->p;
        }
        (ptr) / static_cast<double>(m_size);
        __centroid.set(ptr);
        __centroid.setValid(true);
//        cout << "\nComputeCentroid " << get__centroid() << endl;
    }

    LNodePtr Cluster::getPoints() const {
        return points;
    }

    Point Cluster::get__centroid() const {
        return __centroid.get();
=======
    Point Cluster::get__centroid() const {
        return *__centroid;
>>>>>>> origin/master
    }

    void Cluster::setCentroid(const Point &point) {
        static Point p = point;
        this->__centroid = &p;

<<<<<<< HEAD
        __centroid.set(point);
        __centroid.setValid(true);
    }
=======
        validCentroid = true;
>>>>>>> origin/master

    void Cluster::pickPoints(int k, PointPtr *pointArray) {
        int randPoint = rand() % k;
        __centroid.set(*pointArray[randPoint]);
    }

<<<<<<< HEAD
    static void generateID(){
//        __idGenerator ++;
//        unsigned int Cluster::__idGenerator = 1;

    }

}
=======
    void Cluster::computeCentroid() {
        int dim = this->getPointDimension();
//        __centroid = new Point(dim);
        for (LNodePtr curr = points; curr != NULL; curr = curr->next) {
            *__centroid += *curr->p;
        }
        *(__centroid) / static_cast<double>(m_size);
        cout << "Computed Centroid " << *__centroid << endl;
    }


    void Cluster::pickPoints(int k, PointPtr *pointArray) {
        // Get random point from pointArray
        int randPoint = rand() % k;

//        setCentroid(*pointArray[randPoint]);
        __centroid = pointArray[randPoint];
        cout << "pickPoint " << get__centroid() << endl;
    }
}
>>>>>>> origin/master
