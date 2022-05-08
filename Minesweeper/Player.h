#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class Player {

	private:
	string name;
	string time;
	string mode;
	
	public:
	string getName();
	string getTime();
	string getMode();

	void readFile(std::vector<Player>&, std::string file);
	void writeFile();
};
