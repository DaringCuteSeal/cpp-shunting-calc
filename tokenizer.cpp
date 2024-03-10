#include "tokenizer.hpp"
#include <cwctype>
#include <string>

namespace tokenizer
{
	Token get_number_token(string number)
	{
		uint i = 0;
		if (number.at(0) == '-')
			i = 1;
		for (i = i; i < number.length(); i++)
		{
			if (!isdigit(number.at(i)) && number.at(i) != '.')
				return tokenizer::Token{tokenizer::TokenType::Error, 0, " "};
		}
		return Token{tokenizer::TokenType::Number, stod(number), number};
	};

	Token get_op_token(char op_char)
	{

		/* Only used to test token */
		if (isdigit(op_char))
			return Token{tokenizer::TokenType::Number, double(op_char) - '0', std::to_string(op_char)};

		switch (op_char)
		{
		case '+':
			return Token{tokenizer::TokenType::Plus, 0, "+"};
		case '-':
			return Token{tokenizer::TokenType::Minus, 0, "-"};
		case '*':
			return Token{tokenizer::TokenType::Mult, 0, "*"};
		case '/':
			return Token{tokenizer::TokenType::Div, 0, "/"};
		case '(':
			return Token{tokenizer::TokenType::OpenParenthesis, 0, "("};
		case ')':
			return Token{tokenizer::TokenType::CloseParenthesis, 0, ")"};
		case '\n':
			return tokenizer::Token{tokenizer::TokenType::EOL, 0, " "};
		default:
			return Token{tokenizer::TokenType::Error, 0, " "};
		};
	};

	/* Recursive function which returns the last string index of a single number */
	uint recursive_find_next_num_idx(string *input_string, uint start_idx)
	{
		if ((start_idx + 2) > input_string->length())
			return start_idx;
		if (isdigit(input_string->at(start_idx + 1)) || input_string->at(start_idx + 1) == '.')
		{
			return recursive_find_next_num_idx(input_string, start_idx + 1);
		}
		return start_idx;
	};

	Result<vector<Token>> tokenize_string(string input_string)
	{
		std::vector<Token> tokens;
		uint i = 0;
		char curr_char;
		Token curr_token;

		string number_str;
		uint num_end_idx;
		string num_process_string;

		while (i < input_string.length())
		{
			curr_char = input_string.at(i);

			if (isdigit(curr_char))
			{
				num_end_idx = recursive_find_next_num_idx(&input_string, i);
				number_str = input_string.substr(i, num_end_idx - i + 1);
				tokens.push_back(get_number_token(number_str));
				i = num_end_idx + 1;
				continue;
			}
			else if (iswspace(curr_char))
			{
				i++;
				continue;
			}
			else
			{
				curr_token = get_op_token(input_string.at(i));
				if (curr_token.Type == TokenType::Error)
					return Result<vector<Token>>(result::ResultType::Err, "invalid token: " + std::string(1, input_string.at(i)) + " at index " + std::to_string(i));

				/* Special case for an unary negation */
				// FIXME: why so unreadable
				if (curr_token.Type == TokenType::Minus && (tokens.size() == 0 ||
															(((tokens.back().Type != TokenType::Minus) && (tokens.back().Type != TokenType::Number) && (tokens.back().Type != TokenType::OpenParenthesis) && (tokens.back().Type != TokenType::CloseParenthesis)) &&
															 (get_op_token(input_string.at(i + 1)).Type == TokenType::Number))))

				{
					num_end_idx = recursive_find_next_num_idx(&input_string, i);
					number_str = input_string.substr(i, num_end_idx - i + 1);
					tokens.push_back(get_number_token(number_str));
					i = num_end_idx + 1;
					continue;
				}

				i++;
				tokens.push_back(curr_token);
			};
		}
		return Result<vector<Token>>(result::ResultType::Ok, "success", tokens);
	};
}
