#include <iostream>
#include "tokenizer.hpp"
#include "result.hpp"
#include <bits/stdc++.h>
#include <vector>
#include <string>

using std::string, std::vector;

int main()
{
	std::cout << "Input string> ";
	char input_string[100];
	std::cin.getline(input_string, 100);

	auto result = tokenizer::tokenize_string(input_string);

	if (!result.return_val.has_value())
	{
		std::cout << "Error tokenizing string: " << result.err_msg << '\n';
		exit(1);
	};
	auto result_vec = result.return_val.value();

	for (auto token : result_vec)
	{
		std::cout << token.Symbol << '\n';
	};
}
