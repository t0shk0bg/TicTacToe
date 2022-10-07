#include "GameLayout.hpp"

void GameLayout::loadBackground(Node* node)
{
    Sprite * backgroundSprite;
    
    if(node->getName() != IN_GAME_SCENE_NAME)
    {
        backgroundSprite = Sprite::create(IMAGE_MENU_BG);
        
        CCASSERT(backgroundSprite, backgroundSprite->getResourceName().c_str());
        
        backgroundSprite->setScale(1.3f);
    }
    else
    {
        backgroundSprite = Sprite::create(IMAGE_IN_GAME_BG);
        
        CCASSERT(backgroundSprite, backgroundSprite->getResourceName().c_str());
        
        backgroundSprite->setScale(1.064f, 0.9f);
    }
    
    backgroundSprite->setPosition(Vec2((_visibleSize.width / 2), (_visibleSize.height / 2) + _origin.y));

    node->addChild(backgroundSprite, 0);
}

void GameLayout::showHeadLabel(const std::string& text, Node* node)
{
    auto headLabel = Label::createWithTTF(text, FONT_PATH(FONT_MARKER_FELT), 28);
    
    CCASSERT(headLabel, headLabel->getSystemFontName().c_str());
    
    headLabel->setPosition(Vec2((_visibleSize.width / 2), ((_visibleSize.height / 20) * 17) + _origin.y));
    headLabel->setColor(Color3B(0, 0, 0));
    
    node->addChild(headLabel, 1);
}

void GameLayout::enterPlayerNameTF(const ui::TextField::ccTextFieldCallback& callback, Node* node)
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
