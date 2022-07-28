/********************
*
*    ChargedParticle.hpp
*    Created by:   Matt Kaufman
*    
*    Defines the ChargedParticle class,
*    which inherits from the Particle class, 
*    which itself inherits from the Entity class, to define a charged particle.
*
*********************/

#include "Particle.hpp"     // includes:  "Entity.hpp", "Vec2D.hpp", <cmath>, and <SFML/Graphics.hpp>



/*  Inherits from the Particle class,
 *  which itself inherits from the Entity class.
 *  NOTE: All constructors can have a RenderWindow reference added to them as the final argument for automatic bounds-setting.
 *  @param CONSTRUCTORS:
 *  @param ChargedParticle(sign,radius)
 *  @param ChargedParticle(sign,radius,position)
 *  @param ChargedParticle(sign,radius,position,velocity)
 *  @param ChargedParticle(mass,radius,charge)
 *  @param ChargedParticle(mass,radius,charge,position)
 *  @param ChargedParticle(mass,radius,charge,position,velocity)
 *  @param ChargedParticle(name,color,mass,radius,charge)
 *  @param ChargedParticle(name,color,mass,radius,charge,position)
 *  @param ChargedParticle(name,color,mass,radius,charge,position,velocity)  */
class ChargedParticle : public Particle
{
public:
    float charge;               // The particle's charge (can be + or -).
    float potential_energy;     // The particle's potential energy, as determined by any nearby charges.



    /*****  "Unit" charge constructors  *****/

    ChargedParticle(std::string sign, float radius);
    ChargedParticle(std::string sign, float radius, Vec2D position);
    ChargedParticle(std::string sign, float radius, Vec2D position, Vec2D velocity);



    /*****  "Unit" charge constructors with auto bounds-setting  *****/

    ChargedParticle(std::string sign, float radius, sf::RenderWindow& window);
    ChargedParticle(std::string sign, float radius, Vec2D position, sf::RenderWindow& window);
    ChargedParticle(std::string sign, float radius, Vec2D position, Vec2D velocity, sf::RenderWindow& window);



    /*****  Auto name/color constructors  *****/

    ChargedParticle(float mass, float radius, float charge);
    ChargedParticle(float mass, float radius, float charge, Vec2D position);
    ChargedParticle(float mass, float radius, float charge, Vec2D position, Vec2D velocity);



    /*****  Auto name/color constructors with auto bounds-setting  *****/

    ChargedParticle(float mass, float radius, float charge, sf::RenderWindow& window);
    ChargedParticle(float mass, float radius, float charge, Vec2D position, sf::RenderWindow& window);
    ChargedParticle(float mass, float radius, float charge, Vec2D position, Vec2D velocity, sf::RenderWindow& window);



    /*****  Standard constructors  *****/

    ChargedParticle(std::string name, sf::Color color, float mass, float radius, float charge);
    ChargedParticle(std::string name, sf::Color color, float mass, float radius, float charge, Vec2D position);
    ChargedParticle(std::string name, sf::Color color, float mass, float radius, float charge, Vec2D position, Vec2D velocity);



    /*****  Standard constructors with auto bounds-setting  *****/

    ChargedParticle(std::string name, sf::Color color, float mass, float radius, float charge, sf::RenderWindow& window);
    ChargedParticle(std::string name, sf::Color color, float mass, float radius, float charge, Vec2D position, sf::RenderWindow& window);
    ChargedParticle(std::string name, sf::Color color, float mass, float radius, float charge, Vec2D position, Vec2D velocity, sf::RenderWindow& window);




    /*****  Force & energy calculation methods  *****/

    Vec2D CoulombForce(ChargedParticle& particle);
    float ResolvePotentialEnergy(ChargedParticle& other);
    Vec2D CoulombForce(ChargedParticle& particle, float max_force);


    /*****  Update methods  *****/

