/********************
*
*    Entity.hpp
*    Created by:   Matt Kaufman
*    
*    Defines the Entity class,
*    which is the base class for all simulation objects.
*
*********************/

#include "DrawableVec2D.hpp"    // includes:  "Vec2D.hpp", <cmath>, and <SFML/Graphics.hpp>





class Entity
{
public:
    float mass;             // The mass of the entity.
    std::string name;       // The name of the entity.


    /*  Kinematics struct for storing the kinematic information of the entity;
        i.e., the properties inherent to, or resulting from, the particle's motion.  */
    struct Kinematics
    {
        Vec2D position;             // The position of the entity.
        Vec2D velocity;             // The velocity of the entity.
        Vec2D momentum;             // The momentum of the entity.
        Vec2D acceleration;         // The acceleration of the entity.
        float angular_velocity;     // The angular velocity of the entity, in radians/second; counter-clockwise is positive, clockwise is negative.
        float angular_momentum;     // The angular momentum of the entity, in joule*seconds; counter-clockwise is positive, clockwise is negative.


        /*  Default Kinematics constructor. Sets all attributes to zero.  */
        Kinematics() : position(0, 0), velocity(0, 0), momentum(0, 0), acceleration(0, 0), angular_velocity(0), angular_momentum(0) {}

        /*  Explicit Kinematics constructor.
         *  @param pos: The position of the entity.
         *  @param vel: The velocity of the entity.
         *  @param mom: The momentum of the entity.
         *  @param acc: The acceleration of the entity.
         *  @param ang_vel: The angular velocity of the entity, in radians/second; counter-clockwise is positive, clockwise is negative.
         *  @param ang_mom: The angular momentum of the entity, in joule*seconds; counter-clockwise is positive, clockwise is negative.  */
        Kinematics(const Vec2D& pos, const Vec2D& vel, const Vec2D& mom, const Vec2D& acc, float ang_vel, float ang_mom)
        : position(pos), velocity(vel), momentum(mom), acceleration(acc), angular_velocity(ang_vel), angular_momentum(ang_mom) { }
        

        /*  Assignment operator overload.
         *  Sets all attributes to the same values as the other Kinematics struct.  */
        Kinematics& operator =(const Kinematics& k) {
            position = k.position;
            velocity = k.velocity;
            momentum = k.momentum;
            acceleration = k.acceleration;
            angular_velocity = k.angular_velocity;
            angular_momentum = k.angular_momentum;
            return *this;
        };

        /*  Multiplication operator overload.
         *  Multiplies all attributes by the given scalar.  */
        Kinematics operator *(float f) const {
            return Kinematics(position * f, velocity * f, momentum * f, acceleration * f, angular_velocity * f, angular_momentum * f);
        };

        /*  Division operator overload.
         *  Divides all attributes by the given scalar.  */
        Kinematics operator /(float f) const {
            return Kinematics(position / f, velocity / f, momentum / f, acceleration / f, angular_velocity / f, angular_momentum / f);
        };

        /*  Addition operator overload.
         *  Adds all attributes to the given Kinematics struct.  */
        Kinematics operator +(const Kinematics& k) const {
            return Kinematics(position + k.position, velocity + k.velocity, momentum + k.momentum, acceleration + k.acceleration, angular_velocity + k.angular_velocity, angular_momentum + k.angular_momentum);
        };

        /*  Subtraction operator overload.
         *  Subtracts all attributes from the given Kinematics struct.  */
        Kinematics operator -(const Kinematics& k) const {
            return Kinematics(position - k.position, velocity - k.velocity, momentum - k.momentum, acceleration - k.acceleration, angular_velocity - k.angular_velocity, angular_momentum - k.angular_momentum);
        };

        /*  Times-equals operator overload.
         *  Multiplies all attributes by the given scalar.  */
        Kinematics& operator *=(float f) {
            position *= f;
            velocity *= f;
            momentum *= f;
            acceleration *= f;
            angular_velocity *= f;
            angular_momentum *= f;
            return *this;
        };

        /*  Divides-equals operator overload.
         *  Divides all attributes by the given scalar.  */
        Kinematics& operator /=(float f) {
            position /= f;
            velocity /= f;
            momentum /= f;
            acceleration /= f;
            angular_velocity /= f;
            angular_momentum /= f;
            return *this;
        };

        /*  Plus-equals operator overload.
         *  Adds all attributes to the given Kinematics struct.  */
        Kinematics& operator +=(const Kinematics& k) {
            position += k.position;
            velocity += k.velocity;
            momentum += k.momentum;
            acceleration += k.acceleration;
            angular_velocity += k.angular_velocity;
            angular_momentum += k.angular_momentum;
            return *this;
        };

        /*  Minus-equals operator overload.
         *  Subtracts all attributes from the given Kinematics struct.  */
        Kinematics& operator -=(const Kinematics& k) {
            position -= k.position;
            velocity -= k.velocity;
            momentum -= k.momentum;
            acceleration -= k.acceleration;
            angular_velocity -= k.angular_velocity;
            angular_momentum -= k.angular_momentum;
            return *this;
        };

