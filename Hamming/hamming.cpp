#include "hamming.h"

//----Hamming----
Hamming::Hamming() {//construtor
	//test inputs. is the same as in report
	data->boolData.push_back(0);//0 | lsb	
	data->boolData.push_back(1);//1
	data->boolData.push_back(1);//1
	data->boolData.push_back(1);//1
	data->boolData.push_back(0);//0
	data->boolData.push_back(1);//0 | chnaged bit	
	data->boolData.push_back(1);//1 | chnaged bit 2
	data->boolData.push_back(0);//0
	data->boolData.push_back(1);//1
	data->boolData.push_back(0);//0
	data->boolData.push_back(1);//1 | msb
}

int Hamming::ErrorDetect() //used for data input. using int for tetsing(will be need to change to binray (vectory of bools?))
{	//---works out new pbit values--- 	

	IsPBit();
	GetPBits();//gets the pbits inclued
	CleanData(data->boolData);
	newPBits = getNewP(data->boolData);//generates new pbits
	
	XOR =  VectorXOR(newPBits, pbit);//gets the XOR vaules for testing with
	cout << "Vextor XOR:";
	VectorOut(XOR);
	cout << endl;
	int returned = CheckXOR(XOR, 0);//flag set to 0 as its one deep
	
	cout << "retruned CheckXOR value:" << returned << endl;
	cout << "Error value:" << data->error << endl;
	cout << "output data:";
	cout<< VectorOut(data->retrunData)<<endl;
	return 0;
}
//---------------------------------------------------------------
int Hamming::SetData(vector<int> input)
{
	data->boolData = input;
	return 0;
}

vector<int> Hamming::getData()
{
	return data->retrunData;
}
//------------------------------------------------------------
int Hamming::IsPBit()//works out which bits are parity bits
{
	VectorOut(data->boolData);

	int isP = 0;
	for (int count = 0; isP <= data->boolData.size(); count++)//generates witch bit are polaity
	{
		isP = (pow(2, count));//plarity bits are always this caulation

		if (isP <= data->boolData.size())
		{
			polairtyBits.push_back(isP);
			cout << isP;
		}
		else
		{
			isP = data->boolData.size() + 2;//exit condtion
		}

	}
	cout << endl;
	return 0;
}


//------------------------------

