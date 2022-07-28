/********************
*
*    Application.hpp
*    Created by:   Matt Kaufman
*    
*    Defines the Application class,
*    which provides an interface for managing a RenderWindow and Views.
*
*********************/

#include "Vec2D.hpp"
#include <SFML/Graphics.hpp>





class Application
{
public:
    Vec2D size;
    sf::View view;
    std::string title;
    unsigned int framerate;
    sf::RenderWindow window;
    sf::ContextSettings settings;
    unsigned int anti_aliasing_level;


    Application(const std::string& title, const Vec2D& size);
    Application(const std::string& title, const Vec2D& size, unsigned int framerate);
    
    
    void Close();
    void Clear();
    void Display();
    void Draw(sf::Drawable& drawable);
    void Draw(std::vector<sf::Drawable*>& drawables);

    void SetView(const Vec2D& center, const float zoom);
    void SetView(const Vec2D& center, const float zoom, const Vec2D& size);

    bool IsOpen();
    bool IsClosed();
    bool IsFocused();
    bool IsNotFocused();

    bool WasResized();
    void UpdateViewIfResized();

    void SetFramerate(unsigned int framerate);
    void SetTitle(const std::string& title);
    void SetSize(const Vec2D& size);
    void SetPosition(const Vec2D& position);
};



Application::Application(const std::string& title, const Vec2D& size) :
size(size),
view(sf::FloatRect(0,0,size.x,size.y)),
title(title),
framerate(60),
anti_aliasing_level(4)
{
    settings.antialiasingLevel = anti_aliasing_level;
    window.create(sf::VideoMode(size.x, size.y), title, sf::Style::Default, settings);
    window.setFramerateLimit(framerate);
    window.setView(view);
}


Application::Application(const std::string& title, const Vec2D& size, unsigned int framerate) :
size(size),
view(sf::FloatRect(0,0,size.x,size.y)),
title(title),
framerate(framerate),
anti_aliasing_level(4)
{
    settings.antialiasingLevel = anti_aliasing_level;
    window.create(sf::VideoMode(size.x, size.y), title, sf::Style::Default, settings);
    window.setFramerateLimit(framerate);
    window.setView(view);
}




void Application::Close()
{
    window.close();
}


void Application::Clear()
{
    window.clear();
}


void Application::Display()
{
    window.display();
}


void Application::Draw(sf::Drawable& drawable)
{
    window.draw(drawable);
}


void Application::Draw(std::vector<sf::Drawable*>& drawables)
{
    for (auto& drawable : drawables)
        window.draw(*drawable);
}


void Application::SetView(const Vec2D& center, const float zoom)
{
    view.setCenter(center.x, center.y);
    view.setSize(size.x*zoom, size.y*zoom);
    window.setView(view);
}


void Application::SetView(const Vec2D& center, const float zoom, const Vec2D& size)
{
    view.setCenter(center.x, center.y);
    view.setSize(size.x*zoom, size.y*zoom);
    window.setView(view);
}


bool Application::IsOpen()
{
    return window.isOpen();
}


bool Application::IsClosed()
{
    return !window.isOpen();
}


bool Application::IsFocused()
{
    return window.hasFocus();
}


bool Application::IsNotFocused()
{
    return !window.hasFocus();
}


bool Application::WasResized()
{
    sf::Event event {};
    while (window.pollEvent(event))
        if (event.type == sf::Event::Resized)
            return true;
    return false;
}


void Application::UpdateViewIfResized()
{
    sf::Event event {};
    while (window.pollEvent(event))
        if (event.type == sf::Event::Resized) {
            sf::FloatRect visible_area(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visible_area));
        }
}


void Application::SetFramerate(unsigned int framerate)
{
    window.setFramerateLimit(framerate);
}


void Application::SetTitle(const std::string& title)
{
    window.setTitle(title);
}


void Application::SetSize(const Vec2D& size)
{
    window.setSize(sf::Vector2u(size.x, size.y));
}


void Application::SetPosition(const Vec2D& position)
{
    window.setPosition(sf::Vector2i(position.x, position.y));
}