        /*  Equality operator overload.
         *  Returns true if all attributes are equal to the given Kinematics struct.  */
        bool operator ==(const Kinematics& k) const {
            return position == k.position &&
                   velocity == k.velocity &&
                   momentum == k.momentum &&
                   acceleration == k.acceleration && angular_velocity == k.angular_velocity && angular_momentum == k.angular_momentum;
        };
    };
    Kinematics kinematics;      // The kinematics of the entity.


    /*  Derivative struct for storing the derivative information of the entity;
     *  i.e., the time-rate-of-change of the particle's position & velocity. Used for calculating the next state of the entity.  */
    struct Derivatives {
        Vec2D position;
        Vec2D velocity;

        Derivatives() : position(0, 0), velocity(0, 0) {}
    };
    Derivatives derivatives;    // The derivatives of the entity.



    // virtual ~Entity();

    /*****  Constructors  *****/

    Entity(const Entity& entity);
    Entity(std::string name, float mass);
    Entity(std::string name, float mass, Vec2D position);
    Entity(std::string name, float mass, Vec2D position, Vec2D velocity);
    Entity(std::string name, float mass, Vec2D position, Vec2D velocity, Vec2D acceleration);
    Entity& operator=(const Entity& entity);



    /*****  Resolution methods  *****/

    /*  Computes the momentum of the entity based on its mass and velocity.  */
    Vec2D ResolveMomentum(Vec2D velocity) { return this->mass * velocity; };

    /*  Computes the angular momentum of the entity relative to the origin (i.e. top-left corner of window) based on its mass and velocity.  */
    float ResolveAngularMomentum(Vec2D velocity) { return this->mass * ((this->kinematics.position.x*velocity.y) - (this->kinematics.position.y*velocity.x)); };

    /*  Computes the velocity of the entity based on its momentum and mass.  */
    Vec2D ResolveVelocity(Vec2D momentum) { return momentum / this->mass; };

    /*  Computes the angular velocity of the entity relative to the origin (i.e. top-left corner of window) based on its position and its velocity.  */
    float ResolveAngularVelocity(Vec2D position, Vec2D velocity) { return ((this->kinematics.position.x*velocity.y) - (this->kinematics.position.y*velocity.x)) / (this->kinematics.position.magnitude()*this->kinematics.position.magnitude()); };



    /*****  Runge-Kutta integration methods  *****/

    Vec2D Acceleration(Vec2D force);
    Entity::Derivatives Evaluate(double t, float dt, Vec2D force, const Entity::Derivatives& d);
    void Integrate(double t, float dt, Vec2D force);
    void Integrate(double t, float dt, Vec2D force, float damping);



private:
    /* Overloaded << for printing entity information */
    friend std::ostream& operator<<(std::ostream& os, const Entity& entity)
    {
        os << std::endl << std::endl;
        os << "Entity \"" << entity.name << "\":" << std::endl;
        os << "--------"; for (int i = 0; i < entity.name.length()+2; i++) os << "-"; os << std::endl;
        os << "   > Mass: " << entity.mass << std::endl << std::endl;
        os << "   > Position: " << entity.kinematics.position << std::endl;
        os << "   > Velocity: " << entity.kinematics.velocity << std::endl;
        os << "   > Angular Velocity: " << entity.kinematics.angular_velocity << std::endl;
        os << "   > Acceleration: " << entity.kinematics.acceleration << std::endl;
        os << "   > Momentum: " << entity.kinematics.momentum << std::endl;
        os << "   > Angular Momentum: " << entity.kinematics.angular_momentum << std::endl;
        os << std::endl << std::endl;
        return os;
    }
};







/*  First Entity constructor.
 *  @param entity: The entity to copy on creation of a new one.  */
Entity::Entity(const Entity& entity)
{
    this->mass = entity.mass;
    this->name = entity.name;
    this->kinematics = entity.kinematics;
    this->derivatives = entity.derivatives;
}


/*  Second Entity constructor.
 *  @param name: The name of the entity.
 *  @param mass: The mass of the entity.  */
Entity::Entity(std::string name, float mass)
{
    this->mass = mass;
    this->name = name;
    this->kinematics = Kinematics();
    this->derivatives = Derivatives();
}


/*  Third Entity constructor.
 *  @param name: The name of the entity.
 *  @param mass: The mass of the entity.
 *  @param position: The position of the entity.  */
Entity::Entity(std::string name, float mass, Vec2D position)
{
    this->mass = mass;
    this->name = name;
    this->kinematics = Kinematics(position, Vec2D(0, 0), Vec2D(0, 0), Vec2D(0, 0), 0, 0);
    this->derivatives = Derivatives();
}


/*  Fourth Entity constructor.
 *  @param name: The name of the entity.
 *  @param mass: The mass of the entity.
 *  @param position: The position of the entity.
 *  @param velocity: The velocity of the entity.  */
