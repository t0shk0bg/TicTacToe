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

USING_NS_CC;

namespace TicTacToe {

    GameOutcome EndGameScene::s_gameOutcome;

    Scene* EndGameScene::createScene(GameOutcome gameOutcome)
    {
        EndGameScene::s_gameOutcome = gameOutcome;
        
        return EndGameScene::create();
    }

    bool EndGameScene::init()
    {
        if(!Scene::init())
            return false;
        
        //Loading background image
        loadBackground(this);
        
        //Showing outcome label
        ShowResultLabel();
        
        ShowMenu();
        
        return true;
    }

    void EndGameScene::ShowResultLabel()
    {
        std::string outcomeMSG;
        
        switch(EndGameScene::s_gameOutcome.result)
        {
            case GameOutcomeResult::win:
                outcomeMSG += UI_WINNER_IS + EndGameScene::s_gameOutcome.winner;
                break;
                
            case GameOutcomeResult::draw:
                outcomeMSG += UI_DRAW;
                break;
                
            default:
                CCASSERT(true, "Invalid game outcome result");
                break;
        }
        
        showHeadLabel(outcomeMSG, this);
    }

    void EndGameScene::ShowMenu()
    {
        Vector<MenuItem*> menuItems;
        
        MenuItemFont::setFontSize(24);
        
        menuItems.pushBack(MenuItemFont::create(UI_START_GAME, [this](Ref* pSender) -> void {
            MainScene::_director->replaceScene(TransitionPageTurn::create(ANIM_SCENE_TRANSIT, InGameScene::createScene(), false));
        }));
        menuItems.pushBack(MenuItemFont::create(UI_BACK_TO_MENU, [this](Ref* pSender) -> void {
            MainScene::_director->replaceScene(TransitionPageTurn::create(ANIM_SCENE_TRANSIT, MainMenuScene::createScene(), false));
        }));
        
        auto menu = Menu::createWithArray(menuItems);
        
        menu->setColor(Color3B(0, 0, 0));
        menu->alignItemsVerticallyWithPadding(10);
        menu->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 13)));
        
        this->addChild(menu, 1);
    }

}