//
// Created by Ilias Ahmindach on 18/12/2020.
//

#ifndef DUNGEONRUNNER_AIPLAYERSFML_H
#define DUNGEONRUNNER_AIPLAYERSFML_H
#include "../Logic/AIPlayer.h"
#include "DoorSFML.h"

namespace DungeonRunnerSFML {
    class AIPlayer: public DungeonRunner::AIPlayer {
    private:
        std::vector<std::shared_ptr<DungeonRunner::Entity>> gameEntities;
        std::shared_ptr<sf::RenderWindow> gWindow;
        sf::RectangleShape aiPlayer;
        sf::Texture aiTexture;
        sf::IntRect uvRect;
        int dodgeState = 0; // 0 = straight , 1 = left , 2 = right;
        void avoidObstacles();
        void dodgeObstacle(std::shared_ptr<DungeonRunner::Entity> obstacle);
        bool interactObstacle(std::shared_ptr<DungeonRunner::Entity> obstacle);
        bool isDodging = false;
        bool isStuck = false;
        bool stuckResolving = false;

    public:
        void run();
        AIPlayer(std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities,
        std::shared_ptr<sf::RenderWindow> &gWindow);
        void display() override;
        void update() override;
        void updateGameEntities(std::vector<std::shared_ptr<DungeonRunner::Entity>> &gameEntities);
        int getDodgeState() const;

        void setDodgeState(int dodgeState);

        bool IsStuck() const;

        void setIsStuck(bool isStuck);

        void setUvRect(const sf::IntRect &uvRect);

        float getMovechance();

    };

}
#endif //DUNGEONRUNNER_AIPLAYERSFML_H
