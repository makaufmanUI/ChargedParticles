/********************
*
*    Particle.hpp
*    Created by:   Matt Kaufman
*    
*    Defines the Particle class,
*    which inherits from the Entity class to define a generic particle.
*
*********************/

#include "Entity.hpp"   // includes:  "DrawableVec2D.hpp", "Vec2D.hpp", <cmath>, and <SFML/Graphics.hpp>





class Particle : public Entity
{
public:
    float radius;                   // Radius of the particle, as seen on the screen.
    Vec2D center;                   // Center point of the particle.
    sf::Color color;                // Color of the particle.
    float kinetic_energy;           // Kinetic energy of the particle.
    sf::CircleShape image;          // Image of the particle (i.e., the sf::Drawable).
    
    bool trail_enabled = true;      // Whether or not the particle should have a trail.

    sf::Color trail_color;          // Color of the particle's trail.
    bool trail_color_set = false;   // Keeps track of whether or not the trail color has been set for the particle.

    float trail_lifetime = 1.f;     // Lifetime of the particle's trail.

    float trail_size = 1.f;         // Size of the particle's trail (i.e., the *diameter* of the particles comprising the trail).
    bool trail_size_set = false;    // Keeps track of whether or not the trail size has been set for the particle.

    DrawableVec2D* location_vector;         // Vector of the particle's location, as drawn from the window's origin (i.e., the top-left corner).
    bool showing_location_vector = false;   // Whether or not the particle's location vector is being shown.
    
    
    
    /*  Struct representing a single particle in the trail.
     *  The actual trail is a vector of pointers to these structs.  */
    struct TrailParticle
    {
        float age;                  // Age of the trail particle.
        float radius;               // Radius of the trail particle (i.e., Particle::trail_size / 2).
        Vec2D location;             // Location of the trail particle.
        float lifetime;             // Lifetime of the trail particle (equal to Particle::trail_lifetime).
        sf::Color color;            // Color of the trail particle.
        sf::CircleShape image;      // Image of the trail particle (i.e., the sf::Drawable).


        /*  Trail particle destructor.  */
        ~TrailParticle() { delete image.getTexture(); }


        /*  Marks the trail particle for destruction.
         *  This is done by setting its age equal to its lifetime,
         *  which will cause it to be deleted in the next call to Particle::UpdateTrail().  */
        void MarkForDestruction() { this->age = this->lifetime; }


        /*  First trail particle constructor.
         *  @param pos: The position of the trail particle.
         *  @param r: The radius to give the trail particle.
         *  @param life: The lifetime of the trail particle.  */
        TrailParticle(Vec2D pos, float r, float life)
        {
            age = 0.f;
            radius = r;
            location = pos;
            lifetime = life;
            color = this->color;
            image.setPosition(pos);
            image.setRadius(radius);
            image.setFillColor(color);
        }


        /*  Second trail particle constructor.
         *  @param pos: The position of the trail particle.
         *  @param r: The radius to give the trail particle.
         *  @param c: The color to give the trail particle.
         *  @param life: The lifetime of the trail particle.  */
        TrailParticle(Vec2D pos, float r, sf::Color c, float life)
        {
            age = 0.f;
            color = c;
            radius = r;
            location = pos;
            lifetime = life;
            image.setPosition(pos);
            image.setRadius(radius);
            image.setFillColor(color);
        }


        /*  Trail particle update method. This method
         *  updates the trail particle's age, and checks
         *  if its age is greater than its lifetime,
         *  in which case it deletes itself and returns 1.
         *  @param dt: The time delta between frames.  */
        int Update(float dt)
        {
            age += dt;
            if (age > lifetime) {
                delete this;
                return 1;
            }
            return 0;
        }