Entity::Entity(std::string name, float mass, Vec2D position, Vec2D velocity)
{
    this->mass = mass;
    this->name = name;
    this->kinematics = Kinematics(position, velocity, ResolveMomentum(velocity), Vec2D(0, 0), ResolveAngularVelocity(position, velocity), ResolveAngularMomentum(velocity));
    this->derivatives = Derivatives();
}


/*  Fifth Entity constructor.
 *  @param name: The name of the entity.
 *  @param mass: The mass of the entity.
 *  @param position: The position of the entity.
 *  @param velocity: The velocity of the entity.
 *  @param acceleration: The acceleration of the entity.  */
Entity::Entity(std::string name, float mass, Vec2D position, Vec2D velocity, Vec2D acceleration)
{
    this->mass = mass;
    this->name = name;
    this->kinematics = Kinematics(position, velocity, ResolveMomentum(velocity), acceleration, ResolveAngularVelocity(position, velocity), ResolveAngularMomentum(velocity));
    this->derivatives = Derivatives();
}





/*  Assignment operator overload.
 *  @param entity: The entity to copy.  */
Entity& Entity::operator =(const Entity& entity)
{
    this->mass = entity.mass;
    this->name = entity.name;
    this->kinematics = entity.kinematics;
    this->derivatives = entity.derivatives;
    return *this;
}





/*  Updates this Entity's acceleration based on the given force.
 *  @param force: The force to apply to this Entity.  */
Vec2D Entity::Acceleration(Vec2D force)
{
    return this->kinematics.acceleration + (force / this->mass);
}


/*  Updates this Entity's derivatives based on the given time, delta time, and force.
 *  @param t: The time.
 *  @param dt: The delta time.
 *  @param force: The force to apply to this Entity.  */
Entity::Derivatives Entity::Evaluate(double t, float dt, Vec2D force, const Entity::Derivatives& d)
{
    Entity::Kinematics k2;
    Entity::Derivatives d_next;
    k2.position = this->kinematics.position - d.position * dt;
    k2.velocity = this->kinematics.velocity - d.velocity * dt;
    Entity::Derivatives output;
    output.position = k2.velocity;
    output.velocity = Entity::Acceleration(force);
    return output;
}


/*  Integrates this Entity's kinematics based on the given time, delta time, and force.
 *  @param t: The time.
 *  @param dt: The delta time.
 *  @param force: The force to apply to this Entity.  */
void Entity::Integrate(double t, float dt, Vec2D force)
{
    Entity::Derivatives a, b, c, d;
    a = Entity::Evaluate(t, 0.0f, force, Entity::Derivatives());
    b = Entity::Evaluate(t, dt * 0.5f, force, a);
    c = Entity::Evaluate(t, dt * 0.5f, force, b);
    d = Entity::Evaluate(t, dt, force, c);

    Vec2D x_ = 2.0f * (b.position + c.position);
    Vec2D z_ = a.position + x_ + d.position;
    Vec2D dposdt = (1.0f/6.0f) * z_;
    Vec2D h_ = 2.0f * (b.velocity + c.velocity);
    Vec2D j_ = a.velocity + h_ + d.velocity;
    Vec2D dveldt = (1.0f/6.0f) * j_;

    this->kinematics.position += dposdt * dt;
    this->kinematics.velocity += dveldt * dt;
    // this->kinematics.position = this->kinematics.position + dposdt * dt * damping;
    // this->kinematics.velocity = this->kinematics.velocity + dveldt * dt * damping;
};


/*  Updates this Entity's kinematics based on the given time, delta time, and force. Includes damping.
 *  @param t: The time.
 *  @param dt: The delta time.
 *  @param force: The force to apply to this Entity. 
 *  @param damping: The velocity damping to apply to this Entity.  */
void Entity::Integrate(double t, float dt, Vec2D force, float damping)
{
    Entity::Derivatives a, b, c, d;
    a = Entity::Evaluate(t, 0.0f, force, Entity::Derivatives());
    b = Entity::Evaluate(t, dt * 0.5f, force, a);
    c = Entity::Evaluate(t, dt * 0.5f, force, b);
    d = Entity::Evaluate(t, dt, force, c);

    Vec2D x_ = 2.0f * (b.position + c.position);
    Vec2D z_ = a.position + x_ + d.position;
    Vec2D dposdt = (1.0f/6.0f) * z_;
    Vec2D h_ = 2.0f * (b.velocity + c.velocity);
    Vec2D j_ = a.velocity + h_ + d.velocity;
    Vec2D dveldt = (1.0f/6.0f) * j_;

    // this->kinematics.position += dposdt * dt;
    // this->kinematics.velocity += dveldt * dt * damping;
    this->kinematics.position = this->kinematics.position + dposdt * dt;
    this->kinematics.velocity = this->kinematics.velocity + dveldt * dt;
    this->kinematics.velocity = this->kinematics.velocity * damping;
};


