/********************
*
*    DrawableVec2D.hpp
*    Created by:   Matt Kaufman
*    
*    Defines the DrawableVec2D class,
*    which inherits from the Vec2D class, 
*    to define a graphical version of Vec2D with drawable vectors.
*
*********************/

#include "Vec2D.hpp"    // includes:  <cmath> and <SFML/Graphics.hpp>


/*  A graphical 2D vector class. 
 *  Inherits from the Vec2D class,
 *  and incorporates several new methods 
 *  for drawing the vectors to the screen.  */
class DrawableVec2D : Vec2D
{
public:
    float angle;                // The angle the vector makes with the +x axis, in radians.
    float angle_deg;            // The angle the vector makes with the +x axis, in degrees.
    float angle_between;        // The angle between the vector and another vector, in radians.
    float angle_between_deg;    // The angle between the vector and another vector, in degrees.
    sf::CircleShape head;       // The head of the vector, which is a circle.
    sf::RectangleShape tail;    // The tail of the vector, which is a rectangle.
    bool using_global_coordinates = true;   // Whether or not the vector is using global coordinates.

    struct Properties {
        float length;           // The length of the vector.
        sf::Color color;        // The color of the vector.
        float head_angle;       // The angle of the head of the vector, as measured from the tail.
        Vec2D head_center;      // The location of the center of the head of the vector.
        float head_radius;      // need to set this, as a function of what the tail thickness is, and add to all constructors
        float tail_thickness;   // The thickness of the tail of the vector.
        sf::Color outlineColor; // The color of the outline of the vector.
        float outlineThickness; // The thickness of the outline of the vector.
        
        Properties() : length(0.f), color(sf::Color::White), head_angle(0.f), head_center(0.f,0.f), head_radius(6.f), tail_thickness(2.f), outlineColor(sf::Color::White), outlineThickness(0.f) {}
    };  Properties properties;


    ~DrawableVec2D() { }

    /* Default constructor (0, 0). */
    DrawableVec2D();
    /* Constructor with defined x and y floats. */
    DrawableVec2D(const float& x, const float& y);
    /* Copy constructor (copy a sf::Vector2f vector). */
    DrawableVec2D(const sf::Vector2f& vec);
    /* Copy constructor (copy a Vec2D vector). */
    DrawableVec2D(const Vec2D& vec);

    DrawableVec2D(const sf::Color& color, const float& tail_thickness);
    DrawableVec2D(const float& x, const float& y, const sf::Color& color, const float& tail_thickness);
    DrawableVec2D(const sf::Vector2f& vec, const sf::Color& color, const float& tail_thickness);
    DrawableVec2D(const Vec2D& vec, const sf::Color& color, const float& tail_thickness);

    DrawableVec2D(const Vec2D& start_pos, const Vec2D& end_pos);


    void Draw(sf::RenderWindow& window);

    // Only works when vector is pointing down and to the right
    void DrawFrom(const Vec2D& location, sf::RenderWindow& window);
    void DrawFromTopLeft(sf::RenderWindow& window);
};




DrawableVec2D::DrawableVec2D()
: Vec2D()
{
    this->angle = 0.f;
    this->properties.length = 0.f;
    this->head = sf::CircleShape(this->properties.head_radius, 3);
    this->tail = sf::RectangleShape(sf::Vector2f(this->properties.length, this->properties.tail_thickness));
    this->head.setFillColor(this->properties.color);
    this->head.setOutlineColor(this->properties.outlineColor);
    this->head.setOutlineThickness(this->properties.outlineThickness);
    this->tail.setFillColor(this->properties.color);
    this->tail.setOutlineColor(this->properties.outlineColor);
    this->tail.setOutlineThickness(this->properties.outlineThickness);
}


DrawableVec2D::DrawableVec2D(const float& x, const float& y)
: Vec2D(x, y)
{
    this->angle = this->Vec2D::angle();
    this->properties.length = this->Vec2D::magnitude();
    this->head = sf::CircleShape(this->properties.head_radius, 3);
    this->tail = sf::RectangleShape(sf::Vector2f(this->properties.length, this->properties.tail_thickness));
    this->head.setFillColor(this->properties.color);
    this->head.setOutlineColor(this->properties.outlineColor);
    this->head.setOutlineThickness(this->properties.outlineThickness);
    this->tail.setFillColor(this->properties.color);
    this->tail.setOutlineColor(this->properties.outlineColor);
    this->tail.setOutlineThickness(this->properties.outlineThickness);
}