        /*  Trail particle draw method. This method  
         *  sets the position of the trail particle's image,
         *  sets the fill color of the trail particle's image,
         *  and then draws the trail particle's image to the window.
         *  @param window: The window to draw the trail particle's image to.  */
        void Draw(sf::RenderWindow& window)
        {
            image.setPosition(location);
            image.setFillColor(sf::Color(
                color.r, color.g, color.b, 
                255.f * (1.f - age/lifetime)
            ));
            window.draw(image);
        }
    };
    std::vector<Particle::TrailParticle*> trail;        // Vector of pointers to trail particles.
    
    
    /*  Struct defining the positional bounds of a particle;
        i.e., the region in which the particle is permitted to be.  */
    struct Bounds
    {
        float left;
        float right;
        float top;
        float bottom;

        Bounds() : left(0.f), right(0.f), top(0.f), bottom(0.f) {}
        Bounds(float left, float right, float top, float bottom) : left(left), right(right), top(top), bottom(bottom) {}
    };
    Bounds bounds;      // The acceptable bounds of the particle.



    /*****  Destructor & Constructors  *****/

    ~Particle() { }
    Particle(std::string name, sf::Color color, float mass, float radius);
    Particle(std::string name, sf::Color color, float mass, float radius, Vec2D position);
    Particle(std::string name, sf::Color color, float mass, float radius, Vec2D position, Vec2D velocity);
    Particle(std::string name, sf::Color color, float mass, float radius, Vec2D position, Vec2D velocity, Vec2D acceleration);





    /*  Determines the distance between
     *  this particle and another particle, as measured from their centers.
     *  @param particle: The particle to measure the distance to.  */
    float DistanceTo(Particle& particle)       { return (this->center - particle.center).magnitude(); };


    /*  Determines the Kinetic Energy
     *  of the particle based on its mass and velocity.
     *  @param velocity: The current velocity of the particle.  */
    float ResolveKineticEnergy(Vec2D velocity) { return (this->mass/2.f) * (velocity.magnitude()*velocity.magnitude()); };


    /*  Determines whether or not
     *  the particle is overlapping another.
     *  @param particle: The particle to check for overlap against.  */
    bool OverlappingWith(Particle& particle)   { return (Particle::DistanceTo(particle) < (this->radius + particle.radius)); };


    /*  Returns a unit vector pointing
     *  in the direction of the given particle.
     *  @param particle: The particle to get the direction to.  */
    Vec2D UnitVectorTo(Particle& particle)     { return (particle.kinematics.position - this->kinematics.position).normalize(); };
    


    /**********  COLLISION METHODS  **********/

    Vec2D Rotate(Vec2D velocity, float angle);
    void ResolveCollisionWith(Particle& particle);
    void ResolveCollisionWith(Particle& particle, float restitution);
    void ResolveBoundaryCollisions();
    void ResolveBoundaryCollisions(float restitution);


    
    /**********  UPDATE METHODS  **********/

    void Update(double t, float dt, Vec2D force);
    void Update(double t, float dt, Vec2D force, float collision_restitution);
    void Update(double t, float dt, Vec2D force, double velocity_damping);
    void Update(double t, float dt, Vec2D force, double velocity_damping, float collision_restitution);

    void MoveTo(Vec2D position);
    void MoveCenterTo(Vec2D position);


    /**********  BOUNDING METHODS  **********/

    void SetBounds(sf::RenderWindow& window);
    void SetBounds(float left, float right, float top, float bottom);
    

    /*  Particle draw method.
     *  This method draws the particle's image to the window,
     *  as well as drawing its trail particles if this->trail_enabled is true,
     *  and drawing its location vector if this->show_location_vector is true.
     *  @param window: The window to draw the particle's image to.  */
    void Draw(sf::RenderWindow& window) {
        if (this->trail_enabled) DrawTrail(window);
        window.draw(this->image);
        if (this->showing_location_vector) {
            this->location_vector = new DrawableVec2D(this->kinematics.position);
            this->location_vector->DrawFromTopLeft(window);
            delete this->location_vector;
        }
    }


    /*  Enables the location vector of the particle.
     *  This results in location vectors being drawn
     *  upon the following calls to the particle's draw method.  */
    void EnableLocationVector() { this->showing_location_vector = true; }


