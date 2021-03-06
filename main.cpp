//
//  main.cpp
//  StackOnHeap
//
//  Created by Stanislav Martynov on 01.01.2021.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

bool operator<(const std::pair<size_t, std::string>& d1, const std::pair<size_t, std::string>& d2)
{
	return d1.first < d2.first;
}

class CustomHeap
{
private:
	size_t index = 0;
	std::vector<std::pair<size_t, std::string>> heap;
public:
	void insert(std::string x)
	{
		heap.push_back({ index++, x });
		std::push_heap(heap.begin(), heap.end());
	}

	std::string pop()
	{
		if (index) index--;
		std::string pop_element = heap.front().second;
		std::pop_heap(heap.begin(), heap.end());
		heap.pop_back();
		return pop_element;
	}

	std::vector<std::pair<size_t, std::string>> get_array()
	{
		return heap;
	}
};

class CustomStack
{
private:
	size_t tail = 0;
	size_t max_size = 0;
public:
	CustomHeap c_heap;
	CustomStack() = default;
	CustomStack(size_t n)
	{
		max_size = n;
	}

	void push(std::string x)
	{
		if (tail == max_size) {
			throw std::logic_error("overflow");
		}

		c_heap.insert(x);
		tail++;
	}

	std::string pop()
	{
		if (tail == 0) {
			throw std::logic_error("underflow");
		}

		tail--;
		return c_heap.pop();
	}

	std::vector<std::pair<size_t, std::string>> get_array()
	{
		return c_heap.get_array();
	}
};

std::ostream& operator<<(std::ostream& output, CustomStack& c_stack)
{
	auto temp_arr = c_stack.get_array();
	if (temp_arr.empty()) {
		output << "empty";
		return output;
	}

	std::sort_heap(temp_arr.begin(), temp_arr.end());
	output << temp_arr[0].second;
	for (size_t i = 1; i < temp_arr.size(); i++) {
		output << " " << temp_arr[i].second;
	}
	return output;
}

int main(int argc, char* argv[])
{
	CustomStack c_stack;
	std::string line;

	while (std::getline(std::cin, line)) {
		if (line.empty()) continue;
		if (line.substr(0, 9) == "set_size ") {
			line = line.substr(9);
			if (line.find(' ') != std::string::npos) {
				std::cout << "error" << std::endl;
				continue;
			}
			c_stack = CustomStack(atoi(line.c_str()));
			break;
		}
		std::cout << "error" << std::endl;
	}

	while (std::getline(std::cin, line)) {
		try
		{
			if (line.empty()) continue;
			if (line.substr(0, 5) == "push ") {
				line = line.substr(5);
				if (line.find(' ') != std::string::npos) {
					std::cout << "error" << std::endl;
					continue;
				}
				c_stack.push(line);
				continue;
			}
			if (line == "pop") {
				std::cout << c_stack.pop() << std::endl;
				continue;
			}
			if (line == "print") {
				std::cout << c_stack << std::endl;
				continue;
			}
			std::cout << "error" << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}
