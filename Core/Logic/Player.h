//
// Created by Ilias Ahmindach on 03/12/2020.
//

#ifndef DUNGEONRUNNER_PLAYER_H
#define DUNGEONRUNNER_PLAYER_H
#include "Entity.h"

namespace DungeonRunner {
class Player : public Entity
{
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //                                                          Variables //
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:
        float playerSpeed;
        int playerLives;
        std::string playerName;

public:
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //                                                          Functions //
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
public:
        /**
         * Setter for playerspeed
         * @param playerSpeed float [0.2-0.5]
         */
        void setPlayerSpeed(float playerSpeed);

        void setPlayerLives(int playerLives);

        void setPlayerName(const std::string& playerName);

        void setPlayerPosition(const std::pair<float, float>& playerPosition);

        void setPlayerPosition(float x, float y);
        /**
         * Getter for playerspeed
         * @return
         */
        float getPlayerSpeed() const;

        int getPlayerLives() const;

        const std::string& getPlayerName() const;
};
} // namespace DungeonRunner

#endif // DUNGEONRUNNER_PLAYERSFML_H
