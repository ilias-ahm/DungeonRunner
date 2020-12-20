//
// Created by Ilias on 20/12/2020.
//

#include "Animation.h"

DungeonRunnerSFML::Animation::Animation(const std::shared_ptr<sf::Texture> &aniTexture,const sf::Vector2u &imageCount) : imageCount(imageCount) {
    switchTime = 0;
    currentImage.x = 0;
    uvRect.width = 32.0f;
    uvRect.height = 32.0f;
    aniSpeed = 1/2.5;
}

void DungeonRunnerSFML::Animation::update(int row, float dTime, bool flip,float switchSpeed) {
    currentImage.y = row;
    switchTime += dTime;
    if(switchTime>=switchSpeed){
        switchTime-=switchSpeed;
        currentImage.x++;
        if(currentImage.x == 1) currentImage.x++;
        if(currentImage.x>=imageCount.x){
            currentImage.x = 0;
        }
    }
    uvRect.top = currentImage.y*uvRect.height;
    if(flip){
        uvRect.left = (currentImage.x+1) * std::abs(uvRect.width);
        uvRect.width = -std::abs(uvRect.width);
    } else{
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = std::abs(uvRect.width);
    }
}

sf::IntRect DungeonRunnerSFML::Animation::getUvRect()  {

    return uvRect;
}
