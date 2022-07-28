// TODO: 
// spacebar: play simulation, escape: pause simulation
#include "sim/Utils.hpp"

using namespace sf;
using namespace utils;
typedef ChargedParticle Charge;

const int PLOT_SPEED = 60;      // plots per second
const float SIM_SPEED = 1.f;    // simulation speed

int n = 0;
float t = 0.f;
float dt = SIM_SPEED / float(FPS);





int main()
{
    ContextSettings settings;  settings.antialiasingLevel = 4;
    RenderWindow window(VideoMode(WIDTH,HEIGHT), "Charges", Style::Default, settings);
    window.setFramerateLimit(FPS);
    Events events = Events(window);

    std::vector<Charge> charges;
    charges.emplace_back(Charge("+", 5.f, Vec2D(500,400), Vec2D(0,0), window));
    charges.emplace_back(Charge("-", 5.f, Vec2D(700,500), Vec2D(0,0), window));


    for (auto& charge : charges)
    {
        if (!showing_trails)
            charge.DisableTrail();
        else {
            charge.SetTrailSize(TRAIL_SIZE);
            charge.SetTrailLifetime(TRAIL_LIFE);
            charge.SetTrailColor(Mix(charge.color,sf::Color::White,3,1));
        }
        // charge.showing_location_vector = true;
    }
    
    /* Wait for input to start simulation */
    WaitForSpacebar(charges, window, events);
    if (!window.isOpen()) return EXIT_SUCCESS;


    float start_time = 0.f;
    /* Main loop */
    while (window.isOpen())
    {
        Clear(window);
        Update(charges, t,dt);
        // for (auto& charge : charges) {
        //     if (charge.kinematics.velocity.magnitude() < 10)
        //     for (auto& tp : charge.trail)
        //     if (tp->age > tp->lifetime/1.5f)
        //     tp->age = tp->lifetime;
        // }
        
        

        if (showing_particles)
        Draw(charges, window);
        else for (auto& charge : charges)
        charge.DrawTrail(window);

        if (showing_energy)
        CountEnergies(charges, window);
        if (counting_particles)
        CountParticles(charges, window);


        // for (auto& charge : charges)
        // if (charge.kinematics.velocity.magnitude() > 200.f) {
        //     // charge.charge *= -1;
        //     // charge.kinematics.velocity = charge.kinematics.velocity.randomize().normalize() * 100.f;
        //     // if (n % 2 == 0)
        //     //      charge.kinematics.velocity = charge.kinematics.velocity.normal().randomize().normalize() * 100.f;
        //     // else charge.kinematics.velocity = charge.kinematics.velocity.tangent().randomize().normalize() * 100.f;
        //     // charge.kinematics.velocity = charge.kinematics.velocity.normal().randomize().normalize() * 100.f;
        //     charge.kinematics.velocity *= Random();
        //     // charge.kinematics.velocity = charge.kinematics.velocity.randomize() / 2.f;
        //     // std::cout << "Acceleration: " << charge.kinematics.acceleration.magnitude() << std::endl;
        // }
        
        // for (int i = 0; i < charges.size(); i++) {
        //     // compute the distance between the i'th charge and all other charges
        //     for (int j = i + 1; j < charges.size(); j++) {
        //         float distance = charges[i].DistanceTo(charges[j]);
        //         float angular_velocity1 = charges[i].kinematics.velocity.magnitude() / distance;
        //         float angular_velocity2 = charges[j].kinematics.velocity.magnitude() / distance;
        //         if (n % 2 == 0) {
        //             std::cout << std::endl << "Angular velocities: " << angular_velocity1 << " , " << angular_velocity2 << std::endl;
        //             std::cout << "Actual angular velocities: " << charges[i].kinematics.angular_velocity << " , " << charges[j].kinematics.angular_velocity << std::endl;
        //         }
                
        //         // if (distance < charges[i].radius + charges[j].radius) {

        //         // }
        //         // std::cout << "Too close of an orbit: " << distance << std::endl;
        //     }
        // }


        /* Events */
        HandleInputEvents(charges, window, events);
        if (events.EscapePressed()) PauseSimulation(charges, window, events);


        // if (n % (FPS/PLOT_SPEED) == 0)
        // {
        //     WriteToFile(n/8,
        //     TotalKineticEnergy(charges),
        //     TotalPotentialEnergy(charges));
        // }


        // test_particle.MoveCenterTo(CENTER + Vec2D(r*cos_theta, r*sin_theta));
        // test_particle.Draw(window);



        n++;
        t += dt;
        // theta = fmod
        // (((float(n)/float(FPS))*2*PI), (2*PI));
        // cos_theta = cos(theta);
        // sin_theta = sin(theta);
        window.display();
    }

    return EXIT_SUCCESS;
}