int Hamming::GetPBits()
{	//----gets values of p bits----
	int pBCount = 0;//used to count current pbit
	for (auto const& value : polairtyBits)//loops throu pbit and gets the value of polairty bits
	{
		cout << "P bit:" << value << " values is:" << data->boolData[value - 1] << endl;
		if (data->boolData[value - 1] == true)
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
	cout << "pbit values:";
	VectorOut(pbit);
	return 0;
}
//----------------------------------------------
int Hamming::CleanData(vector<int> input)
{
	int isPCount = 0;//used to count thoru the know numbers if poliaty bits	

	//----sets all pbits to = -1----
	for (int postion = 1; postion <= input.size(); postion++)//loop throu all of the data
	{
		if (postion != polairtyBits[isPCount])//will only let non Pbits through
		{
			cleanData.push_back(input[postion - 1]);
			cout << "postion:" << postion;
			cout << " | data in postion:" << input[postion - 1];
			cout << " | isPCount:" << isPCount;
			cout << " | Current Pbit checking for:" << input[isPCount] << endl;
		}
		else
		{
			cleanData.push_back(-1);//all -1 are were the parity bit will go. might not need this?
			if (polairtyBits.size() - 1 != isPCount) {
				isPCount++;
			}
		}
	}
	cout << "cleanData:";
	VectorOut(cleanData);
	return 0;
}
//-------------------------------------------------------------------

//TODO clean data dose not get the last bit?
vector<int> Hamming::getNewP(vector<int> input)//recaulates the new plairty bits
{	//----works out the new pbits----

	int even;//used to see if the pbit toal trues is even
	vector<int>output;
	for (int testbit = 0; testbit < polairtyBits.size(); testbit++)//loops throuh the bits to check for 
	{
		even = 0;
		cout << "Testbit:" << testbit<< endl;
		
		for (int count = 0; count <= input.size(); count++)
		{
			cout << "num:" << count<< " | ";
			even += IntToBool(count, testbit);
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
	cout << "newPbits:";
	VectorOut(output);
	return output;
}
//----------------------------------------------------------------
int Hamming::IntToBool(int num, int testbit)
{
	bitset<16> bset(num);//max size 65,536. sets num to a binray way
	int even = 0;//hold number of trues for chekcing if evan 
	//TODO need to be moved so it stay around longer
	cout << bset.to_string() << endl;
	if (bset.test(testbit) == true)
	{
		//outputs wich bits are effected by parity bits
		cout << "num:" << num << " | testbit:" << testbit << " | " << bset.test(testbit) << endl;


		//num-1 is the postion in the vector that this is equvalent to
		if (cleanData[num - 1] == 1)//only trues will add to the evan
		{
			return 1;
		}
	}	
	return 0;
}

//--------------------------------------------------

int Hamming::CheckXOR(vector<int> inputXOR, bool flag )
{
	bool error = false;//holds a flag for if thre is an error
	//this funtion will check the output for vectorXOR to see if there are any errors and if so will atempte to fix them
	int num;
	for (auto const& value : inputXOR)//loops throu XOR to check if there are any true vales
	{
		if (value == 1)
		{
			error = true;
		}	
		
	}
	if (error == true & flag == 0)//if there is an error will atempted to fix it
	{		
		//converst xor bools to int
		num = accumulate(inputXOR.rbegin(), inputXOR.rend(), 0, [](int x, int y) { return (x << 1) + y; });
		cout <<"XOR:"<< num << endl;
		//swpa error bit
		vector<int> swaped = data->boolData;
		if (swaped[num - 1] == 1)//swapts bit
		{
			swaped[num - 1] = 0;
		}
		else
		{
			swaped[num - 1] = 1;
		}

		cleanData.clear();
		CleanData(swaped);//recleans data
		vector<int> XorPBit = getNewP(swaped);

		XorPBit = VectorXOR(XorPBit, pbit);
		//sets flag to know it shoudent do all caulations
		if (CheckXOR(XorPBit, 1) == 1)
		{
			cout << "Deep 1| CheckXOR(XorPBit, 1) == 1" << endl;
			data->error = 2;
			data->retrunData.push_back(-1);
			return 1;//will retrun if to main error corect that it cannot be fixed
		}
		else
		{
			cout << "Deep 1| CheckXOR(XorPBit, 1) == 0" << endl;
			data->error = 1;
			data->retrunData = swaped;//sets the swaped item
		}
		//requlauate pbits
		//requlaute xor
		//if ok let through
		//if not repot back two or more error in binary
	}
	else if (error == true & flag == 1)
	{
		cout << "Two or more error. Cannot correct" << endl;
		data->error = 2;
		return 1;
	}
	else if (error == false & flag == 0)
	{
		data->error = 0;
		data->retrunData = data->boolData;//sets the swaped item
	}
	return 0;// retrun 0 if binary is corect or corrected
}

//-----------------------------------------------------------------------------
int Hamming::VectorOut(vector<int> vOut)
{
	for (int i = 0; i < vOut.size(); i++)
	{
		cout << vOut[i] << "|";
	}
	cout << endl;
	return 0;
}

vector<int> Hamming::VectorXOR(vector<int> VOne, vector<int> VTwo)
{
	vector<int> VOut;
	if (VOne.size() == VTwo.size())
	{
		for (int i = 0; i < VOne.size(); i++)
		{
			VOut.push_back(VOne[i] ^ VTwo[i]);
		}
	}
	else
	{
		cout << "vectors cannot XOR due to diffrent sizes" << endl;
	}

	return VOut;
}