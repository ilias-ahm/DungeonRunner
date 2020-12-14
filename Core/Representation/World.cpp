//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include "World.h"
DungeonRunner::World::World(std::shared_ptr<sf::RenderWindow> gWindow, int x, int y) {
    worldSize = std::pair<int,int>(x,y);
    gameWindow = gWindow;
    std::vector<std::shared_ptr<sf::RectangleShape>> placeholder;
    for(int board = 0; board != y ; board++){
        std::vector<std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>>> pVector;
        for(int lane = 0; lane!= x+2; lane++){
            pVector.push_back({placeholder});
        }
        world.push_back(pVector);
    }
    wallTexture.loadFromFile("../Resources/wallSprite/wall1.png");
    initTileTex();
    initDoorTex();
    initPillarTex();
    initSwordTex();
    initWorld();

}

void DungeonRunner::World::initWorld() {
    for(int board = 0; board != worldSize.second;board++) {
        std::shared_ptr<sf::RectangleShape> Wall1 = std::make_shared<sf::RectangleShape>(sf::Vector2f(gameWindow->getSize().x/8.0,gameWindow->getSize().y));
        std::shared_ptr<sf::RectangleShape> Wall2 = std::make_shared<sf::RectangleShape>(sf::Vector2f(gameWindow->getSize().x/8.0,gameWindow->getSize().y));
        Wall1->setTexture(&wallTexture);
        Wall2->setTexture(&wallTexture);
        Wall1->setPosition(gameWindow->getSize().x/8.0,(float)board*(-(float)gameWindow->getSize().y));
        Wall2->setPosition(gameWindow->getSize().x/2.0 + gameWindow->getSize().x/4.0,(float)board*(-(float)gameWindow->getSize().y));
        world[board][0] = {{Wall1}};
        world[board][worldSize.first+1] = {{Wall2}};
        for (int lane = 0; lane != worldSize.first; lane++) {
            int currentRow = 0;
            while (currentRow != 8) {
                std::vector<std::shared_ptr<sf::RectangleShape>> Tile;


                std::random_device dev;
                std::mt19937 rng(dev());
                std::uniform_real_distribution<double> dist(0,1); // distribution in range [1, 6]
                if(dist(rng)<0.012 and board>0) {
                    std::shared_ptr<sf::RectangleShape> dRec = std::make_shared<sf::RectangleShape>(
                            sf::Vector2f(gameWindow->getSize().x / 8.0, gameWindow->getSize().y / 8.0));
                    std::shared_ptr<DungeonRunnerSFML::DoorSFML> dObs = std::make_shared<DungeonRunnerSFML::DoorSFML>(
                            dRec, gameWindow, obstacleTextures);
                    dRec->setPosition((float) (lane + 2) * gameWindow->getSize().x / 8,
                                      (float) currentRow * gameWindow->getSize().y / 8 -
                                      (float) (board * gameWindow->getSize().y));
                    obstacles.push_back(dObs);
                }
                for (int i = 0; i != 4; i++) {
                    std::shared_ptr<sf::RectangleShape> tile = std::make_shared<sf::RectangleShape>();
                    tile->setSize(sf::Vector2f(gameWindow->getSize().x / 16.0, gameWindow->getSize().y / 16.0));
                    tile->setTexture(getRandomFloorTile().get());
                    switch (i) {
                        case 0:
                            tile->setPosition((float) (lane + 2) * gameWindow->getSize().x / 8,
                                              (float) currentRow * gameWindow->getSize().y / 8 -
                                              (float) (board * gameWindow->getSize().y));
                            break;
                        case 1:
                            tile->setPosition((float) (lane + 2) * (float) gameWindow->getSize().x / 8 +
                                              (float) (gameWindow->getSize().x / 16.0),
                                              (float) currentRow * gameWindow->getSize().y / 8 -
                                              (float) (board * gameWindow->getSize().y));
                            break;
                        case 2:
                            tile->setPosition((float) (lane + 2) * gameWindow->getSize().x / 8,
                                              (float) currentRow * gameWindow->getSize().y / 8 +
                                              (float) (gameWindow->getSize().y / 16.0) -
                                              (float) (board * gameWindow->getSize().y));
                            break;
                        case 3:
                            tile->setPosition((float) (lane + 2) * (float)gameWindow->getSize().x / 8 +
                                              (float) (gameWindow->getSize().x / 16.0),
                                              (float) currentRow * gameWindow->getSize().y / 8 +
                                              (float) (gameWindow->getSize().y / 16.0) -
                                              (float) (board * gameWindow->getSize().y));
                            break;
                        default:
                            break;
                    }
                    Tile.push_back(tile);
                }
                if(currentRow == 0){
                    world[board][lane+1][currentRow] = Tile;
                }
                else{
                    world[board][lane+1].push_back(Tile);
                }
                currentRow++;
            }
        }
    }
}

