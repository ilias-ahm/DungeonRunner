//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "PlayerSFML.h"


void DungeonRunnerSFML::Player::update(std::shared_ptr<Transformation> t) {
    std::pair<float,float> pixelC = t->toPixel(playerPosition.first,playerPosition.second);
    player->setPosition(pixelC.first,pixelC.second);
    gWindow->draw(*player);
}

DungeonRunnerSFML::Player::Player(std::shared_ptr<sf::RenderWindow> gWindow, std::shared_ptr<sf::RectangleShape> player,
                                  std::shared_ptr<sf::Texture> playerTexture, std::shared_ptr<sf::IntRect> uvRect) {
    DungeonRunnerSFML::Player::player = player;
    DungeonRunnerSFML::Player::playerTexture = playerTexture;
    DungeonRunnerSFML::Player::uvRect = uvRect;
    DungeonRunnerSFML::Player::gWindow = gWindow;
    playerSpeed = 24*0.0002;
    playerPosition = std::pair<float,float>(-2,-7);
    player->setTexture(&*playerTexture);
    player->setTextureRect(*uvRect);
}

void DungeonRunnerSFML::Player::move(std::shared_ptr<Transformation> t,float x, float y) {
    if(playerPosition.first+x< -(t->getWSize().first/2.0) or playerPosition.first+x>(t->getWSize().first/2.0) or playerPosition.second+y<-(t->getWSize().second/2.0) or playerPosition.second+y>(t->getWSize().second/2.0)) return;
    playerPosition.first+=x;
    playerPosition.second+=y;

}

sf::Vector2f DungeonRunnerSFML::Player::getPos() {
    return player->getPosition();
}

void DungeonRunnerSFML::Player::action() {

}

void DungeonRunnerSFML::Player::display() {

}

void DungeonRunnerSFML::Player::update() {

}