    void Update(double t, float dt, ChargedParticle& nearby_charge);
    void Update(double t, float dt, ChargedParticle& nearby_charge, float max_force);
    void Update(double t, float dt, ChargedParticle& nearby_charge, double velocity_damping);
    void Update(double t, float dt, ChargedParticle& nearby_charge, double velocity_damping, float max_force);
    // void Update(double t, float dt, ChargedParticle& nearby_charge, float collision_restitution);
    void Update(double t, float dt, ChargedParticle& nearby_charge, float collision_restitution, float max_force);
    // void Update(double t, float dt, ChargedParticle& nearby_charge, double velocity_damping, float collision_restitution);
    void Update(double t, float dt, ChargedParticle& nearby_charge, double velocity_damping, float collision_restitution, float max_force);




private:
    /*  Overloaded << for printing particle information.  */
    friend std::ostream& operator<<(std::ostream& os, const ChargedParticle& cp)
    {
        os << std::endl << std::endl;
        os << "ChargedParticle \"" << cp.name << "\":" << std::endl;
        os << "-----------------"; for (int i = 0; i < cp.name.length()+2; i++) os << "-"; os << std::endl;
        os << "   > Mass: " << cp.mass << std::endl;
        os << "   > Charge: " << cp.charge << std::endl;
        os << "   > Radius: " << cp.radius << std::endl;
        os << "   > Center: " << cp.center << std::endl;
        os << "   > Position: " << cp.kinematics.position << std::endl;
        os << "   > Velocity: " << cp.kinematics.velocity << std::endl;
        os << "   > Angular Velocity: " << cp.kinematics.angular_velocity << std::endl;
        os << "   > Acceleration: " << cp.kinematics.acceleration << std::endl;
        os << "   > Momentum: " << cp.kinematics.momentum << std::endl;
        os << "   > Angular Momentum: " << cp.kinematics.angular_momentum << std::endl;
        os << "   > Kinetic Energy: " << cp.kinetic_energy << std::endl;
        os << "   > Potential Energy: " << cp.potential_energy << std::endl;
        os << "   > Total Energy: " << cp.kinetic_energy+cp.potential_energy << std::endl;
        os << std::endl << std::endl;
        return os;
    }
};







/*  Unit charge constructor.
 *  @param sign: "+" or "-"
 *  @param radius: radius of particle  */
ChargedParticle::ChargedParticle(std::string sign, float radius)
: Particle(sign, sf::Color::White, 0.000001f, 5.f)
{
    if (sign == "+") {
        this->charge = 0.00005f;
        this->color = sf::Color::Blue;
        this->image.setFillColor(this->color);
    }
    else if (sign == "-") {
        this->charge = -0.00005f;
        this->color = sf::Color::Red;
        this->image.setFillColor(this->color);
    }
    else throw std::invalid_argument("ChargedParticle::ChargedParticle(std::string sign, float radius): Invalid sign");
    this->potential_energy = 0.f;
}


/*  Unit charge constructor.
 *  @param sign: "+" or "-"
 *  @param radius: radius of particle
 *  @param position: position of particle  */
ChargedParticle::ChargedParticle(std::string sign, float radius, Vec2D position)
: Particle(sign, sf::Color::White, 0.000001f, 5.f, position)
{
    if (sign == "+") {
        this->charge = 0.00005f;
        this->color = sf::Color::Blue;
        this->image.setFillColor(this->color);
    }
    else if (sign == "-") {
        this->charge = -0.00005f;
        this->color = sf::Color::Red;
        this->image.setFillColor(this->color);
    }
    else throw std::invalid_argument("ChargedParticle::ChargedParticle(std::string sign, float radius, Vec2D position): Invalid sign");
    this->potential_energy = 0.f;
}


/*  Unit charge constructor.
 *  @param sign: "+" or "-"
 *  @param radius: radius of particle
 *  @param position: position of particle
 *  @param velocity: velocity of particle  */
ChargedParticle::ChargedParticle(std::string sign, float radius, Vec2D position, Vec2D velocity)
: Particle(sign, sf::Color::White, 0.000001f, 5.f, position, velocity)
{
    if (sign == "+") {
        this->charge = 0.00005f;
        this->color = sf::Color::Blue;
        this->image.setFillColor(this->color);
    }
    else if (sign == "-") {
        this->charge = -0.00005f;
        this->color = sf::Color::Red;
        this->image.setFillColor(this->color);
    }
    else throw std::invalid_argument("ChargedParticle::ChargedParticle(std::string sign, float radius, Vec2D position, Vec2D velocity): Invalid sign");
    this->potential_energy = 0.f;
}


