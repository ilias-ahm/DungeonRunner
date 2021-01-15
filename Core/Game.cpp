//
// Created by Ilias Ahmindach on 03/12/2020.
//

#include <sstream>
#include <iomanip>
#include "Game.h"

DungeonRunner::Game::Game(const std::shared_ptr<sf::RenderWindow> &gameWindow) : gameWindow(gameWindow) {
   gameWorld = AbstractFactory::createWorld(gameWindow,4,14);
   gameView = sf::View(sf::Vector2f(gameWindow->getSize().x/2.0,0),sf::Vector2f(gameWindow->getSize().x,gameWindow->getSize().y));
   gameView.setCenter(gameWindow->getSize().x/2.0,gameWindow->getSize().y/2.0);
   gameWorld->update();
   gameEntities.insert(gameEntities.end(), gameWorld->getWorldEntities().begin(), gameWorld->getWorldEntities().end());
   gameScores = AbstractFactory::createHighscores("../score.txt");
   std::shared_ptr<sf::Texture> aiTex = std::make_shared<sf::Texture>();
   aiTex->loadFromFile("../Resources/characterSprites/Soldier_01-4.png");
   createPlayer();
   initAI();
   gameEntities.push_back(gamePlayer);
   aiAnimation = std::make_shared<DungeonRunnerSFML::Animation>(aiTex,sf::Vector2u(3,4));
   std::shared_ptr<Entity> Wall1 = AbstractFactory::createCollider(std::pair<float,float>(-1.25,-7),std::pair<float,float>(0.5,14));
   std::shared_ptr<Entity> Wall2 = AbstractFactory::createCollider(std::pair<float,float>(1.25,-7),std::pair<float,float>(0.5,14));
   gameEntities.push_back(Wall1);
   gameEntities.push_back(Wall2);
   viewColliders.push_back(Wall1);
   viewColliders.push_back(Wall2);
}

void DungeonRunner::Game::update(double dTime) {
    gameWindow->clear();
    manageScores(dTime);
    spawnTraps();
    manageGameEvents();
    manageTraps(dTime);
    manageCollision(gamePlayer);
    managePlayerMovement(dTime);
    for(auto &ai:aiPlayers){ // before moving AI check for collision
        ai->updateGameEntities(gameEntities);
        manageCollision(ai);
    }
    manageAI(dTime);
    gameWorld->update();
    gameWorld->display();
    for(auto &ai:aiPlayers){ // update AI texture (animation)
        aiAnimation->update(3,dTime,true,0.5/ai->getAiSpeed());
        ai->setUvRect(aiAnimation->getUvRect());
        ai->update();
        ai->display();
    }
    gamePlayer->update();
    // update player texture (animation)
    playerAnimation->update(3,dTime,true,0.15/gamePlayer->getPlayerSpeed());
    gamePlayer->setUvRect(std::make_shared<sf::IntRect>(playerAnimation->getUvRect()));
    gamePlayer->display();

    auto mapCoords = Transformation::toPixel(gameWindow,0,6.5);
    if(gamePlayer->getPos().y < mapCoords.second+gameWindow->getSize().y/2.0-gameWindow->getSize().y/4.0) gameView.setCenter(gameWindow->getSize().x/2.0,mapCoords.second); // set static view untill player progresses
    else gameView.setCenter(gameWindow->getSize().x/2.0,gamePlayer->getPos().y-gameWindow->getSize().y/4.0); // update view position to player position
    updateViewColliders();

    for(auto &entity:gameEntities){
        if(entity==gamePlayer or entity->getType() == "AI") continue;
        entity->update();
        entity->display();
    }
    drawPlayerScore();
    gameWindow->setView(gameView);
}

