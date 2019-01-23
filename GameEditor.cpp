#include "GameEditor.h"
#include <string>
#include <ctime>
#include <Windows.h>

bool GameEditor::getContinueRound(int firstPlayer) {
	//이 라운드가 지속되는지를 bool값으로 알려주는 메소드입니다.
	if ((allPlayers[(firstPlayer + 1) % 4].getContinueGame() == false)
		&& (allPlayers[(firstPlayer + 2) % 4].getContinueGame() == false)
		&& (allPlayers[(firstPlayer + 3) % 4].getContinueGame() == false)
		//만약 가장 위에 쌓인 카드를 낸 사람이 이 플레이어라면, 이 라운드는 끝나게 됩니다.
		)
		return false;
	else {
		allPlayers[(firstPlayer + 1) % 4].setContinueGame(true);
		//다른 사람이 놓은 카드가 가장 위에 쌓여있다면, 라운드는 지속됩니다.
	}
	return true;
}

bool GameEditor::leftCards() {
	//게임 전체를 끝내기 위해 카드가 다 사용되었는지를 리턴하는 메소드입니다.
	if (allPlayers[0].leftCards() + allPlayers[1].leftCards()
		+ allPlayers[2].leftCards() + allPlayers[3].leftCards() == 0)
		return false;
	else
		return true;
}

void GameEditor::runEditor() {
	// 게임의 시작과 진행, 끝을 진행하는 런 에디터입니다.
	int startPlayer;
	for (startPlayer = 0; startPlayer < PLAYER_NUM; startPlayer++) {		
		if (allPlayers[startPlayer].haveCard("Bird", "S"))  
			break;
		//가장 먼저, 특수카드 새를 가진 사용자가 시작하게 됩니다.
	}

	while(leftCards())
		//모든 카드가 사용될 때까지 게임이 계속됩니다.
		this->startGame(startPlayer);

	cout << "게임이 종료되었습니다" << endl;

	
	cout << "최종 A팀(플레이어1, 3)의 점수 : " << scoreA << endl;
	cout << "최종 B팀(플레이어2, 4)의 점수 : " << scoreB << endl;
	if (scoreA > scoreB)
		cout << "승리한 A팀 ! 축하합니다." << endl;
	else if (scoreA < scoreB)
		cout << "승리한 B팀 ! 축하합니다." << endl;
	else
		cout << "비겼습니다!" << endl;
	//전체 게임을 마무리하고 승리팀에게 축하 메세지를 전달합니다.
}

void GameEditor::prepareEditor() {	
	this->shuffleCards();	
	this->divideCards();
	this->changeCards();
	//본격적인 게임 시작에 앞서, 카드를 섞고 사용자에게 나눠준 후 서로 교환하는 메소드를 차례로 실행합니다.
	//prepareEditor의 역할입니다.

	this->runEditor();
	//그 후 런 에디터를 실행합니다.
}

