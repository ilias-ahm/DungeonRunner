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
        sf::RectangleShape lFrame;
        sf::RectangleShape rFrame;
    public:
        DoorSFML(const std::shared_ptr<sf::RectangleShape> &door, const std::shared_ptr<sf::RenderWindow> &gWindow,
                 const std::map<std::string, std::shared_ptr<sf::Texture>> &doorStates);

        void setDoorTexture(const std::shared_ptr<sf::Texture> &doorTexture);

        void setDoor(const std::shared_ptr<sf::RectangleShape> &door);
        void update() override;
        void display() override;
        void action() override;
    };

}
#endif //DUNGEONRUNNER_DOORSFML_H
