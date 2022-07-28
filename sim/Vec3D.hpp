/********************
*
*    Vec3D.hpp
*    Created by:   Matt Kaufman
*    
*    Defines the Vec3D class,
*    to define an object for 3D vector math and operations.
*
*********************/

#include <cmath>
#include <SFML/Graphics.hpp>


class Vec3D : public sf::Vector3f
{
public:
    /*  Default constructor (0, 0, 0).  */
    Vec3D() : sf::Vector3f(0, 0, 0)  { }

    /*  Copy constructor (copy a Vec3D vector).  */
    Vec3D(const Vec3D& vec) : sf::Vector3f(vec)  { }

    /*  Copy constructor (copy a sf::Vector3f vector).  */
    Vec3D(const sf::Vector3f& vec) : sf::Vector3f(vec)  { }

    /*  Constructor with defined  x,  y,  z  floats.  */
    Vec3D(const float& x, const float& y, const float& z) : sf::Vector3f(x, y, z)  { }
    
    

    /*  Assignment operator (set one Vec3D equal to another).  */
    Vec3D& operator=(const Vec3D& vec)  { x = vec.x;  y = vec.y;  z = vec.z;  return *this; }

    /*  Addition operator (new Vec3D = Vec3D + Vec3D).  */
    Vec3D operator+(const Vec3D& vec) const  { return Vec3D(x + vec.x,  y + vec.y,  z + vec.z); }

    /*  Subtraction operator (new Vec3D = Vec3D - Vec3D).  */
    Vec3D operator-(const Vec3D& vec) const  { return Vec3D(x - vec.x,  y - vec.y,  z - vec.z); }

    /*  Division operator (new Vec3D = Vec3D / Vec3D).  */
    Vec3D operator/(const Vec3D& vec) const  { return Vec3D(x / vec.x,  y / vec.y,  z / vec.z); }

    /*  Scalar multiplication operator (new Vec2D = Vec2D * float).  */
    Vec3D operator*(const float& scalar) const  { return Vec3D(x * scalar,  y * scalar,  z * scalar); }

    /*  Vector multiplication operator (new Vec3D = Vec3D * Vec3D).  */
    Vec3D operator*(const Vec3D& vec) const  { return Vec3D(x * vec.x,  y * vec.y,  z * vec.z); }

    /*  Scalar division operator (new Vec3D = Vec3D / float).  */
    Vec3D operator/(const float& scalar) const  { return Vec3D(x / scalar,  y / scalar,  z / scalar); }

    /*  Equality operator (Vec3D == Vec3D) with tolerance of +/- 5% of magnitude.  */
    bool operator==(const Vec3D& vec) const  { return (fabs(x - vec.x) < 0.05f  &&  fabs(y - vec.y) < 0.05f  &&  fabs(z - vec.z) < 0.05f); }

    /*  Inequality operator (Vec3D != Vec3D)
     *  with the same tolerance as the equality operator's tolerance.  */
    bool operator!=(const Vec3D& vec) const  { return !(*this == vec); }



    /*  Returns the dot product of two Vec3D vectors.
     *  @param vec: The other Vec3D vector.  */
    float dot(const Vec3D& vec) const  { return x*vec.x + y*vec.y + z*vec.z; }    // dot product (float = Vec3D.dot(Vec3D))

    /*  Returns the cross product of two Vec3D vectors.
     *  @param vec: The other Vec3D vector.  */
    Vec3D cross(const Vec3D& vec) const  { return Vec3D(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x); }     // cross product (Vec3D = Vec3D.cross(Vec3D))

    /*  Returns the magnitude of a Vec3D vector.  */
    float magnitude() const  { return sqrt(x*x + y*y + z*z); }      // this magnitude (float = Vec3D.magnitude())

    // angleX, angleX2pi
    // angleY, angleY2pi
    // angleZ, angleZ2pi


    // angleBetween


    /*  Returns the normalized (unit) vector of a Vec3D vector.  */
    Vec3D normalize() const  { return *this / magnitude(); }    // this normalized (Vec3D = Vec3D.normalize())


    // normal
    // tangent


    /*  Returns a new vector with randomized x, y, z values,
     *  produced by multiplying the magnitude of this vector by
     *  a vector with random x, y, z values in the range of [0,1].  */
    Vec3D randomize() const  { return (Vec3D(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX))*this->magnitude(); }    // this randomized (Vec3D = Vec3D.randomize())


    // rotate
    // rotateAround


    // distanceTo
    // distanceToSquared


    // lerp


    // flipX
    // flipY
    // flipZ



private:
    /* Overloaded << operator, to print vector information */
    friend std::ostream& operator<<(std::ostream& os, const Vec3D& vec) {
        os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }
};