#include <iostream>
#include "tokenizer.hpp"
#include "parser.hpp"
#include <string>
#include "result.hpp"

int main()
{

	std::cout << "Input string> ";
	char input_string[100];
	std::cin.getline(input_string, 100);

	auto tokens = tokenizer::tokenize_string(input_string);
	if (tokens.result_type == result::ResultType::Err)
	{
		std::cout << "failed to parse tokens";
	};

	auto result_tokens = tokens.return_val.value();
	auto parsed_tokens_result = parser::postfixify(result_tokens);
	if (parsed_tokens_result.result_type == result::ResultType::Err)
	{
		std::cout << "failed converting to postfix, error is: " << parsed_tokens_result.err_msg;
		exit(1);
	}
	else
	{
		if (!parsed_tokens_result.return_val.has_value())
		{
			std::cout << "somehow result is empty";
			exit(1);
		}
	};

	auto parsed_tokens = parsed_tokens_result.return_val.value();

	uint i;
	auto tokens_list_size = parsed_tokens.size();
	for (i = 0; i < tokens_list_size; i++)
	{
		std::cout << parsed_tokens.front().Symbol << " ";
		parsed_tokens.pop();
	}
	std::cout << "\n";
}
