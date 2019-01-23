#include "Player.h"
#include <algorithm>
#include <string>

Player::Player(int playerNum) { 
	//�Ű������� ����ڹ�ȣ�� �Է¹޴� �������Դϴ�.
	this->playerNum = playerNum;	
}

bool Player:: haveCard(string suit, string face) { 
	//�Ű������� �Է¹��� ����� ī�带 �����ִ��� �Ҹ������� �����ϴ� �޼ҵ��Դϴ�.
	for (int i = 0; i < usableCards.size(); i++)
		if ((usableCards[i].getFace()==face) && (usableCards[i].getSuit()==suit)) {
			return true;
		}
	return false;
}

void Player::printUsableCard() {
	//ī�� ������� ī�带 ����Ʈ�ϴ� �޼ҵ��Դϴ�.
	sort(usableCards.begin(), usableCards.end());
	//��� ����, vector<Card>�� ���� �޼ҵ� sort�� �̿��ؼ� �����մϴ�.
	//�̸� ���� �񱳿����ڸ� �������̵� �մϴ�.

	string lowerLine, middleLine, upperLine;
	int i = 0;

	//���� ù��° ī�� ������ ����ϴ�.
	//�ѱ��ڰ� �ƴϾ ���� ���� �ʴ� ��ҵ��� ���������� �����մϴ�.
	if (usableCards.at(i).getFace() == "10") {
		lowerLine = "��      " + usableCards.at(i).getFace() + " ��";
		upperLine = "�� " + usableCards.at(i).getFace() + "      ��";
		middleLine = "��    " + usableCards.at(i).getSuit() + "   ��";
	}
	else if (usableCards.at(i).getFace() == "S") {
		lowerLine = "��       " + usableCards.at(i).getFace() + " ��";
		upperLine = "�� " + usableCards.at(i).getFace() + "       ��";
		if (usableCards.at(i).getSuit() == "Dragon")
			middleLine = "��  Dragon ��";
		else if (usableCards.at(i).getSuit() == "Dog")
			middleLine = "��   Dog   ��";
		else if (usableCards.at(i).getSuit() == "Bird")
			middleLine = "��   Bird  ��";
		else
			middleLine = "�� Phoenix ��";
	}
	else {
		lowerLine = "��       " + usableCards.at(i).getFace() + " ��";
		upperLine = "�� " + usableCards.at(i).getFace() + "       ��";
		middleLine = "��    " + usableCards.at(i).getSuit() + "   ��";
	}

	vector<string> lines = { "����������������������"
		,upperLine
		,"��         ��"
		,"��         ��"
		,middleLine
		,"��         ��"
		,"��         ��"
		,lowerLine
		,"����������������������"
		,"     " + to_string(i) + "     " };
	//ù��° ī�� ����� ���� ��Ʈ�� ���͸� �����, �װ��� �������
	//������ ī�嵵 �߰��մϴ�.

	for (i = 1; i < usableCards.size(); i++) {
		if (usableCards.at(i).getFace() == "10") {
			lowerLine = "��      " + usableCards.at(i).getFace() + " ��";
			upperLine = "�� " + usableCards.at(i).getFace() + "      ��";
			middleLine = "��    " + usableCards.at(i).getSuit() + "   ��";
		}
		else if (usableCards.at(i).getFace() == "S") {
			lowerLine = "��       " + usableCards.at(i).getFace() + " ��";
			upperLine = "�� " + usableCards.at(i).getFace() + "       ��";
			if (usableCards.at(i).getSuit() == "Dragon") 
				middleLine = "��  Dragon ��";
			else if (usableCards.at(i).getSuit() == "Dog") 
				middleLine = "��   Dog   ��";	
			else if (usableCards.at(i).getSuit() == "Bird") 
				middleLine = "��   Bird  ��";
			else 
				middleLine = "�� Phoenix ��";
		}
		else {
			lowerLine = "��       " + usableCards.at(i).getFace() + " ��";
			upperLine = "�� " + usableCards.at(i).getFace() + "       ��";
			middleLine = "��    " + usableCards.at(i).getSuit() + "   ��";
		}


		lines.at(0) += "����������������������";
		lines.at(1) += upperLine;
		lines.at(2) += "��         ��";
		lines.at(3) += "��         ��";
		lines.at(4) += middleLine;
		lines.at(5) += "��         ��";
		lines.at(6) += "��         ��";
		lines.at(7) += lowerLine;
		lines.at(8) += "����������������������";
		lines.at(9) += "     " + to_string(i) + "     ";
	}
	//��Ʈ�� ���Ϳ� ��� ī�带 �߰��� ��, ī�带 ����մϴ�.
	for (int i = 0; i < lines.size(); i++)
		cout << lines[i] << endl;
}

