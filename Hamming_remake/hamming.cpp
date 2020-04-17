#include "hamming.h"

//----Hamming----
Hamming::Hamming() {//construtor
	//test inputs. is the same as in report
	inputData.push_back(0);//0 | lsb	P
	inputData.push_back(1);//1			P
	inputData.push_back(1);//1
	inputData.push_back(1);//1			P
	inputData.push_back(0);//0
	inputData.push_back(1);//0 | chnaged bit
	inputData.push_back(0);//1 | chnaged bit 2
	inputData.push_back(0);//0			P
	inputData.push_back(1);//1
	inputData.push_back(0);//0
	inputData.push_back(1);//1 | msb
}

int Hamming::SetData(std::vector<int> input)//send a vectors to be used as the data
{
	inputData = input;
	return 0;
}

std::vector<int> Hamming::GetData()
{
	return outputData;
}

int Hamming::VectorOut(std::vector<int> vOut)
{
	for (int i = 0; i < vOut.size(); i++)
	{
		std::cout << vOut[i] << "|";
	}
	std::cout << std::endl;
	return 0;
}

int Hamming::TestData()//main
{
	std::cout << "Testing data:";
	VectorOut(inputData);

	std::vector <int>polairtyBits = isPBit();
	std::vector<int> pbit = GetPBits(polairtyBits);//gets the pbits inclued
	std::vector<int> cleanData = CleanData(inputData, polairtyBits);//gets a vertion of the inputdata with all non parity bits set to -1
	std::vector <int>newPBits = getNewP(inputData, polairtyBits, cleanData);//generates new pbits

	std::vector<int>XOR = VectorXOR(newPBits, pbit);//gets the XOR vaules for testing with
	std::cout << "Vextor XOR:";
	VectorOut(XOR);
	std::cout << std::endl;

	int outputErrorValue = CheckXOR(XOR, polairtyBits, pbit);//works out of there are any errors
	return outputErrorValue;
}

//-------------------------------------------------------------------
std::vector<int> Hamming::isPBit()//works out which bits are parity bits
{
	int isP = 0;
	std::vector <int>polairtyBits;
	for (int count = 0; isP <= inputData.size(); count++)//generates witch bit are polaity. can change with the number of inclued bits
	{
		isP = (pow(2, count));//plarity bits are always this caulation

		if (isP <= inputData.size())
		{
			polairtyBits.push_back(isP);
			std::cout << isP;
		}
		else
		{
			isP = inputData.size() + 2;//exit condtion
		}
	}
	std::cout << std::endl;
	return polairtyBits;//retunr bit numbers that are parity bits
}

std::vector<int> Hamming::GetPBits(std::vector<int> polairtyBits)
{
	//----gets values of p bits----
	int pBCount = 0;//used to count current pbit
	std::vector<int> pbit;
	for (auto const& value : polairtyBits)//loops throu pbit and gets the value of polairty bits
	{
		std::cout << "P bit:" << value << " values is:" << inputData[value - 1] << std::endl;
		if (inputData[value - 1] == true)
		{
			pbit.push_back(1);
		}
		else
		{
			pbit.push_back(0);
		}
		pBCount++;
	}
	//----print pbit values
	std::cout << "pbit values:";
	VectorOut(pbit);
	return pbit;
}

std::vector<int> Hamming::CleanData(std::vector<int> input, std::vector<int> polairtyBits)
{
	int isPCount = 0;//used to count thoru the know numbers if poliaty bits. lets other parts ignor non partiy bits
	std::vector<int> CleanData;
	//----sets all pbits to = -1----
	for (int postion = 1; postion <= input.size(); postion++)//loop throu all of the data
	{
		if (postion != polairtyBits[isPCount])//will only let non Pbits through
		{
			CleanData.push_back(input[postion - 1]);
			std::cout << "postion:" << postion;
			std::cout << " | data in postion:" << input[postion - 1];
			std::cout << " | isPCount:" << isPCount;
			std::cout << " | Current Pbit checking for:" << input[isPCount] << std::endl;
		}
		else
		{
			CleanData.push_back(-1);//all -1 are were the parity bit will go. might not need this?
			if (polairtyBits.size() - 1 != isPCount) {
				isPCount++;
			}
		}
	}
	std::cout << "cleanData:";
	VectorOut(CleanData);
	return CleanData;
}

