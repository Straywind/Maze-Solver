#include <iostream>
#include <random>
#include <time.h>
#include <float.h>

#include "GreenBlock.h"
#include "ASharp.h"

int main(){
    srand(time(NULL));

    Maze MZ;
    GreenBlock Green;

    sf::Clock keyPressTimer;

    std::cout << "Press WASD keys to move around the maze.\nPress Enter to solve the maze.\n";
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(globals::WIDTH, globals::HEIGHT), "Maze");

	// Start the game loop
    while (app.isOpen()){
        // Process events
        sf::Event event;
        while (app.pollEvent(event)){
            // Close window : exit
            if (event.type == sf::Event::Closed){
                app.close();
            }
        }

        if (!MZ.IsMazeSolved()){
            ///Controls
            if (keyPressTimer.getElapsedTime().asMilliseconds() > 100){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                    Green.Move(globals::up, &MZ);
                    keyPressTimer.restart();
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    Green.Move(globals::down, &MZ);
                    keyPressTimer.restart();
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    Green.Move(globals::left, &MZ);
                    keyPressTimer.restart();
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    Green.Move(globals::right, &MZ);
                    keyPressTimer.restart();
                }
            }

            if (keyPressTimer.getElapsedTime().asSeconds() > 1 &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                ASharp Solution(&MZ);
                keyPressTimer.restart();
            }

            // Clear screen
            app.clear();

            //Draw maze
            MZ.Draw(app);

            // globals::update the window
            app.display();
        }
    }

    return EXIT_SUCCESS;
}