void DungeonRunner::Game::createPlayer() {
    std::shared_ptr<sf::RectangleShape> player = std::make_shared<sf::RectangleShape>(sf::Vector2f(gameWindow->getSize().x/11.0,gameWindow->getSize().y/11.0));
    std::shared_ptr<sf::Vector2u> playerSize = std::make_shared<sf::Vector2u>(32,32);
    std::shared_ptr<sf::IntRect> uvRect = std::make_shared<sf::IntRect>();
    std::shared_ptr<sf::Texture> maleTex = std::make_shared<sf::Texture>();
    maleTex->loadFromFile("../Resources/characterSprites/Male_16-1.png");
    characterTex.push_back(maleTex);
    playerAnimation = std::make_shared<DungeonRunnerSFML::Animation>(maleTex,sf::Vector2u(3,4));
    uvRect->width = playerSize->x;
    uvRect->height = playerSize->y;
    uvRect->left = uvRect->width*1;
    uvRect->top = uvRect->height*3;
    player->setTextureRect(*uvRect);
    player->setTexture(&*characterTex[0]);
    gamePlayer = AbstractFactory::createPlayer(gameWindow,player,characterTex[0],uvRect);
    gamePlayer->registerObserver(AbstractFactory::createObserver("Player"));
}

bool DungeonRunner::Game::isColliding(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2,float push) {
    Collision newCollision(e1);
    return newCollision.checkCollision(e2,push);
}

void DungeonRunner::Game::updateViewColliders() {
    for(auto &collider:viewColliders){
        std::pair<float,float> newPos = collider->getEPosition();
        if(collider->getEPosition().first!=0){
            newPos.second = Transformation::toCoords(gameWindow,gameView.getCenter().x,gameView.getCenter().y).second-collider->getESize().second/2.0;
            collider->setEPosition(newPos);
        }
    }
}

void DungeonRunner::Game::manageCollision(std::shared_ptr<Entity> entity) {
    if(finished) return; // doesnt check for collision when game ends
    for(auto &collider:gameEntities){
        float push = 1;
        if(collider == entity) continue;
        if(entity->getType() == "AI" and collider->getType() == "Player") push =0.5; // AI and player have the same pushing force
        if(collider->getType() == "AI" and entity->getType() == "Player") push =0.5; // AI and player have the same pushing force
        if(collider->getType() == "AI" and entity->getType() == "AI") push =0.5; // AI and AI have the same pushing force
        if(isColliding(collider,entity,push)){
            if(collider->getType() == "Sword" and (entity->getType() == "Player" or entity->getType() == "AI")){
                collider->setEPosition(std::pair<float,float>(-3,9)); // teleport sword to no mans land when it hits ai or player
                entity->action();
            }
            if(collider->getType() == "Finish" and (entity->getType() == "Player" or entity->getType() == "AI")){ // checks who finished in which place to give score accordingly
                if(finishedPlayers == 0) entity->notifyObservers(DungeonRunner::Observer::finishedFirst);
                if(finishedPlayers == 1) entity->notifyObservers(DungeonRunner::Observer::finishedSecond);
                if(finishedPlayers == 2) entity->notifyObservers(DungeonRunner::Observer::finishedThird);
                if(finishedPlayers == 3) entity->notifyObservers(DungeonRunner::Observer::finishedLast);
                finishedPlayers++;
                if(entity->getType() == "Player") {
                    finished = true; // game ends when player reaches finishline
                    gameScores->addScore(entity->getSubjectObservers()[0]->getObserverName(),entity->getSubjectObservers()[0]->getObserverData());
                    gameScores->writeToFile();
                    std::sort(gameEntities.begin(),gameEntities.end(), [](std::shared_ptr<DungeonRunner::Entity> first, std::shared_ptr<DungeonRunner::Entity> second){
                        return first->getEPosition().second < second->getEPosition().second;
                    }); // sorts entities from smallest y-value to highest
                    for(auto &entity:gameEntities){ // places the rest of the hikers according to position at time that player finishes
                        if(entity->getType() == "AI" and entity->getEPosition().second<7){
                            if(finishedPlayers == 1) entity->notifyObservers(DungeonRunner::Observer::finishedSecond);
                            if(finishedPlayers == 2) entity->notifyObservers(DungeonRunner::Observer::finishedThird);
                            if(finishedPlayers == 3) entity->notifyObservers(DungeonRunner::Observer::finishedLast);
                            finishedPlayers++;
                        }
                    }
                }
            }
            continue;
        }
    }
}

