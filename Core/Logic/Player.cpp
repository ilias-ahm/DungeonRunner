//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "Player.h"

void DungeonRunner::Player::setPlayerSpeed(float playerSpeed) { Player::playerSpeed = playerSpeed; }

void DungeonRunner::Player::setPlayerLives(int playerLives) { Player::playerLives = playerLives; }

void DungeonRunner::Player::setPlayerName(const std::string& playerName) { Player::playerName = playerName; }

void DungeonRunner::Player::setPlayerPosition(const std::pair<float, float>& playerPosition)
{
        Player::ePosition = playerPosition;
}
void DungeonRunner::Player::setPlayerPosition(float x, float y) { Player::ePosition = std::pair<float, float>(x, y); }

float DungeonRunner::Player::getPlayerSpeed() const { return playerSpeed; }

int DungeonRunner::Player::getPlayerLives() const { return playerLives; }

const std::string& DungeonRunner::Player::getPlayerName() const { return playerName; }
