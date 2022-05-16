#include"Player.h"
#include <iomanip>

Player::Player()
{
}

Player::Player(string name, string mode, string time)
{
	_name = name;
	_mode = mode;
	_time = time;
}

void Player::readFile(std::vector<Player>&playerList, std::string file)
{
	ifstream readList(file);
	
	Player gamer;
	readList.ignore();

	while (!readList.eof()) {
		getline(readList, gamer._name, '/');
		getline(readList, gamer._mode, '/');
		getline(readList, gamer._time, '\n');
		playerList.push_back(gamer);
	}
	readList.close();
}

void Player::writeFile()
{
	vector<Player> playerList;
	readFile(playerList, "PlayersList.txt");

	Player gamer;
	gamer._name = _name;
	gamer._time = _time;
	gamer._mode = _mode;
	playerList.push_back(gamer);
	/*for (int i = playerList.size() - 1; i > 0; i++) {
		if (playerList[i].getTime() > playerList[i-1].getTime()) {
			swap(playerList[i], playerList[i-1]);
		}
		else
			break;
	}*/
	
	ofstream writeList("PlayersList.txt");	

	for (int i = 0; i < playerList.size(); i++) {
		//if (playerList[i].getTime.empty()) {
		writeList << endl;
		writeList << playerList[i]._name << "/" << playerList[i]._mode << "/";
		writeList << fixed << setprecision(2) << stoi(playerList[i]._time);
		//continue;
	//}
	/*writeList << endl;
	writeList << playerList[i].getName() << "/" << playerList[i].getMode() << "/";
	writeList << fixed << setprecision(2) << stoi(playerList[i].getTime());
*/
	}
}
