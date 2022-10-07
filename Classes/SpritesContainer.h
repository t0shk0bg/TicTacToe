#pragma once

#include "cocos2d.h"

USING_NS_CC;

struct SpriteNode
{
    uint8_t id;
    Sprite* sprite;
    
    SpriteNode() {}
    SpriteNode(Sprite* s, uint8_t n): id(n), sprite(s) {}
};

class SpritesContainer
{
public:
    static SpritesContainer* getInstance();
    
    bool saveSprite(Sprite* sprite, uint8_t id);
    bool removeSprite(uint8_t id);
    
    Sprite* getSprite(uint8_t id);
    
private:
    SpritesContainer() {};
    SpritesContainer(SpritesContainer const&) = delete;
    void operator=(SpritesContainer const&) = delete;
    
private:
    static SpritesContainer* s_spritesContainer;
    
private:
    std::vector<SpriteNode> _spriteNodes;
};
