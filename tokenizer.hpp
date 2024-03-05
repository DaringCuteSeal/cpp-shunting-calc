#pragma once
#include <string>
#include <vector>

using std::vector, std::string;

namespace tokenizer {
	enum TokenType {
		Error,
		Number,
		Plus,
		Minus,
		Mult,
		Div,
		EOL,
		OpenParanthesis,
		CloseParanthesis,
	};

	struct Token {
		TokenType Type;
		double Value;
		char Symbol;

	};

	Token get_token_from_char(char character);

	vector<Token> tokenize_string(string string);
	
}
