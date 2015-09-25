#include "Cluster.h"
#include <iostream>
#include <cassert>

using namespace std;
namespace Clustering {

    Cluster::Cluster(const Cluster &rhs) {
        m_size = rhs.m_size;
        points = nullptr;
        NodePtr curr = nullptr;
        NodePtr newCurr = rhs.points;
        while (newCurr != NULL) {
            NodePtr newNode = new Node;
            
            // get dimenstion of the copy Cluster's points
            // copy all values from Point and store them in arr
            int dim = rhs.m_size;
            double arr[dim];
            for (int i = 0; i < dim; ++i) {
                arr[i] = newCurr->p->getvalues()[i];
            }
            PointPtr temp = new Point(dim,arr);
            newNode->p = temp;
            newNode->next = NULL;

            if (this->points == NULL) {
                points = newNode;
                cout << "\nCopy Added: " << *points->p << endl;

            }
            else {
                curr = points;
                curr->next = newNode;
                curr = curr->next;
                cout << "Copy Added: " << *curr->p << endl;
            }
            newCurr = newCurr->next;

        }
    }

    Cluster &Cluster::operator=(const Cluster &cluster) {
        if (this == &cluster)
            return *this;
        else {
            m_size = cluster.m_size;
            cout << "AAAAA" << *points->p << endl;
        }
        return *this;
    }

    void Cluster::add(const PointPtr ptr) {
        NodePtr newNode = new Node;
        NodePtr curr;
        newNode->p = ptr;
        newNode->next = NULL;
        if (points == NULL) {
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

// dtor
    Cluster::~Cluster() {
//        if (points == nullptr) {
//            delete points;
//        } else {
////            for (int i = 0; i < m_size; ++i) {
////                cout <<"Dereference\n";
////            }
//        }
//        delete points;


    }

    std::ostream &operator<<(std::ostream &os, const Cluster &c1) {
        NodePtr n = c1.points;

        // while node points to a node, travel to the list
        while (n) {
            os << *(n->p) << std::endl;
            n = n->next;
        }
    }

}