#include <iostream>
#include "Map.h"
#include <string>
#include "DeCodesAndEnCodes.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	string usersText, encoding_result, decoding_result;
	cout << "Please type your text here: " << usersText << endl;
	getline(cin, usersText);
	Summing(usersText, encoding_result, decoding_result);
	return 0;
}