DrawableVec2D::DrawableVec2D(const sf::Vector2f& vec)
: Vec2D(vec)
{
    this->angle = this->Vec2D::angle();
    this->properties.length = this->Vec2D::magnitude();
    this->head = sf::CircleShape(this->properties.head_radius, 3);
    this->tail = sf::RectangleShape(sf::Vector2f(this->properties.length, this->properties.tail_thickness));
    this->head.setFillColor(this->properties.color);
    this->head.setOutlineColor(this->properties.outlineColor);
    this->head.setOutlineThickness(this->properties.outlineThickness);
    this->tail.setFillColor(this->properties.color);
    this->tail.setOutlineColor(this->properties.outlineColor);
    this->tail.setOutlineThickness(this->properties.outlineThickness);
}


DrawableVec2D::DrawableVec2D(const Vec2D& vec)
: Vec2D(vec)
{
    this->angle = this->Vec2D::angle();
    this->properties.length = this->Vec2D::magnitude();
    this->head = sf::CircleShape(this->properties.head_radius, 3);
    this->tail = sf::RectangleShape(sf::Vector2f(this->properties.length, this->properties.tail_thickness));
    this->head.setFillColor(this->properties.color);
    this->head.setOutlineColor(this->properties.outlineColor);
    this->head.setOutlineThickness(this->properties.outlineThickness);
    this->tail.setFillColor(this->properties.color);
    this->tail.setOutlineColor(this->properties.outlineColor);
    this->tail.setOutlineThickness(this->properties.outlineThickness);
}


DrawableVec2D::DrawableVec2D(const sf::Color& color, const float& tail_thickness)
: Vec2D()
{
    this->angle = 0.f;
    this->properties.length = 0.f;
    this->properties.color = color;
    this->properties.tail_thickness = tail_thickness;
    this->head = sf::CircleShape(this->properties.head_radius, 3);
    this->tail = sf::RectangleShape(sf::Vector2f(this->properties.length, tail_thickness));
    this->head.setFillColor(color);
    this->head.setOutlineColor(this->properties.outlineColor);
    this->head.setOutlineThickness(this->properties.outlineThickness);
    this->tail.setFillColor(color);
    this->tail.setOutlineColor(this->properties.outlineColor);
    this->tail.setOutlineThickness(this->properties.outlineThickness);
}


DrawableVec2D::DrawableVec2D(const float& x, const float& y, const sf::Color& color, const float& tail_thickness)
: Vec2D(x, y)
{
    this->angle = this->Vec2D::angle();
    this->properties.length = this->Vec2D::magnitude();
    this->properties.color = color;
    this->properties.tail_thickness = tail_thickness;
    this->head = sf::CircleShape(this->properties.head_radius, 3);
    this->tail = sf::RectangleShape(sf::Vector2f(this->properties.length, tail_thickness));
    this->head.setFillColor(color);
    this->head.setOutlineColor(this->properties.outlineColor);
    this->head.setOutlineThickness(this->properties.outlineThickness);
    this->tail.setFillColor(color);
    this->tail.setOutlineColor(this->properties.outlineColor);
    this->tail.setOutlineThickness(this->properties.outlineThickness);
}


DrawableVec2D::DrawableVec2D(const sf::Vector2f& vec, const sf::Color& color, const float& tail_thickness)
: Vec2D(vec)
{
    this->angle = this->Vec2D::angle();
    this->properties.length = this->Vec2D::magnitude();
    this->properties.color = color;
    this->properties.tail_thickness = tail_thickness;
    this->head = sf::CircleShape(this->properties.head_radius, 3);
    this->tail = sf::RectangleShape(sf::Vector2f(this->properties.length, tail_thickness));
    this->head.setFillColor(color);
    this->head.setOutlineColor(this->properties.outlineColor);
    this->head.setOutlineThickness(this->properties.outlineThickness);
    this->tail.setFillColor(color);
    this->tail.setOutlineColor(this->properties.outlineColor);
    this->tail.setOutlineThickness(this->properties.outlineThickness);
}


DrawableVec2D::DrawableVec2D(const Vec2D& vec, const sf::Color& color, const float& tail_thickness)
: Vec2D(vec)
{
    this->angle = this->Vec2D::angle();
    this->properties.length = this->Vec2D::magnitude();
    this->properties.color = color;
    this->properties.tail_thickness = tail_thickness;
    this->head = sf::CircleShape(this->properties.head_radius, 3);
    this->tail = sf::RectangleShape(sf::Vector2f(this->properties.length, tail_thickness));
    this->head.setFillColor(color);
    this->head.setOutlineColor(this->properties.outlineColor);
    this->head.setOutlineThickness(this->properties.outlineThickness);
    this->tail.setFillColor(color);
    this->tail.setOutlineColor(this->properties.outlineColor);
    this->tail.setOutlineThickness(this->properties.outlineThickness);
}





