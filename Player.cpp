#include "Player.h"
#include <algorithm>
#include <string>

Player::Player(int playerNum) { 
	//매개변수로 사용자번호를 입력받는 생성자입니다.
	this->playerNum = playerNum;	
}

bool Player:: haveCard(string suit, string face) { 
	//매개변수로 입력받은 요소의 카드를 갖고있는지 불리언값으로 리턴하는 메소드입니다.
	for (int i = 0; i < usableCards.size(); i++)
		if ((usableCards[i].getFace()==face) && (usableCards[i].getSuit()==suit)) {
			return true;
		}
	return false;
}

void Player::printUsableCard() {
	//카드 모양으로 카드를 프린트하는 메소드입니다.
	sort(usableCards.begin(), usableCards.end());
	//출력 전에, vector<Card>를 벡터 메소드 sort를 이용해서 정렬합니다.
	//이를 위해 비교연산자를 오버라이드 합니다.

	string lowerLine, middleLine, upperLine;
	int i = 0;

	//먼저 첫번째 카드 모형을 만듭니다.
	//한글자가 아니어서 선이 맞지 않는 요소들은 개별적으로 지정합니다.
	if (usableCards.at(i).getFace() == "10") {
		lowerLine = "│      " + usableCards.at(i).getFace() + " │";
		upperLine = "│ " + usableCards.at(i).getFace() + "      │";
		middleLine = "│    " + usableCards.at(i).getSuit() + "   │";
	}
	else if (usableCards.at(i).getFace() == "S") {
		lowerLine = "│       " + usableCards.at(i).getFace() + " │";
		upperLine = "│ " + usableCards.at(i).getFace() + "       │";
		if (usableCards.at(i).getSuit() == "Dragon")
			middleLine = "│  Dragon │";
		else if (usableCards.at(i).getSuit() == "Dog")
			middleLine = "│   Dog   │";
		else if (usableCards.at(i).getSuit() == "Bird")
			middleLine = "│   Bird  │";
		else
			middleLine = "│ Phoenix │";
	}
	else {
		lowerLine = "│       " + usableCards.at(i).getFace() + " │";
		upperLine = "│ " + usableCards.at(i).getFace() + "       │";
		middleLine = "│    " + usableCards.at(i).getSuit() + "   │";
	}

	vector<string> lines = { "┌─────────┐"
		,upperLine
		,"│         │"
		,"│         │"
		,middleLine
		,"│         │"
		,"│         │"
		,lowerLine
		,"└─────────┘"
		,"     " + to_string(i) + "     " };
	//첫번째 카드 모양을 토대로 스트링 벡터를 만들고, 그것을 기반으로
	//나머지 카드도 추가합니다.

	for (i = 1; i < usableCards.size(); i++) {
		if (usableCards.at(i).getFace() == "10") {
			lowerLine = "│      " + usableCards.at(i).getFace() + " │";
			upperLine = "│ " + usableCards.at(i).getFace() + "      │";
			middleLine = "│    " + usableCards.at(i).getSuit() + "   │";
		}
		else if (usableCards.at(i).getFace() == "S") {
			lowerLine = "│       " + usableCards.at(i).getFace() + " │";
			upperLine = "│ " + usableCards.at(i).getFace() + "       │";
			if (usableCards.at(i).getSuit() == "Dragon") 
				middleLine = "│  Dragon │";
			else if (usableCards.at(i).getSuit() == "Dog") 
				middleLine = "│   Dog   │";	
			else if (usableCards.at(i).getSuit() == "Bird") 
				middleLine = "│   Bird  │";
			else 
				middleLine = "│ Phoenix │";
		}
		else {
			lowerLine = "│       " + usableCards.at(i).getFace() + " │";
			upperLine = "│ " + usableCards.at(i).getFace() + "       │";
			middleLine = "│    " + usableCards.at(i).getSuit() + "   │";
		}


		lines.at(0) += "┌─────────┐";
		lines.at(1) += upperLine;
		lines.at(2) += "│         │";
		lines.at(3) += "│         │";
		lines.at(4) += middleLine;
		lines.at(5) += "│         │";
		lines.at(6) += "│         │";
		lines.at(7) += lowerLine;
		lines.at(8) += "└─────────┘";
		lines.at(9) += "     " + to_string(i) + "     ";
	}
	//스트링 벡터에 모든 카드를 추가한 후, 카드를 출력합니다.
	for (int i = 0; i < lines.size(); i++)
		cout << lines[i] << endl;
}

