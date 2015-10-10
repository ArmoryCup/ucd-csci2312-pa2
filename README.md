## CSCI 2312: Programming Assignment 2
* * *
<h4>Point Class</h4>```
A 3-dimensional point class!

Coordinates are double-precision floating point.

_int dim;_    `` // number of dimensions of the point ``

_double *values;_  ``` // values of the point's dimensions```

  <h6> Point(int);</h6>
	<p>takes int for the number dimension and set values of the Point's dimenstion to zero</p>

  <h6> Point(int, double *)</h6>
	<p>The constructor accepts arguments for the dimension and the values of the point's dimensions.</p>

  <h6> Point(const Point &);</h6>
	<p>The copy constructor copies data from the existing Point object to the new Point object</p>
  <h6>Point &operator=(const Point &);</h6>
	<p>Deletes existing values of the point's dimensions and initializes the values from the right side
	instantiates the members of the Point object to t</p>
  <h6>~Point();</h6>
	<p>deallocates the values of the point's dimensions</p>

 ``` // Accessors & mutators ```
  <h6>int getDims() const
<p>returns the dimention of a point</p>

 <h6> void setValue(int i, double d)
<p>set the values of a point's dimensions</p>
  
  <h6> double getValue(int) const;
<p>get the values of a point's dimensions</p>

 ``` // Functions ```
 <h6>  double distanceTo(const Point &) const;
<p>calculates distance between two points </p>

 ```  // Overloaded operators```

 <h6> friend bool operator==(const Point &, const Point &);
	<p>Compares the values of two point's dimensions. Returns true if they are equal.</p>
 <h6>  friend bool operator!=(const Point &, const Point &);
<p>Compares the values of two point's dimensions. Returns true if they are not equal.</p>
 <h6>friend bool operator<(const Point &, const Point &);
<p>Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion is less than the values of the other point dimention.</p>
  <h6> friend bool operator>(const Point &, const Point &);
Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion is greater than the values of the other point dimention.</p>
 <h6> friend bool operator<=(const Point &, const Point &);
<p>Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion is less or equal than the values of the other point dimention.</p>
 <h6> friend bool operator>=(const Point &, const Point &);
<p>Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion is greater or equal than the values of the other point dimention.</p>

        // Friends
 <h6> friend Point &operator+=(Point &, const Point &);
 Adds the values of a point's dimension on the right of the operator to the values of a point's dimension on the left of the operator and stores the result  on the left of the operator. 
 <h6> friend Point &operator-=(Point &, const Point &);
 Substracts the values of a point's dimension on the right of the operator to the values of a point's dimension on the left of the operator and stores the result on the left of the operator. 
 <h6> friend const Point operator+(const Point &, const Point &);
Adds the values of a point's dimention that is on left side to the values of a point's dimention that is on the left

 <h6> friend const Point operator-(const Point &, const Point &);


 <h6> Point &operator*=(double);
multiplies the given number to the values of the point's dimensions

<h6>Point &operator/=(double);
 <h6>  const Point operator*(double) const; // prevent (p1*2) = p2;
 <h6> const Point operator/(double) const;

        // Note: 1-based index!
 <h6> double &operator[](int index) { return values[index - 1]; } // TODO out-of-bds?

 <h6> friend std::ostream &operator<<(std::ostream &, const Point &);
 <h6> friend std::istream &operator>>(std::istream &, Point &);



    typedef Point *PointPtr;
    typedef struct LNode *LNodePtr;

    struct LNode {
        PointPtr p;
        LNode *next;
    };

    class Cluster {

        LNodePtr points;                    // node pointer to points to the points of the linked list
        int m_size;
        static unsigned int __idGenerator;  // for use with __id
        bool __release_points;

    public:
        static const char POINT_CLUSTER_ID_DELIM = ':';       // for use with operator<<
        int getM_size() const {
            return m_size;
        }

        Cluster() : m_size(0), points(nullptr) { } // default ctor
        Cluster(const Cluster &); // copy ctor
        Cluster &operator=(const Cluster &); // assignment operator
        ~Cluster(); // dtor

        void add(const PointPtr &); // add a point
        const PointPtr &remove(const PointPtr &); // remove a point and return it so we can add it to another cluster

        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference

        Cluster &operator+=(const Point &rhs); // add point
        Cluster &operator-=(const Point &rhs); // remove point
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);

        friend std::ostream &operator<<(std::ostream &os, const Clustering::Cluster &c1);
        friend std::istream &operator>>(std::istream &os, Clustering::Cluster &c1);
