#include "logger.hpp"

namespace logger{

	void print_error(string message)
	{
		std::cout << "\e[31m" << "[ERROR] " << "\e[0m" << message << "\n";
	}
}
