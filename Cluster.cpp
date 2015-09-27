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
        while (newCurr != NULL) {
            LNodePtr newNode = new LNode;

            // get dimenstion of the copy Cluster's points
            // copy all values from Point and store them in arr

            int dim = rhs.points->p->getM_Dim();
            double arr[dim];
            for (int i = 0; i < dim; ++i) {
                arr[i] = newCurr->p->getvalues()[i];
            }
            PointPtr temp = new Point(dim, arr);
            newNode->p = temp;
            newNode->next = NULL;

            if (!this->points) {
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
    }

    void Cluster::add(const PointPtr &ptr) {
        LNodePtr newNode;                // to point to the new node
        LNodePtr curr = nullptr;         // to move thorugh the lsit

        // Allocate a new node and store ptr there.
        newNode = new LNode;
        int dim = ptr->getM_Dim();
        double arr[dim];
        for (int i = 0; i < dim; ++i) {
            arr[i] = ptr->getvalues()[i];
        }

        newNode->p = new Point(dim, arr);
        newNode->next = nullptr;
        if (!points) {
            points = newNode;
        } else {
            curr = points;
            while (curr->next) {
                curr = curr->next;
            }
            curr->next = newNode;
//            curr = curr->next;
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

                // get dimenstion of the copy Cluster's points
                // copy all values from Point and store them in arr
                int dim = rhs.points->p->getM_Dim();
                double arr[dim];
                for (int i = 0; i < dim; ++i) {
                    arr[i] = newCurr->p->getvalues()[i];
                }
                PointPtr temp = new Point(dim, arr);
                newNode->p = temp;
                newNode->next = NULL;

                if (!this->points) {
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
            delete delNode->p;
            delete delNode;
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


    PointPtr &Cluster::remove(const PointPtr &ptr) {
//        NodePtr delPtr = points;
//        NodePtr curr = points;


    }

    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {
        Cluster temp;
        temp.m_size = lhs.m_size + rhs.m_size;
        LNodePtr currLeft = lhs.points;
        LNodePtr currRight = rhs.points;
        LNodePtr currTemp = NULL;


        while (currLeft) {
            LNodePtr newNode = new LNode;
            newNode->p = currLeft->p;
            newNode->next = NULL;

            if (temp.points == NULL) {
                
                temp.points = newNode;
                currLeft = currLeft->next;
            } else {
                currTemp = temp.points;
                while (currTemp->next) {
                    currTemp = currTemp->next;
                }
                currTemp->next = newNode;
                currLeft = currLeft->next;
            }
        }

        while (currRight) {
            LNodePtr newNode = new LNode;
            newNode->p = currRight->p;
            newNode->next = NULL;

            currTemp = temp.points;
            while (currTemp->next) {
                currTemp = currTemp->next;
            }
            currTemp->next = newNode;
            currRight = currRight->next;
        }
        return temp;
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
}