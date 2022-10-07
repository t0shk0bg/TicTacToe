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

}