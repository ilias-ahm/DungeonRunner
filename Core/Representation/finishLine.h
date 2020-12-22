//
// Created by Ilias Ahmindach on 21/12/2020.
//

#ifndef DUNGEONRUNNER_FINISHLINE_H
#define DUNGEONRUNNER_FINISHLINE_H
#include "../Logic/Entity.h"

namespace DungeonRunnerSFML {
    class finishLine: public DungeonRunner::Entity {
        std::shared_ptr<sf::RenderWindow> gWindow;
        sf::RectangleShape finish;
        sf::Texture finishTexture;
        sf::Sprite test;
    public:
        finishLine( std::shared_ptr<sf::RenderWindow> &gWindow,  sf::RectangleShape &finish);
        void display() override;
    };
}


#endif //DUNGEONRUNNER_FINISHLINE_H