bool Player::useVariants(int variants, int &size, int& score, int& top) {
	// ���� ��ȣ, ī�� ����, ����, ���� �ֻ�� ī�� ũ�⸦ �Ű������� �Է¹޽��ϴ�.
	cout << "\n\n\n�÷��̾�" << playerNum + 1 << "�� �����Դϴ�" << endl;
	cout << "���� ž�� " << top << "�Դϴ�\n" << endl;
	int actionSelect;

	while (true) {
		printUsableCard();
		cout << "������ �����ϼ���" << endl;
		cout << "1.ī�� ���� 2.�н�" << endl;
		//���� ī�带 ����ϰ� ������ ���ù޽��ϴ�.
		cin >> actionSelect;
		if (actionSelect == 1) {
			if (useCard(variants, size, score, top) == true)
				return true;
			else
				continue;
			//ī�� ���� ������ ��, ������ ī�尡 ���Դ��� Ȯ���ϰ�
			//���� �ƴ϶�� ���� ���ú��� �ٽ� �޽��ϴ�.
		}
		else if (actionSelect == 2) {
			//�н��Ѵٸ� ������ ����Ѵٴ� �Ӽ��� false�� �����ϰ�, false�� �����մϴ�.
			continueGame = false;
			return false;
		}
		else {
			cout << "��ȿ���� ���� ���Դϴ�" << endl;			
		}
	}
}

