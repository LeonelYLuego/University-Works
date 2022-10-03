#pragma once
#ifndef _MEMORY_H_
#define _MEMORY_H_
#include <stack>
#include <vector>
#include <utility>
#include <string>
#include <stdexcept>

enum stack_type { direction, value };

class memory {
private:
	std::stack<std::pair<int, stack_type>> stack;
	std::vector<std::pair<std::string, int>> variables;
	std::vector < std::pair<std::string, int>> tags;
public:
	void new_variable(std::string name);
	int direction_of_variable(std::string name);
	void set_value_in_direction(int direction, int value);
	int get_value_in_direction(int direction);

	void push(int value, stack_type type);
	std::pair<int, stack_type> pop() {
		if (!stack.empty()) {
			std::pair<int, stack_type> value;
			value = stack.top();
			stack.pop();
			return value;
		}
		else throw std::out_of_range("Stack empty");
	};

	void new_tag(std::string name, int value);
	int direction_of_tag(std::string name);
};

#endif