void DungeonRunner::Game::managePlayerMovement(double dTime) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        gamePlayer->setPlayerSpeed(gamePlayer->getPlayerSpeed()*1.01); // speedup
        if(gamePlayer->getPlayerSpeed()*1.01 > 0.5) gamePlayer->setPlayerSpeed(0.5);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        gamePlayer->setPlayerSpeed(gamePlayer->getPlayerSpeed()/1.01); // slowdown
        if(gamePlayer->getPlayerSpeed()/1.01 < 0.2) gamePlayer->setPlayerSpeed(0.2);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        gamePlayer->move(2*dTime,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        gamePlayer->move(-2*dTime,0);
    }
    gamePlayer->move(0,gamePlayer->getPlayerSpeed()*dTime);
}

void DungeonRunner::Game::manageGameEvents() {
    sf::Event event;
    while (gameWindow->pollEvent(event)){
        if (event.type == sf::Event::Closed) gameWindow->close();
        if(event.type == sf::Event::KeyReleased and event.key.code == sf::Keyboard::Space) {
            for (auto &obstacle:gameEntities) {
                if (obstacle->getType() == "Door"  and !obstacle->isNoClip()){ // if door isnt opened a player can open it by pressing space
                    std::pair<float, float> pPos = gamePlayer->getEPosition();
                    std::pair<float, float> oPos = obstacle->getEPosition();
                    if (oPos.second - pPos.second <= 0.6 and oPos.second - pPos.second >0) { // if distance between object and player is lower dan 0.6 and player and the object are in the same lane
                        if(pPos.first>oPos.first-0.25 and pPos.first<oPos.first+0.25) {
                            obstacle->action(); // opens door
                            gamePlayer->notifyObservers(DungeonRunner::Observer::staticObstacleAction); // penalizes player
                            break;
                        }
                    }
                }
            }
        }

    }
}

void DungeonRunner::Game::spawnTraps() {
    std::pair<float, float> pPos = gamePlayer->getEPosition();
    std::pair<float, float> aiPos = aiPlayers[0]->getEPosition();
    for(auto &ai:aiPlayers){
        if(ai->getEPosition().second > aiPos.second) aiPos = ai->getEPosition();
    }
    if(aiPos.second > pPos.second) pPos = aiPos;
    if(Random::generateRandomChance()<0.013 and pPos.second + 1 <7) { // 1.3% chance every loop to spawn a new sword
        std::pair<float, float> tPos;
        tPos.first = Random::generateRandFloat(-1, 1);
        tPos.second = pPos.second + 0.8;
        std::shared_ptr<Entity> newTrap = AbstractFactory::createSword(gameWindow);
        newTrap->setEPosition(tPos);
        newTrap->update();
        newTrap->display();
        newTrap->setNoClip(true);
        gameEntities.push_back(newTrap);
    }

}

void DungeonRunner::Game::manageTraps(double dTime) {
    for(auto &trap:gameEntities){
        if(trap->getType() == "Sword"){
            trap->move(0,-dTime*0.8);
        }
    }

}

void DungeonRunner::Game::initAI() { // initialise AI
    for(int i=1;i!=4;i++){
        auto newAI = AbstractFactory::createAI(gameEntities,gameWindow);
        auto newObserver = AbstractFactory::createObserver("CPU" + std::to_string(i));
        newAI->registerObserver(newObserver);
        gameEntities.push_back(newAI);
        aiPlayers.push_back(newAI);
    }

}