/*  Unit charge constructor with auto bounds-setting.
 *  @param sign: "+" or "-"
 *  @param radius: radius of particle
 *  @param window: reference to window  */
ChargedParticle::ChargedParticle(std::string sign, float radius, sf::RenderWindow& window)
: Particle(sign, sf::Color::White, 0.000001f, 5.f)
{
    if (sign == "+") {
        this->charge = 0.00005f;
        this->color = sf::Color::Blue;
        this->image.setFillColor(this->color);
    }
    else if (sign == "-") {
        this->charge = -0.00005f;
        this->color = sf::Color::Red;
        this->image.setFillColor(this->color);
    }
    else throw std::invalid_argument("ChargedParticle::ChargedParticle(std::string sign, float radius): Invalid sign");
    this->potential_energy = 0.f;
    this->SetBounds(0, window.getSize().x, 0, window.getSize().y);
}


/*  Unit charge constructor with auto bounds-setting.
 *  @param sign: "+" or "-"
 *  @param radius: radius of particle
 *  @param position: position of particle
 *  @param window: reference to window  */
ChargedParticle::ChargedParticle(std::string sign, float radius, Vec2D position, sf::RenderWindow& window)
: Particle(sign, sf::Color::White, 0.000001f, 5.f, position)
{
    if (sign == "+") {
        this->charge = 0.00005f;
        this->color = sf::Color::Blue;
        this->image.setFillColor(this->color);
    }
    else if (sign == "-") {
        this->charge = -0.00005f;
        this->color = sf::Color::Red;
        this->image.setFillColor(this->color);
    }
    else throw std::invalid_argument("ChargedParticle::ChargedParticle(std::string sign, float radius, Vec2D position): Invalid sign");
    this->potential_energy = 0.f;
    this->SetBounds(0, window.getSize().x, 0, window.getSize().y);
}


/*  Unit charge constructor with auto bounds-setting.
 *  @param sign: "+" or "-"
 *  @param radius: radius of particle
 *  @param position: position of particle
 *  @param velocity: velocity of particle
 *  @param window: reference to window  */
ChargedParticle::ChargedParticle(std::string sign, float radius, Vec2D position, Vec2D velocity, sf::RenderWindow& window)
: Particle(sign, sf::Color::White, 0.000001f, 5.f, position, velocity)
{
    if (sign == "+") {
        this->charge = 0.00005f;
        this->color = sf::Color::Blue;
        this->image.setFillColor(this->color);
    }
    else if (sign == "-") {
        this->charge = -0.00005f;
        this->color = sf::Color::Red;
        this->image.setFillColor(this->color);
    }
    else throw std::invalid_argument("ChargedParticle::ChargedParticle(std::string sign, float radius, Vec2D position, Vec2D velocity): Invalid sign");
    this->potential_energy = 0.f;
    this->SetBounds(0, window.getSize().x, 0, window.getSize().y);
}





/*  Auto name & color constructor.
 *  @param mass: mass of particle
 *  @param radius: radius of particle
 *  @param charge: charge of particle  */
ChargedParticle::ChargedParticle(float mass, float radius, float charge)
: Particle("", sf::Color::White, mass, radius)
{
    if (charge > 0) {
        this->name = "+";
        this->color = sf::Color::Blue;
        this->image.setFillColor(this->color);
    }
    else if (charge < 0) {
        this->name = "-";
        this->color = sf::Color::Red;
        this->image.setFillColor(this->color);
    }
    else throw std::invalid_argument("ChargedParticle::ChargedParticle(float mass, float radius, float charge): Invalid charge");
    this->charge = charge;
    this->potential_energy = 0.f;
}


/*  Auto name & color constructor.
 *  @param mass: mass of particle
 *  @param radius: radius of particle
 *  @param charge: charge of particle
 *  @param position: position of particle  */
ChargedParticle::ChargedParticle(float mass, float radius, float charge, Vec2D position)
: Particle("", sf::Color::White, mass, radius, position)
{
    if (charge > 0) {
        this->name = "+";
        this->color = sf::Color::Blue;
        this->image.setFillColor(this->color);
    }
    else if (charge < 0) {
        this->name = "-";
        this->color = sf::Color::Red;
        this->image.setFillColor(this->color);
    }
    else throw std::invalid_argument("ChargedParticle::ChargedParticle(float mass, float radius, float charge, Vec2D position): Invalid charge");
    this->charge = charge;
    this->potential_energy = 0.f;
}