DrawableVec2D::DrawableVec2D(const Vec2D& start_pos, const Vec2D& end_pos)
{
    float distance_between_points = start_pos.distanceTo(end_pos);

    this->head = sf::CircleShape(this->properties.head_radius, 3);
    this->head.setFillColor(this->properties.color);

    this->properties.length = distance_between_points;
    this->tail = sf::RectangleShape(sf::Vector2f(this->properties.length, this->properties.tail_thickness));
    this->tail.setFillColor(this->properties.color);
    // this->tail.setPosition(start_pos.x, start_pos.y - (this->properties.tail_thickness/2.f));
    this->tail.setPosition(start_pos.x + (cos(this->angle2pi())*2), start_pos.y + (sin(this->angle2pi()))*2);
    std::cout << (cos(this->angle)) << std::endl;
    // std::cout << this->properties.head_center << std::endl;
    // std::cout << "LOCAL:  " << this->head.getLocalBounds().height << " , " << this->head.getLocalBounds().width << " , " << this->head.getLocalBounds().left << " , " << this->head.getLocalBounds().top << std::endl;
    // std::cout << "GLOBAL: " << this->head.getGlobalBounds().height << " , " << this->head.getGlobalBounds().width << " , " << this->head.getGlobalBounds().left << " , " << this->head.getGlobalBounds().top << std::endl;
    // std::cout << "LOCAL CENTER: " << this->head.getLocalBounds().left + this->head.getLocalBounds().width / 2.f << " , " << this->head.getLocalBounds().top + this->head.getLocalBounds().height / 2.f << std::endl;
    // std::cout << "GLOBAL CENTER: " << this->head.getGlobalBounds().left + this->head.getGlobalBounds().width / 2.f << " , " << this->head.getGlobalBounds().top + this->head.getGlobalBounds().height / 2.f << std::endl;

    // this->properties.head_center = sf::Vector2f(this->head.getGlobalBounds().left + this->head.getGlobalBounds().width / 2.f, this->head.getGlobalBounds().top + this->head.getGlobalBounds().height / 2.f);
    // // set the position of the head such that it is centered on the end position
    // // this->head.setPosition(end_pos.x - this->properties.head_center.x, end_pos.y - this->properties.head_center.y);
    // std::cout << "properties.head_center: " << this->properties.head_center.x << " , " << this->properties.head_center.y << std::endl;


    

    Vec2D delta_vector = end_pos - start_pos;
    Vec2D delta_vector_flipped = delta_vector.flipX();

    float delta_angle = delta_vector.angle();
    float delta_angle_deg = delta_angle * 180.f / 3.14159265359f;
    float delta_angle2pi = delta_vector.angle2pi();
    float delta_angle2pi_deg = delta_angle2pi * 180.f / 3.14159265359f;
    float delta_flipped_angle = delta_vector_flipped.angle();
    float delta_flipped_angle_deg = delta_flipped_angle * 180.f / 3.14159265359f;
    float delta_flipped_angle2pi = delta_vector_flipped.angle2pi();
    float delta_flipped_angle2pi_deg = delta_flipped_angle2pi * 180.f / 3.14159265359f;

    this->head.setRotation(90.f - delta_flipped_angle_deg);

    sf::FloatRect head_bounds = this->head.getGlobalBounds();
    float head_width = head_bounds.width;
    float head_height = head_bounds.height;
    float head_left = head_bounds.left;
    float head_top = head_bounds.top;

    float head_center_x = head_left + head_width / 2.f;
    float head_center_y = head_top + head_height / 2.f;

    sf::FloatRect tail_bounds = this->tail.getGlobalBounds();
    float tail_width = tail_bounds.width;
    float tail_height = tail_bounds.height;
    float tail_left = tail_bounds.left;
    float tail_top = tail_bounds.top;

    float tail_center_x = tail_left + tail_width / 2.f;
    float tail_center_y = tail_top + tail_height / 2.f;

    std::cout << "HEAD BOUNDS: " <<
    "left: " << head_left << " , " <<
    "top: " << head_top << " , " <<
    "width: " << head_width << " , " <<
    "height: " << head_height << std::endl;
    std::cout << "HEAD CENTER: " <<
    "x: " << head_center_x << " , " <<
    "y: " << head_center_y << std::endl << std::endl;

    std::cout << "TAIL BOUNDS: " <<
    "left: " << tail_left << " , " <<
    "top: " << tail_top << " , " <<
    "width: " << tail_width << " , " <<
    "height: " << tail_height << std::endl;
    std::cout << "TAIL CENTER: " <<
    "x: " << tail_center_x << " , " <<
    "y: " << tail_center_y << std::endl << std::endl;


    
    this->properties.head_center = Vec2D(head_center_x, head_center_y);
    // set the starting position of the tail at the location of start_pos
    

    // set the angle of the tail to the angle of the delta vector
    // this->tail.setRotation(360.f - delta_angle2pi_deg);
    this->tail.setRotation(360.f - delta_flipped_angle2pi_deg);
    // std::cout << this->tail.getPosition().x << " , " << this->tail.getPosition().y << std::endl;
    std::cout << "head rotation: " << this->head.getRotation() << std::endl;
    // set the angle of the head to the angle of the delta vector
    // this->head.setRotation(90.f - delta_flipped_angle_deg);
    // set the head position such that it is centered on the end position
    // this->head.setPosition(end_pos.x, end_pos.y);
    // this->head.setPosition(end_pos.x - this->properties.head_center.x, end_pos.y - this->properties.head_center.y);
    // this->head.setPosition(end_pos.x + this->properties.head_center.x, end_pos.y + this->properties.head_center.y);
    this->head.setPosition(end_pos.x + (this->properties.head_radius), end_pos.y + (this->properties.head_radius));
    // this->head.setRotation(90.f - delta_angle_deg);
    

    // this->angle = start_pos.angleBetween(end_pos);
    // this->angle_deg = this->angle * 180.f / 3.14159265359f;
    // std::cout << this->angle_deg << std::endl;
}



