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

        if (showing_particles)
        Draw(charges, window);
        else for (auto& charge : charges)
        charge.DrawTrail(window);

        if (showing_energy)
        CountEnergies(charges, window);
        if (counting_particles)
        CountParticles(charges, window);

        /* Events */
        HandleInputEvents(charges, window, events);
        if (events.EscapePressed()) PauseSimulation(charges, window, events);


        n++;
        t += dt;
        window.display();
    }

    return EXIT_SUCCESS;
}
