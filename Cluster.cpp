#include <iostream>
#include <fstream>
#include <sstream>

#include "Point.h"
#include "Cluster.h"

using namespace std;
namespace Clustering {

    Cluster::Cluster(const Cluster &rhs) {

        if (rhs.m_size == 0) {
            m_size = 0;
            points = NULL;
            return;
        }

        m_size = rhs.m_size;
//        LNodePtr curr = NULL;         // to move thorugh the lsit

        LNodePtr rhsNode = rhs.points;
        this->points = NULL;
        while (rhsNode) {

            LNodePtr newNode = new LNode;
            newNode->p = rhsNode->p;
            newNode->next = NULL;
            if (!points)
                points = newNode;
            else {
                LNodePtr lhsCurr = points;
                while (lhsCurr->next) {
                    lhsCurr = lhsCurr->next;
                }
                lhsCurr->next = newNode;

            }

            rhsNode = rhsNode->next;

            // Allocate a new node and store ptr there.
//            LNodePtr newNode = new LNode;

//            newNode->p = rhsNode->p;
//            newNode->next = NULL;
//            if (!points) {
//                points = newNode;
//            } else {
//                curr = points;
//                while (curr->next) {
//                    curr = curr->next;
//                }
//                curr->next = newNode;
//            }
        }
    }

    void Cluster::add(const PointPtr &ptr) {
        LNodePtr curr = NULL;         // to move through the list

        // Allocate a new node and store ptr there.
        LNodePtr newNode = new LNode;
        newNode->p = ptr;
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
            delete delNode;
            delNode = NULL;
        }
    }

    const PointPtr &Cluster::remove(const PointPtr &ptr) {

        if (m_size == 0) {
            cout << "Error! Point is not found.\n";
            return ptr;
        }
        if (ptr->getDims() == 0) {
            return ptr;
        }

        LNodePtr curr = points;
        while (curr != NULL) {
            if (curr->p == ptr) {
//                delete curr->p;
//                curr->p = NULL;
                curr->p->~Point();
                curr = curr->next;

                m_size--;
            }
            else
                curr = curr->next;

        }

        return ptr;
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
        bool isEqual = false;

        if (lhs.m_size == 0 && rhs.m_size == 0) {
            return true;
        }


        else if (lhs.m_size > 0 && rhs.m_size > 0) {

            int size = lhs.points->p->getDims();
            LNodePtr lCurr = lhs.points;
            LNodePtr rCurr = rhs.points;
            PointPtr left, right;

            while (lCurr) {
                left = lCurr->p;
                right = rCurr->p;
                for (int i = 0; i < size; ++i) {
                    if (left->getValue(i) == right->getValue(i)) {
                        isEqual = true;
                    }
                    else {
                        isEqual = false;
                        break;
                    }
                }
                lCurr = lCurr->next;
                rCurr = rCurr->next;
            }
        }
        return isEqual;
    }


    std::ostream &operator<<(std::ostream &os, const Cluster &c1) {

        LNodePtr n = c1.points;
//        os << *(n->p) << "\n";
//        while (n->next) {
//            n = n->next;
//            os << *(n->p) << " ";
//        }
//        os << std::endl;

        while (n) {
            os << *(n->p) << "\n";
            n = n->next;
        }
    }


    Cluster &Cluster::operator+=(const Point &rhs) {

        PointPtr newPoint = new Point(rhs);
        add(newPoint);
        return *this;
    }

    Cluster &Cluster::operator-=(const Point &rhs) {
        m_size--;

        if (points->next == NULL) {
            delete points;
            points = NULL;
            return *this;

        }

        LNodePtr currNode, delNode;
        int dim = points->p->getDims();
        bool isEqual = false;
        bool flag = false;
        currNode = points;

        while (currNode) {
            if (currNode->p == &rhs) {
                delNode = currNode;
                currNode = currNode->next;
                delete delNode;
                delNode = NULL;
            }
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
                }
                rhsCurr = rhsCurr->next;
            }
            curr = curr->next;
        }

        if (intersect.m_size == rhs.m_size) {
            this->m_size = 0;
            this->~Cluster();
        }

        else if (intersect.m_size > 0)
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

//        while (lhsCurr) {
//            rhsCurr = rhs.points;
//            while (rhsCurr) {
//                if (lhsCurr->p == rhsCurr->p) {
//                    intersect.add(rhsCurr->p);
//                }
//                    rhsCurr = rhsCurr->next;
//            }
//            lhsCurr = lhsCurr->next;
//        }

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
        Cluster tempCluster = lhs;
        LNodePtr curr = tempCluster.points;
        while (curr) {
            if (curr->p == rhs) {
                if (rhs->getDims() != 0){
                    curr->p->~Point();
                    tempCluster.m_size--;
                }

            }
            curr = curr->next;

        }
        return tempCluster;
    }

//    std::istream &operator>>(std::istream &istream, Cluster &c1) {
//        std::string line;
//        int dimension;  // to hold a number of dimensions for a point
//        while (getline(istream, line)) {
//            dimension = 1;
//
//                stringstream lineStream(line);
//                Point newPoint(dimension);
//
//                lineStream >> newPoint;
//                c1.add(newPoint);
//        }
//        return istream;
//    }
    std::istream &operator>>(std::istream &istream, Clustering::Cluster &c1) {


        std::string line;
        int dimension;  // to hold a number of dimensions for a point
        while (getline(istream, line)) {
            dimension = 1;

            // get point's dimenstion by counting the delimeter in the line
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == ',') {
                    dimension++;
                }
            }

            stringstream lineStream(line);
            Point *newPoint = new Point(dimension);

            lineStream >> *newPoint;
            c1.add(newPoint);

        }
        return istream;
    }
}