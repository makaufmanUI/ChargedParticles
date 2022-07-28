#include <sstream>
#include <iomanip>
#include <iostream>
#include "Events.hpp"
#include "FileWriter.hpp"
#include "ChargedParticle.hpp"

const float PI = 3.14159265359f;

bool showing_trails = true;
bool showing_energy = false;
bool showing_particles = true;
bool counting_particles = true;
bool simulation_running = false;

float new_spawns_mass = 0.000001f;
float new_spawns_charge = 0.00005f;

const float TRAIL_LIFE = 1.2f;
const float TRAIL_SIZE = 1.5f;


float theta;
float cos_theta;
float sin_theta;
float r = 300.f;



namespace utils
{

const int FPS = 120;
const int WIDTH = 1200;
const int HEIGHT = 900;
const Vec2D CENTER = Vec2D(WIDTH/2, HEIGHT/2);








float Random()
{
    return (rand() / (float)RAND_MAX)-(rand() / (float)RAND_MAX);
}



// Mix two sf::Colors together, with equal proportions.
// @param c1: first color
// @param c2: second color
sf::Color Mix(const sf::Color& c1, const sf::Color& c2)
{
    return sf::Color(
        (c1.r + c2.r) / 2,
        (c1.g + c2.g) / 2,
        (c1.b + c2.b) / 2,
        (c1.a + c2.a) / 2
    );
}

// Mix two sf::Colors together, with the specified parts of each color.
// @param c1: first color
// @param c2: second color
// @param p1: percentage/part of first color - i.e. can be decimal percentage, or expressed in "parts", like 3 parts c1 to 2 parts c2
// @param p2: percentage/part of second color - i.e. can be decimal percentage, or expressed in "parts", like 3 parts c1 to 2 parts c2
// @return: mixed color
sf::Color Mix(const sf::Color& c1, const sf::Color& c2, const float& p1, const float& p2)
{
    return sf::Color(
        (int)(c1.r * p1 + c2.r * p2) / (p1 + p2),
        (int)(c1.g * p1 + c2.g * p2) / (p1 + p2),
        (int)(c1.b * p1 + c2.b * p2) / (p1 + p2),
        (int)(c1.a * p1 + c2.a * p2) / (p1 + p2)
    );
}



void WriteToFile(int t, float value1, float value2)
{
    FileWriter* file_writer = new FileWriter("data.txt");
    if(value2 < -0.4f)
        value2 = -0.4f;
    file_writer->AddLine(
        t,
        value1,
        value2);
    delete file_writer;
}


void Clear(sf::RenderWindow& window)
{
    event::CheckForClose(window);
    window.clear(sf::Color::Black);
}



void Update(std::vector<ChargedParticle>& charges, double t, float dt)
{
    for (int i = 0; i < charges.size(); i++)
    for (int j = 0; j < charges.size(); j++)
    if (i != j) charges[i].Update(t, dt, charges[j], double(0.999), 0.001f);
}


void Draw(std::vector<ChargedParticle>& charges, sf::RenderWindow& window)
{
    for (auto& charge : charges)
        charge.Draw(window);
}


float GetForce(ChargedParticle& p1, ChargedParticle& p2)
{
    float force = p1.CoulombForce(p2,0.01f).magnitude();
    if (force*100000.f > 299.f) return 299.f;
    return force*100000.f;
}


float GetKineticEnergy(std::vector<ChargedParticle>& charges)
{
    float ke = 0.f;
    for (auto& charge : charges)
        ke += charge.kinetic_energy;
    if (899.f - abs(ke*1000.f) < 0.f) return 0.f;
    return 899.f - abs(ke*1000.f);
}


float GetPotentialEnergy(std::vector<ChargedParticle>& charges)
{
    float pe = 0.f;
    for (auto& charge : charges)
        pe += charge.potential_energy;
    if (abs(pe*1000.f) > 899.f) return 899.f;
    return abs(pe*1000.f);
}


float GetRawForce(ChargedParticle& p1, ChargedParticle& p2, float max=0.01f)
{
    return p1.CoulombForce(p2,max).magnitude();
}


float GetTotalForce(std::vector<ChargedParticle>& charges, float max=0.01f)
{
    float total_force = 0.f;
    for (int i = 0; i < charges.size(); i++)
    for (int j = 0; j < charges.size(); j++)
    if (i != j) total_force += GetRawForce(charges[i], charges[j], max);
    return total_force;
}


float TotalKineticEnergy(std::vector<ChargedParticle>& charges)
{
    float ke = 0.f;
    for (auto& charge : charges) {
        ke += charge.kinetic_energy;
    }
    if (ke > 0.04f) return 0.04f;
    return ke;
}


float TotalPotentialEnergy(std::vector<ChargedParticle>& charges)
{
    float pe = 0.f;
    for (auto& charge : charges) {
        pe += charge.potential_energy/30.f;
        if (pe < -0.5f)
        pe = -0.5f;
    }
    return pe;
}



struct ParticleCounter
{
    int trail;
    int positive;
    int negative;
    sf::Font font;
    sf::Text trail_text;
    sf::Text positive_text;
    sf::Text negative_text;
    ~ParticleCounter() { /* std::cout << "ParticleCounter destroyed." << std::endl; */ }
    ParticleCounter() : trail(0), positive(0), negative(0) {
        font.loadFromFile("SemiBold.ttf");
        this->trail_text.setFont(this->font);
        this->trail_text.setCharacterSize(24);
        this->positive_text.setFont(this->font);
        this->negative_text.setFont(this->font);
        this->positive_text.setCharacterSize(24);
        this->negative_text.setCharacterSize(24);
        this->trail_text.setFillColor(sf::Color(255,255,255,175));
        this->positive_text.setFillColor(sf::Color(255,255,255,175));
        this->negative_text.setFillColor(sf::Color(255,255,255,175));
        this->trail_text.setString("Trail particles: ");
        this->positive_text.setString("Positive particles: ");
        this->negative_text.setString("Negative particles: ");
        this->trail_text.setOutlineThickness(2.f);
        this->positive_text.setOutlineThickness(2.f);
        this->negative_text.setOutlineThickness(2.f);
        this->positive_text.setOutlineColor(sf::Color(0,0,255,150));
        this->negative_text.setOutlineColor(sf::Color(255,0,0,150));
        this->trail_text.setOutlineColor(Mix(sf::Color(0,0,255,175),sf::Color(255,0,0,175)));
        // std::cout << "ParticleCounter created." << std::endl;
    }
    void Count(const std::vector<ChargedParticle>& charges) {
        for (auto& charge : charges) {
            if (charge.charge > 0)
            ++this->positive;
            else ++this->negative;
            this->trail += charge.trail.size();
        }
    }
    void SetTextStrings() {
        this->trail_text.setString(this->trail_text.getString() + std::to_string(this->trail));
        this->positive_text.setString(this->positive_text.getString() + std::to_string(this->positive));
        this->negative_text.setString(this->negative_text.getString() + std::to_string(this->negative));
    }
    void SetTextPositions() {
        if (this->trail >= 10000)
        this->trail_text.setPosition(Vec2D(884,10));
        else this->trail_text.setPosition(Vec2D(900,10));
        this->positive_text.setPosition(Vec2D(10,10));
        this->negative_text.setPosition(Vec2D(450,10));
    }
    void SetTextPositions(Vec2D pos, Vec2D neg, Vec2D trail) {
        this->trail_text.setPosition(pos);
        this->positive_text.setPosition(neg);
        this->negative_text.setPosition(trail);
    }
    void DrawTo(sf::RenderWindow& window) {
        this->SetTextStrings();
        this->SetTextPositions();
        window.draw(this->trail_text);
        window.draw(this->positive_text);
        window.draw(this->negative_text);
    }
}; // constructor first, then Count(), then SetTextStrings(), then SetTextPositions(), then DrawTo()

void CountParticles(std::vector<ChargedParticle>& charges, sf::RenderWindow& window)
{
    ParticleCounter* particle_counter
    = new ParticleCounter();
    particle_counter->Count(charges);
    particle_counter->DrawTo(window);
    delete particle_counter;
}





struct EnergyCounter
{
    float total;
    float kinetic;
    float potential;
    sf::Font font;
    sf::Text total_text;
    sf::Text kinetic_text;
    sf::Text potential_text;
    