bool Player:: useCard(int variants, int &size, int& score, int &top) {
	//�� ������ ���� ������ �޼ҵ带 �ҷ��ɴϴ�.
	//������ ī�带 �´����� �Ҹ��� ������ �����մϴ�.
	switch (variants)
	{
	case 1:
		return checkSingleVariant(score, top);
	case 2:
		return checkDoubleVariant(2, score, top);
		// ���� ���� 2���� ����ϴ� ������ ���� �޼ҵ带 ����մϴ�.
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
	//�̱� �������� Ȯ���ϴ� �޼ҵ��Դϴ�.
	int index[14], value;
	cout << "�̱� ī�� �ε����� �Է��ϼ��� : ";
	cin >> index[0];
	value = usableCards.at(index[0]).getValue();
	if (value > top) {		
		//���� ���� �ֻ��� ī�庸�� ���� ������ �´� �ε����� ���õǾ��ٸ�,
		//ī�带 ����ϰ� ������ ���� �� ī�带 �����, �ֻ��� ī�尪�� �����մϴ�.
		usableCards.at(index[0]).print();
		cout << "ī�带 ����߽��ϴ�." << endl;
		score += usableCards.at(index[0]).getScore();
		eraseCard(index[0]);
		top = value;
		return true;
	}
	else {
		cout << "�ùٸ��� ���� �ε����Դϴ�" << endl;
		return false;
	}
}

bool Player::checkDoubleVariant(int size, int& score, int& top) {

	int index[14], value;
	cout << size << "���� ��� ī�� �ε����� ������������ �Է��ϼ��� : ";
	for (int i = 0; i < size; i++)
		cin >> index[i];

	value = usableCards.at(index[size-1]).getValue();
	bool rightPair = true;
	int smallestValue = usableCards.at(index[0]).getValue();
	//�´� �ε������� üũ�ϱ� ���� �ִ�, �ּڰ��� �Ҹ����� �����մϴ�.
	//

	for (int i = 0; i < size; i += 2) {
		//�ε����� �ΰ��� ���ϸ鼭, ��� ���� �����մϴ�.
		//������ ������ �ϳ� ū ���̾�� ��������̹Ƿ� �װ� ���� Ȯ���մϴ�.
		bool samePair = usableCards.at(index[i]).getValue() == usableCards.at(index[i + 1]).getValue();
		bool sameValue = usableCards.at(index[i]).getValue() == smallestValue++;
		if (!samePair || !sameValue)
			//���� �� ���� �ϳ��� �ٸ��ٸ�, false�� �˴ϴ�.
			rightPair = false;
	}

	if (rightPair && value > top) {
		// ���� �� �°�, ���� ���� ž���� ũ�ٸ�,
		for (int i = 0; i < size; i++) {
			usableCards.at(index[i]).print();
			score += usableCards.at(index[i]).getScore();
			//�ش� ī�带 ����ϰ� ������ ���մϴ�.
		}
		cout << "ī�带 ����߽��ϴ�." << endl;
		for (int i = 0; i < size; i++)
			eraseCard(index[i]-i);
		//ī�带 �����, ž�� �����ϰ� true�� �����մϴ�.
		//eraseCard�� �� ������ �ε����� ������ �ϳ��� ������� ������,
		//�ش� �ε����� ������ ������� �����ϰ� ī�带 �� �� �ֽ��ϴ�.
		top = value;
		return true;
	}
	else {
		cout << "�ùٸ��� ���� �ε����Դϴ�" << endl;
		return false;
	}
}

bool Player::checkTripleVariant(int& score, int& top) {

	int index[14], value, size = 3;
	cout << "Ʈ���� ī�� �ε����� ������������ �Է��ϼ��� : ";

	for (int i = 0; i < size; i++)
		cin >> index[i];

	value = usableCards.at(index[size - 1]).getValue();
	bool rightTriple = false;

	if ((usableCards.at(index[0]).getValue() == usableCards.at(index[1]).getValue()) 
		&& (usableCards.at(index[0]).getValue()	== usableCards.at(index[2]).getValue()))
		rightTriple = true;
	//�� ī���� ���� ��� ���ٸ�, �´� Ʈ���� ������ �����մϴ�.

	if (rightTriple && value > top) {
		//���� ž���� ���� Ʈ������ ���� ��, true�� �����մϴ�.
		for (int i = 0; i < size; i++)
			usableCards.at(index[i]).print();
		cout << "ī�带 ����߽��ϴ�." << endl;
		for (int i = 0; i < size; i++)
			score += usableCards.at(index[i]).getScore();
		for (int i = 0; i < size; i++)
			eraseCard(index[i] - i);
		//eraseCard�� �� ������ �ε����� ������ �ϳ��� ������� ������,
		//�ش� �ε����� ������ ������� �����ϰ� ī�带 �� �� �ֽ��ϴ�.
		top = value;
		return true;
	}
	else {
		//���� �ϳ��� �ùٸ��� �ʴٸ�, false�� �����մϴ�.
		cout << "�ùٸ��� ���� �ε����Դϴ�" << endl;
		return false;
	}
}

bool Player::checkFullHouseVariant(int& score, int& top) {
	//Ǯ �Ͽ콺�� Ʈ���ð� ����� �����̹Ƿ�, ������ �� �޼ҵ带 ����մϴ�.
	int dummyTop = 0;
	//Ǯ�Ͽ콺���� Ʈ������ ������ ���� ���������� Ȯ���ϹǷ�, ������ Ȯ���� ���� ž�� ����� �ʿ䰡 �����ϴ�.
	if (checkDoubleVariant(2, score, dummyTop)) {
		printUsableCard();
		if (checkTripleVariant(score, top))
			return true;
		//���� ��� ���� ����� ��, �ٽ� ���� ī�带 ����Ͽ� Ʈ���� ���� ����ϰ� �Ѵ�.
	}
	else return false;
}

bool Player::checkStraightVariant(int size, int& score, int& top) {

	int index[14], value;
	cout << size << "���� ��Ʈ����Ʈ ī�� �ε����� ������������ �Է��ϼ��� : ";

	for (int i = 0; i < size; i++)
		cin >> index[i];
	value = usableCards.at(index[size - 1]).getValue();
	bool rightStraight = true;
	int smallestValue = usableCards.at(index[0]).getValue();
	//��Ʈ����Ʈ�� �´��� Ȯ���ϱ� ���� �ּڰ��� �ִ�, �Ҹ����� �����մϴ�.

	for (int i = 0; i < size; i ++)
		if (!(usableCards.at(index[i]).getValue() == smallestValue++)) 
			rightStraight = false;
	//���� ���� �ϳ��� ���̳��� ��Ʈ����Ʈ�� ���� �ʴٸ�, �Ҹ����� false�� �����մϴ�.
		
	if (rightStraight && value > top) {
		//��Ʈ����Ʈ�� �°�, ž���� ū ���̸�, ������ �����ϰ� ī�带 ������ ��
		//ž�� �����մϴ�.
		for (int i = 0; i < size; i++) {
			score += usableCards.at(index[i]).getScore();
			eraseCard(index[i] - i);
			usableCards.at(index[i]).print();
		}
		cout << "ī�带 ����߽��ϴ�." << endl;
		//eraseCard�� �� ������ �ε����� ������ �ϳ��� ������� ������,
		//�ش� �ε����� ������ ������� �����ϰ� ī�带 �� �� �ֽ��ϴ�.
		top = value;
		return true;
	}
	else {
		cout << "�ùٸ��� ���� �ε����Դϴ�" << endl;
		return false;
	}
}