void DungeonRunner::Game::run() {
    auto start = std::chrono::high_resolution_clock::now();
    double dTime;
    while (gameWindow->isOpen()){
        auto bpos0 = aiPlayers[0]->getEPosition();
        auto bpos1 = aiPlayers[1]->getEPosition();
        auto bpos2 = aiPlayers[2]->getEPosition();
        gameWindow->clear();
        auto now = std::chrono::high_resolution_clock::now();
        dTime = std::chrono::duration_cast<std::chrono::duration<double>>(now-start).count();
        if(dTime>1/60.0f){
            dTime = 1/60.0f;
        }
        start = now;
        if(!finished) update(dTime);
        else {
            manageGameEvents();
            drawHighscores();
        }
        gameWindow->display();
        auto apos0 = aiPlayers[0]->getEPosition();
        auto apos1 = aiPlayers[1]->getEPosition();
        auto apos2 = aiPlayers[2]->getEPosition();
        auto checkPos0 = std::abs(bpos0.second - apos0.second);
        auto checkPos1 = std::abs(bpos1.second - apos1.second);
        auto checkPos2 = std::abs(bpos2.second - apos2.second);

        //check if AI has moved in y-direction to see if they are stuck
        if( checkPos0 +0.000001< aiPlayers[0]->getAiSpeed()*dTime) aiPlayers[0]->setIsStuck(true);
        else aiPlayers[0]->setIsStuck(false);
        if( checkPos1 +0.000001< aiPlayers[1]->getAiSpeed()*dTime) aiPlayers[1]->setIsStuck(true);
        else aiPlayers[1]->setIsStuck(false);
        if( checkPos2 +0.000001< aiPlayers[2]->getAiSpeed()*dTime) aiPlayers[2]->setIsStuck(true);
        else aiPlayers[2]->setIsStuck(false);
    }
}

void DungeonRunner::Game::manageAI(float dTime) {
    for(auto &ai:aiPlayers){
        manageCollision(ai);
        ai->run();
        ai->move(0,ai->getAiSpeed()*dTime);
        for(auto &checkai:aiPlayers){
            manageCollision(checkai);
        }
        if(ai->getDodgeState() == 1){ // dodge left
            ai->move(-2*dTime,0);
        }
        else if(ai->getDodgeState() == 2){ // dodge right
            ai->move(2*dTime,0);
        }
        for(auto &checkai:aiPlayers){
            manageCollision(checkai);
        }
        manageCollision(gamePlayer);
    }

}

void DungeonRunner::Game::manageScores(float dTime) {
    std::sort(gameEntities.begin(),gameEntities.end(), [](std::shared_ptr<DungeonRunner::Entity> first, std::shared_ptr<DungeonRunner::Entity> second){
        return first->getEPosition().second < second->getEPosition().second;
    });
    int placement = 4;
    for(auto &entity:gameEntities){
        if(entity->getType() == "Player" or entity->getType() == "AI"){
            if(placement == 1) entity->notifyObservers(DungeonRunner::Observer::firstPlace, dTime);
            if(placement == 2) entity->notifyObservers(DungeonRunner::Observer::secondPlace, dTime);
            if(placement == 3) entity->notifyObservers(DungeonRunner::Observer::thirdPlace, dTime);
            if(placement == 4) entity->notifyObservers(DungeonRunner::Observer::lastPlace, dTime);
            placement--;
        }
    }

}