    /*  Disables the location vector of the particle.
     *  This results in location vectors *not* being drawn
     *  upon the following calls the the particle's draw method.  */
    void DisableLocationVector() { this->showing_location_vector = false; }

    
    /**********  TRAIL METHODS  **********/

    void AddToTrail();
    void EnableTrail();
    void DisableTrail();
    void UpdateTrail(float dt);
    void SetTrailSize(float size);
    void SetTrailColor(sf::Color color);
    void SetTrailLifetime(float lifetime);
    void DrawTrail(sf::RenderWindow& window);


private:
    /* Overloaded << for printing particle information */
    friend std::ostream& operator<<(std::ostream& os, const Particle& p)
    {
        os << std::endl << std::endl;
        os << "Particle \"" << p.name << "\":" << std::endl;
        os << "----------"; for (int i = 0; i < p.name.length()+2; i++) os << "-"; os << std::endl;
        os << "   > Mass: " << p.mass << std::endl;
        os << "   > Radius: " << p.radius << std::endl;
        os << "   > Center: " << p.center << std::endl;
        os << "   > Position: " << p.kinematics.position << std::endl;
        os << "   > Velocity: " << p.kinematics.velocity << std::endl;
        os << "   > Angular Velocity: " << p.kinematics.angular_velocity << std::endl;
        os << "   > Acceleration: " << p.kinematics.acceleration << std::endl;
        os << "   > Momentum: " << p.kinematics.momentum << std::endl;
        os << "   > Angular Momentum: " << p.kinematics.angular_momentum << std::endl;
        os << "   > Kinetic Energy: " << p.kinetic_energy << std::endl;
        os << std::endl << std::endl;
        return os;
    }
};










/*  First Particle constructor.
 *  @param name: The name to give the particle.
 *  @param color: The color to give the particle.
 *  @param mass: The mass to give the particle.
 *  @param radius: The radius to give the particle.  */
Particle::Particle(std::string name, sf::Color color, float mass, float radius)
: Entity(name, mass)
{
    this->color = color;
    this->radius = radius;
    this->center = Vec2D(radius,radius);
    this->image.setRadius(radius);
    this->image.setFillColor(color);
    this->image.setOrigin(radius,radius);
    this->image.setPosition(this->kinematics.position);
    this->kinetic_energy = 0.f;
}


/*  Second Particle constructor.
 *  @param name: The name to give the particle.
 *  @param color: The color to give the particle.
 *  @param mass: The mass to give the particle.
 *  @param radius: The radius to give the particle.
 *  @param position: The position to give the particle.  */
Particle::Particle(std::string name, sf::Color color, float mass, float radius, Vec2D position)
: Entity(name, mass, position)
{
    this->color = color;
    this->radius = radius;
    this->center = position+Vec2D(radius,radius);
    this->image.setRadius(radius);
    this->image.setFillColor(color);
    this->image.setOrigin(radius,radius);
    this->image.setPosition(position);
    this->kinetic_energy = 0.f;
}


/*  Third Particle constructor.
 *  @param name: The name to give the particle.
 *  @param color: The color to give the particle.
 *  @param mass: The mass to give the particle.
 *  @param radius: The radius to give the particle.
 *  @param position: The position to give the particle.
 *  @param velocity: The velocity to give the particle.  */
Particle::Particle(std::string name, sf::Color color, float mass, float radius, Vec2D position, Vec2D velocity)
: Entity(name, mass, position, velocity)
{
    this->color = color;
    this->radius = radius;
    this->center = position+Vec2D(radius,radius);
    this->image.setRadius(radius);
    this->image.setFillColor(color);
    this->image.setOrigin(radius, radius);
    this->image.setPosition(position);
    this->kinetic_energy = ResolveKineticEnergy(velocity);
}


/*  Fourth Particle constructor.
 *  @param name: The name to give the particle.
 *  @param color: The color to give the particle.
 *  @param mass: The mass to give the particle.
 *  @param radius: The radius to give the particle.
 *  @param position: The position to give the particle.
 *  @param velocity: The velocity to give the particle.
 *  @param acceleration: The acceleration to give the particle.  */