/*  Auto name & color constructor.
 *  @param mass: mass of particle
 *  @param radius: radius of particle
 *  @param charge: charge of particle
 *  @param position: position of particle
 *  @param velocity: velocity of particle  */
ChargedParticle::ChargedParticle(float mass, float radius, float charge, Vec2D position, Vec2D velocity)
: Particle("", sf::Color::White, mass, radius, position, velocity)
{
    if (charge > 0) {
        this->name = "+";
        this->color = sf::Color::Blue;
        this->image.setFillColor(this->color);
    }
    else if (charge < 0) {
        this->name = "-";
        this->color = sf::Color::Red;
        this->image.setFillColor(this->color);
    }
    else throw std::invalid_argument("ChargedParticle::ChargedParticle(float mass, float radius, float charge, Vec2D position, Vec2D velocity): Invalid charge");
    this->charge = charge;
    this->potential_energy = 0.f;
}





/*  Auto name & color constructor with automatic bounds-setting.
 *  @param mass: mass of particle
 *  @param radius: radius of particle
 *  @param charge: charge of particle
 *  @param window: reference to window  */
ChargedParticle::ChargedParticle(float mass, float radius, float charge, sf::RenderWindow& window)
: Particle("", sf::Color::White, mass, radius)
{
    if (charge > 0) {
        this->name = "+";
        this->color = sf::Color::Blue;
        this->image.setFillColor(this->color);
    }
    else if (charge < 0) {
        this->name = "-";
        this->color = sf::Color::Red;
        this->image.setFillColor(this->color);
    }
    else throw std::invalid_argument("ChargedParticle::ChargedParticle(float mass, float radius, float charge): Invalid charge");
    this->charge = charge;
    this->potential_energy = 0.f;
    this->SetBounds(0, window.getSize().x, 0, window.getSize().y);
}


/*  Auto name & color constructor with automatic bounds-setting.
 *  @param mass: mass of particle
 *  @param radius: radius of particle
 *  @param charge: charge of particle
 *  @param position: position of particle
 *  @param window: reference to window  */
ChargedParticle::ChargedParticle(float mass, float radius, float charge, Vec2D position, sf::RenderWindow& window)
: Particle("", sf::Color::White, mass, radius, position)
{
    if (charge > 0) {
        this->name = "+";
        this->color = sf::Color::Blue;
        this->image.setFillColor(this->color);
    }
    else if (charge < 0) {
        this->name = "-";
        this->color = sf::Color::Red;
        this->image.setFillColor(this->color);
    }
    else throw std::invalid_argument("ChargedParticle::ChargedParticle(float mass, float radius, float charge, Vec2D position): Invalid charge");
    this->charge = charge;
    this->potential_energy = 0.f;
    this->SetBounds(0, window.getSize().x, 0, window.getSize().y);
}


/*  Auto name & color constructor with automatic bounds-setting.
 *  @param mass: mass of particle
 *  @param radius: radius of particle
 *  @param charge: charge of particle
 *  @param position: position of particle
 *  @param velocity: velocity of particle
 *  @param window: reference to window  */
ChargedParticle::ChargedParticle(float mass, float radius, float charge, Vec2D position, Vec2D velocity, sf::RenderWindow& window)
: Particle("", sf::Color::White, mass, radius, position, velocity)
{
    if (charge > 0) {
        this->name = "+";
        this->color = sf::Color::Blue;
        this->image.setFillColor(this->color);
    }
    else if (charge < 0) {
        this->name = "-";
        this->color = sf::Color::Red;
        this->image.setFillColor(this->color);
    }
    else throw std::invalid_argument("ChargedParticle::ChargedParticle(float mass, float radius, float charge, Vec2D position, Vec2D velocity): Invalid charge");
    this->charge = charge;
    this->potential_energy = 0.f;
    this->SetBounds(0, window.getSize().x, 0, window.getSize().y);
}





/*  Standard constructor.
 *  @param name: name of particle
 *  @param color: color of particle
 *  @param mass: mass of particle
 *  @param radius: radius of particle
 *  @param charge: charge of particle  */
