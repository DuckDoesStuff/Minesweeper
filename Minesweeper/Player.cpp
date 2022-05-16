#include"Player.h"
#include <iomanip>

string Player::getName()
{
	return name;
}

string Player::getTime()
{
	return time;
}

string Player::getMode()
{
	return mode;
}

void Player::readFile(std::vector<Player>&playerList, std::string file)
{
	ifstream readList(file);
	
	Player gamer;
	readList.ignore();

	while (!readList.eof()) {
		getline(readList, gamer.name, '/');
		getline(readList, gamer.time, '/');
		getline(readList, gamer.mode, '\n');
		playerList.push_back(gamer);
	}
	readList.close();
}

void Player::writeFile()
{
	vector<Player> playerList;
	readFile(playerList, "PlayersList.txt");
	
	Player gamer;
	gamer.time = time;
	gamer.name = name;
	gamer.mode = mode;
	playerList.push_back(gamer);
	for (int i = playerList.size() - 1; i > 0; i++) {
		if (playerList[i].getTime() > playerList[i-1].getTime()) {
			swap(playerList[i], playerList[i-1]);
		}
		else
			break;
	}
	
	ofstream writeList("PlayerList.txt");	

	for (int i = 0; i < playerList.size(); i++) {
		//if (playerList[i].getTime.empty()) {
		writeList << endl;
		writeList << playerList[i].getName() << "/" << playerList[i].getMode() << "/";
		writeList << fixed << setprecision(2) << stoi(playerList[i].getTime());
		//continue;
	//}
	/*writeList << endl;
	writeList << playerList[i].getName() << "/" << playerList[i].getMode() << "/";
	writeList << fixed << setprecision(2) << stoi(playerList[i].getTime());
*/
	}
}
