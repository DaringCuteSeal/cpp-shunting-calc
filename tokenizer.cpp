#include "tokenizer.hpp"

namespace tokenizer
{
	Token get_token_from_char(char character)
	{
		if (isdigit(character))
		{
			return tokenizer::Token{tokenizer::TokenType::Number, double(character) - '0', character};
		}

		switch (character)
		{
		case '+':
			return tokenizer::Token{tokenizer::TokenType::Plus, 0, '+'};
		case '-':
			return tokenizer::Token{tokenizer::TokenType::Minus, 0, '-'};
		case '*':
			return tokenizer::Token{tokenizer::TokenType::Mult, 0, '*'};
		case '/':
			return tokenizer::Token{tokenizer::TokenType::Div, 0, '/'};
		case '(':
			return tokenizer::Token{tokenizer::TokenType::OpenParanthesis, 0, '('};
		case ')':
			return tokenizer::Token{tokenizer::TokenType::CloseParanthesis, 0, ')'};
		case EOF:
			return tokenizer::Token{tokenizer::TokenType::EOL, 0, ' '};
		default:
			return tokenizer::Token{tokenizer::TokenType::Error, 0, ' '};
		};
	};

	vector<Token> tokenize_string(string string)
	{
		std::vector<Token> tokens;
		unsigned long int i;
		char curr_char;
		for (i = 0; i < string.length(); i++)
		{
			curr_char = string.at(i);
			if (curr_char == ' ')
				continue;

			tokens.push_back(get_token_from_char(curr_char));
		}
		return tokens;
	};
}
