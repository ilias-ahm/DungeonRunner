//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_PLAYERSFML_H
#define DUNGEONRUNNER_PLAYERSFML_H
#include "../Logic/Player.h"
#include <SFML/Graphics.hpp>
#include "../Logic/Transformation.h"
#include "Animation.h"
namespace DungeonRunnerSFML{
    class Player : public DungeonRunner::Player {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Variables                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:
        std::shared_ptr<sf::Texture> playerTexture;
        std::shared_ptr<sf::RectangleShape> player;
        std::shared_ptr<sf::IntRect> uvRect;
        std::shared_ptr<sf::RenderWindow> gWindow;
        bool damaged = false;
    public:

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

    public:
        Player(std::shared_ptr<sf::RenderWindow> &gWindow,std::shared_ptr<sf::RectangleShape> &player,std::shared_ptr<sf::Texture> &playerTexture,std::shared_ptr<sf::IntRect> &uvRect);
        sf::Vector2f getPos();
        void update() override;
        void display() override;
        void action() override;

        void setUvRect(const std::shared_ptr<sf::IntRect> &uvRect);
    };
}


#endif //DUNGEONRUNNER_PLAYERSFML_H
