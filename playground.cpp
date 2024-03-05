#include <iostream>
#include <string>
#include <stack>

using std::cout, std::string;

const string get_hello_string()
{
	return "HELLO";
}

struct Person
{
	string name;
	int age;
};

int main()
{
	std::stack<Person> stack_of_int;
	std::cout << "Ya siapa tau gitu";
	std::cout << stack_of_int.size();
}
