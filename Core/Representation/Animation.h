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
    public:
        /**
         *
         * @param aniTexture SFML texture
         * @param imageCount amount of images per row
         */
        Animation(const std::shared_ptr<sf::Texture> &aniTexture,const sf::Vector2u &imageCount);
        /**
         * Updates the texture of the entity
         * @param row
         * @param dTime
         * @param flip
         * @param switchSpeed float
         */
        void update(int row, float dTime, bool flip = true,float switchSpeed = 1/2.0);
        /**
         * Getter for uvRect
         * @return uvRect
         */
         sf::IntRect getUvRect() ;
    };
}


#endif //DUNGEONRUNNER_ANIMATION_H
