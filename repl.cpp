#include <iostream>
#include "tokenizer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"
#include "result.hpp"
#include "logger.hpp"

int main()
{
	string input_string;
	vector<Token> tmp_parsed_tokens;
	queue<Token> tmp_postfix;
	double tmp_result;
	

	while (true) {
		input_string = "";
		std::cout << "Input> ";
		std::getline(std::cin, input_string);
		if(!std::cin)
		{
			if(std::cin.eof())
			{
				std::cout << "\n";
				exit(0);
			}
			else
				logger::print_error("other failure\n");
			continue;
		}

		if (input_string.size() == 0)
			continue;

		// Step 1: tokenize string
		auto parsed_tokens_result = tokenizer::tokenize_string(input_string);

		if (!parsed_tokens_result.default_handler())
		{
			logger::print_error(parsed_tokens_result.err_msg + "\n");
			continue;

		};
		tmp_parsed_tokens = parsed_tokens_result.return_val.value();


		// Step 2: convert the tokens (with infix notation) to tokens arranged with the postfix notation
		auto postfix_result = parser::postfixify(tmp_parsed_tokens);
		if (!postfix_result.default_handler())
		{
			logger::print_error(postfix_result.err_msg + "\n");
			continue;

		};

		tmp_postfix = postfix_result.return_val.value();


		// Step 3: evaluate the postfix tokens to get the final result

		auto evaluator_result = evaluator::evaluate_postfix(tmp_postfix);

		if (!evaluator_result.default_handler())
		{
			logger::print_error(evaluator_result.err_msg + "\n");
			continue;

		};

		tmp_result = evaluator_result.return_val.value();


		std::cout << "Result: " << tmp_result << "\n" << "\n";
	}

	return 0;
}
