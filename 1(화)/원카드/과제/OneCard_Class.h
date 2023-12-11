#pragma once
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

class OneCard_Class
{
public:
	OneCard_Class() {}

	// 게임
	void OneCardGame();              // 게임 준비
	void OneCardPlay();              // 게임 시작
	void Player_OneCardSystem();     // 플레이어 원카드 외치기
	void Target_OneCardSystem();     // 상대방 원카드 외치기

	// 플레이 행동
	void Player();            // 플레이어 행동
	void PlayerNoCard();

	void Target();            // 상대방 행동
	void TargetNoCard();

	// 승리 조건
	void PlayerWin();         // 플레이어 승리
	void PlayerLoser();       // 상대방 승리
};

