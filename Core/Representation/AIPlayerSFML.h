//
// Created by Ilias Ahmindach on 18/12/2020.
//

#ifndef DUNGEONRUNNER_AIPLAYERSFML_H
#define DUNGEONRUNNER_AIPLAYERSFML_H
#include "../Logic/AIPlayer.h"
#include "DoorSFML.h"

namespace DungeonRunnerSFML {
class AIPlayer : public DungeonRunner::AIPlayer
{
private:
        std::shared_ptr<sf::RenderWindow> gWindow;
        sf::RectangleShape aiPlayer;
        sf::Texture aiTexture;
        sf::IntRect uvRect;

public:
        /**
         * Constructor
         * @param gameEntities
         * @param gWindow SFML Renderwindow
         */
        AIPlayer(std::vector<std::shared_ptr<DungeonRunner::Entity>>& gameEntities,
                 std::shared_ptr<sf::RenderWindow>& gWindow);
        /**
         * Displays Ai on Renderwindow
         */
        void display() override;
        /**
         * Updates SMFML rectangle to ai position
         */
        void update() override;
        /**
         * Setter for Texturerect
         * @param uvRect
         */
        void setUvRect(const sf::IntRect& uvRect);
};

} // namespace DungeonRunnerSFML
#endif // DUNGEONRUNNER_AIPLAYERSFML_H
