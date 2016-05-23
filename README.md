## CSCI 2312: Programming Assignment 3

## Point Class
_A Multidimensional point class!_

Coordinates are double-precision floating point.

``` int dim;     // number of dimensions of the point ```

``` double *values;   // values of the point's dimensions ```

### Point(int);
Takes int for the number dimension and set values of the Point's dimenstion to zero by default

### Point(int, double ``` * ```)
The constructor accepts arguments for the dimension and the values of the point's dimensions.

***

``` // // Big three: cpy ctor, overloaded operator=, dtor ```
### Point(const Point &);
The copy constructor copies data from the existing Point object to the new Point object

### Point &operator=(const Point &);
Deletes existing values of the point's dimensions and initializes the values from the right side

### ~Point();
Deallocates the values of the point's dimensions

***

``` //Accessors & mutators ```
### int getDims() const
Returns the dimention of a point

###void setValue(int i, double d)
Set the values of a point's dimensions
  
### double getValue(int) const;
Get the values of a point's dimensions

***

``` // Functions ```
### double distanceTo(const Point &) const;
Calculates distance between two points 

***

``` // Overloaded operators ```
### friend bool operator==(const Point &, const Point &);
Compares the values of two point's dimensions. Returns true if they are equal.

### friend bool operator!=(const Point &, const Point &);
Compares the values of two point's dimensions. Returns true if they are not equal.

### friend bool operator<(const Point &, const Point &);
Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion
is less than the values of the other point dimention.

### friend bool operator>(const Point &, const Point &);
Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion is greater
than the values of the other point dimention.

###friend bool operator<=(const Point &, const Point &);
Compares the values of two point's dimensions. Returns true if the values of the first point 			dimenstion
is less or equal than the values of the other point dimention.

###friend bool operator>=(const Point &, const Point &);
Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion 	
is greater or equal than the values of the other point dimention.

***

``` // Friends ```
###friend Point &operator+=(Point &, const Point &);
Adds the values of a point's dimension on the right of the operator to the values of a point's	dimension
on the left of the operator and stores the result  on the left of the operator. 

###friend Point &operator-=(Point &, const Point &);
Substracts the values of the point's dimension on the right side to the values of a point's
dimension on the left side and stores the result on the left of the operator.

###friend const Point operator+(const Point &, const Point &);
Adds the values of the point's dimention that is on the left side to the values of a point's dimention that is
on the right

###friend const Point operator-(const Point &, const Point &);
Substracts the values of the point's dimension on the left side to the values of a point's
dimension on the right side.

###Point &operator*=(double);
Multiplies the given number to the values of the point's dimensions

###Point &operator/=(double);
Divide the given number to the values of the point's dimensions
### const Point operator*(double) const;

Multiply the given number to the values of the point's dimensions

###const Point operator/(double) const;


###double &operator[](int index); 
Returns the values of the point's dimensions

###friend std::ostream &operator<<(std::ostream &, const Point &);
Displays the values of the point's dimensions to the screen 

***

## Cluster Class
``` typedef Point *PointPtr;  // An alias to the  Point * type ```  
``` typedef struct LNode *LNodePtr;  // An alias to the Node * type ```

``` struct LNode; // Nested structure type Node to support a singly-linked list ```

	
``` LNodePtr points; // Node pointer to points to the points of the linked list ```
``` int m_size;	     // to hold a number of points in a cluster ```
      
### int getM_size() const; 
Returns a quantity of points

### Cluster(); 
Default constructor. Initializes the members of the class to zero

###Cluster(const Cluster &);
The copy constructor copies data from the existing Cluster object to the new Cluster object

###Cluster &operator=(const Cluster &); 
Deletes existing values of the Cluster's dimensions and initializes
the values from the right hand side

###~Cluster();
Deallocates dynamically allocated Points in Linked list

### void add(const PointPtr &);
Add a point to the linked list

###const PointPtr &remove(const PointPtr &);
Removes a point and return it so we can add it to another cluster

### Cluster &operator+=(const Cluster &rhs);
Adds rhs points which left hand side does not have

### Cluster &operator-=(const Cluster &rhs);
 
### Cluster &operator+=(const Point &rhs);
###Cluster &operator-=(const Point &rhs);
###friend bool operator==(const Cluster &lhs, const Cluster &rhs);
###friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
###friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);
###friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
###friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);
###friend std::ostream &operator<<(std::ostream &os, const Clustering::Cluster &c1);
###friend std::istream &operator>>(std::istream &os, Clustering::Cluster &c1);
