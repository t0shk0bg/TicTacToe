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
#include "ui/CocosGUI.h"

#include "Settings.hpp"

namespace TicTacToe {

    class MainScene
    {
    public:
        MainScene(): _director(cocos2d::Director::getInstance()), _visibleSize(_director->getVisibleSize()), _origin(_director->getVisibleOrigin()) {}
        
        virtual void loadBackground(cocos2d::Node* node);
        virtual void showHeadLabel(const std::string& text, cocos2d::Node* node);
        virtual void enterPlayerNameTF(const cocos2d::ui::TextField::ccTextFieldCallback& callback, cocos2d::Node* node);
        
        void playerNameTFevent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType eType);
        
        virtual ~MainScene() {}
        
    protected:
        cocos2d::Director* _director;
        cocos2d::Size _visibleSize;
        cocos2d::Vec2 _origin;
    };

}
