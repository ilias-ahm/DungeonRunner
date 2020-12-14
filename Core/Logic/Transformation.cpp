//
// Created by Ilias Ahmindach on 12/12/2020.
//

#include "Transformation.h"
#include <cmath>

std::pair<float, float> Transformation::toPixel(float x, float y) {
    std::pair<float,float> windowSize = std::pair<float,float>(gWindow->getSize().x,gWindow->getSize().y);
    double lenX = windowSize.first-windowSize.first/2.0-windowSize.first/8.0;
    double lenY = windowSize.second;
    double rPosX = (x+wSize.first/2.0)/wSize.first;
    double rPosY = abs(y) - floor(abs(y));
    double newX = lenX* rPosX + windowSize.first/4.0;
    double newY;
    if(y>0) newY = windowSize.second - (rPosY *lenY) - ((int)y+wSize.second/2.0)*windowSize.second - windowSize.second/8.0;
    else newY = windowSize.second + (rPosY *lenY) - ((int)y+wSize.second/2.0)*windowSize.second - windowSize.second/8.0;
    return std::pair<float, float>(newX,newY);
}

std::pair<float, float> Transformation::toCoords(float x, float y) {
    return std::pair<float, float>();
}

Transformation::Transformation(const std::shared_ptr<sf::RenderWindow> &gWindow, const std::pair<int, int> &wSize)
        : gWindow(gWindow), wSize(wSize) {}

const std::pair<int, int> &Transformation::getWSize() const {
    return wSize;
}
