//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "PlayerSFML.h"


void DungeonRunnerSFML::Player::update() {
    std::pair<float,float> pixelC = Transformation::toPixel(gWindow, ePosition.first, ePosition.second);
    player->setPosition(pixelC.first,pixelC.second);
    gWindow->draw(*player);
}

DungeonRunnerSFML::Player::Player(std::shared_ptr<sf::RenderWindow> gWindow, std::shared_ptr<sf::RectangleShape> player,
                                  std::shared_ptr<sf::Texture> playerTexture, std::shared_ptr<sf::IntRect> uvRect) {
    DungeonRunnerSFML::Player::player = player;
    DungeonRunnerSFML::Player::playerTexture = playerTexture;
    DungeonRunnerSFML::Player::uvRect = uvRect;
    DungeonRunnerSFML::Player::gWindow = gWindow;
    playerSpeed = 14*0.0002;
    ePosition = std::pair<float,float>(-2, -7);
    player->setTexture(&*playerTexture);
    player->setTextureRect(*uvRect);
    player->setOrigin(player->getSize().x/2.0,0);
    eType = "Player";
}

void DungeonRunnerSFML::Player::move(float x, float y) {
    if(ePosition.first + x < -(Transformation::getWSize().first / 2.0) or ePosition.first + x > (Transformation::getWSize().first / 2.0) or
       ePosition.second + y < -(Transformation::getWSize().second / 2.0) or ePosition.second + y > (Transformation::getWSize().second / 2.0)) return;
    ePosition.first+=x;
    ePosition.second+=y;

}

sf::Vector2f DungeonRunnerSFML::Player::getPos() {
    return player->getPosition();
}

void DungeonRunnerSFML::Player::action() {

}

void DungeonRunnerSFML::Player::display() {

}

