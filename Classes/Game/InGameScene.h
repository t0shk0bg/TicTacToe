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

#pragma once

#include "cocos2d.h"

#include "../GameCore/GameCore.h"
#include "EndGameScene.h"
#include "MainScene.h"

namespace NS_Game {

    class InGameScene: public cocos2d::Scene, MainScene
    {
    private:
        enum Turn: uint8_t
        {
            none = 0,
            player,
            bot
        };
        
    public:
        CREATE_FUNC(InGameScene);
        static cocos2d::Scene* createScene();
        
    public:
        InGameScene():
            _gameCore(NS_GameCore::GameCore(static_cast<NS_GameCore::BasicSignature>(cocos2d::UserDefault::getInstance()->getStringForKey(UD_KEY_SIGNATURE)[0]))),
            _botAllowedToPlay(false), _lastTurn(Turn::none)
        {
            this->setName(__FUNCTION__);
        }
        
        virtual bool init() override;
        virtual void update(float dt) override;
        
        void processTurns();
        
        bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
        void delayedEndGameScene(float a);
        
        NS_GameCore::BoardPosition getPositionForPlayerTurn();
        
        void processTurn(Turn turn);
        
    private:
        NS_GameCore::GameCore _gameCore;
        cocos2d::Sprite* _sprites[CORE_BOARD_SIZE][CORE_BOARD_SIZE];
        
        cocos2d::Vec2 _playerMove;
        bool _botAllowedToPlay;
        Turn _lastTurn;
        
        GameOutcome _gameOutcome;
    };

}