Particle::Particle(std::string name, sf::Color color, float mass, float radius, Vec2D position, Vec2D velocity, Vec2D acceleration)
: Entity(name, mass, position, velocity, acceleration)
{
    this->color = color;
    this->radius = radius;
    this->center = position+Vec2D(radius,radius);
    this->image.setRadius(radius);
    this->image.setFillColor(color);
    this->image.setOrigin(radius, radius);
    this->image.setPosition(position);
    this->kinetic_energy = ResolveKineticEnergy(velocity);
}








/*  Helper function - Rotates coordinate system for velocities.
 *  Takes velocities and alters them as if the coordinate system they're on was rotated.
 *  @param velocity: The velocity to rotate.
 *  @param angle: The angle to rotate the velocity by.  */
Vec2D Particle::Rotate(Vec2D velocity, float angle)
{
    float x = (velocity.x * cos(angle)) - (velocity.y * sin(angle));
    float y = (velocity.x * sin(angle)) + (velocity.y * cos(angle));
    return Vec2D(x, y);
}





/*  Swaps out two colliding particle's x and y velocities
 *  after running through an elastic collision reaction equation.
 *  @param particle: The particle to swap velocities with.  */
void Particle::ResolveCollisionWith(Particle& particle)
{
    float dx = particle.kinematics.position.x - this->kinematics.position.x;
    float dy = particle.kinematics.position.y - this->kinematics.position.y;
    float dvx = this->kinematics.velocity.x - particle.kinematics.velocity.x;
    float dvy = this->kinematics.velocity.y - particle.kinematics.velocity.y;
    
    if (Particle::OverlappingWith(particle))
    {
        if (dvx*dx + dvy*dy >= 0)
        {
            float m1 = this->mass;
            float m2 = particle.mass;
            float angle = -atan2(particle.kinematics.position.y - this->kinematics.position.y, particle.kinematics.position.x - this->kinematics.position.x);
            Vec2D u1 = Particle::Rotate(this->kinematics.velocity, angle);
            Vec2D u2 = Particle::Rotate(particle.kinematics.velocity, angle);
            Vec2D v1 = Vec2D( (u1.x * (m1 - m2) / (m1 + m2)) + (u2.x * 2 * m2 / (m1 + m2)), u1.y );
            Vec2D v2 = Vec2D( (u2.x * (m2 - m1) / (m1 + m2)) + (u1.x * 2 * m1 / (m1 + m2)), u2.y );
            Vec2D v1_final = Particle::Rotate(v1, -angle);
            Vec2D v2_final = Particle::Rotate(v2, -angle);
            this->kinematics.velocity = v1_final;
            particle.kinematics.velocity = v2_final;
        }
    }
}


/*  Swaps out two colliding particle's x and y velocities
 *  after running through an elastic collision reaction equation.
 *  @param particle: The particle to swap velocities with.
 *  @param restitution: The coefficient of restitution for the collision.  */
void Particle::ResolveCollisionWith(Particle& particle, float restitution)
{
    float dx = particle.kinematics.position.x - this->kinematics.position.x;
    float dy = particle.kinematics.position.y - this->kinematics.position.y;
    float dvx = this->kinematics.velocity.x - particle.kinematics.velocity.x;
    float dvy = this->kinematics.velocity.y - particle.kinematics.velocity.y;
    
    if (Particle::OverlappingWith(particle))
    {
        if (dvx*dx + dvy*dy >= 0)
        {
            float m1 = this->mass;
            float m2 = particle.mass;
            float angle = -atan2(particle.kinematics.position.y - this->kinematics.position.y, particle.kinematics.position.x - this->kinematics.position.x);
            Vec2D u1 = Particle::Rotate(this->kinematics.velocity, angle);
            Vec2D u2 = Particle::Rotate(particle.kinematics.velocity, angle);
            Vec2D v1 = Vec2D( (u1.x * (m1 - m2) / (m1 + m2)) + (u2.x * 2 * m2 / (m1 + m2)), u1.y );
            Vec2D v2 = Vec2D( (u2.x * (m2 - m1) / (m1 + m2)) + (u1.x * 2 * m1 / (m1 + m2)), u2.y );
            Vec2D v1_final = Particle::Rotate(v1, -angle) * restitution;
            Vec2D v2_final = Particle::Rotate(v2, -angle) * restitution;
            this->kinematics.velocity = v1_final;
            particle.kinematics.velocity = v2_final;
        }
    }
}




