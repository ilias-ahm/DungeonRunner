//
// Created by Ilias Ahmindach on 18/12/2020.
//

#include "AIPlayerSFML.h"


DungeonRunnerSFML::AIPlayer::AIPlayer(
        std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities,
        std::shared_ptr<sf::RenderWindow> &gWindow): gameEntities(gameEntities),gWindow(gWindow) {

}
