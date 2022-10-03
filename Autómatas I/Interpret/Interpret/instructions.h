#pragma once
#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_
#include <string>
#include <stdexcept>

class instructions {
public:
	static int get(std::string line);
	static std::string argument(std::string line);
};

#endif