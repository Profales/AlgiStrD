#include "PrefixList.h"
#include "Stack.h"
#include <string>
#include <iostream>
#include <stdexcept>

double pi = 3.14159265358979323846;
double e = 2.71828182845904523536;

using namespace std;

Prefix::Prefix()
{
	head = nullptr;
	tail = nullptr;
}

PrefixList::PrefixList()
{
	for_symbols = new Prefix();
	for_operators = new stack();
	for_computation = new stack();
}

void PrefixList::clean_for_operator(int priority, char data, string to_prefix) // node*& prefix_current???
{
	if(to_prefix.length() > 0)
		for_symbols->push_back(-1, to_prefix);
	
	if ((for_operators->top) && (for_operators->top->elem->character.length() > 0))
	{
		if (for_operators->top->elem->priority != -1)
		{
			if ((priority == 0) && (data == ')'))
			{
				for_operators->push(data, priority);
			}
			else
			{
				while ((for_operators->top) && (for_operators->top->elem->priority >= priority))
				{
					node* prefix_current = for_operators->pop();									// put operator from stack
					for_symbols->push_back(prefix_current->priority, prefix_current->character);    // to the prefix list
				}
				for_operators->push(data, priority);
			}
		}
		else
		{
			for_operators->top->elem->character = data;
			for_operators->top->elem->priority = priority;
		}
	}
	else
	{
		for_operators->push(data, priority);
	}

	//for_operators->print_to_console();		// for debugging
}

void PrefixList::clean_for_operator(int priority, string data, string to_prefix) // node*& prefix_current???
{									// data is for stack
	if (to_prefix.length() > 0)
		for_symbols->push_back(-1, to_prefix);

	if ((for_operators->top) && (for_operators->top->elem->character.length() > 0))
	{
		if (for_operators->top->elem->priority != -1)
		{
			if ((priority == 0) && (data == ")"))
			{
				for_operators->push(data, priority);
			}
			else
			{
				while ((for_operators->top) && (for_operators->top->elem->priority >= priority))
				{
					node* prefix_current = for_operators->pop();									// put operator from stack
					for_symbols->push_back(prefix_current->priority, prefix_current->character);    // to the prefix list
				}
				for_operators->push(data, priority);
			}
		}
		else
		{
			for_operators->top->elem->character = data;
			for_operators->top->elem->priority = priority;
		}
	}
	else
	{
		for_operators->push(data, priority);
	}

	//for_operators->print_to_console();		// for debugging
}

int PrefixList::for_numbers(char symbol)
{
	switch (symbol)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '.':
		return 1;
	}
	return -1;
}

int PrefixList::for_actions(char symbol)
{
	switch (symbol)
	{
	case '+':
	case '-':
		return 1;
	case '/':
	case '*':
		return 2;
	case '^':
		return 3;
	case ')':
		return 0;
	}
	return -1;
}

