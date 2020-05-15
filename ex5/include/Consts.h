#pragma once

#include "string"
using std::string;

//Texture Consts:
const string DIGGER_PNG = "digger.png";
const string MONSTER_PNG = "monster.png";
const string SMART_MON_PNG = "SmartMonster.png";
const string STONE_PNG = "stone.png";
const string DIAMOND_PNG = "diamond.png";
const string GIFT_PNG = "Gift.png";
const string WALL_PNG = "wall.png";
const string HEART_PNG = "heart.png";
const string TIMESUP_PNG = "timesup.png";
const string NOSTONE_PNG = "nostone.png";
const string YOUWIN_PNG = "youwin.png";
const string YOULOSE_PNG = "youlose.png";
const string BUSTED_PNG = "busted.png";
const string B_STONE_PNG = "bonusstone.png";
const string B_TIME_PNG = "bonustime.png";
const string B_SCORE_PNG = "bonusscore.png";

//Font Consts:
const string FONT = "arial.ttf";

//Sounds Consts:
const string MUSIC_START = "soundStart.ogg";
const string MUSIC_GAME = "soundGame.ogg";
const string MUSIC_MESSAGE = "SMS.ogg";
const string MUSIC_TEXT = "textmessage.ogg";

//Menu Consts:
const int BUTTON_W = 400;			//Button width
const int BUTTON_L = 100;			//Button length
const int BUTTON_POS_X = 760;		//Button position x
const int BUTTON_POS_Y = 600;		//Button position y
const int DISTANCE_BUTTONS = 150;	//Distance between buttons
const int BUTTON_MOVE_EFFECT = 10;  //Button moving effect

//Board Print Consts:
const int X_BOARD = 32;		//a start point board
const int Y_BOARD = 60;

const int W_SCREEN = 1855;	//size of board
const int L_SCREEN = 933;

const int P_X_MESSAGE = 700;	//a start point messages
const int P_Y_MESSAGE = 350;

const int SPACE = 16;

const int NOTIME = 9999;

//Manager Consts:
const int LIFE_START = 3;	//Define life

const float PAUSE = 1000;	//Pause for message
const float PAUSE_GIFT = 35;	//Pause for message's gift

const int SPEED = 400;		//Digger Speed Move
const int SPEED_MONSTER = 140;	//Monsters Speed Move



enum Objects
{
	O_Digger, O_Monster, O_Smart_Mon, O_Stone, O_Diamond, O_Gift, O_Wall, T_Heart, M_Timesup, M_Nostone,
	M_Youwin, M_Youlose, M_Busted, M_Bstone, M_Bscore, M_Btime
};

enum Sounds
{
	S_Start, S_Game, S_Message, S_Text
};