/*  Boundary collision detection and response.
 *  Uses the particle's bounds struct to determine
 *  if the particle is colliding with the boundary defined by the Bounds struct.  */
void Particle::ResolveBoundaryCollisions()
{
    if (this->kinematics.position.y+this->radius > (this->bounds.bottom)) {
        this->kinematics.position.y = this->bounds.bottom - this->radius;
        this->kinematics.velocity.y = -this->kinematics.velocity.y;
    }
    if (this->kinematics.position.y-this->radius < this->bounds.top) {
        this->kinematics.position.y = this->bounds.top+this->radius;
        this->kinematics.velocity.y = -this->kinematics.velocity.y;
    }
    if (this->kinematics.position.x-this->radius < this->bounds.left) {
        this->kinematics.position.x = this->bounds.left+this->radius;
        this->kinematics.velocity.x = -this->kinematics.velocity.x;
    }
    if ((this->kinematics.position.x + this->radius) > this->bounds.right) {
        this->kinematics.position.x = this->bounds.right - this->radius;
        this->kinematics.velocity.x = -this->kinematics.velocity.x;
    }
}


/*  Boundary collision detection and response.
 *  Uses the particle's bounds struct to determine
 *  if the particle is colliding with the boundary defined by the Bounds struct.
 *  Incorporates a coefficient of restitution, for energy loss.
 *  @param restitution: The coefficient of restitution for the collision.  */
void Particle::ResolveBoundaryCollisions(float restitution)
{
    if (this->kinematics.position.y+this->radius > (this->bounds.bottom)) {
        this->kinematics.position.y = this->bounds.bottom - this->radius;
        this->kinematics.velocity.y = -this->kinematics.velocity.y * restitution;
    }
    if (this->kinematics.position.y-this->radius < this->bounds.top) {
        this->kinematics.position.y = this->bounds.top+this->radius;
        this->kinematics.velocity.y = -this->kinematics.velocity.y * restitution;
    }
    if (this->kinematics.position.x-this->radius < this->bounds.left) {
        this->kinematics.position.x = this->bounds.left+this->radius;
        this->kinematics.velocity.x = -this->kinematics.velocity.x * restitution;
    }
    if ((this->kinematics.position.x + this->radius) > this->bounds.right) {
        this->kinematics.position.x = this->bounds.right - this->radius;
        this->kinematics.velocity.x = -this->kinematics.velocity.x * restitution;
    }
}



/*  Moves the particle to the specified position.
 *  @param position: The position to move the particle to.  */
void Particle::MoveTo(Vec2D position)
{
    this->kinematics.position = position;
    this->image.setPosition(position);
}

/*  Moves the *center* of the particle to the specified position.
 *  @param position: The position to move the particle to.  */
void Particle::MoveCenterTo(Vec2D position)
{
    this->kinematics.position.x = position.x - this->radius;
    this->kinematics.position.y = position.y - this->radius;
    this->image.setPosition(this->kinematics.position);
}




/*  Sets the bounds of the particle
 *  to the dimensions of the window.
 *  @param window: The window to set the bounds to.  */
void Particle::SetBounds(sf::RenderWindow& window)
{
    this->bounds.left = 0;
    this->bounds.right = window.getSize().x;
    this->bounds.top = 0;
    this->bounds.bottom = window.getSize().y;
}


