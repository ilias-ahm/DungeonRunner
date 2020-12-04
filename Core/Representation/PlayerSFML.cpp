//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "PlayerSFML.h"

DungeonRunnerSFML::Player::Player(sf::RectangleShape player, sf::Texture playerTexture, sf::IntRect uvRect) {
    DungeonRunnerSFML::Player::player = player;
    DungeonRunnerSFML::Player::playerTexture = playerTexture;
    DungeonRunnerSFML::Player::uvRect = uvRect;
    player.setTexture(&playerTexture);
    player.setPosition(128*2,0);
    player.setTextureRect(uvRect);
}
