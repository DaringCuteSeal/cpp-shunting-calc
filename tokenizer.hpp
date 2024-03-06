#pragma once
#include <string>
#include <vector>
#include "result.hpp"

using std::vector, std::string;
using result::Result;

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
		string Symbol;

	};

	Token get_token_from_char(char character);

	Result<vector<Token>> tokenize_string(string string);

	uint recursive_find_next_num_idx(string* input_string, uint start_idx);
	
}
