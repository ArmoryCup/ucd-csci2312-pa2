// A 3-dimensional point class!
// Coordinates are double-precision floating point.
#include <ostream>
#include <vector>
#include "OutOfBoundEx.h"

#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H
namespace Clustering {
    template<typename T, int dims>
    class Point;

    template<typename T, int d>
     Point<T, d> &operator+=(Point<T, d> &, const Point<T, d> &);

    template<typename T, int d>
    Point<T, d> &operator-=(Point<T, d> &, const Point<T, d> &);


    template<typename T, int d>
    const Point<T, d> operator+(const Point<T, d> &, const Point<T, d> &);

    template<typename S, int d>
    const Point<S, d> operator-(const Point<S, d> &, const Point<S, d> &);

    template<typename S, int d>
    bool operator==(const Point<S, d> &, const Point<S, d> &);

    template<typename S, int d>
    bool operator!=(const Point<S, d> &, const Point<S, d> &);

    template<typename S, int d>
    bool operator<(const Point<S, d> &, const Point<S, d> &);

    template<typename S, int d>
    bool operator>(const Point<S, d> &, const Point<S, d> &);

    template<typename S, int d>
    bool operator<=(const Point<S, d> &, const Point<S, d> &);

    template<typename S, int d>
    bool operator>=(const Point<S, d> &, const Point<S, d> &);

    template<typename S, int d>
    std::ostream &operator<<(std::ostream &, const Point<S, d> &);

    template<typename S, int d>
    std::istream &operator>>(std::istream &, Point<S, d> &);


    template<typename T, int dims>
    class Point {
        int dim;        // number of dimensions of the point
        std::vector<T> m_values;

        unsigned int __id;
        static unsigned int idGenerator;


    public:
        static const char POINT_VALUE_DELIM = ',';

        Point();
//        Point(unsigned int);
        Point(T *arr);


        // Big three: cpy ctor, overloaded operator=, dtor
        Point(const Point &);

        Point &operator=(const Point &);

        ~Point();

        void generatePoint_ID() { __id = idGenerator++; }

        static void rewindIdGen() { idGenerator--; }

        // Accessors & mutators
        int getDims() const { return dim; }
        T getValue(unsigned int index) const { return m_values[index]; }

        void setValue(int i, T d) { m_values[i] = d; }

        // Functions
        T distanceTo(const Point &) const;

        // Overloaded operators
        Point &operator*=(T);
        Point &operator/=(T);

        const Point operator*(T); // prevent (p1*2) = p2;
        const Point operator/(T);


        // Friends. <> this is how templates should be declared
        friend const Point operator+<>(const Point<T, dims> &, const Point<T, dims> &);
        friend const Point operator-<>(const Point<T, dims> &, const Point<T, dims> &);

        friend Point &operator+= <>(Point<T, dims> &, const Point<T, dims> &);
        friend Point &operator-= <>(Point<T, dims> &, const Point<T, dims> &);


        friend bool operator==<>(const Point<T, dims> &, const Point<T, dims> &);
        friend bool operator!=<>(const Point<T, dims> &, const Point<T, dims> &);
        friend bool operator< <>(const Point<T, dims> &, const Point<T, dims> &);
        friend bool operator> <>(const Point<T, dims> &, const Point<T, dims> &);
        friend bool operator<= <>(const Point<T, dims> &, const Point<T, dims> &);
        friend bool operator>= <>(const Point<T, dims> &, const Point<T, dims> &);

        friend std::ostream &operator<< <>(std::ostream &, const Point<T, dims> &);
        friend std::istream &operator>> <>(std::istream &, Point<T, dims> &);


        double &operator[](const unsigned int index) {
            if (index >= dim)
                throw OutOfBoundEx("Point[]", index);
            return m_values[index];
        }
    };
}

#include "Point.cpp"

#endif // CLUSTERING_POINT_H
