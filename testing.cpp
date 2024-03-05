#include <iostream>
#include "tokenizer.hpp"
#include "parser.hpp"
#include <string>
#include "result.hpp"

int main()
{
	std::string string = "(3*2)+1-3*9";
	auto tokens = tokenizer::tokenize_string(string);
	auto parsed_tokens_result = parser::postfixify(tokens);
	if (parsed_tokens_result.result_type == result::ResultType::Err)
	{
		std::cout << "failed to parse tokens, error is: " << parsed_tokens_result.err_msg;
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
		std::cout << parsed_tokens.front().Symbol << "";
		parsed_tokens.pop();
	}
}
