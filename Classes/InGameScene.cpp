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
    return InGameScene::create();;
}

bool InGameScene::init()
{
    if(!Scene::init())
        return false;
    
    //Loading InGame background image
    loadBackground(this);
    
    //Setting touch listener
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(InGameScene::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    scheduleUpdate();
    
    return true;
}

void InGameScene::update(float dt)
{
    processTurns();
    
    bool isWinner = _gameCore.isWinner();
    bool isDraw = _gameCore.isDraw();
    
    if(!_gameOutcome.result && (isWinner || isDraw))
    {
        float delay = ANIM_WIN_DELAY;
        
        if(isWinner)
        {
            Winner winner = _gameCore.getWinner();
            
            for(uint8_t i = 0; i < CORE_BOARD_SIZE; i++)
                _sprites[winner.coordinates[i].row][winner.coordinates[i].col]->runAction(Blink::create(delay, ANIM_WIN_BLINKS));
            
            _gameOutcome.result = GameOutcomeResult::win;
            _gameOutcome.winner = UserDefault::getInstance()->getStringForKey(UD_KEY_NICKNAME);
            
            if(_gameCore.getBotSign() == static_cast<BasicSignature>(winner.winnerSign))
                _gameOutcome.winner += UI_MIGHTY_IPHONE;
        }
        
        if(isDraw)
        {
            _gameOutcome.result = GameOutcomeResult::draw;
            delay = ANIM_DRAW_DELAY;
        }
        
        scheduleOnce(CC_SCHEDULE_SELECTOR(InGameScene::delayedEndGameScene), delay);
        _eventDispatcher->resumeEventListenersForTarget(this);
    }
    
    Scene::update(dt);
}

void InGameScene::processTurns()
{
    playerTurn();
    
    if(_botAllowedToPlay)
    {
        botTurn();
        
        _eventDispatcher->resumeEventListenersForTarget(this);
        _botAllowedToPlay = false;
    }
}

bool InGameScene::onTouchBegan(Touch* touch, Event* event)
{
    _playerMove = touch->getLocation();
    
    log("X = %f, Y= %f", _playerMove.x, _playerMove.y);
    
    _eventDispatcher->pauseEventListenersForTarget(this);
    
    return true;
}

void InGameScene::delayedEndGameScene(float dt)
{
    GameLayout::_director->replaceScene(TransitionPageTurn::create(ANIM_SCENE_TRANSIT, EndGameScene::createScene(_gameOutcome), false));
}

BoardPosition InGameScene::getPosition()
{
    BoardPosition bPosition;
    
    if(_playerMove.y < 130)
        bPosition.row = 2;
    else if(_playerMove.y < 202)
        bPosition.row = 1;
    else
        bPosition.row = 0;
    
    if(_playerMove.x > 95 && _playerMove.x < 380)
    {
        if(_playerMove.x < 190)
            bPosition.col = 0;
        else if(_playerMove.x < 295)
            bPosition.col = 1;
        else
            bPosition.col = 2;
    }
    
    return bPosition;
}

bool InGameScene::playerTurn()
{
    auto playerPosition = getPosition();
    
    if(_gameCore.playerMove(playerPosition))
        return false;
    
    std::string signFileName;
    
    signFileName = static_cast<char>(_gameCore.getPlayerSign());
    signFileName += GAME_SIGN_EXTS;
    
    _sprites[playerPosition.row][playerPosition.col] = Sprite::create(signFileName);
    
    CCASSERT(_sprites[playerPosition.row][playerPosition.col],
             _sprites[playerPosition.row][playerPosition.col]->getResourceName().c_str());
    
    _sprites[playerPosition.row][playerPosition.col]->setPosition(Vec2(
       (((_visibleSize.width - 174) / 3) * (playerPosition.col + 1) + 37),
       ((_visibleSize.height / 3) * (2 - playerPosition.row)) + 93));
    
    this->addChild(_sprites[playerPosition.row][playerPosition.col], 1);
    
    scheduleOnce([this](float) -> void { _botAllowedToPlay = true; }, ANIM_BOT_TURN_DELAY, "botDisallowedToPlay");
    
    return true;
}

bool InGameScene::botTurn()
{
    auto botPosition = _gameCore.findBestBotMove();
    
    if(_gameCore.botMove(botPosition))
        return false;
    
    std::string signFileName;
    
    signFileName = static_cast<char>(_gameCore.getBotSign());
    signFileName += GAME_SIGN_EXTS;
    
    _sprites[botPosition.row][botPosition.col] = Sprite::create(signFileName);
    
    CCASSERT(_sprites[botPosition.row][botPosition.col],
             _sprites[botPosition.row][botPosition.col]->getResourceName().c_str());
    
    _sprites[botPosition.row][botPosition.col]->setPosition(Vec2(
         (((_visibleSize.width - 174) / 3) * (botPosition.col + 1) + 37),
         ((_visibleSize.height / 3) * (2 - botPosition.row)) + 93));
    
    this->addChild(_sprites[botPosition.row][botPosition.col], 1);
    
    return true;
}
