#include "Cluster.h"
#include <iostream>
#include <cassert>

using namespace std;
namespace Clustering {

    Cluster::Cluster(const Cluster &rhs) {
        this->points = NULL;
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
        Cluster newCluster;
        LNodePtr curr1, curr2, dup;

        curr1 = lhs.points, curr2 = rhs.points;
        while (curr1) {
            newCluster.add(curr1->p);
            curr1 = curr1->next;
        }
        while (curr2) {
            newCluster.add(curr2->p);
            curr2 = curr2->next;
        }

        LNodePtr ptr1 = newCluster.points,
                ptr2;
        while (ptr1 != NULL ) {
            ptr2 = ptr1;
            while (ptr2->next != NULL) {
                if (ptr1->p == ptr2->next->p) {
                    dup = ptr2->next;
                    ptr2->next = ptr2->next->next;
                    free(dup);
                } else {
                    ptr2 = ptr2->next;
                }
            }
            ptr1 = ptr1->next;
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
        LNodePtr curr = points;
        LNodePtr newNode = new LNode;
        PointPtr ptr = new Point(rhs);
        newNode->p = ptr;
        newNode->next = NULL;
        int i = 0;
        while (curr) {
            if (curr->p->getvalues()[i] == rhs.getvalues()[i]) {
                points->next = curr->next;
                delete curr->p;
                delete curr;
            } else {
                i++;
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