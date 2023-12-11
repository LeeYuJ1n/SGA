// 게임 선택

#pragma once
#include <iostream>
#include <Windows.h>
#include "OneCard_Class.h"

using namespace std;

class Game_Select_Class : public OneCard_Class
{
public:
	Game_Select_Class() {}

	void Game_Select_Print();
};

