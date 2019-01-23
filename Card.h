#ifndef CARD_H
#define CARD_H
#define CARD_NUM 56
using namespace std;
#include <iostream>
#include <string>
//��ü ī�� ���� 56���� define�߽��ϴ�.

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
	//������ ���Ϳ� ���ʹ� ����ο��� �����߽��ϴ�.

	void print();
	int getValue();
	int getScore();
	bool operator<(Card & b);
	//��, ���� ���Ϳ� ��� �޼ҵ�, ������ �޼ҵ��Դϴ�.
};

#endif