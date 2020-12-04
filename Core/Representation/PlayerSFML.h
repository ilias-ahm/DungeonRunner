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
        sf::Texture playerTexture;
        sf::RectangleShape player;
        sf::IntRect uvRect;
    public:

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                          Functions                                                           //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

    public:
        Player(sf::RectangleShape player,sf::Texture playerTexture,sf::IntRect uvRect);
    };
}


#endif //DUNGEONRUNNER_PLAYERSFML_H
