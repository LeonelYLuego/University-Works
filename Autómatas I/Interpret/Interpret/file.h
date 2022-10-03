#pragma once
#ifndef _FILE_H_
#define _FILE_H_
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>

class file {
private:
	std::string path;
	std::ifstream txt;
	std::vector<std::string> lines;
	int count = 0;

public:
	file(std::string path);
	~file();

	int size();
	std::string next_line();
	int last_direction_line() { return count - 1; }
	void go_to(int direction);
};

#endif