void PrefixList::input_and_perform(string to_input)
{
	if (to_input.length() == 0)
		throw("Invalid input. Wrong symbols.");
	int i = to_input.length() - 1;
	int num_of_operators = 0, num_of_symbols = 0;
	int left_brackets = 0, right_brackets = 0;
	string buf_string;

	while (i >= 0)
	{
		if (to_input[i] == ' ')
		{
			i--;
		}
		else 
		{
			if (for_numbers(to_input[i]) == 1)
			{
				buf_string = to_input[i] + buf_string;
				num_of_symbols++;
				if (i <= 0)
					break;
				i--;
			}
			else 
				if (for_actions(to_input[i]) != -1)
				{
					clean_for_operator(for_actions(to_input[i]), to_input[i], buf_string); // clean stack
					buf_string.clear();
					num_of_symbols++;
					if (to_input[i] == ')')
						right_brackets++;
					if (i <= 0)
						break;
					i--;
				}
			else
				if ((i >= 1) && (to_input[i] == '(') && ((to_input[i - 1] == 's') || (to_input[i - 1] == 'n') ||		// function check
					(to_input[i - 1] == 'g') || (to_input[i - 1] == 't') || (to_input[i - 1] == 'p')))
				{
					if (right_brackets == 0)
						throw ("Invalid input. Expression with unclosed brackets was not expected.");
					node* buf;

					if (buf_string.length() > 0)
					{
						for_symbols->push_back(-1, buf_string);
							buf_string.clear();
					}
					while (for_operators->top->elem->character[0] != ')')
					{
						buf = for_operators->pop();
						for_symbols->push_back(buf->priority, buf->character);
					}
					buf = for_operators->pop();	  // this is for ')'
					i--;
					
					if ((i >= 2) && (to_input[i] == 's') && (to_input[i - 1] == 'o') && (to_input[i - 2] == 'c'))
					{
						clean_for_operator(4, "cos", buf_string);
						buf_string.clear();
						num_of_operators++;
						i -= 3;
					}
					else if ((i >= 2) && (to_input[i - 2] == 's') && (to_input[i - 1] == 'i') && (to_input[i] == 'n'))
					{
						clean_for_operator(4, "sin", buf_string);
						buf_string.clear();
						num_of_operators++;
						i -= 3;
					}
					else if ((i >= 1) && (to_input[i - 1] == 't') && (to_input[i] == 'g'))
					{
						clean_for_operator(4, "tg", buf_string);
						buf_string.clear();
						num_of_operators++;
						i -= 2;
					}
					else if ((i >= 2) && (to_input[i - 2] == 'c') && (to_input[i - 1] == 't') && (to_input[i] == 'g'))
					{
						clean_for_operator(4, "ctg", buf_string);
						buf_string.clear();
						num_of_operators++;
						i -= 3;
					}
					else if ((i >= 2) && (to_input[i - 2] == 'l') && (to_input[i - 1] == 'o') && (to_input[i] == 'g'))
					{
						clean_for_operator(4, "log", buf_string);
						buf_string.clear();
						num_of_operators++;
						i -= 3;
					}
					else if ((i >= 1) && (to_input[i - 1] == 'l') && (to_input[i] == 'n'))
					{
						clean_for_operator(4, "ln", buf_string);
						buf_string.clear();
						num_of_operators++;
						i -= 2;
					}
					else if ((i >= 3) && (to_input[i - 3] == 's') && (to_input[i - 2] == 'q') && (to_input[i - 1] == 'r') && (to_input[i] == 't'))
					{
						clean_for_operator(4, "sqrt", buf_string);
						buf_string.clear();
						num_of_operators++;
						i -= 4;
					}
					else if ((i >= 2) && (to_input[i - 2] == 'a') && (to_input[i - 1] == 'b') && (to_input[i] == 's'))
					{
						clean_for_operator(4, "abs", buf_string);
						buf_string.clear();
						num_of_operators++;
						i -= 3;
					}
					else if ((i >= 2) && (to_input[i - 2] == 'e') && (to_input[i - 1] == 'x') && (to_input[i] == 'p'))
					{	
						clean_for_operator(4, "exp", buf_string);
						buf_string.clear();
						num_of_operators++;
						i -= 3;
					}
					left_brackets++;
				}
				else
					if ((i >= 1) && (to_input[i] == 'i') && (to_input[i - 1] == 'p'))
					{
						if (buf_string.length() > 0)
						{
							for_symbols->push_back(-1, buf_string);
							buf_string.clear();
						}
						buf_string = "pi";
						for_symbols->push_back(-1, buf_string);
						buf_string.clear();
						num_of_symbols += 2;
						i--;
						if (i <= 0)
							break;
						i--;
					}
					else if ((i >= 1) && (to_input[i] == 'e'))
					{
						if (buf_string.length() > 0)
						{
							for_symbols->push_back(-1, buf_string);
							buf_string.clear();
						}
						buf_string = "e";
						for_symbols->push_back(-1, buf_string);
						buf_string.clear();
						num_of_symbols++;
						if (i <= 0)
							break;
						i--;
					}
			else 
				if (to_input[i] == '(')
			{
				node* buf;
				if (right_brackets == 0)
					throw ("Invalid input. Expression with unclosed brackets was not expected.");
				if (for_operators->top->elem->character[0] == ')')
					throw ("Invalid input. Expression like () was not expected.");

				if (buf_string.length() > 0)
				{
					for_symbols->push_back(-1, buf_string);
					buf_string.clear();
				}

				while (for_operators->top->elem->character[0] != ')')
				{
					buf = for_operators->pop();
					for_symbols->push_back(buf->priority, buf->character);
				}
				buf = for_operators->pop();	  // this is for ')'
				left_brackets++;
				if (i <= 0)
					break;
				i--;
			}
		}
	}
	
	if (buf_string.length() > 0)
	{
		if (for_symbols->tail->character.length() == 0)
			for_symbols->tail->character = buf_string;
		else
		{
			for_symbols->push_back(-1, buf_string);
		}
	}

	if (num_of_symbols == num_of_operators)
		throw("Invalid input. Too much operators.");

	if (left_brackets != right_brackets)
		throw("Invalid input. Some brackets aren't closed.");

	sum_lists();
}

