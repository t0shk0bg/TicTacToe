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

namespace TicTacToe {

    struct SpriteNode
    {
        uint8_t id;
        cocos2d::Sprite* sprite;
        
        SpriteNode() {}
        SpriteNode(cocos2d::Sprite* s, uint8_t n): id(n), sprite(s) {}
    };

    class SpritesContainer
    {
    public:
        static SpritesContainer* getInstance();
        
        bool saveSprite(cocos2d::Sprite* sprite, uint8_t id);
        bool removeSprite(uint8_t id);
        
        cocos2d::Sprite* getSprite(uint8_t id);
        
    private:
        SpritesContainer() {};
        SpritesContainer(SpritesContainer const&) = delete;
        void operator=(SpritesContainer const&) = delete;
        
    private:
        static SpritesContainer* s_spritesContainer;
        
    private:
        std::vector<SpriteNode> _spriteNodes;
    };

}