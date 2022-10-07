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

#include "SettingsScene.h"
#include "MainMenuScene.h"
#include "ChangeNicknameScene.h"

static bool showMenuUpdate = true;

Scene* SettingsScene::createScene()
{
    return SettingsScene::create();
}

bool SettingsScene::init()
{
    if(!Scene::init())
        return false;
    
    //Loading background image
    loadBackground(this);
    
    //Adding settings label
    showHeadLabel(UI_SETTINGS, this);
    
    //Showing the settings menu
    ShowMenu();
    
    scheduleUpdate();
    
    return true;
}

void SettingsScene::update(float delta)
{
    //Updating the settings menu
    ShowMenu();
    
    Scene::update(delta);
}

void SettingsScene::onExit()
{
    showMenuUpdate = true;
    
    Scene::onExit();
}

void SettingsScene::ShowMenu()
{
    if(showMenuUpdate)
    {
        Vector<MenuItem*> settingsMenuItems;
        UserDefault* userDefault = UserDefault::getInstance();
        
        MenuItemFont::setFontSize(24);
        
        settingsMenuItems.pushBack(MenuItemFont::create(UI_CHANGE_NICKNAME, [=](Ref* pSender) {
            GameLayout::_director->replaceScene(TransitionPageTurn::create(ANIM_SCENE_TRANSIT, ChangeNicknameScene::createScene(), false));
        }));
        settingsMenuItems.pushBack(MenuItemFont::create(UI_PLAYER_SIGN + userDefault->getStringForKey(UD_KEY_SIGNATURE), [=](Ref* pSender) {
            showMenuUpdate = true;
            
            userDefault->setStringForKey(UD_KEY_SIGNATURE, userDefault->getStringForKey(UD_KEY_SIGNATURE) == GAME_SIGN_X ? GAME_SIGN_O : GAME_SIGN_X);
            
            this->removeChildByName("settingsMenu");
        }));
        settingsMenuItems.pushBack(MenuItemFont::create(UI_GO_BACK, [&](Ref* pSender) {
            GameLayout::_director->replaceScene(TransitionPageTurn::create(ANIM_SCENE_TRANSIT, MainMenuScene::createScene(), true));
        }));
        
        auto settingsMenu = Menu::createWithArray(settingsMenuItems);
        
        settingsMenu->setColor(Color3B(0, 0, 0));
        settingsMenu->alignItemsVerticallyWithPadding(10);
        settingsMenu->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 13)));
        
        this->addChild(settingsMenu, 1, "settingsMenu");
        
        showMenuUpdate = false;
    }
}

