#pragma once

#include	"Mof.h"

//存在するシーンの列挙
enum tag_SCENENO {
	SCENENO_TITLE,
	SCENENO_GAME,
	SCENENO_GAMECLEAR,
	SCENENO_GAMEOVER,
};

//重力
#define		GRAVITY		0.5f