/*  Sets the bounds of the particle
 *  to the specified dimensions.
 *  @param left: The left bound.
 *  @param right: The right bound.
 *  @param top: The top bound.
 *  @param bottom: The bottom bound.  */
void Particle::SetBounds(float left, float right, float top, float bottom)
{
    this->bounds.left = left;
    this->bounds.right = right;
    this->bounds.top = top;
    this->bounds.bottom = bottom;
}



/*  First particle update method.
 *  Calls Entity::Integrate(), resolves boundary collisions,
 *  updates the particle's center, momentum, kinetic energy,
 *  sets the particle's image position to the new position,
 *  and if the particle's trail is enabled, adds a new particle
 *  to it and calls the UpdateTrail() method.
 *  @param t: The current simulation time.
 *  @param dt: The time step.
 *  @param force: The force to apply to the particle.  */
void Particle::Update(double t, float dt, Vec2D force)
{
    Entity::Integrate(t, dt, force);
    ResolveBoundaryCollisions();
    this->center = Vec2D(this->kinematics.position.x+this->radius, this->kinematics.position.y+this->radius);
    this->kinematics.momentum = this->mass * this->kinematics.velocity;
    this->kinetic_energy = ResolveKineticEnergy(this->kinematics.velocity);
    this->image.setPosition(this->kinematics.position);
    if (this->trail_enabled) {
        Particle::AddToTrail();
        Particle::UpdateTrail(dt);
    }
}


/*  Second particle update method.
 *  Calls Entity::Integrate(), resolves boundary collisions (with restitution),
 *  updates the particle's center, momentum, kinetic energy,
 *  sets the particle's image position to the new position,
 *  and if the particle's trail is enabled, adds a new particle
 *  to it and calls the UpdateTrail() method.
 *  @param t: The current simulation time.
 *  @param dt: The time step.
 *  @param force: The force to apply to the particle.
 *  @param collision_restitution: The coefficient of restitution for the collision.  */
void Particle::Update(double t, float dt, Vec2D force, float collision_restitution)
{
    Entity::Integrate(t, dt, force);
    ResolveBoundaryCollisions(collision_restitution);
    this->center = Vec2D(this->kinematics.position.x+this->radius, this->kinematics.position.y+this->radius);
    this->kinematics.momentum = this->mass * this->kinematics.velocity;
    this->kinetic_energy = ResolveKineticEnergy(this->kinematics.velocity);
    this->image.setPosition(this->kinematics.position);
    if (this->trail_enabled) {
        Particle::AddToTrail();
        Particle::UpdateTrail(dt);
    }
}


/*  Third particle update method.
 *  Calls Entity::Integrate() (with velocity damping), resolves boundary collisions,
 *  updates the particle's center, momentum, kinetic energy,
 *  sets the particle's image position to the new position,
 *  and if the particle's trail is enabled, adds a new particle
 *  to it and calls the UpdateTrail() method.
 *  @param t: The current simulation time.
 *  @param dt: The time step.
 *  @param force: The force to apply to the particle.
 *  @param velocity_damping: The velocity damping coefficient.  */
void Particle::Update(double t, float dt, Vec2D force, double velocity_damping)
{
    float damping = (float)velocity_damping;
    Vec2D last_velocity = this->kinematics.velocity;
    Entity::Integrate(t, dt, force, damping);

    this->kinematics.acceleration = this->kinematics.velocity - last_velocity;                                          //
    this->kinematics.angular_velocity = ResolveAngularVelocity(this->kinematics.position, this->kinematics.velocity);   // THESE TWO WERE ADDED (THIS IS A GLOABAL ANGULAR VELOCITY, I.E. WITH RESPECT TO THE TOP LEFT CORNER)

    ResolveBoundaryCollisions();
    this->center = Vec2D(this->kinematics.position.x+this->radius, this->kinematics.position.y+this->radius);
    this->kinematics.momentum = this->mass * this->kinematics.velocity;
    this->kinetic_energy = ResolveKineticEnergy(this->kinematics.velocity);
    this->image.setPosition(this->kinematics.position);
    if (this->trail_enabled) {
        Particle::AddToTrail();
        Particle::UpdateTrail(dt);
    }
}


