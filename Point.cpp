#include <cmath>
#include <vector>
#include <iomanip>
#include <cassert>
#include <fstream>
#include <iostream>
#include "Exceptions.h"
#include "Point.h"


namespace Clustering {

    template<typename T, int dims>
    unsigned int Point<T, dims>::idGenerator = 1;

    template<typename T, int dims>
    Point<T, dims>::Point() {
        dim = dims;
        for (unsigned int i = 0; i < dims; i++) {
            m_values.push_back(0);
        }
        generatePoint_ID();
    };

//    template<typename T, int dims>
//    Point<T, dims>::Point(unsigned int d) {
//        dim = d;
//        for (int i = 0; i < d; ++i) {
//            m_values.push_back(0);
//        }
//        generatePoint_ID();
//    }


    template<typename T, int dims>
    Point<T, dims>::Point(T *arr) {
        dim = dims;
        for (int i = 0; i < dims; ++i) {
            m_values.push_back(arr[i]);
        }
        generatePoint_ID();
    }

    template<typename T, int dims>
    Point<T, dims>::Point(const Point<T, dims> &copy) {
        dim = copy.dim;
        __id = copy.__id;

        for (auto it = copy.m_values.begin(); it != copy.m_values.end(); it++)
            m_values.push_back(*it);
    }

// Destructor
    template<typename T, int dims>
    Point<T, dims>::~Point() {
        idGenerator--;
        m_values.clear();
    }


// return the object on the left side of the = sign
    template<typename T, int dims>
    Point<T, dims> &Point<T, dims>::operator=(const Point<T, dims> &rightSide) {
        if (this == &rightSide)
            return *this;
        else {
            // erase vector and then copy values from rhs
            m_values.clear();
//            dim = rightSide.dim;
            __id = rightSide.__id;

            m_values = rightSide.m_values;

            return *this;
        }
    }

    template<typename T, int dims>
    bool operator<(const Point<T, dims> &p1, const Point<T, dims> &p2) {
        if (p1.dim != p2.dim)
            throw DimensionalityMismatchEx("Point <operator", p1.dim, p2.dim);


        for (unsigned int i = 0; i < p1.dim; ++i) {
            if (p1.m_values[i] < p2.m_values[i])
                return true;
            else if (p2.m_values[i] < p1.m_values[i])
                return false;
        }
        return false;
    }

    template<typename T, int dims>
    bool operator>(const Point<T, dims> &p1, const Point<T, dims> &p2) {
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

    template<typename T, int dims>
    bool operator>=(const Point<T, dims> &p1, const Point<T, dims> &p2) {
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

    template<typename T, int dims>
    const Point<T, dims> operator+(const Point<T, dims> &operand1, const Point<T, dims> &operand2) {
        if (operand1.dim != operand2.dim)
            throw DimensionalityMismatchEx("Point +operator", operand1.dim, operand2.dim);

        Point<T, dims> temp(operand1);
        for (unsigned int i = 0; i < temp.dim; ++i) {
            temp.m_values[i] = operand1.m_values[i] + operand2.m_values[i];
        }
        return temp;
    }

    template<typename T, int dims>
    Point<T, dims> &operator+=(Point<T, dims> &point, const Point<T, dims> &point1) {
        if (point.dim != point1.dim)
            throw DimensionalityMismatchEx("Point +=operator", point.dim, point1.dim);

        for (unsigned int i = 0; i < point1.dim; ++i) {
            point.m_values[i] += point1.m_values[i];
        }

        return point;
    }

    template<typename T, int dims>
    Point<T, dims> &operator-=(Point<T, dims> &point, const Point<T, dims> &point1) {
        if (point.dim != point1.dim)
            throw DimensionalityMismatchEx("Point -=operator", point.dim, point1.dim);

        for (int i = 0; i < point.dim; ++i) {
            point.m_values[i] -= point1.m_values[i];
        }
        return point;
    }

    template<typename T, int dims>
    const Point<T, dims> operator-(const Point<T, dims> &operand1, const Point<T, dims> &operand2) {
        if (operand1.getDims() != operand2.getDims())
            throw DimensionalityMismatchEx("Point -operator", operand1.getDims(), operand2.getDims());

        Point<T, dims> temp(operand1);
        for (unsigned int i = 0; i < temp.getDims(); ++i) {
            temp.m_values[i] = temp.m_values[i] - operand2.m_values[i];
        }
        return temp;
    }

    template<typename T, int dims>
    Point<T, dims> &Point<T, dims>::operator*=(const T d) {
        for (int i = 0; i < dim; ++i) {
            m_values[i] *= d;

        }
        return *this;
    }

    template<typename T, int dims>
    Point<T, dims> &Point<T, dims>::operator/=(T d) {
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

    template<typename T, int dims>
    const Point<T, dims> Point<T, dims>::operator*(T d) {
        double t = 0;
        int dim = getDims();
        for (int i = 0; i < dim; ++i) {
            t = m_values[i] * d;
            m_values[i] = t;
        }
        return *this;
    }

    template<typename T, int dims>
    const Point<T, dims> Point<T, dims>::operator/(T d) {
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


    template<typename T, int dims>
    bool operator==(const Point<T, dims> &point, const Point<T, dims> &point1) {
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

    template<typename T, int dims>
    bool operator!=(const Point<T, dims> &point, const Point<T, dims> &point1) {
        if (point.dim != point1.dim)
            throw DimensionalityMismatchEx("Point !=operator", point.dim, point1.dim);
        return !(point == point1);
    }

    template<typename T, int dims>
    T Point<T, dims>::distanceTo(const Point<T, dims> &point) const {
        if (dim != point.dim)
            throw DimensionalityMismatchEx("Point distanceTo", dim, point.dim);

        double distance = 0, d = 0;
        for (unsigned int i = 0; i < dim; ++i) {
            d += pow((point.m_values[i] - m_values[i]), 2);
        }
        distance = sqrt(d);
        return distance;
    }

    template<typename T, int dims>
    bool operator<=(const Point<T, dims> &point, const Point<T, dims> &point1) {
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

    template<typename D, int dims>
    std::ostream &operator<<(std::ostream &os, const Point<D, dims> &point) {
        os << std::fixed << std::setprecision(1);
        os << point.m_values[0];
        for (unsigned int j = 1; j < point.getDims(); ++j) {
            os << Point<D, dims>::POINT_VALUE_DELIM << " " << point.m_values[j];
        }
        os << "";
    }

    template<typename T, int dims>
    std::istream &operator>>(std::istream &istream, Point<T, dims> &point) {
        std::string line;
        int i = 0;
        while (getline(istream, line, ',')) {
            double d;
            d = std::stod(line);
//            point.setValue(i, d);
            point[i] = d;
            i++;
        }
        return istream;
    }


}
