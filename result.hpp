#pragma once
#include <string>
#include <optional>

using std::string;
using std::optional;

/* Basic error handling system */
namespace result
{
	enum ResultType
	{
		Ok,
		Err
	};



	/* Result of a process */
	template <typename T>
	class Result {
		public:
			Result(ResultType result_type, string err_msg, optional<T> return_val = std::nullopt, int a = 10)
			{
				this->result_type = result_type;
				this->return_val = return_val;
				this->err_msg = err_msg;

			};

			virtual ~Result() {};

			ResultType result_type;
			optional<T> return_val;
			string err_msg = "";
	};

}