    ~EnergyCounter() { /* std::cout << "EnergyCounter destroyed." << std::endl; */ }
    EnergyCounter() : total(0.f), kinetic(0.f), potential(0.f) {
        font.loadFromFile("SemiBold.ttf");
        this->total_text.setFont(this->font);
        this->total_text.setCharacterSize(24);
        this->total_text.setOutlineThickness(2.f);
        this->total_text.setFillColor(sf::Color(255,255,255,175));
        this->total_text.setOutlineColor(Mix(sf::Color(0,0,255,175),sf::Color(255,0,0,175)));
        this->kinetic_text.setFont(this->font);
        this->kinetic_text.setCharacterSize(24);
        this->kinetic_text.setOutlineThickness(2.f);
        this->kinetic_text.setFillColor(sf::Color(255,255,255,175));
        this->kinetic_text.setOutlineColor(Mix(sf::Color(0,0,255,175),sf::Color(255,0,0,175)));
        this->potential_text.setFont(this->font);
        this->potential_text.setCharacterSize(24);
        this->potential_text.setOutlineThickness(2.f);
        this->potential_text.setFillColor(sf::Color(255,255,255,175));
        this->potential_text.setOutlineColor(Mix(sf::Color(0,0,255,175),sf::Color(255,0,0,175)));
        this->total_text.setString("Total energy: ");
        this->kinetic_text.setString("Kinetic energy: ");
        this->potential_text.setString("Potential energy: ");
        // std::cout << "EnergyCounter created." << std::endl;
    }
    void Count(const std::vector<ChargedParticle>& charges) {
        for (auto& charge : charges) {
            this->kinetic += charge.kinetic_energy;
            this->potential += charge.potential_energy;
            this->total += (charge.kinetic_energy + charge.potential_energy);
        }
        // this->total = std::round(this->total * 1000.f) / 1000.f;
        this->kinetic = std::round(this->kinetic * 1000.f) / 1000.f;
        // this->potential = std::round(this->potential * 1000.f) / 1000.f;
    }
    void SetTextStrings() {
        std::ostringstream kinetic_stream, potential_stream, total_stream;
        total_stream << std::setprecision(3) << this->total;
        kinetic_stream << std::setprecision(3) << this->kinetic;
        potential_stream << std::setprecision(3) << this->potential;
        this->total_text.setString(this->total_text.getString() + total_stream.str());
        this->kinetic_text.setString(this->kinetic_text.getString() + kinetic_stream.str());
        this->potential_text.setString(this->potential_text.getString() + potential_stream.str());
    }
    void SetTextPositions() {
        this->kinetic_text.setPosition(Vec2D(900,866));
        this->potential_text.setPosition(Vec2D(10,866));
        this->total_text.setPosition(Vec2D(480,866));
    }
    void DrawTo(sf::RenderWindow& window) {
        this->SetTextStrings();
        this->SetTextPositions();
        window.draw(this->total_text);
        window.draw(this->kinetic_text);
        window.draw(this->potential_text);
    }
};


void CountEnergies(std::vector<ChargedParticle>& charges, sf::RenderWindow& window)
{
    EnergyCounter* energy_counter
    = new EnergyCounter();
    energy_counter->Count(charges);
    energy_counter->DrawTo(window);
    delete energy_counter;
}






void ToggleLocationVectors(std::vector<ChargedParticle>& charges, Events& events)
{
    if (events.GetTime()-events.last_l > 0.25f)
    {
        events.last_l = events.GetTime();
        bool current_state = charges.back().showing_location_vector;
        if (current_state)
            for (auto& charge : charges)
            charge.DisableLocationVector();
        else
            for (auto& charge : charges)
            charge.EnableLocationVector();
    }
}



void ToggleParticles(Events& events)
{
    if (events.GetTime()-events.last_p > 0.25f) {
        events.last_p = events.GetTime();
        showing_particles = !showing_particles;
    }
}



void ToggleParticleCounter(Events& events)
{
    if (events.GetTime()-events.last_c > 0.25f) {
        events.last_c = events.GetTime();
        counting_particles = !counting_particles;
    }
}



void ToggleEnergyInfo(Events& events)
{
    if (events.GetTime()-events.last_e > 0.25f) {
        events.last_e = events.GetTime();
        showing_energy = !showing_energy;
    }
}



void ToggleTrails(std::vector<ChargedParticle>& charges, Events& events)
{
    if (events.GetTime()-events.last_t > 0.25f)
    {
        events.last_t = events.GetTime();
        showing_trails = !showing_trails;
        for (auto& charge : charges) {
            if (charge.trail_enabled && !showing_trails) {
                for (auto& particle : charge.trail)
                    particle->MarkForDestruction();
                charge.UpdateTrail(5.f);
            }
            charge.trail_enabled = showing_trails;
        }
    }
}



void SpawnPositiveCharge(std::vector<ChargedParticle>& charges, sf::RenderWindow& window, Events& events)
{
    if (events.GetTime()-events.last_left_click > 0.5f)
    {
        bool location_vectors_showing = charges.back().showing_location_vector;
        events.last_left_click = events.GetTime();
        charges.emplace_back(
            ChargedParticle("+", 5.0f, Vec2D(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), window)
        );  charges.back().charge = new_spawns_charge;
        if (!showing_trails)
        charges.back().DisableTrail();
        else {
            charges.back().SetTrailLifetime(TRAIL_LIFE);
            charges.back().SetTrailColor(Mix(Mix(charges.back().color, sf::Color::White), charges.back().color));
            if (charges[charges.size()-2].trail_size_set) charges.back().SetTrailSize(charges[charges.size()-2].trail_size);
        }
        if (location_vectors_showing) charges.back().EnableLocationVector();
    }
}



void SpawnPositiveCharges(std::vector<ChargedParticle>& charges, sf::RenderWindow& window)
{
    bool location_vectors_showing = charges.back().showing_location_vector;
    charges.emplace_back(
        ChargedParticle("+", 5.0f, Vec2D(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), window)
    );  charges.back().charge = new_spawns_charge;
    if (!showing_trails)
    charges.back().DisableTrail();
    else {
        charges.back().SetTrailLifetime(TRAIL_LIFE);
        charges.back().SetTrailColor(Mix(Mix(charges.back().color, sf::Color::White), charges.back().color));
        if (charges[charges.size()-2].trail_size_set) charges.back().SetTrailSize(charges[charges.size()-2].trail_size);
    }
    if (location_vectors_showing) charges.back().EnableLocationVector();
}



void SpawnNegativeCharge(std::vector<ChargedParticle>& charges, sf::RenderWindow& window, Events& events)
{
    if (events.GetTime()-events.last_right_click > 0.5f)
    {
        bool location_vectors_showing = charges.back().showing_location_vector;
        events.last_right_click = events.GetTime();
        charges.emplace_back(
            ChargedParticle("-", 5.0f, Vec2D(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), window)
        );  charges.back().charge = -new_spawns_charge;
        if (!showing_trails)
        charges.back().DisableTrail();
        else {
            charges.back().SetTrailLifetime(TRAIL_LIFE);
            charges.back().SetTrailColor(Mix(Mix(charges.back().color, sf::Color::White), charges.back().color));
            if (charges[charges.size()-2].trail_size_set) charges.back().SetTrailSize(charges[charges.size()-2].trail_size);
        }
        if (location_vectors_showing) charges.back().EnableLocationVector();
    }
}



void SpawnNegativeCharges(std::vector<ChargedParticle>& charges, sf::RenderWindow& window)
{
    bool location_vectors_showing = charges.back().showing_location_vector;
    charges.emplace_back(
        ChargedParticle("-", 5.0f, Vec2D(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), window)
    );  charges.back().charge = -new_spawns_charge;
    if (!showing_trails)
    charges.back().DisableTrail();
    else {
        charges.back().SetTrailLifetime(TRAIL_LIFE);
        charges.back().SetTrailColor(Mix(Mix(charges.back().color, sf::Color::White), charges.back().color));
        if (charges[charges.size()-2].trail_size_set) charges.back().SetTrailSize(charges[charges.size()-2].trail_size);
    }
    if (location_vectors_showing) charges.back().EnableLocationVector();
}



void HandleInputEvents(std::vector<ChargedParticle>& charges, sf::RenderWindow& window, Events& events)
{
    if (events.PPressed())
        ToggleParticles(events);
    if (events.EPressed())
        ToggleEnergyInfo(events);
    if (events.CPressed())
        ToggleParticleCounter(events);
    if (events.TPressed())
        ToggleTrails(charges, events);
    if (events.LPressed())
        ToggleLocationVectors(charges, events);
    if (events.CtrlLeftClick())
        SpawnPositiveCharges(charges, window);
    if (events.CtrlRightClick())
        SpawnNegativeCharges(charges, window);
    if (events.LeftClick())
        SpawnPositiveCharge(charges, window, events);
    if (events.RightClick())
        SpawnNegativeCharge(charges, window, events);
}



void PauseSimulation(std::vector<ChargedParticle>& charges, sf::RenderWindow& window, Events& events)
{
    if (events.GetTime()-events.last_escape > 0.5f && simulation_running)
    {
        simulation_running = false;
        events.last_escape = events.GetTime();
        while (true)
        {
            Clear(window);
            if (showing_energy)
            CountEnergies(charges, window);
            if (counting_particles)
            CountParticles(charges, window);
            HandleInputEvents(charges, window, events);
            if (showing_particles)
            Draw(charges, window);
            else for (auto& charge : charges)
            charge.DrawTrail(window);
            window.display();
            if (events.SpacePressed()) {
                simulation_running = true;
                break;
            }
        }
        return;
    }
    return;
}



void WaitForSpacebar(std::vector<ChargedParticle>& charges, sf::RenderWindow& window, Events& events)
{
    while (true)
    {
        Clear(window);
        if (showing_energy)
        CountEnergies(charges, window);
        if (counting_particles)
        CountParticles(charges, window);
        HandleInputEvents(charges, window, events);
        if (showing_particles)
        Draw(charges, window);
        else for (auto& charge : charges)
        charge.DrawTrail(window);
        window.display();
        if (events.SpacePressed() || (!window.isOpen())) {
            simulation_running = true;
            break;
        }
    }
    return;
}






};