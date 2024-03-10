#pragma once

#include "parser.hpp"
#include "result.hpp"

using result::Result;

namespace evaluator {

	/** Evaluate a postfix notation. */
	Result<double> evaluate_postfix(queue<Token> postfix_tokens);


}
