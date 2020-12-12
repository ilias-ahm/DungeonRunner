//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_PLAYERSFML_H
#define DUNGEONRUNNER_PLAYERSFML_H
#include "../Logic/Player.h"
#include <SFML/Graphics.hpp>

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
    public:

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

    public:
        void update(sf::View gView);
        Player(std::shared_ptr<sf::RenderWindow> gWindow,std::shared_ptr<sf::RectangleShape> player,std::shared_ptr<sf::Texture> playerTexture,std::shared_ptr<sf::IntRect> uvRect);
        void move(float x, float y);
        sf::Vector2f getPos();
    };
}


#endif //DUNGEONRUNNER_PLAYERSFML_H
