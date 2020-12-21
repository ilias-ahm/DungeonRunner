//
// Created by Ilias Ahmindach on 21/12/2020.
//

#include "finishLine.h"

DungeonRunnerSFML::finishLine::finishLine(std::shared_ptr<sf::RenderWindow> &gWindow,
                                           sf::RectangleShape &finish) : gWindow(
        gWindow), finish(finish) {}

void DungeonRunnerSFML::finishLine::display() {
    gWindow->draw(finish);
}
