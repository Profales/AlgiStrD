#pragma once
#include "Node.h"
#include "Stack.h"
#include "Prefix.h"
class PrefixList
{
private:
	stack* for_operators;
	Prefix* for_symbols;
	stack* for_computation;
public:
	PrefixList();
	~PrefixList();
	int for_numbers(char symbol);
	int for_actions(char symbol);
	void clean_for_operator(int priority, string data, string to_prefix);
	void clean_for_operator(int priority, char data, string to_prefix);
	void input_and_perform(string to_input);
	void print_to_console();
	double calculate();
	double calc_operator(string data, double first, double second);
	double return_pi_or_e_or_data(string data);
	double calc_function(string data, double argument);
	void sum_lists();
};