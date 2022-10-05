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

#include "EntryPointScene.h"
#include "MainMenuScene.h"

Scene * EntryPointScene::createScene()
{
    return EntryPointScene::create();
}

bool EntryPointScene::init()
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
    auto welcomeLabel = Label::createWithTTF("Welcome", "fonts/Marker Felt.ttf", 28);
    
    if(welcomeLabel == nullptr)
        log("Problem loading: %s", welcomeLabel->getSystemFontName().c_str());
    else
    {
        welcomeLabel->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 17) + origin.y));
        this->addChild(welcomeLabel, 1);
    }
    
    //Entering player's nickname
    enterPlayerNameTF();
    
    return true;
}

void EntryPointScene::enterPlayerNameTF()
{
    auto playerNameTextField = ui::TextField::create("Enter you nickname here :)", "fonts/Marker Felt.ttf", 28);
    
    if(playerNameTextField == nullptr)
        log("Problem loading: %s", playerNameTextField->getFontName().c_str());
    else
    {
        playerNameTextField->setMaxLength(25);
        playerNameTextField->setMaxLengthEnabled(true);
        playerNameTextField->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 15)));

        playerNameTextField->addEventListener(CC_CALLBACK_2(EntryPointScene::playerNameTFevent, this));

        this->addChild(playerNameTextField, 1);
    }
}

void EntryPointScene::playerNameTFevent(Ref * sender, ui::TextField::EventType eType)
{
    if(eType == ui::TextField::EventType::DETACH_WITH_IME)
    {
        ui::TextField * playerNameTF = dynamic_cast<ui::TextField *>(sender);
        
        if(playerNameTF == nullptr)
            log("Unable to perform dynamic conversion!");
        else
        {
            auto userDefault = UserDefault::getInstance();
            
            userDefault->setStringForKey("nickname", playerNameTF->getString());
            userDefault->setStringForKey("playerSign", "X");
            
            _director->replaceScene(TransitionPageTurn::create(1.2f, MainMenuScene::createScene(), false));
        }
    }
}
