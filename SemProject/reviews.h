#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "restaurants.h"

class reviews : public restaurants{
private:
	std::vector<std::pair<std::string, std::chrono::steady_clock>> review;
public:
	void get_user_review(const std::string, std::chrono::steady_clock);
};
