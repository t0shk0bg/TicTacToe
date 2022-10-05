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
    
    //Showing the main menu
    ShowMenu();

    /*auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = visibleSize.width - closeItem->getContentSize().width;
        float y = visibleSize.height - closeItem->getContentSize().height;
        closeItem->setPosition(Vec2(x,y));
    }
     */
    return true;
}

void MainMenuScene::ShowMenu()
{
    Vector<MenuItem *> MainMenuItems;
    
    MenuItemFont::setFontSize(24);
    
    MainMenuItems.pushBack(MenuItemFont::create("Start new game", [&](Ref* pSender) {
        _director->replaceScene(TransitionPageTurn::create(1.2f, InGameScene::createScene(), false));
    }));
    MainMenuItems.pushBack(MenuItemFont::create("Settings", [&](Ref* pSender) {
        _director->replaceScene(TransitionPageTurn::create(1.2f, SettingsScene::createScene(), false));
    }));
    MainMenuItems.pushBack(MenuItemFont::create("Exit", [&](Ref* pSender) { Director::getInstance()->end(); }));
    
    auto mainMenu = Menu::createWithArray(MainMenuItems);
    
    mainMenu->alignItemsVerticallyWithPadding(10);
    mainMenu->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 13)));
    
    this->addChild(mainMenu, 1);
}
