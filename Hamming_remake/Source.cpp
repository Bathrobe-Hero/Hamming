#include "hamming.h"

#pragma once
using namespace std;

//this vertion of hamming dose not store all vales in the object. reduinge its size when at rest
//only the inputdata and output data will be stored
//the rest should be cleaned up when the testing is done
//allso have inprovments to how it calutates the xor error a second time if there was one (no flag value/ split up methdon into two smaller ones).

int VectorOut(std::vector<int> vOut)
{
	for (int i = 0; i < vOut.size(); i++)
	{
		std::cout << vOut[i] << "|";
	}
	std::cout << std::endl;
	return 0;
}

int menu()
{//basic menu for inpur / output
	vector<int> vectorInput;
	int input = 0;
	Hamming hamming;
	while (input != -1)
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
			int errorOut = hamming.TestData();
			cout << "---testing done---" << endl;
			switch (errorOut)
			{
			case 0:
				cout << "No errors found, data is good" << endl;
				cout << "data recved:";
				VectorOut(hamming.GetData());
				break;

			case 1:
				cout << "Error found and fixed" << endl;
				cout << "data recved:";
				VectorOut(hamming.GetData());
				break;

			case -1:
				cout << "more than one error found, data cannot be fixed" << endl;
				break;

			default:
				cout << "\n----Error--- \n Unkown error code:" << errorOut << endl;
				break;
			}

			cout << endl;
		}
	}
	return 0;
}

int main(void)
{
	menu();
	Hamming hamming;
	hamming.TestData();
	return 0;
}