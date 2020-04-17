#pragma once
#include <iostream>
#include <vector>
#include <cmath>	//used for pow()
#include <bitset>
#include <numeric>  //useds for acumulate

//using namespace std;

class Hamming
{
public:
	int TestData();//main funtion that will do all caulations
	int SetData(std::vector<int> input);
	std::vector<int> GetData();
	Hamming();//construtor (used for testing untill an input method is devied)

private:
	//make a struct for passing data around? (would it lead to just haveing the data stored in the obj agin? if done in TestData how to get conster data in(for testing only)?)

	std::vector<int> inputData;
	std::vector<int> outputData;

	std::vector<int> isPBit();//returns the bits thart are parity bits
	int VectorOut(std::vector<int> vOut);//outputs the contents of a vector
	std::vector<int> GetPBits(std::vector<int> polairtyBits);
	std::vector<int> CleanData(std::vector<int> input, std::vector<int> polairtyBits);//will creat a vertion of boolData withthe p bits set to -1 for easer caulations later
	std::vector<int> getNewP(std::vector<int> input, std::vector<int> polairtyBits, std::vector<int> cleanData);//used to check what the value of new pbit is
	int IntToBool(int num, int testbit, std::vector<int> cleanData);
	std::vector<int> VectorXOR(std::vector<int>VOne, std::vector<int> VTwo);//used to check if the pbits and newpbits are equal to echother. should be all 0 if they are

	// to be vealey editded
	int CheckXOR(std::vector<int> inputXOR, std::vector<int> polairtyBits, std::vector<int> pbit);
	std::vector<int> SwapBit(std::vector<int> inputXOR);
	bool XORErrorCheck(std::vector<int> inputXOR);
};