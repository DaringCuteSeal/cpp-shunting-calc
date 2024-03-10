#include "evaluator.hpp"
#include "tokenizer.hpp"
#include <stack>

using parser::TokenCategory;
using result::ResultType;
using tokenizer::TokenType;

namespace evaluator
{
	Result<double> evaluate_postfix(queue<Token> postfix_tokens)
	{
		std::stack<Token> evaluator_stack;

		Token first_operand;
		Token second_operand;
		double tmp_result;

		while (postfix_tokens.size() > 0)
		{
			Token curr_token = postfix_tokens.front();
			switch (parser::get_token_category(curr_token))
			{

			case TokenCategory::Number:
			{
				evaluator_stack.push(curr_token);
				postfix_tokens.pop();
				break;
			}

			case TokenCategory::Operator:
			{

				if (evaluator_stack.size() < 2)
					return Result<double>(ResultType::Err, "Invalid evaluation stack length (insufficient operands)");

				Token second_operand = evaluator_stack.top();
				evaluator_stack.pop();
				Token first_operand = evaluator_stack.top();
				evaluator_stack.pop();

				switch (curr_token.Type)
				{
				case TokenType::Plus:
					tmp_result = first_operand.Value + second_operand.Value;
					break;
				case TokenType::Minus:
					tmp_result = first_operand.Value - second_operand.Value;
					break;
				case TokenType::Mult:
					tmp_result = first_operand.Value * second_operand.Value;
					break;
				case TokenType::Div:
					tmp_result = first_operand.Value / second_operand.Value;
					break;
				default:
					return Result<double>(ResultType::Err, "Invalid operator found");
				}

				evaluator_stack.push(Token{TokenType::Number, tmp_result, std::to_string(tmp_result)});
				postfix_tokens.pop();
				break;
			}

			default:
				return Result<double>(ResultType::Err, "Invalid evaluation stack length (insufficient operands)");
			}
		};
		return Result<double>(ResultType::Ok, "success", evaluator_stack.top().Value);
	};

};
