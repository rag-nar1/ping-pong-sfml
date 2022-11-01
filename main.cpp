#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;

int main()
{
    const int window_width = 800;
    const int window_height = 600;
    const float ball_radius = 16.f;
    const int bpp = 32;


    sf::RenderWindow window(sf::VideoMode(window_width, window_height, bpp), "Bouncing ball");
    window.setVerticalSyncEnabled(true);

     std::random_device seed_device;
    std::default_random_engine engine(seed_device());
    std::uniform_int_distribution<int> distribution(-16, 16);
    auto random = std::bind(distribution, std::ref(engine));

    sf::Vector2f direction(random(), random());
    if(direction.x==0)
    direction.x=1;
    if(direction.y==0)
    direction.y=1;
    const float velocity = 0.7;
    int a=0,b=0;


    sf::CircleShape ball(ball_radius - 4);
    ball.setOutlineThickness(4);
    ball.setOutlineColor(sf::Color::Black);
    ball.setFillColor(sf::Color::Yellow);
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    ball.setPosition(window_width / 2, window_height / 2);


    RectangleShape shape1(Vector2f(15,100));
    RectangleShape shape2(Vector2f(15,100));
    //shape1.setOrigin()
    shape1.setPosition(20,window_height/2);
    shape2.setPosition(window_width-30,(window_height/2));


    Keyboard keys;
    sf::Clock clock;
    sf::Time elapsed = clock.restart();
    const sf::Time update_ms = sf::seconds(1.f / 30.f);
   

    Font font;
    font.loadFromFile("/home/rganar/Desktop/vs c++/odc project/danger_night/Danger Night - Personal Use.ttf");
    Text text;
    text.setFont(font);
    text.setString("score");
    text.setCharacterSize(50);
    text.setPosition(375,0);
    while(window.isOpen())
    {
        Event event;
        // Check for all the events that occured since the last frame.
        while (window.pollEvent(event))
        {
            //Handle events here
            if (event.type == event.Closed)
                window.close();
            if(event.type==Event::EventType::KeyPressed){
                if(keys.isKeyPressed(keys.Up)){
                    shape2.setPosition(window_width-30,shape2.getPosition().y-20);
                }
            }
            if(event.type==Event::EventType::KeyPressed){
                if(keys.isKeyPressed(keys.Down)){
                    shape2.setPosition(window_width-30,shape2.getPosition().y+20);
                }
            }
            if(event.type==Event::EventType::KeyPressed){
                if(keys.isKeyPressed(keys.W)){
                    shape1.setPosition(20,shape1.getPosition().y-20);
                }
            } if(event.type==Event::EventType::KeyPressed){
                if(keys.isKeyPressed(keys.S)){
                    shape1.setPosition(20,shape1.getPosition().y+20);
                }
            }
        }
        elapsed += clock.restart();
        while (elapsed >= update_ms){
            const auto pos = ball.getPosition();
             const auto delta =velocity;
            sf::Vector2f new_pos(pos.x + direction.x * delta, pos.y + direction.y * delta);
            if(new_pos.x-ball_radius>=shape2.getPosition().x-20 && (new_pos.y-ball_radius>shape2.getPosition().y && new_pos.y-ball_radius<=shape2.getPosition().y+90)){
                direction.x*=-1;
            }
            if(new_pos.x-ball_radius<=shape1.getPosition().x+10 && (new_pos.y-ball_radius>shape1.getPosition().y && new_pos.y-ball_radius<=shape1.getPosition().y+90)){
                direction.x*=-1;
            }
             if (new_pos.x - ball_radius < 0) { // left window edge
             b++;
                new_pos.x = window_width/2;
                new_pos.y =window_height/2;
            } else if (new_pos.x + ball_radius >= window_width) { // right window edge
            a++;
               new_pos.x = window_width/2;
                new_pos.y =window_height/2;
            } else if (new_pos.y - ball_radius < 0) { // top of window
                direction.y *= -1;
                new_pos.y = 0 + ball_radius;
            } else if (new_pos.y + ball_radius >= window_height) { // bottom of window
                direction.y *= -1;
                new_pos.y = window_height - ball_radius;
            }
            ball.setPosition(new_pos);
            elapsed -= update_ms;

        }
        //cout<<a;
        Text scorea,scoreb;
        Font fono;
        fono.loadFromFile("/home/rganar/Desktop/vs c++/odc project/AlexBrush-Regular.ttf");
        scorea.setFont(fono);
        scorea.setString(to_string(a));
        scorea.setCharacterSize(60);
        scorea.setPosition(window_width/4,0);
        scoreb.setFont(fono);
        scoreb.setString(to_string(b));
        scoreb.setCharacterSize(60);
        scoreb.setPosition(3*window_width/4,0);
        window.clear(sf::Color(30, 30, 120));
        window.draw(ball);
        window.draw(shape1);
        window.draw(shape2);
        window.draw(text);
        window.draw(scorea);
        window.draw(scoreb);
        window.display();
    }

    return 0;
}
