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

static bool showMenuUpdate = true;

Scene * SettingsScene::createScene()
{
    return SettingsScene::create();
}

bool SettingsScene::init()
{
    if(!Scene::init())
        return false;
    
    Vec2 origin = _director->getVisibleOrigin();
    
    //Setting background
    auto backgroundSprite = Sprite::create("background.jpeg");
    
    if(backgroundSprite == nullptr)
        log("Problem loading: %s", backgroundSprite->getResourceName().c_str());
    else
    {
        backgroundSprite->setPosition(Vec2((_visibleSize.width / 2), (_visibleSize.height / 2) + origin.y));
        backgroundSprite->setScale(1.062f, 0.9f);
        
        this->addChild(backgroundSprite, 0);
    }
    
    //Adding welcoming label
    auto welcomeMSG = std::string("Welcome ") + UserDefault::getInstance()->getStringForKey("nickname");
    auto welcomeLabel = Label::createWithTTF(welcomeMSG, "fonts/Marker Felt.ttf", 28);
    
    if(welcomeLabel == nullptr)
        log("Problem loading: %s", welcomeLabel->getSystemFontName().c_str());
    else
    {
        welcomeLabel->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 17) + origin.y));
        this->addChild(welcomeLabel, 1);
    }
    
    //Showing the settings menu
    ShowMenu();
    
    schedule(CC_SCHEDULE_SELECTOR(SettingsScene::updatePerFrame), 0);
    
    return true;
}

void SettingsScene::onExit()
{
    Scene::onExit();
    
    showMenuUpdate = true;
    unschedule(CC_SCHEDULE_SELECTOR(SettingsScene::updatePerFrame));
}

void SettingsScene::updatePerFrame(float dt)
{
    //Updating the settings menu
    ShowMenu();
}

void SettingsScene::ShowMenu()
{
    if(showMenuUpdate)
    {
        Vector<MenuItem *> settingsMenuItems;
        
        UserDefault* userDefault = UserDefault::getInstance();
        
        MenuItemFont::setFontSize(24);
        
        settingsMenuItems.pushBack(MenuItemFont::create("Player sign: " + userDefault->getStringForKey("playerSign"), [=](Ref* pSender) {
            showMenuUpdate = true;
            
            userDefault->setStringForKey("playerSign", userDefault->getStringForKey("playerSign")[0] == 'X' ? "O" : "X");
            
            this->removeChildByName("settingsMenu");
        }));
        settingsMenuItems.pushBack(MenuItemFont::create("Go back", [&](Ref* pSender) {
            _director->replaceScene(TransitionPageTurn::create(1.2f, MainMenuScene::createScene(), true));
        }));
        
        auto settingsMenu = Menu::createWithArray(settingsMenuItems);
        
        settingsMenu->alignItemsVerticallyWithPadding(10);
        settingsMenu->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 13)));
        
        this->addChild(settingsMenu, 1, "settingsMenu");
        
        showMenuUpdate = false;
    }
}

