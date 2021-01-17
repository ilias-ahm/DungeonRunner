//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_PLAYERSFML_H
#define DUNGEONRUNNER_PLAYERSFML_H
#include "../Logic/Player.h"
#include "../Logic/Transformation.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
namespace DungeonRunnerSFML {
class Player : public DungeonRunner::Player
{
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //                                                          Variables //
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
        std::shared_ptr<sf::Texture> playerTexture;
        std::shared_ptr<sf::RectangleShape> player;
        std::shared_ptr<sf::IntRect> uvRect;
        std::shared_ptr<sf::RenderWindow> gWindow;
        bool damaged = false;

public:
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //                                                          Functions //
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
public:
        /**
         * Constructor
         * @param gWindow SFML Renderwindow
         * @param player SFML Rectangleshape
         * @param playerTexture SFML Texture
         * @param uvRect SFML IntRect
         */
        Player(std::shared_ptr<sf::RenderWindow>& gWindow, std::shared_ptr<sf::RectangleShape>& player,
               std::shared_ptr<sf::Texture>& playerTexture, std::shared_ptr<sf::IntRect>& uvRect);
        /**
         * Getter for playerposition in SFML coordinates
         * @return
         */
        sf::Vector2f getPos();
        /**
         * Updates SFML Position to entity position
         */
        void update() override;
        /**
         * Displays player to SFML Renderwindow
         */
        void display() override;
        /**
         * Turns player red for a split moment to show that the player is damaged
         */
        void action() override;
        /**
         * Setter for uvRect
         * @param uvRect
         */
        void setUvRect(const std::shared_ptr<sf::IntRect>& uvRect);
};
} // namespace DungeonRunnerSFML

#endif // DUNGEONRUNNER_PLAYERSFML_H
