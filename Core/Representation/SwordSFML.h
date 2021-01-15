//
// Created by Ilias Ahmindach on 17/12/2020.
//

#ifndef DUNGEONRUNNER_SWORDSFML_H
#define DUNGEONRUNNER_SWORDSFML_H
#include "../Logic/Sword.h"
namespace DungeonRunnerSFML {
    class Sword: public DungeonRunner::Sword {
        std::shared_ptr<sf::RectangleShape> sword;
        std::shared_ptr<sf::Texture> swordTexture;
        std::shared_ptr<sf::RenderWindow> gWindow;
    public:
        /**
         * Constructor
         * @param gWindow SFML Renderwindow
         */
        Sword(std::shared_ptr<sf::RenderWindow> &gWindow);
        /**
         * Updates SFML Position to entity position
         */
        void update() override;
        /**
         * Displays player to SFML Renderwindow
         */
        void display() override;

    };
}


#endif //DUNGEONRUNNER_SWORDSFML_H
