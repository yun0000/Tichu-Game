#ifndef PLAYER_H
#define PLAYER_H
#define PLAYER_NUM 4
#include "Card.h"
#include <algorithm>
#include <vector>
using namespace std;
//전체 사용자 수를 4로 define했습니다.

//사용자를 의미하는 player객체입니다.

class Player {
	vector<Card> usableCards;
	int playerNum;
	bool largeTichu = false;
	bool smallTichu = false;
	bool continueGame = true;
	//손에 든 카드, 사용자 번호, 티츄 유무, 진행 여부의 변수입니다.
public:
	Player(int playerNum);
	int leftCards() { return usableCards.size(); }
	//남은 카드가 몇장인지 리턴합니다.

	void setContinueGame(bool continueGame) {	this->continueGame = continueGame;	}
	bool getContinueGame() { return continueGame; }
	//진행 여부의 게터와 세터입니다.

	bool useVariants(int variants, int& size, int& score, int& top);
	bool useCard(int variants, int &size, int& score, int &top);
	//내야하는 족보를 확인하고, 그 족보에 맞는 카드를 내는 메소드입니다.

	bool haveCard(string suit, string face);
	//카드를 소유하고 있는지를 리턴합니다.

	Card getCard(int index) { return this->usableCards[index]; }
	//카드 교환시 사용되는 카드의 게터입니다.

	void sayLargeTichu() { this->largeTichu = true; }
	bool saidLargeTichu() { return this->largeTichu; }
	void sayTichu() { this->smallTichu = true; }
	bool saidTichu() { return this->smallTichu; }
	//티츄 유무의 게터와 세터입니다.

	void pushCard(Card c) { usableCards.push_back(c); }
	void eraseCard(int index) { usableCards.erase(usableCards.begin() + index); }
	//카드를 푸쉬하거나 지우는 메소드입니다.

	void printUsableCard();
	//사용가능한 카드를 출력하는 메소드입니다.

	bool checkSingleVariant(int& score, int& top);
	bool checkDoubleVariant(int size, int& score, int& top);
	bool checkTripleVariant(int& score, int& top);
	bool checkFullHouseVariant(int& score, int& top);
	bool checkStraightVariant(int size, int& score, int& top);
	//족보에 맞는지 확인하는 메소드입니다.
};

#endif