#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class Player {
private:
	string _name;
	string _time;
	string _mode;
public:
	Player();
	Player(string, string, string);

	void readFile(std::vector<Player>&, std::string file);
	void writeFile();
};
