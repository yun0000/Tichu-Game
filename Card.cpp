#include "Card.h"
#include <vector>

int Card::getValue() {
	//string���� ī���� Face�� ���� ī���� ���� int������ �����մϴ�.
	if (isalpha(cardFace.at(0))) {
		switch (cardFace.at(0))
		{
		case'J': return 11;
		case'Q': return 12;
		case'K': return 13;
		case'A': return 14;
		case'S':
			if (cardSuit == "Dragon") return 20;
			else if (cardSuit == "Dog") return 1;
			else if (cardSuit == "Bird") return 1;
			else {
				string phoenixNum;
				cout << "��Ȳ ī�带 � ���� ����Ͻðڽ��ϱ�?(2~A) : ";
				cin >> phoenixNum;
				Card exampleCard;
				exampleCard.setCard("example", phoenixNum);
				return exampleCard.getValue();
				//��Ȳ ī��� ���ϴ� ���ڷ� ����� �� �����Ƿ�,
				//� ���ڷ� ����Ұ����� ����ڿ��Լ� �Է¹޽��ϴ�.
			}
		}
	}
	return stoi(cardFace);
	//�Ϲ����� ������ ���, stoi �Լ��� �̿��ϸ� ���� ���� �� �ֽ��ϴ�.
}

int Card::getScore() {
	//Ƽ��� ����ī�忡�� 5, 10, K ī�常 ������ ������,
	//Ư�� ī�� �� ��� ���׵� ������ �����ϴ�.
	switch (cardFace.at(0))
	{
	case'5': return 5;
	case'1': return 10;
	//'10' ī�带 ���մϴ�. 1�� �����ϴ� ī��� 10�� �����ϱ� �����Դϴ�.
	case'K': return 10;
	case'S':
		if (cardSuit == "Dragon") return 25;
		else if (cardSuit == "Phoenix") return -25;
	default:
		return 0;
	}
}

void Card::print() {
	//������ ī�带 ����ϴ� �޼ҵ��Դϴ�.
	string lowerLine, middleLine, upperLine;

	if (cardFace == "10") {
		lowerLine = "��      " + cardFace + " ��";
		upperLine = "�� " + cardFace + "      ��";
		middleLine = "��    " + cardSuit + "   ��";
	}
	else if (cardFace == "S") {
		lowerLine = "��       " + cardFace + " ��";
		upperLine = "�� " + cardFace + "       ��";
		if (cardSuit == "Dragon")
			middleLine = "��  Dragon ��";
		else if (cardSuit == "Dog")
			middleLine = "��   Dog   ��";
		else if (cardSuit == "Bird")
			middleLine = "��   Bird  ��";
		else
			middleLine = "�� Phoenix ��";
	}
	else {
		lowerLine = "��       " + cardFace + " ��";
		upperLine = "�� " + cardFace + "       ��";
		middleLine = "��    " + cardSuit + "   ��";
	}

	vector<string> lines = { "����������������������"
		,upperLine
		,"��         ��"
		,"��         ��"
		,middleLine
		,"��         ��"
		,"��         ��"
		,lowerLine
		,"����������������������" };

	for (int i = 0; i < lines.size(); i++)
		cout << lines[i] << endl;

}

bool Card::operator<(Card & b) {
	//ī�带 ������� �����ϱ� ���� ���Ǵ� ������ �������̵� �޼ҵ��Դϴ�.

	int indexSuitA = -1, indexSuitB = -1, indexFaceA = -1, indexFaceB = -1;
	string suits[] = { "��","��","��","��" };
	string faces[] = { "2","3" ,"4" ,"5" ,"6" ,"7","8","9","10","J","Q","K","A","S" };

	for (int i = 0; i < 4; i++) {
		if (cardSuit == suits[i])
			indexSuitA = i;
		if (b.getSuit() == suits[i])
			indexSuitB = i;
	}
	for (int i = 0; i < 14; i++) {
		if (cardFace == faces[i])
			indexFaceA = i;
		if (b.getFace() == faces[i])
			indexFaceB = i;
	}
	//for���� �̿��ؼ� suits�� faces�� � �ε����� ��ġ�ϴ����� �˾Ƴ��ϴ�.
	if (indexFaceA == indexFaceB)
		return indexSuitA < indexSuitB;
	else
		return indexFaceA < indexFaceB;
	//face�� ���ٸ� suit������ ���մϴ�.
}
