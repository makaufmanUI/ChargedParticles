/********************
*
*    Vec2D.hpp
*    Created by:   Matt Kaufman
*    
*    Defines the Vec2D class,
*    which inherits from the sf::Vector2f class,
*    to define an improved object for easier/more robust vector math.
*
*********************/

#include <cmath>
#include <SFML/Graphics.hpp>


/*
A simple 2D vector class.
This class is meant to be used as a replacement for sf::Vector2f.

Includes the following operators and functions for working with vectors:
    - << (for printing vector information)
    - copy constructor ( = )
    - vector addition ( + )
    - vector subtraction ( - )
    - vector division ( / )
    - scalar division ( / )
    - vector multiplication ( * )
    - scalar multiplication ( * )
    - equality operator ( == )
    - inequality operator ( != )
    - dot product ( Vec2D.dot(Vec2D) )
    - magnitude ( Vec2D.magnitude() )
    - angle ( Vec2D.angle() )
    - angle2pi ( Vec2D.angle2pi() )
    - normal ( Vec2D.normal() )
    - tangent ( Vec2D.tangent() )
    - normalize ( Vec2D.normalize() )
    - randomize ( Vec2D.randomize() )
    - rotate ( Vec2D.rotate() )
    - distanceTo ( Vec2D.distanceTo(Vec2D) )
    - distanceToSquared ( Vec2D.distanceSquared() )
    - lerp ( Vec2D.lerp(Vec2D, float) )
    - rotateAround ( Vec2D.rotateAround(Vec2D, float) )
    - angleBetween ( Vec2D.angleBetween(Vec2D) )
    - flipX ( Vec2D.flipX() )
    - flipY ( Vec2D.flipY() )  */
class Vec2D : public sf::Vector2f
{
public:
    /*  Default constructor (0, 0).  */
    Vec2D() : sf::Vector2f(0, 0) {}

    /*  Constructor with defined x and y floats.  */
    Vec2D(const float& x, const float& y) : sf::Vector2f(x, y) {}

    /*  Copy constructor (copy a sf::Vector2f vector).  */
    Vec2D(const sf::Vector2f& vec) : sf::Vector2f(vec) {}

    /*  Copy constructor (copy a Vec2D vector).  */
    Vec2D(const Vec2D& vec) : sf::Vector2f(vec) {}


    /*  Assignment operator (set one Vec2D equal to another).  */
    Vec2D& operator=(const Vec2D& vec) { x = vec.x; y = vec.y; return *this; }

    /*  Addition operator (new Vec2D = Vec2D + Vec2D).  */
    Vec2D operator+(const Vec2D& vec) const { return Vec2D(x + vec.x, y + vec.y); }

    /*  Subtraction operator (new Vec2D = Vec2D - Vec2D).  */
    Vec2D operator-(const Vec2D& vec) const { return Vec2D(x - vec.x, y - vec.y); }

    /*  Division operator (new Vec2D = Vec2D / Vec2D).  */
    Vec2D operator/(const Vec2D& vec) const { return Vec2D(x / vec.x, y / vec.y); }

    /*  Scalar multiplication operator (new Vec2D = Vec2D * float).  */
    Vec2D operator*(const float& scalar) const { return Vec2D(x * scalar, y * scalar); }

    /*  Vector multiplication operator (new Vec2D = Vec2D * Vec2D).  */
    Vec2D operator*(const Vec2D& vec) const { return Vec2D(x * vec.x, y * vec.y); }

    /*  Scalar division operator (new Vec2D = Vec2D / float).  */
    Vec2D operator/(const float& scalar) const { return Vec2D(x / scalar, y / scalar); }


    /*  Equality operator (Vec2D == Vec2D) with tolerance of +/- 5% of magnitude.  */
    bool operator==(const Vec2D& vec) const { return (fabs(x - vec.x) < 0.05f && fabs(y - vec.y) < 0.05f); }     // +/- 5% tolerance
    // bool operator==(const Vec2D& vec) const { return (fabs(x - vec.x) < 0.1f && fabs(y - vec.y) < 0.1f); }    // +/- 10% tolerance
    // bool operator==(const Vec2D& vec) const { return (fabs(x - vec.x) < 0.01 && fabs(y - vec.y) < 0.01); }    // +/- 1% tolerance

    /*  Inequality operator (Vec2D != Vec2D)
     *  with the same tolerance as the equality operator's tolerance.  */
    bool operator!=(const Vec2D& vec) const { return !(*this == vec); }

    /*  Returns the dot product of two Vec2D vectors.
     *  @param vec: The other Vec2D vector.  */
    float dot(const Vec2D& vec) const { return x * vec.x + y * vec.y; }             // dot product (float = Vec2D.dot(Vec2D))

