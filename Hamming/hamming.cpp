#include "hamming.h"

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

int IntToBool(int num, int testbit) {

	bitset<16> bset(num);//max size 65,536
	int even = 0;
	cout << bset.to_string() << endl;
	if (bset.test(testbit) == true)
	{
		//outputs wich bits are effected by parity bits
		cout << "num:" << num << " | testbit;" << testbit << " | " << bset.test(testbit) << endl;		
	}
	return 0;
}

//----Hamming----
Hamming::Hamming() {//construtor	
	data->boolData.push_back(0);//test inputs. is the same as in report
	data->boolData.push_back(1);
	data->boolData.push_back(1);
	data->boolData.push_back(1);
	data->boolData.push_back(0);
	data->boolData.push_back(0);
	data->boolData.push_back(1);
	data->boolData.push_back(0);
	data->boolData.push_back(1);
	data->boolData.push_back(0);
	data->boolData.push_back(1);
}

int Hamming::ErrorDetect() //used for data input. using int for tetsing(will be need to change to binray (vectory of bools?))
{
	VectorOut(data->boolData);
	//const int noOfBits = polairtyBits.size(); //dose not count as a const?
	const int noOfBits = 4;//hold how meny bits the bitset will hold
	
	
	
	int isP=0;
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
			isP = data->boolData.size() +2 ;//exit condtion
		}
		
	}
	cout<<endl;

	//---works out new pbit values--- 	
	GetPBits();
	getNewP();
	

	

	

	//vector xor test
	vector<int>VOne{0,1,1,0};
	vector<int> VTwo{0,1,0,0};

	vector<int> VOut = VectorXOR(VOne, VTwo);
	cout << "---Vector XOR test---";
	VectorOut(VOut);
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

//TODO clean data dose not get the last bit?
int Hamming::getNewP()//recaulates the new plairty bits
{
	int isPCount = 0;//used to count thoru the know numbers if poliaty bits
	vector<int> cleanData;// all pbit will be set to -1

	//----sets all pbits to = -1----
	for (int postion = 1; postion <= data->boolData.size(); postion++)//loop throu all of the data
	{
		if (postion != polairtyBits[isPCount])//will only let non Pbits through
		{
			cleanData.push_back(data->boolData[postion-1]);
			cout << "postion:" << postion;
			cout << " | data in postion:" << data->boolData[postion-1];
			cout <<  " | isPCount:" << isPCount;
			cout << " | Current Pbit checking for:" << polairtyBits[isPCount] << endl;
		}
		else
		{
			cleanData.push_back(-1);//all -1 are were the parity bit will go. might not need this?
			if (polairtyBits.size()-1!= isPCount){
				isPCount++;
			}			
		}
	}
	cout << "cleanData:";
	VectorOut(cleanData);
	//----works out the new pbits----

	for (int testbit = 0; testbit <= polairtyBits.size(); testbit++)//loops throuh the bits to check for 
	{
		cout << "Testbit:" << testbit<< endl;
		//for (int count = 0; count < cleanData.size(); count++)
		for (int count = 0; count <= data->boolData.size(); count++)		
		{
			cout << "num;" << count<< " | ";
			IntToBool(count, testbit);
		}
	}


	VectorOut(cleanData);
	return 0;
}

