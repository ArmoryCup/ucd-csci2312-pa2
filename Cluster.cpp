#include "Cluster.h"
#include <iostream>
#include <cassert>

using namespace std;
namespace Clustering {

    Cluster::Cluster(const Cluster &rhs) {
        m_size = rhs.m_size;
        points = NULL;
        LNodePtr curr = NULL;
        LNodePtr newCurr = rhs.points;
        while (newCurr) {
            add(newCurr->p);
            newCurr = newCurr->next;
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
        m_size++;
    }


    Cluster &Cluster::operator=(const Cluster &rhs) {
        if (this == &rhs)
            return *this;
        else {
            points = NULL;
            LNodePtr curr = NULL;
            LNodePtr newCurr = rhs.points;
            while (newCurr != NULL) {
                LNodePtr newNode = new LNode;
                newNode->p = newCurr->p;
                newNode->next = NULL;

                if (!points) {
                    points = newNode;
                    newCurr = newCurr->next;
                }
                else {
                    curr = points;
                    while (curr->next) {
                        curr = curr->next;
                    }
                    curr->next = newNode;
                    newCurr = newCurr->next;
                }
            }
            return *this;
        }
    }


    // dtor
    Cluster::~Cluster() {
        while (points != NULL) {
            LNodePtr delNode = points;
            points = points->next;
            if (delNode->p != nullptr)
                delete delNode->p;
            delete delNode;
        }
    }

    PointPtr &Cluster::remove(const PointPtr &ptr) {
        PointPtr delPtr = nullptr;
        LNodePtr curr = points;

        while (curr) {
            if (curr->p == ptr) {
                delPtr = ptr;
                points->next = curr->next;
                delete curr;
            } else {
                // Move to the next node
                curr = curr->next;
            }
            return delPtr;
        }

        cout << "The pointer is not in the Cluster!\n";
    }

    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {
        Cluster newCluster;
//        temp.m_size = lhs.m_size ;
//        LNodePtr currLeft = lhs.points;
//        LNodePtr currRight = rhs.points;
//        PointPtr pRemove;

        for (LNodePtr curr = lhs.points; curr != nullptr; curr = curr->next) {

            for (LNodePtr curr2 = rhs.points; curr2 != nullptr; curr2 = curr2->next) {
                if (curr->p != curr2->p) {
                    newCluster.add(curr2->p);
                }
            }


        }
//        while (currLeft) {
//
//            newCluster.add(currLeft->p);
//            currLeft = currLeft->next;
//        }
//        currLeft = lhs.points;
//        while(currRight->p== currLeft->p){
//            currRight = currRight->next;
//        }
//        for (LNodePtr curr = currRight; curr != nullptr; curr = curr->next) {
//            if (currLeft->p != curr->p) {
//                newCluster.add(curr->p);
//
//            }
//        }
//        while (currRight) {
//            if (currRight->p != currLeft->p) {
//                newCluster.add(currRight->p);
//                currRight = currRight->next;
//            }
//            else
//                currRight = currRight->next;
//        }
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
        LNodePtr curr = points;
        while (curr) {
            if (curr->p== &rhs) {
                points->next = curr->next;
                delete curr->p;
                delete curr;
            } else {
                curr = curr->next;
            }
        }
        return *this;
    }

    Cluster &Cluster::operator+=(const Cluster &rhs) {

        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &rhs) {
        return *this;
    }
}