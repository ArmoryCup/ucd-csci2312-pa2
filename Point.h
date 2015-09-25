// A 3-dimensional point class!
// Coordinates are double-precision floating point.
#include <ostream>

#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H
namespace Clustering {

    class Point {

        int m_Dim;              // to hold dimension of a pointer
        double *values;   // to hold dimensions of array of double

    public:
        // Constructors
        Point();                                       // default constructor. It is two dimension pointer by default
        Point(const int);                              // constructor that takes an int for the dimension
        Point(const int, const double *);              // constructor that takes an int for the dimension
        //  and an array of doubles

        Point(const Point &);                           // copy constructor

        double *getvalues() const {
            return values;
        }

        void setM_Dim(int dim) {                        // set dimention for the Points
            Point::m_Dim = dim;
        }


        void setValue(int index, double value) {      // set value to the element of the array
            Point::values[index] = value;         // assign the selected element of the array to new value
        }

        // Destructor
        ~Point();

        // asignment overloaded operator
        Point &operator=(const Point &);

        // << overloading operator
        friend std::ostream &operator<<(std::ostream &os, const Clustering::Point &point);

        // Boolean overloading operators
        friend bool operator==(Point &p1, Point &p2);

        friend bool operator!=(Point &p1, Point &p2);

        friend bool operator<(Point &p1, Point &p2);

        friend bool operator>(Point &p1, Point &p2);

        friend bool operator<=(Point &p1, Point &p2);

        friend bool operator>=(Point &p1, Point &p2);


        // Arithmetic overloading operators
        friend const Point operator+(const Point &, const Point &);

        friend const Point operator-(const Point &, const Point &);

        friend const Point operator*(const Point &, const double);

        friend const Point operator/(const Point &, const double);

        Point &operator+=(const Point &);

        Point &operator-=(const Point &);

        Point &operator*=(const Point &);

        Point &operator*=(const double);

        Point &operator/=(const Point &);


        int getM_Dim() const { return m_Dim; }

        // this function return a double that approximates the distance between points.
        double distanceTo(Point &point);

    };
}
#endif // CLUSTERING_POINT_H
