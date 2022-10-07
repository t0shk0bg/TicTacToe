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

#include "ChangeNicknameScene.h"
#include "SettingsScene.h"

Scene* ChangeNicknameScene::createScene()
{
    return ChangeNicknameScene::create();
}

bool ChangeNicknameScene::init()
{
    if(!Scene::init())
        return false;
    
    //Loading background image
    loadBackground(this);
    
    //Adding settings label
    showHeadLabel(UI_SETTINGS, this);
    
    //Entering player's nickname
    enterPlayerNameTF(CC_CALLBACK_2(ChangeNicknameScene::playerNameTFevent, this), this);
    
    return true;
}

void ChangeNicknameScene::playerNameTFevent(Ref* sender, ui::TextField::EventType eType)
{
    if(eType == ui::TextField::EventType::DETACH_WITH_IME)
    {
        ui::TextField* playerNameTF = dynamic_cast<ui::TextField*>(sender);
        
        CCASSERT(playerNameTF, "Unable to perform dynamic conversion!");
        
        if(!playerNameTF->getString().length())
            return;
        
        UserDefault::getInstance()->setStringForKey(UD_KEY_NICKNAME, playerNameTF->getString());
        
        GameLayout::_director->replaceScene(TransitionPageTurn::create(ANIM_SCENE_TRANSIT, SettingsScene::createScene(), true));
    }
}
