#include <cmath>
#include <vector>
#include <iomanip>
#include <cassert>
#include <fstream>
#include <iostream>
#include "Exceptions.h"
#include "Point.h"


namespace Clustering {

    unsigned int Point::idGenerator = 1;

    Point::Point(unsigned int dims) {
        dim = dims;
        for (size_t i = 0; i < dims; i++) {
            m_values.push_back(0);
        }

        generatePoint_ID();
    }


    Point::Point(unsigned int dims, double *arr) {
        dim = dims;
        for (int i = 0; i < dims; ++i) {
            m_values.push_back(arr[i]);
        }
        generatePoint_ID();
    }


    Point::Point(const Point &copy) {
        dim = copy.dim;
        __id = copy.__id;

        for(auto it = copy.m_values.begin(); it != copy.m_values.end(); it++)
            m_values.push_back(*it);
    }

// Destructor
    Point::~Point() {
        idGenerator--;
        m_values.clear();
    }


    double Point::getValue(unsigned int i) const {
        return m_values[i];
    }

// return the object on the left side of the = sign
    Point &Point::operator=(const Point &rightSide) {
        if (this == &rightSide)
            return *this;
        else {
            // erase vector and then copy values from rhs
            m_values.clear();
            dim = rightSide.dim;
            __id = rightSide.__id;

            m_values= rightSide.m_values;

            return *this;
        }
    }


    bool operator<(const Point &p1, const Point &p2) {
        if (p1.dim != p2.dim)
            throw DimensionalityMismatchEx("Point <operator",p1.dim, p2.dim);


        for (unsigned int i = 0; i < p1.dim; ++i) {
            if (p1.m_values[i] < p2.m_values[i])
                return true;
            else if (p2.m_values[i] < p1.m_values[i])
                return false;
        }
        return false;
    }

    bool operator>(const Point &p1, const Point &p2) {
        if (p1.dim != p2.dim)
            throw DimensionalityMismatchEx("Point >operator", p1.dim, p2.dim);

        int iDim = p1.getDims();
        for (unsigned int i = 0; i < iDim; ++i) {
            if (p1.getValue(i) > p2.getValue(i))
                return true;
            else if (p2.getValue(i) > p1.getValue(i))
                return false;
        }
        return false;
    }


    bool operator>=(const Point &p1, const Point &p2) {
        if (p1.dim != p2.dim)
            throw DimensionalityMismatchEx("Point >=operator", p1.dim, p2.dim);

        int size = p1.getDims();
        for (unsigned int i = 0; i < size; ++i) {
            if (p1.getValue(i) >= p2.getValue(i))
                return true;
            else
                return false;
        }
    }

    const Point operator+(const Point &operand1, const Point &operand2) {
        if (operand1.dim != operand2.dim)
            throw DimensionalityMismatchEx("Point +operator", operand1.dim, operand2.dim);

        Point temp(operand1);
        for (unsigned int i = 0; i < temp.dim; ++i) {
            temp.m_values[i] = operand1.m_values[i] + operand2.m_values[i];
        }
        return temp;
    }


    const Point operator-(const Point &operand1, const Point &operand2) {
        if (operand1.getDims() != operand2.getDims())
            throw DimensionalityMismatchEx("Point -operator", operand1.getDims(), operand2.getDims());

        Point temp(operand1);
        for (unsigned int i = 0; i < temp.getDims(); ++i) {
            temp.m_values[i] = operand1.m_values[i] - operand2.m_values[i];
        }
        return temp;
    }


    Point &Point::operator*=(const double d) {
        for (int i = 0; i < dim; ++i) {
            m_values[i] *= d;

        }
        return *this;
    }

    Point &Point::operator/=(double d) {
        if (d == 0) {
            std::cout << "Error, attempting to divide by zero.\n";
            return *this;
        }
        for (unsigned int i = 0; i < dim; ++i) {
            assert(!m_values[i] == 0);
            m_values[i] /= d;
        }
        return *this;
    }

    const Point Point::operator*(double d)  {
        double t = 0;
        int dim = getDims();
        for (int i = 0; i < dim; ++i) {
            t = m_values[i] * d;
            m_values[i] = t;
        }
        return *this;
    }

    const Point Point::operator/(double d)  {
        if (d == 0) {
            std::cout << "Error! You can not divide by zero\n";
            return *this;
        }
        double t;
        for (unsigned int i = 0; i < dim; ++i) {
            t = m_values[i] / d;
            m_values[i] = t;
        }
        return *this;
    }

    Point &operator+=(Point &point, const Point &point1) {
        if (point.dim != point1.dim)
            throw DimensionalityMismatchEx("Point +=operator", point.dim, point1.dim);


        for (unsigned int i = 0; i < point1.dim; ++i) {
            point.m_values[i] += point1.m_values[i];
        }

        return point;
    }

    Point &operator-=(Point &point, const Point &point1) {
        if (point.dim != point1.dim)
            throw DimensionalityMismatchEx("Point -=operator", point.dim, point1.dim);

        for (int i = 0; i < point.dim; ++i) {
            point.m_values[i] -= point1.m_values[i];
        }
        return point;
    }

    bool operator==(const Point &point, const Point &point1) {
        if (point.dim != point1.dim)
            throw DimensionalityMismatchEx("Point ==operator", point.dim, point1.dim);


        bool isEqual = false;

        for (unsigned int i = 0; i < point.dim; ++i) {
            if (point.m_values[i] == point1.m_values[i] && point.__id == point1.__id) {
                isEqual = true;
            } else {
                return false;
            }
        }
        return isEqual;
    }

    bool operator!=(const Point &point, const Point &point1) {
        if (point.dim != point1.dim)
            throw DimensionalityMismatchEx("Point !=operator", point.dim, point1.dim);
        return !(point == point1);
    }

    double Point::distanceTo(const Point &point) const {
        if (dim != point.dim)
            throw DimensionalityMismatchEx("Point distanceTo", dim, point.dim);

        double distance = 0, d = 0;
        for (unsigned int i = 0; i < dim; ++i) {
            d += pow((point.m_values[i] - m_values[i]), 2);
        }
        distance = sqrt(d);
        return distance;
    }

    bool operator<=(const Point &point, const Point &point1) {
        if (point.dim != point1.dim)
            throw DimensionalityMismatchEx("Point <=operator", point.dim, point1.dim);

        int size = point.getDims();
        for (unsigned int i = 0; i < size; ++i) {
            if (point.getValue(i) <= point1.getValue(i))
                return true;
            else if (point1.getValue(i) >= point.getValue(i))
                return false;
        }
    }

    std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << std::fixed << std::setprecision(1);
        os << point.m_values[0];
        for (unsigned int j = 1; j < point.getDims(); ++j) {
            os  << Point::POINT_VALUE_DELIM<< " " << point.m_values[j];
        }
        os << "";
    }

    std::istream &operator>>(std::istream &istream, Point &point) {
        std::string line;
        int i = 0;
        while (getline(istream, line, ',')) {
            double d;
            d = std::stod(line);
            point.setValue(i, d);
            i++;
        }
        return istream;
    }


}
