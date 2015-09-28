#include <cmath>
#include "Point.h"
#include <cassert>

namespace Clustering {
    Point::Point() {
        m_Dim = 2;
        values = new double[m_Dim];
        for (int i = 0; i < m_Dim; ++i) {
            values[i] = 0;
        }
    }

    Point::Point(const int dims) {
        m_Dim = dims;
        values = new double[dims];
        for (size_t i = 0; i < dims; i++) {
            values[i] = 0;
        }
    }

    Point::Point(const int dims, const double *arr) {
        m_Dim = dims;
        values = new double[dims];
        for (int i = 0; i < dims; i++) {
            values[i] = arr[i];
        }
    }

    Point::Point(const Point &copy) {

        m_Dim = copy.m_Dim;
        values = new double[m_Dim];
        for (int i = 0; i < m_Dim; ++i) {
            values[i] = copy.values[i];
        }
    }

// Destructor
// No dynamic allocation, so nothing to do; if omitted, generated automatically
    Point::~Point() {
        if(values!= nullptr) {
            delete[] values;
            values = NULL;
        }
    }

// this function return a double that approximates the distance between the two points.
    double Point::distanceTo(Point &point) {

        double distance;
        double d;
        for (int i = 0; i < m_Dim; ++i) {
            d += pow((point.values[i] - values[i]), 2);
        }
        distance = sqrt(d);
        return distance;
    }

    std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << "(" << point.values[0];
        for (int i = 1; i < point.m_Dim; i++) {
            os << ", " << point.values[i];
        }
        os << ")";

    }

// return the object on the left side of the = sign
    Point &Point::operator=(const Point &rightSide) {
        if (this == &rightSide)
            return *this;
        else {
            delete[] values;
            m_Dim = rightSide.m_Dim;
            values = new double[m_Dim];
            for (int i = 0; i < m_Dim; ++i) {
                values[i] = rightSide.values[i];
            }
            return *this;
        }
    }

    bool operator==(Point &p1, Point &p2) {

        for (int i = 0; i < p1.m_Dim; ++i) {
            if (p1.values[i] == p2.values[i])
                return true;
            else return false;
        }

    }

    bool operator!=(Point &p1, Point &p2) {
        return !(p1 == p2);
    }

    bool operator<(Point &p1, Point &p2) {

        for (int i = 0; i < p1.m_Dim; ++i) {
            if (p1.values[i] < p2.values[i])
                return true;
            else if (p2.values[i] < p1.values[i])
                return false;
            else return false;
        }
    }

    bool operator>(Point &p1, Point &p2) {
        for (int i = 0; i < p1.m_Dim; ++i) {
            if (p1.values[i] > p2.values[i])
                return true;
            else if (p2.values[i] > p1.values[i])
                return false;
            else return false;
        }
    }

    bool operator<=(Point &p1, Point &p2) {
        for (int i = 0; i < p1.getM_Dim(); ++i) {
            if (p1.values[i] <= p2.values[i])
                return true;
            else if (p2.values[i] > p1.values[i])
                return false;
            else return false;
        }
    }

    bool operator>=(Point &p1, Point &p2) {
        for (int i = 0; i < p1.m_Dim; ++i) {
            if (p1.values[i] >= p2.values[i])
                return true;
            else
                return false;
        }
    }

    const Point operator+(const Point &operand1, const Point &operand2) {
        Point temp(operand1);

        for (int i = 0; i < temp.m_Dim; ++i) {
            temp.values[i] = operand1.values[i] + operand2.values[i];
        }
        return temp;
    }

    const Point operator-(const Point &operand1, const Point &operand2) {
        Point temp(operand1);

        for (int i = 0; i < temp.m_Dim; ++i) {
            temp.values[i] = operand1.values[i] - operand2.values[i];
        }
        return temp;
    }

    const Point operator*(const Point &right, const double numb) {
        Point temp(right);
        for (int i = 0; i < temp.m_Dim; ++i) {

            temp.values[i] = right.values[i] * numb;
        }
        return temp;
    }

    const Point operator/(const Point &right, const double numb) {
        Point temp(right);
        for (int i = 0; i < temp.m_Dim; ++i) {

            assert(!temp.values[i] == 0);
            temp.values[i] = right.values[i] / numb;
        }
        return temp;

    }


    Point &Point::operator+=(const Point &right) {
        for (int i = 0; i < m_Dim; ++i) {
            values[i] += right.values[i];
        }
        return *this;

    }

    Point &Point::operator-=(const Point &right) {

        for (int i = 0; i < m_Dim; ++i) {
            values[i] -= right.values[i];
        }
        return *this;
    }

    Point &Point::operator*=(const Point &right) {

        for (int i = 0; i < m_Dim; ++i) {
            values[i] *= right.values[i];
        }
        return *this;
    }

    Point &Point::operator/=(const Point &right) {

        for (int i = 0; i < m_Dim; ++i) {
            assert(!values[i] == 0);
            values[i] /= right.values[i];
        }
        return *this;
    }

    Point &Point::operator*=(const double d) {
        for (int i = 0; i < m_Dim; ++i) {
            values[i] *= d;
        }
        return *this;
    }
}