//----------------------------------------------------------------
std::vector<int> Hamming::getNewP(std::vector<int> input, std::vector<int> polairtyBits, std::vector<int> cleanData)//recaulates the new plairty bits
{
	//----works out the new pbits----

	int even;//used to see if the pbit toal trues is even
	std::vector<int>output;
	for (int testbit = 0; testbit < polairtyBits.size(); testbit++)//loops throuh the bits to check for
	{
		even = 0;
		std::cout << "Testbit:" << testbit << std::endl;

		for (int count = 0; count <= input.size(); count++)
		{
			std::cout << "num:" << count << " | ";
			even += IntToBool(count, testbit, cleanData);
		}
		//once all nums have been tested with that bit checks if the total is even.
		//if so will that newPbit to 0
		//if its odd sets newpbit to 1

		if (even % 2 == 0)//devide by 2 and check remander
		{//if even
			output.push_back(0);
		}
		else
		{//if odd
			output.push_back(1);
		}
	}
	std::cout << "newPbits:";
	VectorOut(output);
	return output;
}

int Hamming::IntToBool(int num, int testbit, std::vector<int> cleanData)
{
	std::bitset<16> bset(num);//max size 65,536. sets num to binray equivalent
	int even = 0;//hold number of trues for chekcing if evan
	std::cout << bset.to_string() << std::endl;
	if (bset.test(testbit) == true)
	{
		//outputs wich bits are effected by parity bits
		std::cout << "num:" << num << " | testbit:" << testbit << " | " << bset.test(testbit) << std::endl;

		//num-1 is the postion in the vector that this is equvalent to
		if (cleanData[num - 1] == 1)//only trues will add to the evan
		{
			return 1;
		}
	}
	return 0;
}

//------------------------------------------------------------------------------------
std::vector<int> Hamming::VectorXOR(std::vector<int> VOne, std::vector<int> VTwo)
{
	std::vector<int> VOut;
	if (VOne.size() == VTwo.size())
	{
		for (int i = 0; i < VOne.size(); i++)
		{
			VOut.push_back(VOne[i] ^ VTwo[i]);
		}
	}
	else
	{
		std::cout << "vectors cannot XOR due to diffrent sizes" << std::endl;
	}

	return VOut;
}

//------------------------------------------------------
int Hamming::CheckXOR(std::vector<int> inputXOR, std::vector<int> polairtyBits, std::vector<int> pbit)//this funtion will check the output for vectorXOR to see if there are any errors and if so will atempte to fix them
{
	bool error = XORErrorCheck(inputXOR);//holds a flag for if thre is an error

	int returnErrorValue;
	if (error == true)//atmeps fix
	{
		std::cout << "Error dected" << std::endl;

		std::vector<int> swapedBit = SwapBit(inputXOR);//swaps the bit
		std::cout << "Swaped bit:";
		VectorOut(swapedBit);

		std::vector<int> errorCleanData = CleanData(swapedBit, polairtyBits);//cleasn the new spawed bit

		std::vector<int> XorPBit = getNewP(swapedBit, polairtyBits, errorCleanData);
		std::cout << "fixed xor bits";
		VectorOut(XorPBit);

		XorPBit = VectorXOR(XorPBit, pbit);
		std::cout << "fixed XOR value:";
		VectorOut(XorPBit);

		if (XORErrorCheck(XorPBit))
		{//still has error
			std::cout << "two or more error detected. Cannot not fix" << std::endl;
			outputData.clear();
			outputData.push_back(-1);
			returnErrorValue = -1;
		}
		else
		{//no longer has error
			std::cout << "Error was fixed" << std::endl;
			outputData = swapedBit;
			returnErrorValue = 1;
		}
	}
	else
	{
		std::cout << "no errors detected" << std::endl;
		outputData = inputData;
		returnErrorValue = 0;
	}

	return returnErrorValue;
}

bool Hamming::XORErrorCheck(std::vector<int> inputXOR)
{
	bool error = false;//holds a flag for if thre is an error
	for (auto const& value : inputXOR)//loops throu XOR to check if there are any true vales. if there are there is an error. will atemted to corect the error
	{
		if (value == 1)
		{
			error = true;
			break;
		}
	}
	return error;
}

std::vector<int> Hamming::SwapBit(std::vector<int> inputXOR)
{
	int num = accumulate(inputXOR.rbegin(), inputXOR.rend(), 0, [&](int x, int y) { return (x << 1) + y; });// turns the xor vale from bits to int
	std::cout << "XOR:" << num << std::endl;

	// swap error bit. should only do this once. will need to split
	std::vector<int> swaped = inputData;
	if (swaped[num - 1] == 1)//swapts bit
	{
		swaped[num - 1] = 0;
	}
	else
	{
		swaped[num - 1] = 1;
	}
	return swaped;
}