#include "Cluster.h"
#include <iostream>
#include <cassert>

using namespace std;
namespace Clustering {

    Cluster::Cluster(const Cluster &rhs) {
        m_size = rhs.m_size;
        LNodePtr newNode;                // to point to the new node
        LNodePtr curr = nullptr;         // to move thorugh the lsit

        LNodePtr copy = rhs.points;
        this->points = nullptr;
        while (copy) {
            // Allocate a new node and store ptr there.
            newNode = new LNode;

            newNode->p = copy->p;
            newNode->next = nullptr;
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
        LNodePtr curr = nullptr;         // to move thorugh the lsit

        // Allocate a new node and store ptr there.
        newNode = new LNode;
        newNode->p = ptr;
        newNode->next = nullptr;
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
        LNodePtr currNode = points, nextNode;
        PointPtr dup;
        while (currNode) {
            nextNode = currNode;
            while (nextNode->next!=NULL) {
                if (currNode->p > nextNode->next->p) {
                    dup = nextNode->next->p;
                    nextNode->next->p=currNode->p;
                    currNode->p=dup;

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
                LNodePtr delNode = points;
                points = points->next;
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
//            if (delNode->p != nullptr)
//                delete delNode->p;
            delete delNode;
        }
//        cout << "Dereferencing\n";
    }

    PointPtr &Cluster::remove(const PointPtr &ptr) {
        PointPtr delPtr = nullptr;
        LNodePtr delNode = nullptr;
        LNodePtr curr = points;
        while (curr) {
            if (curr->p == ptr) {
                delPtr = ptr;
                delNode = curr;
                points = curr->next;
                delete delNode;
            } else {
                // Move to the next node
                curr = curr->next;
            }
        }
        return delPtr;
        cout << "The pointer is not in the Cluster!\n";
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
        int size = lhs.points->p->getM_Dim();
        LNodePtr lCurr = lhs.points;
        LNodePtr rCurr = rhs.points;

        PointPtr left, right;

        while (lCurr) {
            left = lCurr->p;
            right = rCurr->p;
            for (int i = 0; i < size; ++i) {
                if (left->getvalues()[i] == right->getvalues()[i]) {
                    return true;
                }
                else
                    return false;
            }
            lCurr = lCurr->next;
            rCurr = rCurr->next;
        }
    }


    std::ostream &operator<<(std::ostream &os, const Cluster &c1) {
        LNodePtr n = c1.points;
        // while node points to a node, travel to the list
        os << *(n->p) << endl;
        while (n->next) {
            n = n->next;
            os << *(n->p) << endl;
        }
    }

    Cluster &Cluster::operator+=(const Point &rhs) {

        LNodePtr newNode;                // to point to the new node
        LNodePtr curr = nullptr;         // to move thorugh the lsit

        PointPtr newPoint = new Point(rhs);
        add(newPoint);
        return *this;
    }

    Cluster &Cluster::operator-=(const Point &rhs) {
        LNodePtr curr = points, prev = points, del;
        int dim = points->p->getM_Dim();
        int i = 0;
        while (curr && curr->next != nullptr) {
            if (curr->p->getvalues()[i] == rhs.getvalues()[i]) {
                del = curr;
                if (curr->next == NULL) {
                    curr = prev;
                    curr->next = NULL;
                    delete del->p;
                    delete del;
                } else {
                    curr = curr->next;
                    prev->next = prev->next->next;
                    delete del->p;
                    delete del;
                }


            } else {
                prev = curr;
                curr = curr->next;
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
        Cluster *intersect = new Cluster;

        LNodePtr curr = this->points,
                rhsCurr = rhs.points;
        while (curr) {
            rhsCurr = rhs.points;
            while (rhsCurr) {
                if (curr->p == rhsCurr->p) {
                    intersect->add(rhsCurr->p);
//                    rhsCurr = rhsCurr->next;
                }
                rhsCurr = rhsCurr->next;
            }
            curr = curr->next;
        }


        this->~Cluster();
        return *intersect;
    }
}