    /* Returns the magnitude of a Vec2D vector. */
    float magnitude() const { return sqrt(x * x + y * y); }                         // this magnitude (float = Vec2D.magnitude())

    /*  Returns the angle a Vec2D vector makes with the +x-axis, in radians.
     * On the interval [0, pi) , [0, -pi].  */
    float angle() const {                                                           // this angle (float = Vec2D.angle())
        float angle = atan2(y, x);
        // return pi if angle is negative pi, else return angle
        return (angle < 0) ? (angle + 2 * 3.14159265359f) : angle;
    }

    /*  Returns the angle a Vec2D vector makes with the +x-axis, in radians.
     *  On the interval [0, 2pi).  */
    float angle2pi() const {                                                        // this angle (float = Vec2D.angle2pi())
        float angle = atan2(y, x);
        if (angle < 0) angle += 2 * 3.14159265359f;
        return angle;
    }

    /*  Returns the normalized (unit) vector of a Vec2D vector.  */
    Vec2D normalize() const { return *this / magnitude(); }                         // this normalized (Vec2D = Vec2D.normalize())

    /*  Returns a normal vector of a given Vec2D vector.
     *  i.e. the vector 90deg CCW from it.  */
    Vec2D normal() const { return Vec2D(-y, x); }                                   // this normal (Vec2D = Vec2D.normal())

    /*  Returns the tangent of a Vec2D vector.
     *  i.e. the vector 90deg CW from it.  */
    Vec2D tangent() const { return Vec2D(y, -x); }                                  // this tangent (Vec2D = Vec2D.tangent())

    /*  Returns a new vector with randomized x and y values,
     *  produced by multiplying the magnitude of this vector by
     *  a vector with random x and y values in the range of [0,1].  */
    Vec2D randomize() const { return (Vec2D(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX))*this->magnitude(); }     // this randomized (Vec2D = Vec2D.randomize())

    /*  Returns a new Vec2D vector rotated by a given angle, in radians.
     *  @param angle: The angle to rotate by, in radians.  */
    Vec2D rotate(float angle) const { return Vec2D(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)); }   // rotate (Vec2D = Vec2D.rotate(float))

    /*  Returns the distance between two Vec2D vectors.
     *  @param vec: The other Vec2D vector, with which to get distance to.  */
    float distanceTo(const Vec2D& vec) const { return sqrt(pow(x - vec.x, 2) + pow(y - vec.y, 2)); }                      // distance (float = Vec2D.distanceTo(Vec2D))
    
    /*  Returns the squared distance between two Vec2D vectors.
     *  @param vec: The other Vec2D vector, with which to get distance to.  */
    float distanceToSquared(const Vec2D& vec) const { return pow(x - vec.x, 2) + pow(y - vec.y, 2); }                       // distance squared (float = Vec2D.distanceSquared(Vec2D))
    
    /*  Returns a new Vec2D vector that is lerped between this vector and another at t, where 0 <= t <= 1
     *  @param vec: The other Vec2D vector, with which to lerp to.
     *  @param t: The amount to lerp by, between 0 and 1.  */
    Vec2D lerp(const Vec2D& vec, float t) const { return *this * (1 - t) + vec * t; }                                     // lerp (Vec2D = Vec2D.lerp(Vec2D, float))

    /*  Returns a new Vec2D vector that is the result of rotating this vector around anoter vector by angle
     *  @param vec: The other Vec2D vector, with which to rotate around.
     *  @param angle: The angle to rotate by, in radians.  */
    Vec2D rotateAround(const Vec2D& vec, float angle) const { return rotate(angle) + vec - *this; }                       // rotate around (Vec2D = Vec2D.rotateAround(Vec2D, float))
    
    /*  Returns the angle between two Vec2D vectors.
     *  @param vec: The other Vec2D vector, with which to get the angle to.  */
    float angleBetween(const Vec2D& vec) const { return acos(dot(vec) / (magnitude() * vec.magnitude())); }               // angle between (float = Vec2D.angleBetween(Vec2D))

    /*  Returns a new Vec2D vector that has been flipped over the x-axis.  */
    Vec2D flipX() const { return Vec2D(x, -y); }                                                                          // flip x (Vec2D = Vec2D.flipX())

    /*  Returns a new Vec2D vector that has been flipped over the y-axis.  */
    Vec2D flipY() const { return Vec2D(-x, y); }                                                                          // flip y (Vec2D = Vec2D.flipY())



private:
    /*  Overloaded << operator, to print vector information  */
    friend std::ostream& operator<<(std::ostream& os, const Vec2D& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        // os << "(" << vec.x << ", " << vec.y << "),  mag: " << vec.magnitude() << ", theta: " << vec.angle() << " (" << 57.29578*(vec.angle()) << " deg)";
        return os;
    }
};