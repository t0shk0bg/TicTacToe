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

#include "SpritesContainer.h"

USING_NS_CC;

namespace TicTacToe {

    SpritesContainer* SpritesContainer::s_spritesContainer = nullptr;

    SpritesContainer* SpritesContainer::getInstance()
    {
        if(s_spritesContainer == nullptr)
        {
            s_spritesContainer = new (std::nothrow) SpritesContainer;
        }

        return s_spritesContainer;
    }

    bool SpritesContainer::saveSprite(Sprite* sprite, uint8_t id)
    {
        for(const auto& spriteNode: _spriteNodes)
            if(spriteNode.id == id)
                return false;
        
        sprite->retain();
        _spriteNodes.push_back(SpriteNode(sprite, id));
        
        return true;
    }

    bool SpritesContainer::removeSprite(uint8_t id)
    {
        for(auto it = _spriteNodes.begin(); it != _spriteNodes.end(); it++)
        {
            auto spriteNode = *it;
            
            if(spriteNode.id == id)
            {
                spriteNode.sprite->release();
                _spriteNodes.erase(it);
                
                return true;
            }
        }
        
        return false;
    }

    Sprite* SpritesContainer::getSprite(uint8_t id)
    {
        for(const auto& spriteNode: _spriteNodes)
            if(spriteNode.id == id)
                return spriteNode.sprite;
        
        return nullptr;
    }

}