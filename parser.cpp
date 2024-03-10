#include "parser.hpp"
#include <stack>

using tokenizer::TokenType, std::stack;

namespace parser
{
	uint get_precedence(Token token)
	{
		switch (token.Type)
		{
		case TokenType::Minus:
			return 1;
		case TokenType::Plus:
			return 1;
		case TokenType::Mult:
			return 2;
		case TokenType::Div:
			return 2;
		case TokenType::OpenParanthesis:
			return 0;
		case TokenType::CloseParanthesis:
			return 0;
		default:
			return 4;
		}
	};

	TokenCategory get_token_category(Token token)
	{
		switch (token.Type)
		{
		case TokenType::Number:
			return TokenCategory::Number;
		case TokenType::Minus:
			return TokenCategory::Operator;
		case TokenType::Plus:
			return TokenCategory::Operator;
		case TokenType::Mult:
			return TokenCategory::Operator;
		case TokenType::Div:
			return TokenCategory::Operator;
		case TokenType::OpenParanthesis:
			return TokenCategory::OpenParanthesis;
		case TokenType::CloseParanthesis:
			return TokenCategory::CloseParanthesis;
		case TokenType::Error:
			return TokenCategory::Error;
		default:
			return TokenCategory::Unknown;
		}
	};

	result::Result<queue<Token>> postfixify(vector<Token> infix_vec)
	{
		stack<Token> ops_stack;
		queue<Token> result_queue;

		uint i;
		for (i = 0; i < infix_vec.size(); i++)
		{
			auto token = infix_vec.at(i);
			switch (get_token_category(token))
			{
			case TokenCategory::Error:
				return result::Result<queue<Token>>(result::ResultType::Err, "Error token encountered");
				break;
			case TokenCategory::Number:
				result_queue.push(token);
				break;
			case TokenCategory::Operator:
				if (ops_stack.size() == 0)
				{
					ops_stack.push(token);
				}
				else
				{
					if (get_precedence(token) > get_precedence(ops_stack.top()))
					{
						ops_stack.push(token);
					}
					else
					{
						result_queue.push(ops_stack.top());
						ops_stack.pop();
						ops_stack.push(token);
					}
				}
				break;
			case TokenCategory::CloseParanthesis:
				if (ops_stack.size() == 0)
				{
					return result::Result<queue<Token>>(result::ResultType::Err, "Invalid syntax");
				};
				while (ops_stack.size() > 0)
				{
					auto top_item = ops_stack.top();
					if (top_item.Type != TokenType::OpenParanthesis)
					{
						result_queue.push(top_item);
						ops_stack.pop();
					}
					else
					{
						ops_stack.pop();
						break;
					}
				}
				break;
			case TokenCategory::OpenParanthesis:
				ops_stack.push(token);
				break;

			case TokenCategory::Unknown:
				return result::Result<queue<Token>>(result::ResultType::Err, "Unknown token encountered");
			}
		}

		while (ops_stack.size() > 0)
		{
			if (ops_stack.top().Type != TokenType::OpenParanthesis)
			{
				result_queue.push(ops_stack.top());
				ops_stack.pop();
			}
			else
			{
				return result::Result<queue<Token>>(result::ResultType::Err, "Invalid syntax");
			}
		}
		return result::Result<queue<Token>>(result::ResultType::Ok, "Successfully parsed tokens", result_queue);
	};
}