ChargedParticle::ChargedParticle(std::string name, sf::Color color, float mass, float radius, float charge)
: Particle(name, color, mass, radius)
{
    this->charge = charge;
    this->potential_energy = 0.f;
}


/*  Standard constructor.
 *  @param name: name of particle
 *  @param color: color of particle
 *  @param mass: mass of particle
 *  @param radius: radius of particle
 *  @param charge: charge of particle
 *  @param position: position of particle  */
ChargedParticle::ChargedParticle(std::string name, sf::Color color, float mass, float radius, float charge, Vec2D position)
: Particle(name, color, mass, radius, position)
{
    this->charge = charge;
    this->potential_energy = 0.f;
}


/*  Standard constructor.
 *  @param name: name of particle
 *  @param color: color of particle
 *  @param mass: mass of particle
 *  @param radius: radius of particle
 *  @param charge: charge of particle
 *  @param position: position of particle
 *  @param velocity: velocity of particle  */
ChargedParticle::ChargedParticle(std::string name, sf::Color color, float mass, float radius, float charge, Vec2D position, Vec2D velocity)
: Particle(name, color, mass, radius, position, velocity)
{
    this->charge = charge;
    this->potential_energy = 0.f;
}





/*  Standard constructor with automatic bounds-setting.
 *  @param name: name of particle
 *  @param color: color of particle
 *  @param mass: mass of particle
 *  @param radius: radius of particle
 *  @param charge: charge of particle
 *  @param window: reference to window  */
ChargedParticle::ChargedParticle(std::string name, sf::Color color, float mass, float radius, float charge, sf::RenderWindow& window)
: Particle(name, color, mass, radius)
{
    this->charge = charge;
    this->potential_energy = 0.f;
    this->SetBounds(0, window.getSize().x, 0, window.getSize().y);
}


/*  Standard constructor with automatic bounds-setting.
 *  @param name: name of particle
 *  @param color: color of particle
 *  @param mass: mass of particle
 *  @param radius: radius of particle
 *  @param charge: charge of particle
 *  @param position: position of particle
 *  @param window: reference to window  */
ChargedParticle::ChargedParticle(std::string name, sf::Color color, float mass, float radius, float charge, Vec2D position, sf::RenderWindow& window)
: Particle(name, color, mass, radius, position)
{
    this->charge = charge;
    this->potential_energy = 0.f;
    this->SetBounds(0, window.getSize().x, 0, window.getSize().y);
}


/*  Standard constructor with automatic bounds-setting.
 *  @param name: name of particle
 *  @param color: color of particle
 *  @param mass: mass of particle
 *  @param radius: radius of particle
 *  @param charge: charge of particle
 *  @param position: position of particle
 *  @param velocity: velocity of particle
 *  @param window: reference to window  */
ChargedParticle::ChargedParticle(std::string name, sf::Color color, float mass, float radius, float charge, Vec2D position, Vec2D velocity, sf::RenderWindow& window)
: Particle(name, color, mass, radius, position, velocity)
{
    this->charge = charge;
    this->potential_energy = 0.f;
    this->SetBounds(0, window.getSize().x, 0, window.getSize().y);
}










/*  Returns the potential energy that exists 
 *  between this charged particle and another.
 *  @param other: other charged particle  */
float ChargedParticle::ResolvePotentialEnergy(ChargedParticle& other)
{
    return (8.987551787e9f * this->charge * other.charge) / this->Particle::DistanceTo(other);
}





/*  Returns the Coulomb Force between
 *  this charged particle and another.
 *  @param particle: other charged particle  */
Vec2D ChargedParticle::CoulombForce(ChargedParticle& particle)
{
    float force = -(8.987551787e9f * this->charge * particle.charge) / (this->Particle::DistanceTo(particle) * this->Particle::DistanceTo(particle));
    Vec2D vector = force * this->Particle::UnitVectorTo(particle);
    return vector;
}


/*  Returns the Coulomb Force between this charged particle and another,
 *  but with a maximum allowable force, beyond which the force is reduced to the given maximum.
 *  @param particle: other charged particle
 *  @param max_force: maximum allowable force  */
