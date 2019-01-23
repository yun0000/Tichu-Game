#ifndef GAMEEDITOR_H
#define GAMEEDITOR_H
#include <iostream>
#include <vector>
#include "Card.h"
#include "Player.h"

//������ ������ ���� ���� ������ Ŭ������ ������Դϴ�.

class GameEditor {
	Card allCards[CARD_NUM];
	int scoreA = 0, scoreB = 0;
	Player allPlayers[4] = { Player(0), Player(1), Player(2), Player(3) };
	//ī��� ����, �׸��� ������Դϴ�.
public:
	void prepareEditor();
	void shuffleCards();
	void divideCards();
	void changeCards();
	//�� �� �޼ҵ�� prepareEditor�ȿ��� ����Ǵ� �޼ҵ��Դϴ�.
	//ī�带 ����, ������ ��ȯ�ϴ� �޼ҵ��Դϴ�.

	void runEditor();
	int startGame(int &firstPlayer);
	bool leftCards();
	bool getContinueRound(int firstPlayer);
	//�� �޼ҵ�� runEditor ������ ����Ǵ� �޼ҵ��Դϴ�.
	//���带 �����ϴ� �޼ҵ�, ���� ī�带 Ȯ���ϴ� �޼ҵ�, ���尡 ���ӵǴ��� Ȯ���ϴ� �޼ҵ��Դϴ�.

	void upLinePrompt(int count);
};

#endif
