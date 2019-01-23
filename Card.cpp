#include "Card.h"
#include <vector>

int Card::getValue() {
	//string값인 카드의 Face를 토대로 카드의 값을 int값으로 리턴합니다.
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
				cout << "봉황 카드를 어떤 수로 사용하시겠습니까?(2~A) : ";
				cin >> phoenixNum;
				Card exampleCard;
				exampleCard.setCard("example", phoenixNum);
				return exampleCard.getValue();
				//봉황 카드는 원하는 숫자로 사용할 수 있으므로,
				//어떤 숫자로 사용할건지를 사용자에게서 입력받습니다.
			}
		}
	}
	return stoi(cardFace);
	//일반적인 숫자인 경우, stoi 함수를 이용하면 쉽게 구할 수 있습니다.
}

int Card::getScore() {
	//티츄는 숫자카드에선 5, 10, K 카드만 점수를 가지며,
	//특수 카드 중 용과 봉항도 점수를 갖습니다.
	switch (cardFace.at(0))
	{
	case'5': return 5;
	case'1': return 10;
	//'10' 카드를 뜻합니다. 1로 시작하는 카드는 10만 존재하기 때문입니다.
	case'K': return 10;
	case'S':
		if (cardSuit == "Dragon") return 25;
		else if (cardSuit == "Phoenix") return -25;
	default:
		return 0;
	}
}

void Card::print() {
	//한장의 카드를 출력하는 메소드입니다.
	string lowerLine, middleLine, upperLine;

	if (cardFace == "10") {
		lowerLine = "│      " + cardFace + " │";
		upperLine = "│ " + cardFace + "      │";
		middleLine = "│    " + cardSuit + "   │";
	}
	else if (cardFace == "S") {
		lowerLine = "│       " + cardFace + " │";
		upperLine = "│ " + cardFace + "       │";
		if (cardSuit == "Dragon")
			middleLine = "│  Dragon │";
		else if (cardSuit == "Dog")
			middleLine = "│   Dog   │";
		else if (cardSuit == "Bird")
			middleLine = "│   Bird  │";
		else
			middleLine = "│ Phoenix │";
	}
	else {
		lowerLine = "│       " + cardFace + " │";
		upperLine = "│ " + cardFace + "       │";
		middleLine = "│    " + cardSuit + "   │";
	}

	vector<string> lines = { "┌─────────┐"
		,upperLine
		,"│         │"
		,"│         │"
		,middleLine
		,"│         │"
		,"│         │"
		,lowerLine
		,"└─────────┘" };

	for (int i = 0; i < lines.size(); i++)
		cout << lines[i] << endl;

}

bool Card::operator<(Card & b) {
	//카드를 순서대로 정렬하기 위해 사용되는 연산자 오버라이딩 메소드입니다.

	int indexSuitA = -1, indexSuitB = -1, indexFaceA = -1, indexFaceB = -1;
	string suits[] = { "♠","♣","♥","◆" };
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
	//for문을 이용해서 suits와 faces의 어떤 인덱스에 위치하는지를 알아냅니다.
	if (indexFaceA == indexFaceB)
		return indexSuitA < indexSuitB;
	else
		return indexFaceA < indexFaceB;
	//face가 같다면 suit순으로 비교합니다.
}