std::shared_ptr<sf::Texture> DungeonRunner::World::getRandomFloorTile() {
    std::string floorTile = "../Resources/floorSprites/floor_";
    int random = rand()%100;
    if(0<=random and random <50) random = 1;
    else if (50<=random and random <53) random = 2;
    else if (53<=random and random <73) random = 3;
    else if (73<=random and random <90) random = 5;
    else{
        int r3 = rand()%4;
        switch (r3) {
            case 0:
                random = 6;
                break;
            case 1:
                random = 7;
                break;
            case 2:
                random = 8;
                break;
            case 3:
                random = 4;
                break;
        }
    }
    return tileTextures[random-1];
}

void DungeonRunner::World::update() {
    for(auto &board:world){
        for( auto &lane:board){
            for(auto &tile:lane){
                for(auto &subtile:tile){
                    gameWindow->draw(*subtile);
                }
            }
        }
    }
    for(auto &obstacle:obstacles){
        obstacle->update();
        obstacle->display();
    }
}

void DungeonRunner::World::initTileTex() {
    for(int i=1;i!=9;i++){
        std::shared_ptr<sf::Texture> fTile = std::make_shared<sf::Texture>();
        std::string filePath = "../Resources/floorSprites/floor_";
        filePath+= std::to_string(i) + ".png";
        fTile->loadFromFile(filePath);
        tileTextures.push_back(fTile);
    }
}

void DungeonRunner::World::initSwordTex() {
    std::shared_ptr<sf::Texture> sTile = std::make_shared<sf::Texture>();
    std::string filePath = "../Resources/obstaclesSprites/swords/sword_1.png";
    sTile->loadFromFile(filePath);
    obstacleTextures["sword_1"] = sTile;

}

void DungeonRunner::World::initDoorTex() {
    std::shared_ptr<sf::Texture> dcTile = std::make_shared<sf::Texture>();
    std::string filePath = "../Resources/obstaclesSprites/door/door_c.png";
    dcTile->loadFromFile(filePath);
    obstacleTextures["door_c"] = dcTile;
    std::shared_ptr<sf::Texture> doTile = std::make_shared<sf::Texture>();
    filePath = "../Resources/obstaclesSprites/door/door_o.png";
    doTile->loadFromFile(filePath);
    obstacleTextures["door_o"] = doTile;

}

void DungeonRunner::World::initPillarTex() {
    std::shared_ptr<sf::Texture> pbTile = std::make_shared<sf::Texture>();
    std::string filePath = "../Resources/obstaclesSprites/pillar/pTop.png";
    pbTile->loadFromFile(filePath);
    obstacleTextures["pBase"] = pbTile;
    std::shared_ptr<sf::Texture> pmTile = std::make_shared<sf::Texture>();
    filePath = "../Resources/obstaclesSprites/pillar/pMid.png";
    pmTile->loadFromFile(filePath);
    obstacleTextures["pMid"] = pmTile;
    std::shared_ptr<sf::Texture> ptTile = std::make_shared<sf::Texture>();
    filePath = "../Resources/obstaclesSprites/pillar/pTop.png";
    ptTile->loadFromFile(filePath);
    obstacleTextures["pTop"] = ptTile;


}

void DungeonRunner::World::action() {

}

void DungeonRunner::World::display() {

}
