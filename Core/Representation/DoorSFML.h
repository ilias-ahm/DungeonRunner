//
// Created by Ilias Ahmindach on 13/12/2020.
//

#ifndef DUNGEONRUNNER_DOORSFML_H
#define DUNGEONRUNNER_DOORSFML_H
#include <SFML/Graphics.hpp>
#include "../Logic/Door.h"

namespace DungeonRunnerSFML {
    class DoorSFML: public DungeonRunner::Door{
        std::shared_ptr<sf::Texture> doorTexture;
        std::shared_ptr<sf::RectangleShape> door;
        std::shared_ptr<sf::RenderWindow> gWindow;
        std::map<std::string,std::shared_ptr<sf::Texture>> doorStates;
    public:
        /**
         * Constructor
         * @param door SFML Rectangle
         * @param gWindow SFML Renderwindow
         * @param doorStates map containing 'open' and 'closed' door textures
         */
        DoorSFML(std::shared_ptr<sf::RectangleShape> &door, const std::shared_ptr<sf::RenderWindow> &gWindow,
                 const std::map<std::string, std::shared_ptr<sf::Texture>> &doorStates);

        virtual ~DoorSFML();
        /**
         * Updates texture according to isOpen variable
         */
        void update() override;
        /**
         * Displays door on SFML Renderwindow
         */
        void display() override;
    };

}
#endif //DUNGEONRUNNER_DOORSFML_H
