// A 3-dimensional point class!
// Coordinates are double-precision floating point.
#include <ostream>

#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H
namespace Clustering {
    class Point {
        int dim;        // number of dimensions of the point
        double *values; // values of the point's dimensions

    public:
        Point(int);
        Point(int,double *);

        // Big three: cpy ctor, overloaded operator=, dtor
        Point(const Point &);
        Point &operator=(const Point &);
        ~Point();

        // Accessors & mutators
        int getDims() const { return dim; }
        void setValue(int index, double value){
            values[index] = value;
        }
        double getValue(int) const;

        // Functions
        double distanceTo(const Point &) const;

        // Overloaded operators

        // Members
        Point &operator*=(double);
        Point &operator/=(double);

        const Point operator*(double) const; // prevent (p1*2) = p2;
        const Point operator/(double) const;

        // Note: 1-based index!
        double &operator[](int index) { return values[index]; }

        // Friends
        friend Point &operator+=(Point &, const Point &);
        friend Point &operator-=(Point &, const Point &);
        friend const Point operator+(const Point &, const Point &);
        friend const Point operator-(const Point &, const Point &);

        friend bool operator==(const Point &, const Point &);
        friend bool operator!=(const Point &, const Point &);

        friend bool operator<(const Point &, const Point &);
        friend bool operator>(const Point &, const Point &);
        friend bool operator<=(const Point &, const Point &);
        friend bool operator>=(const Point &, const Point &);

        friend std::ostream &operator<<(std::ostream &, const Point &);
        friend std::istream &operator>>(std::istream &, Point &);
    };
}
#endif // CLUSTERING_POINT_H
