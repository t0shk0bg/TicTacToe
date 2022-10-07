#pragma once

#include "cocos2d.h"

//Background sprite IDs for SpritesContainer
#define MENU_BACKGROUND_SPRITE_ID   0
#define INGAME_BACKGROUND_SPRITE_ID 1

//Scene names
#define ENTRY_POINT_SCENE_NAME      "EntryPointScene"
#define MAIN_MENU_SCENE_NAME        "MainMenuScene"
#define SETTINGS_SCENE_NAME         "SettingsScene"
#define IN_GAME_SCENE_NAME          "InGameScene"
#define END_GAME_SCENE_NAME         "EndGameScene"
#define CHANGE_NICKNAME_SCENE       "ChangeNicknameScene"

//UI messages
#define UI_WELCOME_MSG              "Welcome"
#define UI_WELCOME_MSG_WN           "Welcome "
#define UI_ENTER_NICKNAME           "Enter you nickname here :)"
#define UI_START_GAME               "Start new game"
#define UI_SETTINGS                 "Settings"
#define UI_EXIT                     "Exit"
#define UI_WINNER_IS                "Winner is "
#define UI_DRAW                     "Draw! Good luck next time ;)"
#define UI_BACK_TO_MENU             "Back to menu"
#define UI_CHANGE_NICKNAME          "Change nickname"
#define UI_PLAYER_SIGN              "Player sign: "
#define UI_GO_BACK                  "Go back"
#define UI_MIGHTY_IPHONE            "'s mighty iPhone"

//Fonts
#define FONT_DIR                    "fonts/"
#define FONT_MARKER_FELT            "Marker Felt.ttf"

//Images
#define IMAGE_MENU_BG               "menuBackground.jpeg"
#define IMAGE_IN_GAME_BG            "background.jpeg"

//UserDefault storage keys
#define UD_KEY_NICKNAME             "nickname"
#define UD_KEY_SIGNATURE            "playerSign"

//Game signs
#define GAME_SIGN_X                 "X"
#define GAME_SIGN_O                 "O"
#define DEFAULT_GAME_SIGN           GAME_SIGN_X
#define GAME_SIGN_EXTS              ".png"

//Animations
#define ANIM_WIN_DELAY              2.0f
#define ANIM_WIN_BLINKS             5
#define ANIM_DRAW_DELAY             1.0f
#define ANIM_SCENE_TRANSIT          1.2f
#define ANIM_BOT_TURN_DELAY         0.5f

//Helpers
#define FONT_PATH(FONT_NAME)        FONT_DIR FONT_NAME
