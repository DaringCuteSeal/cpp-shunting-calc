#pragma once
#include <vector>
#include "tokenizer.hpp"
#include "result.hpp"
#include <queue>

using result::Result;
using std::queue;
using std::vector;
using tokenizer::Token;

namespace parser
{

	enum TokenCategory
	{
		Operator,
		Number,
		Error,
		OpenParanthesis,
		CloseParanthesis,
		Unknown
	};

	/* Rearrange infix tokens into a vector of tokens with postfix notation with the shunting-yard algorithm. */
	result::Result<queue<Token>> postfixify(vector<Token> infix_vec);

	uint get_precedence(Token token);
	TokenCategory get_token_category(Token token);

}
