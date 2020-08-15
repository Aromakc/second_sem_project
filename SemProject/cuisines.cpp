#include "cuisines.h"

cuisines::cuisines()
{
}

cuisines::cuisines(const std::vector<std::string>& food_types)
	:cuisines_available(food_types)
{
}

void cuisines::add_cuisine_list(const std::vector<std::string>& food_list)
{
	this->cuisines_available = food_list;
}

std::vector<std::string> cuisines::get_cuisines()
{
	return this->cuisines_available;
}
