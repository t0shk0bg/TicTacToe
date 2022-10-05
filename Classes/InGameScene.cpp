/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "InGameScene.h"

Scene* InGameScene::createScene()
{
    return InGameScene::create();
}

bool InGameScene::init()
{
    if(!Scene::init())
        return false;
    
    //Setting background
    auto backgroundSprite = Sprite::create("background.jpeg");
    
    if(backgroundSprite == nullptr)
        log("Problem loading: %s", backgroundSprite->getResourceName().c_str());
    else
    {
        Vec2 origin = _director->getVisibleOrigin();
        
        backgroundSprite->setPosition(Vec2((_visibleSize.width / 2), (_visibleSize.height / 2) + origin.y));
        backgroundSprite->setScale(1.062f, 0.9f);
        
        this->addChild(backgroundSprite, 0);
    }
    
    //Setting touch listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(InGameScene::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void InGameScene::ProcessMoves(float x, float y)
{
    if(playerTurn(x, y))
        return;
    
    if(botTurn())
        return;
}

bool InGameScene::onTouchBegan(Touch * touch, Event * event)
{
    float x = touch->getLocation().x;
    float y = touch->getLocation().y;
    
    log("X = %f, Y= %f", x, y);
    
    ProcessMoves(x, y);
    
    bool isWinner = _gameCore.isWinner();
    bool isDraw = _gameCore.isDraw();
    
    if(isWinner || isDraw)
    {
        float delay = 2.0f;
        
        if(isWinner)
        {
            Winner winner = _gameCore.getWinner();
            
            for(uint8_t i = 0; i < CORE_BOARD_SIZE; i++)
                _sprites[winner.coordinates[i].row][winner.coordinates[i].col]->runAction(Blink::create(delay, 5));
            
            _gameOutcome.result = GameOutcomeResult::win;
            _gameOutcome.winner = UserDefault::getInstance()->getStringForKey("nickname");
            
            if(_gameCore.getBotSign() == static_cast<BasicSignature>(winner.winnerSign))
                _gameOutcome.winner += "'s mighty iPhone";
        }
        
        if(isDraw)
        {
            _gameOutcome.result = GameOutcomeResult::draw;
            delay = 1.0f;
        }
        
        scheduleOnce(CC_SCHEDULE_SELECTOR(InGameScene::DelayedEndGameScene), delay);
    }
    
    return true;
}

void InGameScene::DelayedEndGameScene(float dt)
{
    _director->replaceScene(TransitionPageTurn::create(1.2f, EndGameScene::createScene(_gameOutcome), false));
}

BoardPosition InGameScene::getPosition(float x, float y)
{
    BoardPosition bPosition;
    
    if(y < 130)
        bPosition.row = 2;
    else if(y < 202)
        bPosition.row = 1;
    else
        bPosition.row = 0;
    
    if(x > 95 && x < 380)
    {
        if(x < 190)
            bPosition.col = 0;
        else if(x < 295)
            bPosition.col = 1;
        else
            bPosition.col = 2;
    }
    
    return bPosition;
}

int8_t InGameScene::playerTurn(float x, float y)
{
    auto playerPosition = getPosition(x, y);
    
    if(_gameCore.playerMove(playerPosition))
        return -1;
    
    std::string signFileName;
    
    signFileName = static_cast<char>(_gameCore.getPlayerSign());
    signFileName += ".png";
    
    _sprites[playerPosition.row][playerPosition.col] = Sprite::create(signFileName);
    
    if(_sprites[playerPosition.row][playerPosition.col] == nullptr)
        log("Problem loading %s", _sprites[playerPosition.row][playerPosition.col]->getResourceName().c_str());
    else
    {
        _sprites[playerPosition.row][playerPosition.col]->setPosition(Vec2(
           (((_visibleSize.width - 174) / 3) * (playerPosition.col + 1) + 37),
           ((_visibleSize.height / 3) * (2 - playerPosition.row)) + 93));
        
        this->addChild(_sprites[playerPosition.row][playerPosition.col], 1);
    }
    
    return 0;
}

int8_t InGameScene::botTurn()
{
    auto botPosition = _gameCore.findBestBotMove();
    
    if(_gameCore.botMove(botPosition))
        return -1;
    
    std::string signFileName;
    
    signFileName = static_cast<char>(_gameCore.getBotSign());
    signFileName += ".png";
    
    _sprites[botPosition.row][botPosition.col] = Sprite::create(signFileName);
    
    if (_sprites[botPosition.row][botPosition.col] == nullptr)
        log("Problem loading %s", _sprites[botPosition.row][botPosition.col]->getResourceName().c_str());
    else
    {
        _sprites[botPosition.row][botPosition.col]->setPosition(Vec2(
             (((_visibleSize.width - 174) / 3) * (botPosition.col + 1) + 37),
             ((_visibleSize.height / 3) * (2 - botPosition.row)) + 93));
        
        this->addChild(_sprites[botPosition.row][botPosition.col], 1);
    }
}
