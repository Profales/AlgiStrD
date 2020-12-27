#include <iostream>
#include "PrefixList.h"
using namespace std;
int main()
{
    PrefixList* for_test = new PrefixList;
    string to_input;
    cout << "Enter your arithmetic expression: ";
    getline(cin, to_input);
    cout << endl;
    for_test->input_and_perform(to_input);
    for_test->print_to_console();
    cout << endl << "Result of prefix computation: " << for_test->calculate() << endl;
    return 0;
}
