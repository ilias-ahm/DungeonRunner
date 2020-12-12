//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "PlayerSFML.h"


void DungeonRunnerSFML::Player::update(sf::View gView) {
    gWindow->draw(*player);
}

DungeonRunnerSFML::Player::Player(std::shared_ptr<sf::RenderWindow> gWindow, std::shared_ptr<sf::RectangleShape> player,
                                  std::shared_ptr<sf::Texture> playerTexture, std::shared_ptr<sf::IntRect> uvRect) {
    DungeonRunnerSFML::Player::player = player;
    DungeonRunnerSFML::Player::playerTexture = playerTexture;
    DungeonRunnerSFML::Player::uvRect = uvRect;
    DungeonRunnerSFML::Player::gWindow = gWindow;

    player->setTexture(&*playerTexture);
    player->setTextureRect(*uvRect);
}

void DungeonRunnerSFML::Player::move(float x, float y) {
    player->move(x,y);
}

sf::Vector2f DungeonRunnerSFML::Player::getPos() {
    return player->getPosition();
}

