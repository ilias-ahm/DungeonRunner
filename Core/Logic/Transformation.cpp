//
// Created by Ilias Ahmindach on 12/12/2020.
//

#include "Transformation.h"
#include <cmath>

std::pair<float, float> Transformation::_toPixel(std::shared_ptr<sf::RenderWindow>gWindow,float x, float y) {
    std::pair<float,float> windowSize = std::pair<float,float>(gWindow->getSize().x,gWindow->getSize().y);
    double lenX = windowSize.first;
    double lenY = windowSize.second;
    double rPosX = (x+wSize.first/2.0)/wSize.first;
    double rPosY = std::abs(y) - std::floor(std::abs(y));
    double newX = lenX* rPosX;
    double newY;
    if(y>0) newY = windowSize.second - (rPosY *lenY) - ((int)y+wSize.second/2.0)*windowSize.second;
    else newY = windowSize.second + (rPosY *lenY) - ((int)y+wSize.second/2.0)*windowSize.second;
    return std::pair<float, float>(newX,newY);
}



Transformation::Transformation(){
    Transformation::wSize = std::pair<int,int>(4,14);
}

std::pair<float, float> Transformation::toPixel(std::shared_ptr<sf::RenderWindow> gWindow, float x, float y) {
    return getInstance()._toPixel(gWindow,x,y);
}

std::pair<int, int> Transformation::getWSize(){
    return getInstance()._getWSize();
}

Transformation &Transformation::getInstance() {
    static Transformation newInstance;
    return newInstance;
}

std::pair<int, int> Transformation::_getWSize() {
    return wSize;
}

std::pair<float, float> Transformation::toCoords(std::shared_ptr<sf::RenderWindow>gWindow,float x, float y) {
    return getInstance()._toCoords(gWindow,x,y);
}

std::pair<float, float> Transformation::_toCoords(std::shared_ptr<sf::RenderWindow>gWindow,float x, float y) {
    std::pair<float,float> windowSize = std::pair<float,float>(gWindow->getSize().x,gWindow->getSize().y);
    double lenX = windowSize.first;
    double lenY = wSize.second*windowSize.second;
    double rPosX = x/lenX;
    double rPosY = (y-windowSize.second)/lenY;
    double newX = rPosX*wSize.first-wSize.first/2.0;
    double newY = std::abs(rPosY)*wSize.second-wSize.second/2.0;
    return std::pair<float, float>(newX,newY);
}
