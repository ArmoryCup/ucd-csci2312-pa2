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
 <h6> friend bool operator==(const Point &, const Point &);</h6>
	<p>Compares the values of two point's dimensions. Returns true if they are equal.</p>
 <h6>  friend bool operator!=(const Point &, const Point &);</h6>
	<p>Compares the values of two point's dimensions. Returns true if they are not equal.</p>
 <h6>friend bool operator<(const Point &, const Point &);</h6>
	<p>Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion is less than the values of the other point dimention.</p>
  <h6> friend bool operator>(const Point &, const Point &);
	<p>Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion 	is greater than the values of the other point dimention.</p>
 <h6> friend bool operator<=(const Point &, const Point &);
	<p>Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion 	is less or equal than the values of the other point dimention.</p>
 <h6> friend bool operator>=(const Point &, const Point &);
	<p>Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion 	is greater or equal than the values of the other point dimention.</p>

        // Friends
 <h6> friend Point &operator+=(Point &, const Point &);</h6>
	 <p>Adds the values of a point's dimension on the right of the operator to the values of a point's 			dimension on the left of the operator and stores the result  on the left of the operator.</p> 
 <h6> friend Point &operator-=(Point &, const Point &);</h6>
 	<p>Substracts the values of a point's dimension on the right of the operator to the values of a point's 		dimension on the left of the operator and stores the result on the left of the operator.</p>
 <h6> friend const Point operator+(const Point &, const Point &);</h6>
	<p>Adds the values of a point's dimention that is on left side to the values of a point's dimention that is 	on the left</p>
 <h6> friend const Point operator-(const Point &, const Point &);</h6>

 <h6> Point &operator*=(double);</h6>
	<p>multiplies the given number to the values of the point's dimensions</p>

<h6>Point &operator/=(double);
 <h6>  const Point operator*(double) const; </h6>
 <h6> const Point operator/(double) const;</h6>

 <h6> double &operator[](int index); </h6>
	<p> Returns the values of the point's dimensions</p>
 <h6> friend std::ostream &operator<<(std::ostream &, const Point &);</h6>
 	<p>Displays the values of the point's dimensions to the screen </p>

<h4>Cluster Class</h4>
    ``` 
    typedef Point *PointPtr; // An alias for the type Point * 
    	typedef struct LNode *LNodePtr; // An alias to the Node * type
     ```

```
    // Nested structure type Node to support a singly-linked list.
    struct LNode {
        PointPtr p;
        LNode *next;
    };
```
	```
        <h6>LNodePtr points; // Node pointer to points to the points of the linked list
        
        int m_size;	     // to hold a number of points in a cluster
      ```
      
        <h6>int getM_size() const;</h6>
 		<p>Returns a quantity of points</p>
        <h6>Cluster(); </h6>
        	<p>Default constructor. Initializes the members of the class to zero</p>
        <h6>Cluster(const Cluster &); </h6>
        <h6>Cluster &operator=(const Cluster &);</h6> 
        <h6>~Cluster();</h6> 
        <h6>void add(const PointPtr &); // add a point</h6>
        <h6>const PointPtr &remove(const PointPtr &);</h6>
        <p> Removes a point and return it so we can add it to another cluster</p>

       <h6> Cluster &operator+=(const Cluster &rhs);</h6>
       <h6> Cluster &operator-=(const Cluster &rhs); </h6>

       <h6> Cluster &operator+=(const Point &rhs);</h6>
        <h6>Cluster &operator-=(const Point &rhs);</h6>
        <h6>friend bool operator==(const Cluster &lhs, const Cluster &rhs);</h6>

        <h6>friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);</h6>
        <h6>friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);</h6>
        <h6>friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);</h6>
        <h6>friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);</h6>

        <h6>friend std::ostream &operator<<(std::ostream &os, const Clustering::Cluster &c1);</h6>
        <h6>friend std::istream &operator>>(std::istream &os, Clustering::Cluster &c1);</h6>
