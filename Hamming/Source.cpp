#include "hamming.h"

#pragma once
using namespace std;

int menu() 
{//basic menu for inpur / output
	vector<int> vectorInput;
	int input = 0;
	Hamming hamming;
	while ( input != -1)
	{
		input = 0;
		vectorInput.clear();
		cout << "Enter binary one bit at a time, start with the LSB. \n Use -1 to exit and 2 to check" << endl;
		while (input == 1 || input == 0)
		{
			cin >> input;
			if (input == 0 || input == 1)
			{
				vectorInput.push_back(input);
			}
		}

		if (input == 2)
		{
			hamming.SetData(vectorInput);//dont use if you want to use the conster for faster testing
			hamming.ErrorDetect();
			cout << endl;
		}
	}
	return 0;
}


int main(void)
{
	menu();
	Hamming hamming;
	hamming.ErrorDetect();
	return 0;
}