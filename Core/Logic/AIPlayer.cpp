//
// Created by Ilias Ahmindach on 18/12/2020.
//

#include "AIPlayer.h"

float DungeonRunner::AIPlayer::getAiSpeed() const {
    return aiSpeed;
}

void DungeonRunner::AIPlayer::setAiSpeed(float aiSpeed) {
    AIPlayer::aiSpeed = aiSpeed;
}
