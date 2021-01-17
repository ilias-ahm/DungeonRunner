//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "PlayerSFML.h"

void DungeonRunnerSFML::Player::update()
{
        std::pair<float, float> pixelC = Transformation::toPixel(gWindow, ePosition.first, ePosition.second);
        player->setPosition(pixelC.first, pixelC.second);
        if (damaged) {
                player->setFillColor(sf::Color::Red);
                damaged = false;

        } else
                player->setFillColor(sf::Color::White);
}

DungeonRunnerSFML::Player::Player(std::shared_ptr<sf::RenderWindow>& gWindow,
                                  std::shared_ptr<sf::RectangleShape>& player,
                                  std::shared_ptr<sf::Texture>& playerTexture, std::shared_ptr<sf::IntRect>& uvRect)
{
        DungeonRunnerSFML::Player::player = player;
        DungeonRunnerSFML::Player::playerTexture = playerTexture;
        DungeonRunnerSFML::Player::uvRect = uvRect;
        DungeonRunnerSFML::Player::gWindow = gWindow;
        playerSpeed = 0.2;
        ePosition = std::pair<float, float>(-0.75, -6.7);
        std::pair<float, float> tSize = Transformation::toCoords(gWindow, player->getSize().x, player->getSize().y);
        tSize.first += Transformation::getWSize().first / 2.0;
        tSize.second += Transformation::getWSize().second / 2.0;
        tSize.second = 1 - tSize.second;
        eSize = tSize;
        player->setTexture(&*playerTexture);
        player->setTextureRect(*uvRect);
        player->setOrigin(player->getSize().x / 2.0, player->getSize().y);
        eType = "Player";
}

sf::Vector2f DungeonRunnerSFML::Player::getPos() { return player->getPosition(); }

void DungeonRunnerSFML::Player::action() { damaged = true; }

void DungeonRunnerSFML::Player::display() { gWindow->draw(*player); }

void DungeonRunnerSFML::Player::setUvRect(const std::shared_ptr<sf::IntRect>& uvRect)
{
        Player::uvRect = uvRect;
        player->setTextureRect(*uvRect);
}
