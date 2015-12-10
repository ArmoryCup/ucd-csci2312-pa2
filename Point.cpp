#include <cmath>
#include "Point.h"
#include <iostream>
#include <iomanip>

namespace Clustering {

    Point::Point(const int dims) {
        dim = dims;

        values = new double[dims+1];
        for (unsigned int i = 0; i < dims; i++) {
            values[i] = 0;
        }
    }

    Point::Point(int dims, double *arr) {
        dim = dims;
        values = new double[dims];
        for (int i = 0; i < dims; i++) {
            values[i] = arr[i];
        }
    }

    Point::Point(const Point &copy) {

        dim = copy.dim;
        values = new double[dim];
        for (int i = 0; i <= dim; ++i) {
            values[i] = copy.values[i];
        }
    }

// Destructor
// No dynamic allocation, so nothing to do; if omitted, generated automatically
    Point::~Point() {
//        if (values != nullptr && values == NULL) {
        if (values != NULL) {
            dim = 0;
            delete[] values;
        }
    }

    double Point::getValue(int i) const {
        return values[i];
    }

    std::ostream &operator<<(std::ostream &os, const Point &point) {

        if(point.values == nullptr)
            std::cout <<"Points are empty\n";

        os << std::fixed << std::setprecision(1);
        os  << point.values[0];
        for (int i = 1; i < point.dim+1; i++) {
            os << ", " << point.values[i];
//            os << point.values[i] << ", ";
        }
        os.flush();

    }

// return the object on the left side of the = sign
    Point &Point::operator=(const Point &rightSide) {
        if (this == &rightSide)
            return *this;
        else {
            delete[] values;
            dim = rightSide.dim;
            values = new double[dim];
            for (int i = 0; i <= dim; ++i) {
                values[i] = rightSide.values[i];
            }
            return *this;
        }
    }


    bool operator<(const Point &p1, const Point &p2) {
        bool isLess = false;
        for (int i = 0; i <= p1.dim; ++i) {
            if (p1.values[i] < p2.values[i] || p1.values[i] == p2.values[i]) {
                isLess = true;
            }
            else if (p2.values[i] < p1.values[i])
                isLess = true;
            else {
                isLess = false;
                break;
            }
        }
        return isLess;
    }

    bool operator>(const Point &p1, const Point &p2) {
        int iDim = p1.getDims();
        for (int i = 0; i < iDim; ++i) {
            if (p1.getValue(i) > p2.getValue(i))
                return true;
            else if (p2.getValue(i) > p1.getValue(i))
                return false;
        }
        return false;
    }


    bool operator>=(const Point &p1, const Point &p2) {
        int size = p1.getDims();
        for (int i = 0; i < size; ++i) {
            if (p1.getValue(i) >= p2.getValue(i))
                return true;
            else
                return false;
        }
    }

    const Point operator+(const Point &operand1, const Point &operand2) {
        Point temp(operand1);

        for (int i = 0; i <= temp.dim; ++i) {
            temp.values[i] = operand1.values[i] + operand2.values[i];
        }
        return temp;
    }

    const Point operator-(const Point &operand1, const Point &operand2) {
        Point temp(operand1);
//        operand1.~Point();

        for (int i = 0; i <= temp.dim; ++i) {
            temp.values[i] = operand1.values[i] - operand2.values[i];
        }
        return temp;
    }


    Point &Point::operator*=(const double d) {
        for (int i = 0; i <= dim; ++i) {
            values[i] *= d;
        }
        return *this;
    }

    Point &Point::operator/=(double d) {
        if (d == 0) {
            std::cout << "Error, attempting to divide by zero.\n";
            return *this;
        }
        for (int i = 0; i <= dim; ++i) {
            values[i] /= d;
        }
        return *this;
    }

    const Point Point::operator*(double d) const {
        Point temp = *this;
        for (int i = 0; i <= temp.getDims(); ++i) {

            temp.values[i] = values[i] * d;
        }
        return temp;
    }

    const Point Point::operator/(double d) const {
        if (d == 0) {
            std::cout << "Error! You can not divide by zero\n";
            return *this;
        }
        Point tempPoint = *this;

        double temp = 0;
        for (int i = 0; i <= dim; ++i) {
            temp = tempPoint.values[i] / d;
            values[i] = temp;

        }


        return *this;
    }

    Point &operator+=(Point &point, const Point &point1) {

        for (int i = 0; i <= point.dim; ++i) {
            point.values[i] += point1.values[i];
        }

        return point;
    }

    Point &operator-=(Point &point, const Point &point1) {
        for (int i = 0; i <= point.dim; ++i) {
            point.values[i] -= point1.values[i];
        }
        return point;
    }

    bool operator==(const Point &point, const Point &point1) {
        bool equal = false;
        for (int i = 0; i <= point.dim; ++i) {
            if (point.values[i] == point1.values[i]) {
                equal = true;
            } else {
                return false;
                break;
            }
        }

        return equal;

    }

    bool operator!=(const Point &point, const Point &point1) {
        return !(point == point1);
    }

    double Point::distanceTo(const Point &point) const {

        double distance = 0;
        double d = 0;
        for (int i = 0; i <= dim; ++i) {
            d += pow((point.getValue(i) - values[i]), 2);
        }
        distance = sqrt(d);
        return distance;
        return 0;
    }


    bool operator<=(const Point &point, const Point &point1) {
        int size = point.getDims();
        for (int i = 0; i < size; ++i) {
            if (point.getValue(i) <= point1.getValue(i))
                return true;
            else if (point1.getValue(i) >= point.getValue(i))
                return false;
        }
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
