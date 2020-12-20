//
// Created by Ilias on 20/12/2020.
//

#ifndef DUNGEONRUNNER_ANIMATION_H
#define DUNGEONRUNNER_ANIMATION_H
#include <SFML/Graphics.hpp>
#include <memory>

namespace DungeonRunnerSFML {
    class Animation {
        sf::IntRect uvRect;
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        float switchTime;
        float aniSpeed;
    public:
        Animation(const std::shared_ptr<sf::Texture> &aniTexture,const sf::Vector2u &imageCount);
        void update(int row, float dTime, bool flip = true,float switchSpeed = 1/2.0);

         sf::IntRect getUvRect() ;
    };
}


#endif //DUNGEONRUNNER_ANIMATION_H
