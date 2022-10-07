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

#include "MainScene.h"

USING_NS_CC;

namespace NS_Game {

    void MainScene::loadBackground(Node* node)
    {
        std::string backgroundImageName;
        Vec2 backgroundScale;

        if(node->getName() == IN_GAME_SCENE_NAME)
        {
            backgroundImageName = IMAGE_IN_GAME_BG;
            backgroundScale.set(1.064f, 0.9f);
        }
        else
        {
            backgroundImageName = IMAGE_MENU_BG;
            backgroundScale.set(1.3f, 1.3f);
        }

        auto backgroundSprite = Sprite::create(backgroundImageName);

        CCASSERT(backgroundSprite, backgroundSprite->getResourceName().c_str());

        backgroundSprite->setScale(backgroundScale.x, backgroundScale.y);
        backgroundSprite->setPosition(Vec2((_visibleSize.width / 2), (_visibleSize.height / 2) + _origin.y));

        node->addChild(backgroundSprite, 0);
    }

    void MainScene::showHeadLabel(const std::string& text, Node* node)
    {
        auto headLabel = Label::createWithTTF(text, FONT_PATH(FONT_MARKER_FELT), 28);
        
        CCASSERT(headLabel, headLabel->getSystemFontName().c_str());
        
        headLabel->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 17) + _origin.y));
        headLabel->setColor(Color3B(0, 0, 0));
        
        node->addChild(headLabel, 1);
    }

    void MainScene::enterPlayerNameTF(const ui::TextField::ccTextFieldCallback& callback, Node* node)
    {
        auto playerNameTextField = ui::TextField::create(UI_ENTER_NICKNAME, FONT_PATH(FONT_MARKER_FELT), 28);
        
        CCASSERT(playerNameTextField, playerNameTextField->getFontName().c_str());
        
        playerNameTextField->setMaxLength(25);
        playerNameTextField->setMaxLengthEnabled(true);
        playerNameTextField->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 15)));
        playerNameTextField->setColor(Color3B(130, 130, 130));
        playerNameTextField->setTextColor(Color4B(0, 0, 0, UCHAR_MAX));
        
        std::string oldName = UserDefault::getInstance()->getStringForKey(UD_KEY_NICKNAME);
        
        if(oldName.length())
            playerNameTextField->setString(oldName);

        playerNameTextField->addEventListener(callback);

        node->addChild(playerNameTextField, 1);
    }

}
