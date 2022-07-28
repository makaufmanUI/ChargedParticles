

#include <SFML/Graphics.hpp>






class Wire
{
public:
    float thickness;
    sf::RectangleShape inside;
    sf::RectangleShape outside;

    struct OutsideBounds
    {
        float top;
        float bottom;
        float left;
        float right;
    };  OutsideBounds outside_bounds;


    Wire();
    Wire(const float& thickness);

    void SetBounds(const float& top, const float& bottom, const float& left, const float& right);

    void Draw(sf::RenderWindow& window);

};




Wire::Wire()
{
    thickness = 50.f;
    this->outside = sf::RectangleShape(sf::Vector2f(this->outside_bounds.right-this->outside_bounds.left, this->outside_bounds.bottom-this->outside_bounds.top));
    this->inside = sf::RectangleShape(sf::Vector2f(this->outside_bounds.right-this->outside_bounds.left-2*thickness,this->outside_bounds.bottom-this->outside_bounds.top-2*thickness));
    outside.setPosition(this->outside_bounds.left, this->outside_bounds.top);
    inside.setPosition(this->outside_bounds.left+thickness, this->outside_bounds.top+thickness);
    inside.setFillColor(sf::Color::Black);
    outside.setFillColor(sf::Color::Black);
    inside.setOutlineColor(sf::Color::White);
    outside.setOutlineColor(sf::Color::White);
    inside.setOutlineThickness(-1.f);
    outside.setOutlineThickness(1.f);
}

Wire::Wire(const float& thickness)
{
    this->thickness = thickness;
    this->outside = sf::RectangleShape(sf::Vector2f(this->outside_bounds.right-this->outside_bounds.left, this->outside_bounds.bottom-this->outside_bounds.top));
    this->inside = sf::RectangleShape(sf::Vector2f(this->outside_bounds.right-this->outside_bounds.left-2*thickness,this->outside_bounds.bottom-this->outside_bounds.top-2*thickness));
    outside.setPosition(this->outside_bounds.left, this->outside_bounds.top);
    inside.setPosition(this->outside_bounds.left+thickness, this->outside_bounds.top+thickness);
    inside.setFillColor(sf::Color::Black);
    outside.setFillColor(sf::Color::Black);
    inside.setOutlineColor(sf::Color::White);
    outside.setOutlineColor(sf::Color::White);
    inside.setOutlineThickness(-1.f);
    outside.setOutlineThickness(1.f);
}


void Wire::SetBounds(const float& top, const float& bottom, const float& left, const float& right)
{
    this->outside_bounds.top = top;
    this->outside_bounds.bottom = bottom;
    this->outside_bounds.left = left;
    this->outside_bounds.right = right;
    this->outside = sf::RectangleShape(sf::Vector2f(this->outside_bounds.right-this->outside_bounds.left, this->outside_bounds.bottom-this->outside_bounds.top));
    this->inside = sf::RectangleShape(sf::Vector2f(this->outside_bounds.right-this->outside_bounds.left-2*thickness,this->outside_bounds.bottom-this->outside_bounds.top-2*thickness));
    outside.setPosition(this->outside_bounds.left, this->outside_bounds.top);
    inside.setPosition(this->outside_bounds.left+thickness, this->outside_bounds.top+thickness);
    inside.setFillColor(sf::Color::Black);
    outside.setFillColor(sf::Color::Black);
    inside.setOutlineColor(sf::Color::White);
    outside.setOutlineColor(sf::Color::White);
    inside.setOutlineThickness(-1.f);
    outside.setOutlineThickness(1.f);
}


void Wire::Draw(sf::RenderWindow& window)
{
    window.draw(outside);
    window.draw(inside);
}