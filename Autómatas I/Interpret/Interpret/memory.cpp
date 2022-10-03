#include "memory.h"

void memory::new_variable(std::string name) {
	if (direction_of_variable(name) == -1)
		variables.push_back(std::make_pair(name, 0));
	else throw std::invalid_argument("Variable already exits");
}

int memory::direction_of_variable(std::string name) {
	for (int i = 0; i < variables.size(); i++)
		if (variables[i].first == name)
			return i;
	return -1;
}

void memory::set_value_in_direction(int direction, int value) {
	if (direction >= 0 && direction < variables.size()) {
		variables[direction] = std::make_pair(variables[direction].first, value);
	}
	else throw std::out_of_range("Direction out of range");
}

int memory::get_value_in_direction(int direction) {
	if (direction >= 0 && direction < variables.size())
		return variables[direction].second;
	else throw std::out_of_range("Direction out of range");
}

void memory::push(int value, stack_type type) {
	stack.push(std::make_pair(value, type));
}

void memory::new_tag(std::string name, int value) {
	tags.push_back(std::make_pair(name, value));
}

int memory::direction_of_tag(std::string name) {
	for (int i = 0; i < tags.size(); i++) 
		if (tags[i].first == name) 
			return tags[i].second;
	throw std::invalid_argument("Tag not found");
}