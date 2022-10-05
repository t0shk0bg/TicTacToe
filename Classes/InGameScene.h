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
#include "GameCore.h"
#include "EndGameScene.h"

USING_NS_CC;

class InGameScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(InGameScene);
    static cocos2d::Scene* createScene();
    
public:
    InGameScene():
    _director(Director::getInstance()),
    _visibleSize(_director->getVisibleSize()),
    _gameCore(GameCore(static_cast<BasicSignature>(UserDefault::getInstance()->getStringForKey("playerSign")[0]))) {}
    
    virtual bool init() override;
    
    void ProcessMoves(float x, float y);
    
    bool onTouchBegan(Touch * touch, Event * event);
    void DelayedEndGameScene(float a);
    
    BoardPosition getPosition(float x, float y);
    
    int8_t playerTurn(float x, float y);
    int8_t botTurn();
    
private:
    Director * _director;
    Size _visibleSize;
    
    GameCore _gameCore;
    Sprite * _sprites[CORE_BOARD_SIZE][CORE_BOARD_SIZE];
    
    GameOutcome _gameOutcome;
};