Vec2D ChargedParticle::CoulombForce(ChargedParticle& particle, float max_force)
{
    float force = -(8.987551787e9f * this->charge * particle.charge) / (this->Particle::DistanceTo(particle) * this->Particle::DistanceTo(particle));
    Vec2D vector = force * this->Particle::UnitVectorTo(particle);
    if (vector.magnitude() > max_force)  vector = vector.normalize() * max_force;
    return vector;
}





/*  Updates the charged particle based on
 *  its current state and a nearby charged particle.
 *  @param t: simulation time
 *  @param dt: simulation time step
 *  @param nearby_charge: nearby charged particle  */
void ChargedParticle::Update(double t, float dt, ChargedParticle& nearby_charge)
{
    Particle::Update(t, dt, this->CoulombForce(nearby_charge));
    this->potential_energy = ResolvePotentialEnergy(nearby_charge);
}


/*  Updates the charged particle based on
 *  its current state and a nearby charged particle,
 *  but with a maximum allowable force between the two.
 *  @param t: simulation time
 *  @param dt: simulation time step
 *  @param nearby_charge: nearby charged particle
 *  @param max_force: maximum allowable force  */
void ChargedParticle::Update(double t, float dt, ChargedParticle& nearby_charge, float max_force)
{
    Particle::Update(t, dt, this->CoulombForce(nearby_charge, max_force));
    this->potential_energy = ResolvePotentialEnergy(nearby_charge);
}


/*  Updates the charged particle based on
 *  its current state and a nearby charged particle,
 *  with some applied damping to the updated particle's velocity.
 *  @param t: simulation time
 *  @param dt: simulation time step
 *  @param nearby_charge: nearby charged particle
 *  @param velocity_damping: velocity damping factor (0.f to 1.f)  */
void ChargedParticle::Update(double t, float dt, ChargedParticle& nearby_charge, double velocity_damping)
{
    Particle::Update(t, dt, this->CoulombForce(nearby_charge), velocity_damping);
    this->potential_energy = ResolvePotentialEnergy(nearby_charge);
}


/*  Updates the charged particle based on
 *  its current state and a nearby charged particle,
 *  but with a maximum force allowable between the two,
 *  and some applied damping to the updated particle's velocity.
 *  @param t: simulation time
 *  @param dt: simulation time step
 *  @param nearby_charge: nearby charged particle
 *  @param velocity_damping: velocity damping factor (0.f to 1.f)
 *  @param max_force: maximum allowable force  */
void ChargedParticle::Update(double t, float dt, ChargedParticle& nearby_charge, double velocity_damping, float max_force)
{
    Particle::Update(t, dt, this->CoulombForce(nearby_charge, max_force), velocity_damping);
    this->potential_energy = ResolvePotentialEnergy(nearby_charge);
    // Particle::ResolveCollisionWith(nearby_charge);
}


/*  Updates the charged particle based on
 *  its current state and a nearby charged particle,
 *  but with a maximum force allowable between the two
 *  and a specified restitution coefficient for wall collisions.
 *  @param t: simulation time
 *  @param dt: simulation time step
 *  @param nearby_charge: nearby charged particle
 *  @param collision_restitution: restitution coefficient (0.f to 1.f)
 *  @param max_force: maximum allowable force  */
void ChargedParticle::Update(double t, float dt, ChargedParticle& nearby_charge, float collision_restitution, float max_force)
{
    Particle::Update(t, dt, this->CoulombForce(nearby_charge, max_force), collision_restitution);
    this->potential_energy = ResolvePotentialEnergy(nearby_charge);
}


/*  Updates the charged particle based on
 *  its current state and a nearby charged particle,
 *  but with a maximum force allowable between the two,
 *  a specified restitution coefficient for wall collisions,
 *  and some applied damping to the updated particle's velocity.
 *  @param t: simulation time
 *  @param dt: simulation time step
 *  @param nearby_charge: nearby charged particle
 *  @param velocity_damping: velocity damping factor (0.f to 1.f)
 *  @param collision_restitution: restitution coefficient (0.f to 1.f)
 *  @param max_force: maximum allowable force  */
void ChargedParticle::Update(double t, float dt, ChargedParticle& nearby_charge, double velocity_damping, float collision_restitution, float max_force)
{
    Particle::Update(t, dt, this->CoulombForce(nearby_charge, max_force), velocity_damping, collision_restitution);
    this->potential_energy = ResolvePotentialEnergy(nearby_charge);
}
