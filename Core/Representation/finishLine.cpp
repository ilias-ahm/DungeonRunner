//
// Created by Ilias Ahmindach on 21/12/2020.
//

#include "finishLine.h"

DungeonRunnerSFML::finishLine::finishLine(std::shared_ptr<sf::RenderWindow>& gWindow, sf::RectangleShape& finish)
    : gWindow(gWindow), finish(finish)
{
        finishTexture.loadFromFile("../Resources/floorSprites/finishLine.png");
        finishTexture.setRepeated(true);
        this->finish.setTextureRect(sf::IntRect(0, 0, gWindow->getSize().x / 2.0, gWindow->getSize().x / 8.0));
        this->finish.setTexture(&finishTexture);
        eType = "Finish";
}

void DungeonRunnerSFML::finishLine::display() { gWindow->draw(finish); }
