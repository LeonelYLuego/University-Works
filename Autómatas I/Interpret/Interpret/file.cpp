#include "file.h"

file::file(std::string path) {
	this->path = path;
	txt.open(path);
	std::string line;
	if (txt.is_open()) {
		while (std::getline(txt, line)) {
			lines.push_back(line);
		}
	}
	else throw std::invalid_argument("File could not be opened");
}

int file::size() {
	return lines.size();
}

std::string file::next_line() {
	if (count >= lines.size()) throw std::out_of_range("Next line out of file size");
	else {
		std::string line = lines[count];
		count++;
		return line;
	}
}

void file::go_to(int direction) {
	if (direction >= 0 && direction < lines.size()) {
		count = direction;
	}
	else throw std::out_of_range("Direction out of range");
}

file::~file() {
	txt.close();
}