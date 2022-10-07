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

#include "Settings.hpp"
#include "MainMenuScene.h"
#include "InGameScene.h"
#include "SettingsScene.h"

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

bool MainMenuScene::init()
{
    if(!Scene::init())
        return false;
    
    //Loading background image
    loadBackground(this);
    
    //Adding welcoming label
    showHeadLabel((std::string(UI_WELCOME_MSG_WN) + UserDefault::getInstance()->getStringForKey(UD_KEY_NICKNAME)), this);
    
    //Showing the main menu
    ShowMenu();
    
    return true;
}

void MainMenuScene::ShowMenu()
{
    Vector<MenuItem*> MainMenuItems;

    MenuItemFont::setFontSize(24);
    
    MainMenuItems.pushBack(MenuItemFont::create(UI_START_GAME, [&](Ref* pSender) {
        GameLayout::_director->replaceScene(TransitionPageTurn::create(ANIM_SCENE_TRANSIT, InGameScene::createScene(), false));
    }));
    MainMenuItems.pushBack(MenuItemFont::create(UI_SETTINGS, [&](Ref* pSender) {
        GameLayout::_director->replaceScene(TransitionPageTurn::create(ANIM_SCENE_TRANSIT, SettingsScene::createScene(), false));
    }));
    MainMenuItems.pushBack(MenuItemFont::create(UI_EXIT, [&](Ref* pSender) { Director::getInstance()->end(); }));
    
    auto mainMenu = Menu::createWithArray(MainMenuItems);
    
    mainMenu->setColor(Color3B(0, 0, 0));
    mainMenu->alignItemsVerticallyWithPadding(10);
    mainMenu->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 13)));
    
    this->addChild(mainMenu, 1);
}