bool Player::useVariants(int variants, int &size, int& score, int& top) {
	// 족보 번호, 카드 개수, 점수, 현재 최상단 카드 크기를 매개변수로 입력받습니다.
	cout << "\n\n\n플레이어" << playerNum + 1 << "의 차례입니다" << endl;
	cout << "현재 탑은 " << top << "입니다\n" << endl;
	int actionSelect;

	while (true) {
		printUsableCard();
		cout << "동작을 선택하세요" << endl;
		cout << "1.카드 내기 2.패스" << endl;
		//현재 카드를 출력하고 동작을 선택받습니다.
		cin >> actionSelect;
		if (actionSelect == 1) {
			if (useCard(variants, size, score, top) == true)
				return true;
			else
				continue;
			//카드 내는 동작일 때, 적절한 카드가 나왔는지 확인하고
			//만약 아니라면 동작 선택부터 다시 받습니다.
		}
		else if (actionSelect == 2) {
			//패스한다면 게임을 계속한다는 속성을 false로 지정하고, false를 리턴합니다.
			continueGame = false;
			return false;
		}
		else {
			cout << "유효하지 않은 수입니다" << endl;			
		}
	}
}

bool Player:: useCard(int variants, int &size, int& score, int &top) {
	//각 족보에 따라 적절한 메소드를 불러옵니다.
	//적절한 카드를 냈는지를 불리언 값으로 리턴합니다.
	switch (variants)
	{
	case 1:
		return checkSingleVariant(score, top);
	case 2:
		return checkDoubleVariant(2, score, top);
		// 연속 페어에서 2장을 사용하는 것으로 같은 메소드를 사용합니다.
	case 3:
		return checkDoubleVariant(size, score, top);
	case 4:
		return checkTripleVariant(score, top);
	case 5:
		return checkFullHouseVariant(score, top);
	case 6:
		return checkStraightVariant(size, score, top);
	default:
		break;
	}
	return 0;
}

bool Player::checkSingleVariant(int& score, int& top){
	//싱글 족보인지 확인하는 메소드입니다.
	int index[14], value;
	cout << "싱글 카드 인덱스를 입력하세요 : ";
	cin >> index[0];
	value = usableCards.at(index[0]).getValue();
	if (value > top) {		
		//만약 현재 최상위 카드보다 높을 값으로 맞는 인덱스가 선택되었다면,
		//카드를 출력하고 점수를 더한 후 카드를 지우고, 최상위 카드값을 변경합니다.
		usableCards.at(index[0]).print();
		cout << "카드를 사용했습니다." << endl;
		score += usableCards.at(index[0]).getScore();
		eraseCard(index[0]);
		top = value;
		return true;
	}
	else {
		cout << "올바르지 않은 인덱스입니다" << endl;
		return false;
	}
}

bool Player::checkDoubleVariant(int size, int& score, int& top) {

	int index[14], value;
	cout << size << "장의 페어 카드 인덱스를 오름차순으로 입력하세요 : ";
	for (int i = 0; i < size; i++)
		cin >> index[i];

	value = usableCards.at(index[size-1]).getValue();
	bool rightPair = true;
	int smallestValue = usableCards.at(index[0]).getValue();
	//맞는 인덱스인지 체크하기 위해 최댓값, 최솟값과 불리언값을 정리합니다.
	//

	for (int i = 0; i < size; i += 2) {
		//인덱스를 두개씩 더하면서, 페어 값을 구분합니다.
		//이전의 값보다 하나 큰 값이어야 연속페어이므로 그것 또한 확인합니다.
		bool samePair = usableCards.at(index[i]).getValue() == usableCards.at(index[i + 1]).getValue();
		bool sameValue = usableCards.at(index[i]).getValue() == smallestValue++;
		if (!samePair || !sameValue)
			//만약 두 값중 하나라도 다르다면, false가 됩니다.
			rightPair = false;
	}

	if (rightPair && value > top) {
		// 연속 페어가 맞고, 값이 현재 탑보다 크다면,
		for (int i = 0; i < size; i++) {
			usableCards.at(index[i]).print();
			score += usableCards.at(index[i]).getScore();
			//해당 카드를 출력하고 점수를 더합니다.
		}
		cout << "카드를 사용했습니다." << endl;
		for (int i = 0; i < size; i++)
			eraseCard(index[i]-i);
		//카드를 지우고, 탑을 지정하고 true를 리턴합니다.
		//eraseCard를 할 때마다 인덱스가 앞으로 하나씩 당겨지기 때문에,
		//해당 인덱스의 순서를 빼줘야지 적절하게 카드를 뺄 수 있습니다.
		top = value;
		return true;
	}
	else {
		cout << "올바르지 않은 인덱스입니다" << endl;
		return false;
	}
}

