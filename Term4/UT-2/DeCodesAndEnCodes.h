#pragma once
#include "Map.h"
#include <stdexcept>
#include <iostream>
using namespace std;
template<class array_t>
int SliceItUp(array_t* freqs, int freq_start, int freq_end)
{
	// we have 2 arrays: freqs[] and symbs[]
	// FOR EXAMPLE: freqs = { 6, 5, 4, 3, 2, 2 }
	// FOR EXAMPLE: symbs = { a, b, c, d, e, f }
	// because our algorythm is done recursively, we should have two indexes: start and end
	double average = 0;
	int i = 0;
	for (i = freq_start; i < freq_end; i++)
		average = average + freqs[i];
	// average = 22 for our example
	average = average / 2;	// now it's 11...
	int sum = 0, median = freq_start;
	i = freq_start;
	while ((i < freq_end) && (sum + freqs[i] < average))
	{
		sum += freqs[i];
		i++;
		median++;
	}
	// i = 0, median = 0;
	// 0 + 6 < 11 - true
	// i = 1; median = 1;
	// 6 + 5 < 11 - false
	// median = 1
	// now we can slice our { 6 [5] 4 3 2 2 } and { a [b] c d e f }
	// and make 4 arrays - {6 5} and {a b}, {4 3 2 2} and {c d e f}
	// and then slice every pair again while arrays_size != 1
	return median;
}
template <class array_t>
void Swap(array_t* arr, int first, int second)
{
	array_t tmp;
	tmp = arr[first];
	arr[first] = arr[second];
	arr[second] = tmp;
}
template<class array_t1, class array_t2>
void SortTwoArrays(array_t1* freqs, array_t2* symbs, int arrays_size)
{	
	// we have 2 arrays: freqs[] and symbs[]
	// freqs size == arrays_size
	// symbs size == arrays_size
	// FOR EXAMPLE: freqs = { 2, 6, 3, 5, 2, 4 }
	// FOR EXAMPLE: symbs = { f, a, d, b, e, c }
	// we are sorting freqs

	for (int i = 0; i < arrays_size; ++i)
	{
		for (int j = i + 1; j < arrays_size; ++j)
		{
			if (freqs[i] < freqs[j])
			{
				Swap(freqs, i, j);
				Swap(symbs, i, j);
			}
		}
	}
	// freqs = { 6, 5, 4, 3, 2, 2 }
	// symbs = { a, b, c, d, e, f }
}
// The main algorithm of our program
void Shannon_Fano_Algo(int* symbs_freqs, char* symbs, string& left_or_right, string& fullCode, int i_start, int i_end, map<char, string>* mapWithCodes, unsigned& memory_after)
{
	// couldn't make it with the char*, i'm sorry
	string tmpCode;
	tmpCode = fullCode + left_or_right;	// e.g. "1001" + '0'
	if (i_start == i_end)	// end of an algorithm (symbs[i_start] == symbs[i_end] == 'a')
	{
		memory_after += tmpCode.length() * symbs_freqs[i_start];
		mapWithCodes->insert(symbs[i_start], tmpCode);	// filling a map array with the pair like ("A", "10011")
		cout << "Symbol: " << symbs[i_start] << "   Frequency: " << symbs_freqs[i_start] << "       Code: " << tmpCode << endl;
		return;
	}
	int array_median = SliceItUp(symbs_freqs, i_start, i_end);	// {6 [5] 4 3 2 2}
	string one = "1";		// i can't just write Shannon_Fano_Algo(..., ..., "1", ...), because he can't transform const char[2] in string type
	string zero = "0";
	Shannon_Fano_Algo(symbs_freqs, symbs, one, tmpCode, i_start, array_median, mapWithCodes, memory_after);	// example is given in the comments in SliceItUp(): {6 5}
	Shannon_Fano_Algo(symbs_freqs, symbs, zero, tmpCode, array_median + 1, i_end, mapWithCodes, memory_after);	// {4 3 2 2}
}

// analog of int main() but as a function (to combine it all together and then test it)
void Summing(string usersText, string encodeResult, string decodeResult)
{
	// we need usersText only to read from console, find memory, make symbols arrays and that's all
	cout << "Your text: " << usersText << endl;
	unsigned memBe4 = usersText.length() * 8, memAfter = 0;		// it's needed to make final statistics
	map<char, int>* charAndFreqs;
	charAndFreqs = new map<char, int>();
	for (size_t i = 0; i < usersText.length(); i++)
	{
		try
		{
			charAndFreqs->insert(usersText[i], 1);	// we are making pairs ('A', 1)
		}
		catch (int ex)
		{
			// for that purpose we need an operator overloading
			if (ex == -1)
				(*charAndFreqs)[usersText[i]]++;		// if 'A' meets 2+ times: ('A', 2), ('A', 3), ... 
		}
	}
	int* symb_freqs = new int[charAndFreqs->give_size()];
	char* symbs = new char[charAndFreqs->give_size()];
	charAndFreqs->MakeAnArray(charAndFreqs->give_root(), symb_freqs, 0);
	charAndFreqs->MakeAnArray(charAndFreqs->give_root(), symbs, 1);
	SortTwoArrays(symb_freqs, symbs, charAndFreqs->give_size());	// to make {6 5 4 3 2 2} and { a b c d e f} by sorting two arrays at the same time

	// Encoding process
	string temp = "";
	map<char, string>* charsAndCodes;
	charsAndCodes = new map<char, string>();
	Shannon_Fano_Algo(symb_freqs, symbs, temp, temp, 0, charAndFreqs->give_size() - 1, charsAndCodes, memAfter);
	string Encoding_Result = "";
	for (int i = 0; i < usersText.length(); i++)
	{
		Encoding_Result += (*charsAndCodes)[usersText[i]] + ' ';	// string will look like "1010 1001 001 11 11 11 ..."
	}
	encodeResult = Encoding_Result;
	cout << "Compression ratio: " << (float)memAfter / (double)memBe4 << endl;
	cout << "Memory occupied before encoding (in bits): " << memBe4 << endl;
	cout << "Memory occupied after encoding (in bits): " << memAfter << endl;
	cout << "Encoding resut: " << encodeResult << endl;

	// Decoding process
	map<string, char>* codesAndChars;
	codesAndChars = new map<string, char>();
	for (int i = 0; i < charAndFreqs->give_size(); ++i)
	{
		codesAndChars->insert((*charsAndCodes)[symbs[i]], symbs[i]);
	}
	string Decoding_Result = "", Code;
	for (int i = 0; i < Encoding_Result.length(); i++)
	{
		Code = "";
		while (Encoding_Result[i] != ' ')
		{
			Code += Encoding_Result[i++];
		}
		Decoding_Result += (*codesAndChars)[Code];
	}
	decodeResult = Decoding_Result;
	cout << "Decoding resut: " << decodeResult << endl;
	delete[] symb_freqs;
	delete[] symbs;
}