int GameEditor::startGame(int &firstPlayer) {

	for (int i = 0; i < PLAYER_NUM; i++)
		allPlayers[i].setContinueGame(true);
	//새로운 족보로 플레이하기 전, 모든 플레이어들의 게임 상태를 true로 설정합니다.

	cout << "현재 A팀의 점수: " << scoreA << "\n현재 B팀의 점수: " << scoreB << endl;
	//현재 점수를 보여줍니다.


	cout << "\n\n플레이어" << (firstPlayer%PLAYER_NUM) + 1 << "가 라운드를 시작합니다" << endl;
	int score = 0;
	int variant, size = 0, top = 0;
	while (true) {
		cout << "<내려는 카드 종류를 선택하세요>" << endl;
		cout << "1.싱글 2.페어 \n3.연속페어 4.트리플 \n5.풀하우스 6.스트레이트 7.개>>";
		cin >> variant;
		//사용자에게 원하는 족보를 입력받습니다.
		if (variant > 0 && variant < 8) {
			if (variant == 3 || variant == 6) {
				cout << "몇 장의 카드를 내시겠습니까?(연속페어:2이상의 짝수, 스트레이트 5~14장) >> ";
				//카드 개수를 고를 수 있는 족보는 그 크기까지 입력받습니다.
				cin >> size;
				//연속 페어의 경우, 페어이기 때문에 늘 짝수 개수여야 합니다.
				//스트레이트의 경우, 최소 5에서 최대 14장을 낼 수 있습니다.
			}
			break;
		}
		else
			cout << "올바른 값을 입력하세요 >>";
		//틀린 값을 입력했다면 재입력할 수 있도록 합니다.
	}

	while (getContinueRound(firstPlayer)){
		//각 사용자의 사용할 수 있는 카드를 출력하고, 카드를 사용하게 합니다.
		cout << "\n\n\n"<<endl;
		if(allPlayers[firstPlayer%4].leftCards() == 0)
			firstPlayer++;
		//만약 카드를 다 사용했다면 다음 사용자로 넘어갑니다.
		
		else {
			if (allPlayers[firstPlayer % 4].getContinueGame())
				allPlayers[firstPlayer++ % 4].useVariants(variant, size, score, top);
			else
				firstPlayer++;
		}
		if ((allPlayers[(firstPlayer + 1) % 4].leftCards() == 0)
			&& (allPlayers[(firstPlayer + 2) % 4].leftCards() == 0)
			&& (allPlayers[(firstPlayer + 3) % 4].leftCards() == 0)
			&& (allPlayers[(firstPlayer) % 4].leftCards() == 0))
			return 0;
		// 모든 사용자가 카드가 없다면 리턴합니다.
	}
	//라운드가 끝나면 점수를 계산하고, 마지막 카드를 낸 사용자의 팀에 점수를 더합니다.
	cout << "점수는 " << score << endl;
	(firstPlayer % 2 == 0) ? (scoreA += score) : (scoreB += score);
	return 0;

}

void GameEditor::changeCards() {
	//카드를 교환하는 메소드입니다. 자신을 제외한 세명과 한장씩 교환합니다.
	vector<Card> player[4];
	cout << "카드를 교환합니다 " << endl;
	for (int i = 0; i < PLAYER_NUM; i++) {
		cout << "플레이어" << i + 1 << "의 차례입니다" << endl;
		for (int j = 0; j < PLAYER_NUM; j++) {
			if (i == j)
				continue;
			allPlayers[i].printUsableCard();
			cout << "플레이어" << j + 1 << "에게 줄 카드를 선택하세요" << endl;
			int changeIndex;
			cin >> changeIndex;
			player[j].push_back(allPlayers[i].getCard(changeIndex));
			//교환할 카드를 사용자 객체 인덱스와 같은 인덱스의 스트링 벡터에 저장합니다.
			allPlayers[i].eraseCard(changeIndex);
			//그 후 카드를 삭제합니다.
		}
	}
	for (int i = 0; i < PLAYER_NUM; i++) {
		for (int j = 0; j < 3; j++)
			allPlayers[i].pushCard(player[i].at(j));
		//교환한 카드를 사용자 객체의 카드 벡터값에 더하고, 전체 카드를 출력합니다.
		cout << "플레이어" << i + 1 << "의 전체 카드는 >>" << endl;
		allPlayers[i].printUsableCard();
	}
}

