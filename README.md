<h2>CSCI 2312: Programming Assignment 2</h2>
<hr/>
<p><h4>Point Class</h4>```<br/><p>A 3-dimensional point class!</p></p>
<p>Coordinates are double-precision floating point.</p>
<h6> int dim;     // number of dimensions of the point </h6>
<h6> double *values;   // values of the point's dimensions </h6>
<p><h6> Point(int);</h6><br/> <p>takes int for the number dimension and set values of the Point's dimenstion to zero</p></p>
<p><h6> Point(int, double *)</h6><br/> <p>The constructor accepts arguments for the dimension and the values of the point's dimensions.</p></p>
<p><h6> Point(const Point &amp;);</h6><br/> <p>The copy constructor copies data from the existing Point object to the new Point object</p><br/> <h6>Point &amp;operator=(const Point &amp;);</h6><br/> <p>Deletes existing values of the point's dimensions and initializes the values from the right side<br/> instantiates the members of the Point object to t</p><br/> <h6>~Point();</h6><br/> <p>deallocates the values of the point's dimensions</p></p>
<p><code>// Accessors &amp; mutators</code><br/> <h6>int getDims() const<br/><p>returns the dimention of a point</p></p>
<p><h6> void setValue(int i, double d)<br/><p>set the values of a point's dimensions</p></p>
<p><h6> double getValue(int) const;<br/><p>get the values of a point's dimensions</p></p>
<ul>
  <li>
  <p>// Functions *<br/> <h6> double distanceTo(const Point &amp;) const;<br/><p>calculates distance between two points </p></p></li>
  <li>
    <p>// Overloaded operators *<br/> <h6> friend bool operator==(const Point &amp;, const Point &amp;);</h6><br/><p>Compares the values of two point's dimensions. Returns true if they are equal.</p><br/> <h6> friend bool operator!=(const Point &amp;, const Point &amp;);</h6><br/><p>Compares the values of two point's dimensions. Returns true if they are not equal.</p><br/> <h6>friend bool operator&lt;(const Point &amp;, const Point &amp;);</h6><br/><p>Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion</p><br/><p>is less than the values of the other point dimention.</p><br/> <h6> friend bool operator&gt;(const Point &amp;, const Point &amp;);<br/><p>Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion is greater than the values of the other point dimention.</p><br/> <h6> friend bool operator&lt;=(const Point &amp;, const Point &amp;);<br/><p>Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion</p><br/><p>is less or equal than the values of the other point dimention.</p><br/> <h6> friend bool operator&gt;=(const Point &amp;, const Point &amp;);</h6><br/><p>Compares the values of two point's dimensions. Returns true if the values of the first point dimenstion</p><br/><p>is greater or equal than the values of the other point dimention.</p></p>
    <pre><code>// Friends
</code></pre>
    <p><h6> friend Point &amp;operator+=(Point &amp;, const Point &amp;);</h6><br/> <p>Adds the values of a point's dimension on the right of the operator to the values of a point's</p> <p>dimension on the left of the operator and stores the result on the left of the operator.</p><br/> <h6> friend Point &amp;operator-=(Point &amp;, const Point &amp;);</h6><br/> <p>Substracts the values of a point's dimension on the right of the operator to the values of a point's dimension on the left of the operator and stores the result on the left of the operator.</p><br/> <h6> friend const Point operator+(const Point &amp;, const Point &amp;);</h6><br/><p>Adds the values of a point's dimention that is on left side to the values of a point's dimention that is on the left</p><br/> <h6> friend const Point operator-(const Point &amp;, const Point &amp;);</h6></p>
  </li>
</ul>
<p><h6> Point &amp;operator*=(double);</h6><br/> <p>multiplies the given number to the values of the point's dimensions</p></p>
<p><h6>Point &amp;operator/=(double);<br/> <h6> const Point operator*(double) const; </h6><br/> <h6> const Point operator/(double) const;</h6></p>
<p><h6> double &amp;operator[](int index); </h6><br/> <p> Returns the values of the point's dimensions</p><br/> <h6> friend std::ostream &amp;operator&lt;&lt;(std::ostream &amp;, const Point &amp;);</h6><br/> <p>Displays the values of the point's dimensions to the screen </p><br/><h4>Cluster Class</h4><br/> <h6>typedef Point *PointPtr; // An alias to the Point * type </h6><br/> <h6>typedef struct LNode *LNodePtr; // An alias to the Node * type </h6></p>
<pre><code>&lt;h6&gt;struct LNode;&lt;/h6&gt;
&lt;p&gt; Nested structure type Node to support a singly-linked list.&lt;/p&gt;
</code></pre>
<h6>LNodePtr points; // Node pointer to points to the points of the linked list </h6>
<pre><code>    &lt;h6&gt;int m_size;      // to hold a number of points in a cluster &lt;/h6&gt;

    &lt;h6&gt;int getM_size() const;&lt;/h6&gt;
</code></pre>
<p> <p>Returns a quantity of points</p><br/> <h6>Cluster(); </h6><br/> <p>Default constructor. Initializes the members of the class to zero</p><br/> <h6>Cluster(const Cluster &amp;); </h6><br/> <h6>Cluster &amp;operator=(const Cluster &amp;);</h6><br/> <h6>~Cluster();</h6><br/> <h6>void add(const PointPtr &amp;); // add a point</h6><br/> <h6>const PointPtr &amp;remove(const PointPtr &amp;);</h6><br/> <p> Removes a point and return it so we can add it to another cluster</p><br/> <h6> Cluster &amp;operator+=(const Cluster &amp;rhs);</h6><br/> <h6> Cluster &amp;operator-=(const Cluster &amp;rhs); </h6><br/> <h6> Cluster &amp;operator+=(const Point &amp;rhs);</h6><br/> <h6>Cluster &amp;operator-=(const Point &amp;rhs);</h6><br/> <h6>friend bool operator==(const Cluster &amp;lhs, const Cluster &amp;rhs);</h6><br/> <h6>friend const Cluster operator+(const Cluster &amp;lhs, const Cluster &amp;rhs);</h6><br/> <h6>friend const Cluster operator-(const Cluster &amp;lhs, const Cluster &amp;rhs);</h6><br/> <h6>friend const Cluster operator+(const Cluster &amp;lhs, const PointPtr &amp;rhs);</h6><br/> <h6>friend const Cluster operator-(const Cluster &amp;lhs, const PointPtr &amp;rhs);</h6><br/> <h6>friend std::ostream &amp;operator&lt;&lt;(std::ostream &amp;os, const Clustering::Cluster &amp;c1);</h6><br/> <h6>friend std::istream &amp;operator&gt;&gt;(std::istream &amp;os, Clustering::Cluster &amp;c1);</h6></p>