bool Player::checkTripleVariant(int& score, int& top) {

	int index[14], value, size = 3;
	cout << "트리플 카드 인덱스를 오름차순으로 입력하세요 : ";

	for (int i = 0; i < size; i++)
		cin >> index[i];

	value = usableCards.at(index[size - 1]).getValue();
	bool rightTriple = false;

	if ((usableCards.at(index[0]).getValue() == usableCards.at(index[1]).getValue()) 
		&& (usableCards.at(index[0]).getValue()	== usableCards.at(index[2]).getValue()))
		rightTriple = true;
	//세 카드의 값이 모두 같다면, 맞는 트리플 쌍으로 인정합니다.

	if (rightTriple && value > top) {
		//현재 탑보다 높은 트리플이 맞을 때, true를 리턴합니다.
		for (int i = 0; i < size; i++)
			usableCards.at(index[i]).print();
		cout << "카드를 사용했습니다." << endl;
		for (int i = 0; i < size; i++)
			score += usableCards.at(index[i]).getScore();
		for (int i = 0; i < size; i++)
			eraseCard(index[i] - i);
		//eraseCard를 할 때마다 인덱스가 앞으로 하나씩 당겨지기 때문에,
		//해당 인덱스의 순서를 빼줘야지 적절하게 카드를 뺄 수 있습니다.
		top = value;
		return true;
	}
	else {
		//둘중 하나라도 올바르지 않다면, false를 리턴합니다.
		cout << "올바르지 않은 인덱스입니다" << endl;
		return false;
	}
}

bool Player::checkFullHouseVariant(int& score, int& top) {
	//풀 하우스는 트리플과 페어의 조합이므로, 만들어둔 두 메소드를 사용합니다.
	int dummyTop = 0;
	//풀하우스에선 트리플의 값으로 높은 숫자인지를 확인하므로, 더블을 확인할 때는 탑을 사용할 필요가 없습니다.
	if (checkDoubleVariant(2, score, dummyTop)) {
		printUsableCard();
		if (checkTripleVariant(score, top))
			return true;
		//먼저 페어 값을 사용한 후, 다시 남은 카드를 출력하여 트리플 값을 사용하게 한다.
	}
	else return false;
}

bool Player::checkStraightVariant(int size, int& score, int& top) {

	int index[14], value;
	cout << size << "장의 스트레이트 카드 인덱스를 오름차순으로 입력하세요 : ";

	for (int i = 0; i < size; i++)
		cin >> index[i];
	value = usableCards.at(index[size - 1]).getValue();
	bool rightStraight = true;
	int smallestValue = usableCards.at(index[0]).getValue();
	//스트레이트가 맞는지 확인하기 위한 최솟값과 최댓값, 불리언값을 지정합니다.

	for (int i = 0; i < size; i ++)
		if (!(usableCards.at(index[i]).getValue() == smallestValue++)) 
			rightStraight = false;
	//만약 값이 하나씩 차이나는 스트레이트가 맞지 않다면, 불리언값을 false로 지정합니다.
		
	if (rightStraight && value > top) {
		//스트레이트가 맞고, 탑보다 큰 값이면, 점수를 저장하고 카드를 제거한 후
		//탑을 변경합니다.
		for (int i = 0; i < size; i++) {
			score += usableCards.at(index[i]).getScore();
			eraseCard(index[i] - i);
			usableCards.at(index[i]).print();
		}
		cout << "카드를 사용했습니다." << endl;
		//eraseCard를 할 때마다 인덱스가 앞으로 하나씩 당겨지기 때문에,
		//해당 인덱스의 순서를 빼줘야지 적절하게 카드를 뺄 수 있습니다.
		top = value;
		return true;
	}
	else {
		cout << "올바르지 않은 인덱스입니다" << endl;
		return false;
	}
}