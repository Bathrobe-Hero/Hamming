#pragma once
//this libary will take in some binrary data, check for partity error, then retrun with any fixes or null if it cant be fixed
#include <iostream>
#include <vector>
#include <cmath>	//used for pow()
#include <bitset>
#include<algorithm>	//used for find()
#pragma once

using namespace std;

class Data { //used to trancef data in and out of the hamming section 
	//TODO how would the data be gotten
public:
	vector<bool> boolData;//used to hold the data stream (not using bitsream as that needs to know how meany bites befor it can create)
							//frount values is LSB
private:
	int error = 0; //for return: 0=no error found, 1=error found and fixed, -1=error fanc and cant be fixed
};

class Hamming :private Data
{
public:
	int ErrorDetect();
	Hamming();//construtor (used for testing untill an input method is devied)

private:
	Data* data = new Data();//used to return the data (would the user have to make there own data object?)
	int getNewP(int pBit);//used to check what the value of new pbit is
	vector <int>polairtyBits;//what number bits are the parity bits
};