#include <iostream>
#include <cmath>
#include "memory.h"
#include "file.h"
#include "instructions.h"

int main() {
    file txt("code.txt");
    memory data;

    int operation;
    std::string argument;
    int direction;
    int value;
    std::pair<int, stack_type> element1;
    std::pair<int, stack_type> element2;

    for (int i = 0; i < txt.size(); i++) {
        std::string line = txt.next_line();

        operation = instructions::get(line);

        if (operation == 9) { //LABEL
            std::string argument = instructions::argument(line);
            value = txt.last_direction_line();
            data.new_tag(argument, value);
        }
    }
    txt.go_to(0);

    do {
        std::string line = txt.next_line();

        std::cout << line << std::endl;

        operation = instructions::get(line);

        switch (operation) {
        case 0: //INT
            argument = instructions::argument(line);
            data.new_variable(argument);
            break;
        case 1: //PUSHA
            argument = instructions::argument(line);
            direction = data.direction_of_variable(argument);
            if (direction == -1) throw std::invalid_argument("Variable not found");
            else data.push(direction, stack_type::direction);
            break;
        case 2: //PUSHC
            argument = instructions::argument(line);
            value = std::stoi(argument);
            data.push(value, stack_type::value);
            break;
        case 3: //LOAD
            element1 = data.pop();
            value = data.get_value_in_direction(element1.first);
            data.push(value, stack_type::value);
            break;
        case 4: //STORE
            element1 = data.pop();
            element2 = data.pop();
            data.set_value_in_direction(element2.first, element1.first);
            break;
        case 5: //ADD
            element1 = data.pop();
            element2 = data.pop();
            data.push(element1.first + element2.first, stack_type::value);
            break;
        case 6: //SUB
            element1 = data.pop();
            element2 = data.pop();
            data.push(element1.first - element2.first, stack_type::value);
            break;
        case 7: //MUL
            element1 = data.pop();
            element2 = data.pop();
            data.push(element1.first * element2.first, stack_type::value);
            break;
        case 8: //DIV
            element1 = data.pop();
            element2 = data.pop();
            data.push(element1.first / element2.first, stack_type::value);
            break;
        case 10: //JMPZ
            argument = instructions::argument(line);
            direction = data.direction_of_tag(argument);
            value = data.pop().first;
            if (value == 0) txt.go_to(direction);
            break;
        case 11: //JMPGZ
            argument = instructions::argument(line);
            direction = data.direction_of_tag(argument);
            value = data.pop().first;
            if (value > 0) txt.go_to(direction);
            break;
        case 12: //GOTO
            argument = instructions::argument(line);
            direction = data.direction_of_tag(argument);
            txt.go_to(direction);
            break;
        case 13: //JPMLZ
            argument = instructions::argument(line);
            direction = data.direction_of_tag(argument);
            value = data.pop().first;
            if (value < 0) txt.go_to(direction);
            break;
        case 14: //OUTPUT
            argument = instructions::argument(line);
            direction = data.direction_of_variable(argument);
            value = data.get_value_in_direction(direction);
            std::cout << ">> " << value << std::endl;
            break;
        case 15: //INPUT
            argument = instructions::argument(line);
            direction = data.direction_of_variable(argument);
            std::cout << "<< ";
            std::cin >> value;
            data.set_value_in_direction(direction, value);
            break;
        case 16: //ECHO
            argument = instructions::argument(line);
            std::cout << ">> " << argument << std::endl;
            break;
        case 17: //POW
            element1 = data.pop();
            element2 = data.pop();
            data.push(std::pow(element1.first, element2.first), stack_type::value);
            break;
        case 18: //SQRT
            element1 = data.pop();
            data.push(std::sqrt(element1.first), stack_type::value);
            break;
        case 19: //JMPNZ
            argument = instructions::argument(line);
            direction = data.direction_of_tag(argument);
            value = data.pop().first;
            if (value != 0) txt.go_to(direction);
            break;
        case 20: //PUSHV
            argument = instructions::argument(line);
            direction = data.direction_of_variable(argument);
            value = data.get_value_in_direction(direction);
            data.push(value, stack_type::value);
            break;
        }
    } while (txt.last_direction_line() < txt.size() - 1);
    system("PAUSE");
}
