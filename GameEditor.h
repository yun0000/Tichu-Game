#ifndef GAMEEDITOR_H
#define GAMEEDITOR_H
#include <iostream>
#include <vector>
#include "Card.h"
#include "Player.h"

//게임의 진행을 돕는 게임 에디터 클래스의 선언부입니다.

class GameEditor {
	Card allCards[CARD_NUM];
	int scoreA = 0, scoreB = 0;
	Player allPlayers[4] = { Player(0), Player(1), Player(2), Player(3) };
	//카드와 점수, 네명의 사용자입니다.
public:
	void prepareEditor();
	void shuffleCards();
	void divideCards();
	void changeCards();
	//위 세 메소드는 prepareEditor안에서 실행되는 메소드입니다.
	//카드를 섞고, 나누고 교환하는 메소드입니다.

	void runEditor();
	int startGame(int &firstPlayer);
	bool leftCards();
	bool getContinueRound(int firstPlayer);
	//위 메소드는 runEditor 내에서 실행되는 메소드입니다.
	//라운드를 시작하는 메소드, 남은 카드를 확인하는 메소드, 라운드가 지속되는지 확인하는 메소드입니다.

	void upLinePrompt(int count);
};

#endif