void DungeonRunner::Game::drawHighscores() {
    sf::Text textTemplate;
    sf::Font textFont;
    textFont.loadFromFile("../Resources/Fonts/RetroGaming.ttf");
    textTemplate.setFont(textFont);
    textTemplate.setCharacterSize(gameWindow->getSize().x*0.035);
    sf::Text hsText(textTemplate);
    hsText.setString("**GAME SCORES**");
    hsText.setOrigin(hsText.getGlobalBounds().width / 2.0, hsText.getGlobalBounds().height / 2.0);
    hsText.setPosition(gameView.getCenter().x,gameView.getCenter().y-gameView.getSize().y/8.0);

    sf::Text scoreText1(textTemplate);
    sf::Text scoreText2(textTemplate);
    sf::Text scoreText3(textTemplate);
    sf::Text scoreText4(textTemplate);

    scoreText1.setFillColor(sf::Color::Yellow);
    scoreText2.setFillColor(sf::Color(59,59,59));
    scoreText3.setFillColor(sf::Color(102, 51, 0));


    std::vector<std::pair<std::string,int>> endScore;
    endScore.emplace_back(gamePlayer->getSubjectObservers()[0]->getObserverName(),gamePlayer->getSubjectObservers()[0]->getObserverData());
    for(auto &ai:aiPlayers){
        endScore.emplace_back(ai->getSubjectObservers()[0]->getObserverName(),ai->getSubjectObservers()[0]->getObserverData());
    }
    std::sort(endScore.begin(),endScore.end(),[](std::pair<std::string,int> a, std::pair<std::string,int> b){
        return a.second > b.second;
    });

    std::stringstream firstPlace;
    std::stringstream secondPlace;
    std::stringstream thirdPlace;
    std::stringstream fourthPlace;
    firstPlace << endScore[0].first << std::setw(15) << endScore[0].second <<std::endl;
    secondPlace << endScore[1].first << std::setw(15) << endScore[1].second <<std::endl;
    thirdPlace << endScore[2].first << std::setw(15) << endScore[2].second <<std::endl;
    fourthPlace << endScore[3].first << std::setw(15) << endScore[3].second <<std::endl;
    scoreText1.setString(firstPlace.str());
    scoreText2.setString(secondPlace.str());
    scoreText3.setString(thirdPlace.str());
    scoreText4.setString(fourthPlace.str());

    scoreText1.setOrigin(scoreText1.getGlobalBounds().width/2.0,scoreText1.getGlobalBounds().height/2.0);
    scoreText2.setOrigin(scoreText2.getGlobalBounds().width/2.0,scoreText2.getGlobalBounds().height/2.0);
    scoreText3.setOrigin(scoreText3.getGlobalBounds().width/2.0,scoreText3.getGlobalBounds().height/2.0);
    scoreText4.setOrigin(scoreText4.getGlobalBounds().width/2.0,scoreText4.getGlobalBounds().height/2.0);

    scoreText1.setPosition(gameView.getCenter().x,gameView.getCenter().y);
    scoreText2.setPosition(gameView.getCenter().x,scoreText1.getPosition().y+scoreText2.getLocalBounds().height);
    scoreText3.setPosition(gameView.getCenter().x,scoreText2.getPosition().y+scoreText3.getLocalBounds().height);
    scoreText4.setPosition(gameView.getCenter().x,scoreText3.getPosition().y+scoreText4.getLocalBounds().height);

    gameWindow->draw(hsText);
    gameWindow->draw(scoreText1);
    gameWindow->draw(scoreText2);
    gameWindow->draw(scoreText3);
    gameWindow->draw(scoreText4);
}

void DungeonRunner::Game::drawPlayerScore() {
    sf::Text playerScore;
    sf::Font textFont;
    playerScore.setCharacterSize(gameWindow->getSize().x*0.03);
    textFont.loadFromFile("../Resources/Fonts/RetroGaming.ttf");
    playerScore.setFont(textFont);

    playerScore.setString(std::to_string(gamePlayer->getSubjectObservers()[0]->getObserverData()));
    playerScore.setPosition(gameView.getCenter().x-gameWindow->getSize().x/2.0,gameView.getCenter().y-gameWindow->getSize().y/2.0);
    playerScore.setScale(1.5,1.5);
    playerScore.setOutlineThickness(5);
    gameWindow->draw(playerScore);


}
