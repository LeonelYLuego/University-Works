#include "instructions.h"

int instructions::get(std::string line) {
	int index = line.find(' ');
	if (index != -1)
		line = line.substr(0, index);
	for (int i = 0; i < line.size(); i++)
		line[i] = toupper(line[i]);
	if (line == "INT") return 0;
	else if (line == "PUSHA") return 1;
	else if (line == "PUSHC") return 2;
	else if (line == "LOAD") return 3;
	else if (line == "STORE") return 4;
	else if (line == "ADD") return 5;
	else if (line == "SUB") return 6;
	else if (line == "MUL") return 7;
	else if (line == "DIV") return 8;
	else if (line == "LABEL") return 9;
	else if (line == "JMPZ") return 10;
	else if (line == "JMPGZ") return 11;
	else if (line == "GOTO") return 12;
	else if (line == "JMPLZ") return 13;
	else if (line == "OUTPUT") return 14;
	else if (line == "INPUT") return 15;
	else if (line == "ECHO") return 16;
	else if (line == "POW") return 17;
	else if (line == "SQRT") return 18;
	else if (line == "JMPNZ") return 19;
	else if (line == "PUSHV") return 20;
	throw std::invalid_argument("Instruction " + line + " not found");
	return -1;
}

std::string instructions::argument(std::string line) {
	int index = line.find(' ');
	if (index != -1) return line.substr(index + 1);
	else throw std::invalid_argument("Argument must be provided");
}