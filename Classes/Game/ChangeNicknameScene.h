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

#include "MainScene.h"

namespace NS_Game {

    class ChangeNicknameScene: public cocos2d::Scene, MainScene
    {
    public:
        static cocos2d::Scene* createScene();
        
        CREATE_FUNC(ChangeNicknameScene);
        
    public:
        ChangeNicknameScene()
        {
            setName(__FUNCTION__);
        }
        
        virtual bool init() override;
        
        /// A callback which would be called when a TextField event happens.
        /// - Parameters:
        ///   - sender: Event sender
        ///   - eType: Event type
        void playerNameTFevent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType eType);
    };

}
