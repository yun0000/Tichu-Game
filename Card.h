#ifndef CARD_H
#define CARD_H
#define CARD_NUM 56
using namespace std;
#include <iostream>
#include <string>
//전체 카드 수를 56으로 define했습니다.

class Card {
	string cardFace;
	string cardSuit;
public:
	string getFace() { return cardFace; }
	string getSuit() { return cardSuit; }
	void setCard(string cardSuit, string cardFace ) {
		this->cardSuit = cardSuit;
		this->cardFace = cardFace;
	}
	//간단한 게터와 세터는 선언부에서 정리했습니다.

	void print();
	int getValue();
	int getScore();
	bool operator<(Card & b);
	//값, 점수 게터와 출력 메소드, 연산자 메소드입니다.
};

#endif