void PrefixList::sum_lists()
{
	while (for_operators->top)
	{
		if (for_symbols->head->character.length() == 0)
			{
				for_symbols->head = for_operators->pop();
				for_symbols->head->next = nullptr;
				delete for_symbols->tail;
				for_symbols->tail = for_symbols->head;
			}
		else
			if (for_operators->top->elem->priority >= 0)
			{
				node* buf = for_operators->pop();			// put operator from stack
															// to the prefix list
				for_symbols->push_back(buf->priority, buf->character);
			}
	}
}

void PrefixList::print_to_console()
{
	node* current;
	if (for_symbols->tail)
	{
		cout << "Here is your prefix form: ";
		current = for_symbols->tail;
		while (current != nullptr)
		{
			cout << current->character << ' ';
			current = current->prev;
		}
		cout << endl;
	}
	else
		cout << "Nothing to print." << endl;
}

double PrefixList::calc_operator(string data, double first, double second)
{
	switch (data[0])
	{
	case '+':
		return first + second;
	case '-':
		return first - second;
	case '*':
		return first * second;
	case '/':
		return first / second;
	case '^':
		return pow(first,second);
	}
	return 0;
}

double PrefixList::calc_function(string data, double argument)
{
	if (data == "cos")
		return cos(argument);
	if (data == "sin")
		return sin(argument);
	if (data == "tg")
		return tan(argument);
	if (data == "ctg")
		return 1/tan(argument);
	if (data == "log")
		return log10(argument);
	if (data == "ln")
		return log(argument);
	if (data == "sqrt")
		return sqrt(argument);
	if (data == "abs")
		return abs(argument);
	if (data == "exp")
		return exp(argument);
	return 0;
}

double PrefixList::return_pi_or_e_or_data(string data)
{
	double result;
	if (data == "pi")
	{
		result = pi;
	}
	else
	{
		if (data == "e")
			result = e;
		else result = stod(data);
	}
	return result;
}

double PrefixList::calculate()
{
	node* current_prefix = for_symbols->head;
	node* buf;
	double result = 0, first = 0, second = 0;
	while (current_prefix)
	{
		if (current_prefix->priority == -1)		// is number
		{
			for_computation->push(current_prefix->character, current_prefix->priority);
			current_prefix = current_prefix->next;
		}
		else if (current_prefix->character.length() == 1)	// is + - * / or ^
		{
			first = return_pi_or_e_or_data(for_computation->top->elem->character);
			second = return_pi_or_e_or_data(for_computation->top->next->elem->character);
			result = calc_operator(current_prefix->character, first, second);
			buf = for_computation->pop();
			buf = for_computation->pop();
			for_computation->push(to_string(result), -1);
			current_prefix = current_prefix->next;
		}
		else if (current_prefix->character.length() > 1)	// is function
		{
			first = return_pi_or_e_or_data(for_computation->top->elem->character);
			result = calc_function(current_prefix->character, first);
			buf = for_computation->pop();
			for_computation->push(to_string(result), -1);
			current_prefix = current_prefix->next;
		}
	}
	return result;
}

PrefixList::~PrefixList()
{
	for_operators->~stack();
	for_computation->~stack();
	for_symbols->~Prefix();
}