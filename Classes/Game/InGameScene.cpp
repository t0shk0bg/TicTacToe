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

USING_NS_CC;

namespace NS_Game {

    using namespace NS_GameCore;

    Scene* InGameScene::createScene()
    {
        return InGameScene::create();;
    }

    bool InGameScene::init()
    {
        if(!Scene::init())
            return false;
        
        loadBackground(this);
        
        //Setting touch listener event
        auto touchListener = EventListenerTouchOneByOne::create();
        
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(InGameScene::onTouchBegan, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        scheduleUpdate();
        
        return true;
    }

    void InGameScene::update(float dt)
    {
        Scene::update(dt);
        
        processTurns();
        
        bool isWinner = _gameCore.isWinner();
        bool isDraw = _gameCore.isDraw();
        
        if(!_gameOutcome.result && (isWinner || isDraw))
        {
            float delay = ANIM_WIN_DELAY;
            
            if(isWinner)
            {
                log("There is a winner!");
                
                auto& winner = _gameCore.getWinner();
                
                for(uint8_t i = 0; i < CORE_BOARD_SIZE; i++)
                    _sprites[winner.coordinates[i].row][winner.coordinates[i].col]->runAction(Blink::create(delay, ANIM_WIN_BLINKS));
                
                _gameOutcome.result = GameOutcomeResult::win;
                _gameOutcome.winner = UserDefault::getInstance()->getStringForKey(UD_KEY_NICKNAME);
                
                if(_gameCore.getBotSign() == static_cast<BasicSignature>(winner.winnerSign))
                    _gameOutcome.winner += UI_MIGHTY_IPHONE;
            }
            
            if(isDraw)
            {
                log("Draw game");
                
                _gameOutcome.result = GameOutcomeResult::draw;
                delay = ANIM_DRAW_DELAY;
            }
            
            scheduleOnce(CC_SCHEDULE_SELECTOR(InGameScene::delayedEndGameScene), delay);
        }
    }

    void InGameScene::processTurns()
    {
        processTurn(Turn::player);
        
        if(_botAllowedToPlay && _gameCore.movesLeft())
        {
            processTurn(Turn::bot);
            
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
        MainScene::_director->replaceScene(TransitionPageTurn::create(ANIM_SCENE_TRANSIT, EndGameScene::createScene(_gameOutcome), false));
    }

    BoardPosition InGameScene::getPositionForPlayerTurn()
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

    void InGameScene::processTurn(Turn turn)
    {
        BoardPosition position;
        BasicSignature signForThisTurn;
        
        switch(turn)
        {
        case Turn::player:
        {
            position = getPositionForPlayerTurn();
            signForThisTurn = _gameCore.getPlayerSign();

            break;
        }

        case Turn::bot:
        {
            position = _gameCore.findBestBotMove();
            signForThisTurn = _gameCore.getBotSign();

            break;
        }

        default:
            CCASSERT(true, "Invalid turn!");
        }

        if((turn == _lastTurn) || _gameCore.move(position, signForThisTurn))
        {
            _eventDispatcher->resumeEventListenersForTarget(this);
            return;
        }

        std::string signFileName;
        
        signFileName = static_cast<char>(signForThisTurn);
        signFileName += GAME_SIGN_EXTS;
        
        _sprites[position.row][position.col] = Sprite::create(signFileName);

        CCASSERT(_sprites[position.row][position.col],
                 _sprites[position.row][position.col]->getResourceName().c_str());

        _sprites[position.row][position.col]->setPosition(Vec2(
           (((_visibleSize.width - 174) / 3) * (position.col + 1) + 37),
           ((_visibleSize.height / 3) * (2 - position.row)) + 93));

        this->addChild(_sprites[position.row][position.col], 1);
        
        _lastTurn = turn;

        if((turn == Turn::player) && _gameCore.movesLeft())
            scheduleOnce([this](float) -> void { _botAllowedToPlay = true; }, ANIM_BOT_TURN_DELAY, "botDisallowedToPlay");
    }

}
