//
// Created by Ilias Ahmindach on 18/12/2020.
//

#ifndef DUNGEONRUNNER_AIPLAYERSFML_H
#define DUNGEONRUNNER_AIPLAYERSFML_H
#include "../Logic/AIPlayer.h"

namespace DungeonRunnerSFML {
    class AIPlayer: public DungeonRunner::AIPlayer {
    private:
        std::vector<std::shared_ptr<DungeonRunner::Entity>> gameEntities;
        std::shared_ptr<sf::RenderWindow> gWindow;
        sf::RectangleShape aiPlayer;
        sf::Texture aiTexture;
        sf::IntRect uvRect;

    public:
        AIPlayer(std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities,
        std::shared_ptr<sf::RenderWindow> &gWindow);
        void display() override;
        void update() override;

        void setUvRect(const sf::IntRect &uvRect);
    };

}
#endif //DUNGEONRUNNER_AIPLAYERSFML_H
