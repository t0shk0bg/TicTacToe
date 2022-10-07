#include "SpritesContainer.h"

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
