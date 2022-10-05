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

#include "EndGameScene.h"
#include "InGameScene.h"
#include "MainMenuScene.h"

GameOutcome EndGameScene::_gameOutcome;

Scene* EndGameScene::createScene(GameOutcome gameOutcome)
{
    EndGameScene::_gameOutcome = gameOutcome;
    
    return EndGameScene::create();
}

bool EndGameScene::init()
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
    
    ShowOutcomeLabel();
    
    ShowMenu();
    
    return true;
}

void EndGameScene::ShowOutcomeLabel()
{
    std::string outcomeMSG;
    
    if(EndGameScene::_gameOutcome.result == GameOutcomeResult::win)
        outcomeMSG += "Winner is " + EndGameScene::_gameOutcome.winner;
    else if(EndGameScene::_gameOutcome.result == GameOutcomeResult::draw)
        outcomeMSG += "Draw! Good luck next time ;)";
    else
        log("Invalid game outcome result!");
    
    //Adding outcome label
    auto outcomeLabel = Label::createWithTTF(outcomeMSG, "fonts/Marker Felt.ttf", 28);
    
    if(outcomeLabel == nullptr)
        log("Problem loading: %s", outcomeLabel->getSystemFontName().c_str());
    else
    {
        Vec2 origin = _director->getVisibleOrigin();
        
        outcomeLabel->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 17) + origin.y));
        this->addChild(outcomeLabel, 1);
    }
}

void EndGameScene::ShowMenu()
{
    Vector<MenuItem *> menuItems;
    
    MenuItemFont::setFontSize(24);
    
    menuItems.pushBack(MenuItemFont::create("Start new game", [&](Ref * pSender) {
        _director->replaceScene(TransitionPageTurn::create(1.2f, InGameScene::createScene(), false));
    }));
    menuItems.pushBack(MenuItemFont::create("Back to menu", [&](Ref * pSender) {
        _director->replaceScene(TransitionPageTurn::create(1.2f, MainMenuScene::createScene(), false));
    }));
    
    auto menu = Menu::createWithArray(menuItems);
    
    menu->alignItemsVerticallyWithPadding(10);
    menu->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 13)));
    
    this->addChild(menu, 1);
}
