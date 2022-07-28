#include <SFML/Graphics.hpp>
namespace event
{






// Hanldes the event of closing the window
// @param window: the window to close
void CheckForClose(sf::RenderWindow& window)
{
    sf::Event e {};
    while (window.pollEvent(e))
        if (e.type == sf::Event::Closed)
            window.close();
}


bool LeftClick()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
bool RightClick()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Right);
}





}





class Events
{
public:
    sf::Clock clock;
    sf::RenderWindow& window;
    float last_l = 0.f;
    float last_p = 0.f;
    float last_t = 0.f;
    float last_c = 0.f;
    float last_e = 0.f;
    float last_up = 0.f;
    float last_down = 0.f;
    float last_space = 0.f;
    float last_escape = 0.f;
    float last_shift_space = 0.f;
    float last_left_click  = 0.f;
    float last_right_click = 0.f;
    float last_shift_escape = 0.f;

    Events(sf::RenderWindow& window) : window(window) { clock.restart(); }

    void CheckForClose()
    {
        event::CheckForClose(window);
    }

    bool HasFocus()
    {
        return window.hasFocus();
    }

    bool NoModifiersPressed()
    {
        return !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
               !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) &&
               !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
               !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) &&
               !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) &&
               !sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);
    }


    bool LeftClick()         { return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && HasFocus() && NoModifiersPressed()); }

    bool RightClick()        { return (sf::Mouse::isButtonPressed(sf::Mouse::Right) && HasFocus() && NoModifiersPressed()); }

    bool CtrlLeftClick()     { return (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && HasFocus()); }

    bool CtrlRightClick()     { return (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && (sf::Mouse::isButtonPressed(sf::Mouse::Right)) && HasFocus()); }

    bool EnterPressed()      { return (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && HasFocus() && NoModifiersPressed()); }

    bool EscapePressed()     { return (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && HasFocus() && NoModifiersPressed()); }

    bool ShiftEscapePressed(){ return (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && HasFocus()); }

    bool SpacePressed()      { return (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && HasFocus() && NoModifiersPressed()); }

    bool ShiftSpacePressed() { return (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && HasFocus()); }

    bool UpPressed()         { return (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && HasFocus() && NoModifiersPressed()); }

    bool DownPressed()       { return (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && HasFocus() && NoModifiersPressed()); }

    bool PPressed()          { return (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && HasFocus() && NoModifiersPressed()); }

    bool TPressed()          { return (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && HasFocus() && NoModifiersPressed()); }

    bool CPressed()          { return (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && HasFocus() && NoModifiersPressed()); }

    bool EPressed()          { return (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && HasFocus() && NoModifiersPressed()); }

    bool LPressed()          { return (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && HasFocus() && NoModifiersPressed()); }
    


    float GetTime()
    {
        return clock.getElapsedTime().asSeconds();
    }


    bool MouseWheelScroll()
    {
        sf::Event e {};
        while (window.pollEvent(e))
            if (e.type == sf::Event::MouseWheelScrolled) {
                // if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                //     std::cout << "Wheel type: vertical" << std::endl;
                // else if (e.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                //     std::cout << "Wheel type: horizontal" << std::endl;
                // else
                //     std::cout << "Wheel type: unknown" << std::endl;
                
                // std::cout << "Wheel movement: " << e.mouseWheelScroll.delta << std::endl;
                // std::cout << "Mouse x: " << e.mouseWheelScroll.x << std::endl;
                // std::cout << "Mouse y: " << e.mouseWheelScroll.y << std::endl;
                return true;
            }
        return false;
    }


    int GetScrollAmount()
    {
        sf::Event e {};
        while (window.pollEvent(e))
            if (e.type == sf::Event::MouseWheelScrolled)
                return e.mouseWheelScroll.delta;
        return 0;
    }


    void Zoom(sf::View view, float zoom)
    {
        view.zoom(zoom);
        window.setView(view);

        std::cout << "Zoom: " << zoom << std::endl;
    }



};