/*  Fourth particle update method.
 *  Calls Entity::Integrate() (with velocity damping),
 *  resolves boundary collisions (with restitution),
 *  updates the particle's center, momentum, kinetic energy,
 *  sets the particle's image position to the new position,
 *  and if the particle's trail is enabled, adds a new particle
 *  to it and calls the UpdateTrail() method.
 *  @param t: The current simulation time.
 *  @param dt: The time step.
 *  @param force: The force to apply to the particle.
 *  @param velocity_damping: The velocity damping coefficient.
 *  @param collision_restitution: The coefficient of restitution for the collision.  */
void Particle::Update(double t, float dt, Vec2D force, double velocity_damping, float collision_restitution)
{
    float damping = (float)velocity_damping;
    Entity::Integrate(t, dt, force, damping);
    ResolveBoundaryCollisions(collision_restitution);
    this->center = Vec2D(this->kinematics.position.x+this->radius, this->kinematics.position.y+this->radius);
    this->kinematics.momentum = this->mass * this->kinematics.velocity;
    this->kinetic_energy = ResolveKineticEnergy(this->kinematics.velocity);
    this->image.setPosition(this->kinematics.position);
    if (this->trail_enabled) {
        Particle::AddToTrail();
        Particle::UpdateTrail(dt);
    }
}





/*  Enables the particle's trail.  */
void Particle::EnableTrail()
{
    this->trail_enabled = true;
}


/*  Disables the particle's trail.  */
void Particle::DisableTrail()
{
    this->trail_enabled = false;
}


/*  Sets the size of the particle's trail.
 *  @param size: The size to give the trail.  */
void Particle::SetTrailSize(float size)
{
    this->trail_size = size;
    this->trail_size_set = true;
}


/*  Sets the lifetime of the particle's trail.
 *  @param lifetime: The lifetime to give the trail.  */
void Particle::SetTrailLifetime(float lifetime)
{
    this->trail_lifetime = lifetime;
}


/*  Sets the color of the particle's trail.
 *  @param color: The color to give the trail.  */
void Particle::SetTrailColor(sf::Color color)
{
    this->trail_color = color;
    this->trail_color_set = true;
}


/*  Adds a new trail particle to the particle's trail.  */
void Particle::AddToTrail()
{
    if (this->trail_size_set && this->trail_color_set)
    this->trail.emplace_back(new Particle::TrailParticle(this->kinematics.position, this->trail_size/2.f, this->trail_color, this->trail_lifetime));

    else if (this->trail_size_set)
    this->trail.emplace_back(new Particle::TrailParticle(this->kinematics.position, this->trail_size/2.f, this->color, this->trail_lifetime));

    else if (this->trail_color_set)
    this->trail.emplace_back(new Particle::TrailParticle(this->kinematics.position, 1, this->trail_color, this->trail_lifetime));

    else
    this->trail.emplace_back(new Particle::TrailParticle(this->kinematics.position, 1, this->color, this->trail_lifetime));
}


/*  Updates the particle's trail vector.
 *  Loops through the trail vector and updates each trail particle.
 *  If the TrailParticle struct's Update method returns 1,
 *  the particle is removed from the trail vector to prevent bad pointers.
 *  @param dt: The time step.  */
void Particle::UpdateTrail(float dt)
{
    int update_return = 0;
    for (int i = 0; i < this->trail.size(); i++) {
        update_return = this->trail[i]->Update(dt);
        if (update_return == 1) {
            this->trail.erase(this->trail.begin() + i);
            i--;
        }
    }
}


/*  Draws the particle's trail.
 *  Loops through the trail vector and calls the
 *  TrailParticle Draw method on each trail particle.
 *  @param window: The window to draw the trail on.  */
void Particle::DrawTrail(sf::RenderWindow& window)
{
    for (auto& particle : this->trail)  particle->Draw(window);
}