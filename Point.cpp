#include <cmath>
#include "Point.h"
#include <cassert>

namespace Clustering {
    Point::Point() {
        m_Dim = 2;
        m_arrDoubles = new double[m_Dim];
        for (int i = 0; i < m_Dim; ++i) {
            m_arrDoubles[i] = 0;
        }
    }

    Point::Point(const int dims) {

        m_Dim = dims;
        m_arrDoubles = new double[dims];
        for (size_t i = 0; i < dims; i++) {
            m_arrDoubles[i] = 0;
        }
    }

    Point::Point(const int dims, const double *arr) {
        m_Dim = dims;
        m_arrDoubles = new double[m_Dim];
        for (int i = 0; i < m_Dim; i++) {
            m_arrDoubles[i] = arr[i];
        }
    }

    Point::Point(const Point &copy) {

        m_Dim = copy.m_Dim;
        m_arrDoubles = new double[m_Dim];
        for (int i = 0; i < m_Dim; ++i) {
            m_arrDoubles[i] = copy.m_arrDoubles[i];
        }
    }

// Destructor
// No dynamic allocation, so nothing to do; if omitted, generated automatically
    Point::~Point() {
        delete[] m_arrDoubles;
    }

// this function return a double that approximates the distance between the two points.
    double Point::distanceTo(Point &point) {

        double distance;

        return distance;
    }

    double Point::distanceTo(int dim) {
        double a, b, c;
        a = m_arrDoubles[0];
        b = m_arrDoubles[1];
        c = m_arrDoubles[2];
    }

    std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << "(" << point.getM_arrDoubles()[0];
        for (int i = 1; i < point.getM_Dim(); i++) {
            os << ", " << point.getM_arrDoubles()[i];
        }
        os << ")";

    }

// return the object on the left side of the = sign
    Point &Point::operator=(const Point &rightSide) {
        if (this == &rightSide)
            return *this;
        else {

            delete[] m_arrDoubles;
            m_Dim = rightSide.getM_Dim();
            m_arrDoubles = new double[m_Dim];
            for (int i = 0; i < this->getM_Dim(); ++i) {
                m_arrDoubles[i] = rightSide.m_arrDoubles[i];
            }
            return *this;
        }
    }

    bool operator==(Point &p1, Point &p2) {

        for (int i = 0; i < p1.getM_Dim(); ++i) {
            if (p1.m_arrDoubles[i] == p2.getM_arrDoubles()[i])
                return true;
        }
    }

    bool operator!=(Point &p1, Point &p2) {
        return !(p1 == p2);
    }

    bool operator<(Point &p1, Point &p2) {

        for (int i = 0; i < p1.getM_Dim(); ++i) {
            if (p1.m_arrDoubles[i] < p2.getM_arrDoubles()[i])
                return true;
            else if (p2.getM_arrDoubles()[i] > p1.m_arrDoubles[i])
                return false;
            else return false;
        }
    }

    bool operator>(Point &p1, Point &p2) {
        for (int i = 0; i < p1.getM_Dim(); ++i) {
            if (p1.m_arrDoubles[i] > p2.getM_arrDoubles()[i])
                return true;
            else if (p2.getM_arrDoubles()[i] > p1.m_arrDoubles[i])
                return false;
            else return false;
        }
    }

    bool operator<=(Point &p1, Point &p2) {
        for (int i = 0; i < p1.getM_Dim(); ++i) {
            if (p1.m_arrDoubles[i] <= p2.getM_arrDoubles()[i])
                return true;
            else if (p2.getM_arrDoubles()[i] > p1.m_arrDoubles[i])
                return false;
            else return false;
        }
    }

    bool operator>=(Point &p1, Point &p2) {
        for (int i = 0; i < p1.getM_Dim(); ++i) {
            if (p1.m_arrDoubles[i] >= p2.getM_arrDoubles()[i])
                return true;
            else
                return false;
        }
    }

    const Point operator+(const Point &operand1, const Point &operand2) {
        Point temp(operand1);

        for (int i = 0; i < temp.m_Dim; ++i) {
            temp.m_arrDoubles[i] = operand1.getM_arrDoubles()[i] + operand2.getM_arrDoubles()[i];
        }

        return temp;
    }

    const Point operator-(const Point &operand1, const Point &operand2) {
        Point temp(operand1);

        for (int i = 0; i < temp.m_Dim; ++i) {
            temp.m_arrDoubles[i] = operand1.getM_arrDoubles()[i] - operand2.getM_arrDoubles()[i];
        }
        return temp;
    }

    const Point operator*(const Point &right, const double numb) {
        Point temp(right);
        for (int i = 0; i < temp.m_Dim; ++i) {

            temp.m_arrDoubles[i] = right.m_arrDoubles[i] * numb;
        }
        return temp;
    }

    const Point operator/(const Point &right, const double numb) {
        Point temp(right);
        for (int i = 0; i < temp.m_Dim; ++i) {

            assert(!temp.m_arrDoubles[i] == 0);
            temp.m_arrDoubles[i] = right.m_arrDoubles[i] / numb;
        }
        return temp;

    }


    Point &Point::operator+=(const Point &right) {
        for (int i = 0; i < m_Dim; ++i) {
            m_arrDoubles[i] += right.m_arrDoubles[i];
        }
        return *this;

    }

    Point &Point::operator-=(const Point &right) {

        for (int i = 0; i < m_Dim; ++i) {
            m_arrDoubles[i] -= right.m_arrDoubles[i];
        }
        return *this;
    }

    Point &Point::operator*=(const Point &right) {

        for (int i = 0; i < m_Dim; ++i) {
            m_arrDoubles[i] *= right.m_arrDoubles[i];
        }
        return *this;
    }

    Point &Point::operator/=(const Point &right) {

        for (int i = 0; i < m_Dim; ++i) {
            assert(!m_arrDoubles[i] == 0);
            m_arrDoubles[i] /= right.m_arrDoubles[i];
        }
        return *this;
    }

    Point &Point::operator*=(const double d) {
        for (int i = 0; i < m_Dim; ++i) {
            m_arrDoubles[i] *= d;
        }
        return *this;
    }
}