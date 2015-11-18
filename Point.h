// A 3-dimensional point class!
// Coordinates are double-precision floating point.
#include <ostream>
#include <vector>
#include "OutOfBoundEx.h"

#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H
namespace Clustering {


    class Point {
        int dim;        // number of dimensions of the point
        std::vector<double> m_values;

        unsigned int __id;
        static unsigned int idGenerator;


    public:
        static const char POINT_VALUE_DELIM = ',';

        Point(unsigned int d);

        Point(unsigned int, double *);

        // Big three: cpy ctor, overloaded operator=, dtor
        Point(const Point &);

        Point &operator=(const Point &);

        ~Point();

        void generatePoint_ID() { __id = idGenerator++; }
        static void rewindIdGen() { idGenerator--; }

        // Accessors & mutators
        int getDims() const { return dim; }

        void setValue(int i, double d) {
            m_values[i] = d;
        }

        double getValue(unsigned int) const;

        // Functions
        double distanceTo(const Point &) const;

        // Overloaded operators
        Point &operator*=(double);

        Point &operator/=(double);

        const Point operator*(double); // prevent (p1*2) = p2;
        const Point operator/(double);

        // Note: 1-based index!
        double &operator[](const unsigned int index) {
            if (index >= dim)
                throw OutOfBoundEx("Point[]", index);
            return m_values[index];
        }

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
