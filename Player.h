#ifndef PLAYER_H
#define PLAYER_H
#define PLAYER_NUM 4
#include "Card.h"
#include <algorithm>
#include <vector>
using namespace std;
//��ü ����� ���� 4�� define�߽��ϴ�.

//����ڸ� �ǹ��ϴ� player��ü�Դϴ�.

class Player {
	vector<Card> usableCards;
	int playerNum;
	bool largeTichu = false;
	bool smallTichu = false;
	bool continueGame = true;
	//�տ� �� ī��, ����� ��ȣ, Ƽ�� ����, ���� ������ �����Դϴ�.
public:
	Player(int playerNum);
	int leftCards() { return usableCards.size(); }
	//���� ī�尡 �������� �����մϴ�.

	void setContinueGame(bool continueGame) {	this->continueGame = continueGame;	}
	bool getContinueGame() { return continueGame; }
	//���� ������ ���Ϳ� �����Դϴ�.

	bool useVariants(int variants, int& size, int& score, int& top);
	bool useCard(int variants, int &size, int& score, int &top);
	//�����ϴ� ������ Ȯ���ϰ�, �� ������ �´� ī�带 ���� �޼ҵ��Դϴ�.

	bool haveCard(string suit, string face);
	//ī�带 �����ϰ� �ִ����� �����մϴ�.

	Card getCard(int index) { return this->usableCards[index]; }
	//ī�� ��ȯ�� ���Ǵ� ī���� �����Դϴ�.

	void sayLargeTichu() { this->largeTichu = true; }
	bool saidLargeTichu() { return this->largeTichu; }
	void sayTichu() { this->smallTichu = true; }
	bool saidTichu() { return this->smallTichu; }
	//Ƽ�� ������ ���Ϳ� �����Դϴ�.

	void pushCard(Card c) { usableCards.push_back(c); }
	void eraseCard(int index) { usableCards.erase(usableCards.begin() + index); }
	//ī�带 Ǫ���ϰų� ����� �޼ҵ��Դϴ�.

	void printUsableCard();
	//��밡���� ī�带 ����ϴ� �޼ҵ��Դϴ�.

	bool checkSingleVariant(int& score, int& top);
	bool checkDoubleVariant(int size, int& score, int& top);
	bool checkTripleVariant(int& score, int& top);
	bool checkFullHouseVariant(int& score, int& top);
	bool checkStraightVariant(int size, int& score, int& top);
	//������ �´��� Ȯ���ϴ� �޼ҵ��Դϴ�.
};

#endif