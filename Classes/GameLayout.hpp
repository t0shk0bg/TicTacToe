#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Settings.hpp"

USING_NS_CC;

class GameLayout
{
public:
    GameLayout(): _director(Director::getInstance()), _visibleSize(_director->getVisibleSize()), _origin(_director->getVisibleOrigin()) {}
    
    virtual void loadBackground(Node* node);
    virtual void showHeadLabel(const std::string& text, Node* node);
    virtual void enterPlayerNameTF(const ui::TextField::ccTextFieldCallback& callback, Node* node);
    
    void playerNameTFevent(Ref* sender, ui::TextField::EventType eType);
    
    virtual ~GameLayout() {}
    
protected:
    Director* _director;
    Size _visibleSize;
    Vec2 _origin;
};
