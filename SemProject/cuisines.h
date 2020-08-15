#pragma once
#include <iostream>
#include <vector>
#include <string>
class cuisines {
private:
	std::vector<std::string> cuisines_available;

public:
	cuisines();
	cuisines(const std::vector<std::string>& cuisines);
	void add_cuisine_list(const std::vector<std::string>& food_list);
	std::vector<std::string> get_cuisines();
};