void DrawableVec2D::Draw(sf::RenderWindow& window)
{
    window.draw(this->tail);
    window.draw(this->head);
}




void DrawableVec2D::DrawFromTopLeft(sf::RenderWindow& window)
{
    this->tail.setPosition(0, 0 - (this->properties.tail_thickness/2.f));
    Vec2D flipped_vec = this->Vec2D::flipX();
    float head_adjustment = 1 + ((6.28318530718f - flipped_vec.angle()) / 1.2853981633975f);
    float head_adjustment_x = (1.05f - ((6.28318530718f - flipped_vec.angle()) / 3.14159265359f)) + ((6.28318530718f - flipped_vec.angle()) / 2.3853981633975f);
    float head_adjustment_y = (1.f + ((6.28318530718f - flipped_vec.angle()) / 3.14159265359f)) + ((6.28318530718f - flipped_vec.angle()) / 0.7853981633975f);
    this->head.setPosition(this->x + this->properties.head_radius/head_adjustment_x, this->y - this->properties.head_radius/head_adjustment_y);
    this->head.setRotation( ((1.570796326795f - flipped_vec.angle()) * 57.295779513078f ));
    this->tail.setRotation( 360 - (57.295779513078f * (6.28318530718f - this->Vec2D::angle2pi())) );
    window.draw(this->head);
    window.draw(this->tail);
}



void DrawableVec2D::DrawFrom(const Vec2D& location, sf::RenderWindow& window)
{
    this->tail.setPosition(location.x, location.y - (this->properties.tail_thickness/2.f));
    Vec2D flipped_vec = this->Vec2D::flipX();
    float head_adjustment = 1 + ((6.28318530718f - flipped_vec.angle()) / 1.2853981633975f);
    float head_adjustment_x = (1.05f - ((6.28318530718f - flipped_vec.angle()) / 3.14159265359f)) + ((6.28318530718f - flipped_vec.angle()) / 2.3853981633975f);
    float head_adjustment_y = (1.f + ((6.28318530718f - flipped_vec.angle()) / 3.14159265359f)) + ((6.28318530718f - flipped_vec.angle()) / 0.7853981633975f);
    this->head.setPosition(location.x + (this->magnitude()*cos(this->angle)) + this->properties.head_radius/head_adjustment_x, (this->magnitude()*sin(this->angle)) + location.y - this->properties.head_radius/head_adjustment_y);
    this->head.setRotation( ((1.570796326795f - flipped_vec.angle()) * 57.295779513078f ));
    this->tail.setRotation( 360 - (57.295779513078f * (6.28318530718f - this->Vec2D::angle2pi())) );
    window.draw(this->head);
    window.draw(this->tail);
}