void GameEditor::divideCards() {
	cout << "\n카드 셔플이 끝났습니다. 티츄 게임을 시작합니다." << endl;
	cout << "플레이어 1부터 차례대로 8장의 카드를 확인합니다." << endl;
	for (int i = 0; i < PLAYER_NUM; i++) {
		cin.get();
		//사용자의 편의를 위해 엔터를 치면 카드를 확인할 수 있도록 했습니다.
		cout << "플레이어 " << i + 1 << "의 카드를 확인합니다." << endl;
		for (int j = 0; j < 8; j++)
			allPlayers[i].pushCard(allCards[i * 14 + j]);
			//먼저 8장만을 우선적으로 나누어주고, 라지티츄 여부를 입력받습니다.
		allPlayers[i].printUsableCard();
		cout << "\n";
	}
	while (true) {
		//라지 티츄를 부르려는 사용자를 입력받고, 출력합니다.
		cout << "라지 티츄를 부르려는 플레이어가 있습니까? (Y/N)";
		char yesNo;
		cin >> yesNo;
		if (yesNo == 'Y') {
			cin.ignore(100, '\n');
			cout << "플레이어 번호를 입력하세요 >>";
			int pnum;
			cin >> pnum;
			if (pnum > 0 && pnum < 5)
				allPlayers[pnum - 1].sayLargeTichu();
			else
				cout << "플레이어 번호가 올바르지 않습니다." << pnum;
		}
		else if (yesNo == 'N')
			break;
		else
			cout << "선택이 올바르지 않습니다.";
	}
	for (int i = 0; i < PLAYER_NUM; i++)
		if (allPlayers[i].saidLargeTichu())
			cout << "플레이어" << i + 1 << "이 라지 티츄를 불렀습니다" << endl;

	cout << "남은 카드를 배분합니다" << endl;
	for (int i = 0; i < PLAYER_NUM; i++) {
		cin.get();
		cout << "player" << i + 1 << "의 전체 카드는 >>"<<endl;
		for (int j = 8; j < 14; j++)
			allPlayers[i].pushCard(allCards[i * 14 + j]);
		//라지 티츄를 선언받은 이후, 나머지 6장의 카드를 나눠줍니다.
		allPlayers[i].printUsableCard();
		cout << "\n";
	}
	while (true) {
		cout << "티츄를 부르려는 플레이어가 있습니까? (Y/N)";
		char yesNo;
		cin >> yesNo;
		if (yesNo == 'Y') {
			cin.ignore(100, '\n');
			cout << "플레이어 번호를 입력하세요 >>";
			int pnum;
			cin >> pnum;
			if (pnum > 0 && pnum < 5)
				allPlayers[pnum - 1].sayTichu();
			else
				cout << "플레이어 번호가 올바르지 않습니다." << pnum;
		}
		else if (yesNo == 'N')
			break;
		else
			cout << "선택이 올바르지 않습니다.";

	}
	//14장의 카드를 모두 나눠준 후, 티츄를 선언받고 출력합니다.
	for (int i = 0; i < PLAYER_NUM; i++)
		if (allPlayers[i].saidTichu())
			cout << "플레이어" << i + 1 << "이 티츄를 불렀습니다" << endl;

}

void GameEditor::shuffleCards() {

	int count = 0;
	string suits[] = { "♠","♣","♥","◆" };
	string faces[] = { "2","3" ,"4" ,"5" ,"6" ,"7","8","9","10","J","Q","K","A","S" };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 13; j++, count++) 
			this->allCards[count].setCard(suits[i], faces[j]);
		this->allCards[count++].setCard("Dragon", faces[13]);
		this->allCards[count++].setCard("Dog", faces[13]);
		this->allCards[count++].setCard("Bird", faces[13]);
		this->allCards[count].setCard("Phoenix", faces[13]);
	//일반적인 트럼프 카드를 Card 객체에 지정하고, 특수 카드 역시 하나씩 지정합니다.

	cout << "카드를 셔플합니다 " << endl;
	vector<string> lines = { "┌─────────┐","│ ▒▒▒▒│","│ ▒▒▒▒│","│ ▒▒▒▒│"
		,"│ ▒▒▒▒│","│ ▒▒▒▒│","└─────────┘" };
	//동적 모습을 위해 추가, 제거가 쉬운 벡터를 이용해서 카드 뒷면을 표시합니다.

	for (int i = 0; i < lines.size(); i++)
		cout << lines[i] << endl;
	for (int i = 0, j = 1; i < 10000; i++) {
		int s1 = rand() % CARD_NUM;
		int s2 = rand() % CARD_NUM;

		Card temp = allCards[s1];
		allCards[s1] = allCards[s2];
		allCards[s2] = temp;
		if (i == j * 10) {
			//특정한 만큼 카드 섞기가 진행되면, 스트링 벡터의 마지막에 다음 카드를 더해 재출력합니다.
			Sleep(500);
			upLinePrompt(7);
			lines.at(0) += "┐";
			for (int i = 1; i < lines.size() - 1; i++)
				lines.at(i) += "│";
			lines.at(lines.size() - 1) += "┘";
			for (int i = 0; i < lines.size(); i++)
				cout << lines[i] << endl;
			j *= 5;
		}
	}
}

void GameEditor::upLinePrompt(int count) {
	//동적으로 섞이는 카드의 모습을 위해 줄을 지우고 한 줄 위로 커서를 올리는 메소드입니다.
	for (int i = 0; i < count; ++i) {
		cout << "\33[2K"; 
		cout << "\x1b[A"; 
	}
}
