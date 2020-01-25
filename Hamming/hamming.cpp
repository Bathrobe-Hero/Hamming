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



//----Hamming----
Hamming::Hamming() {//construtor
	//test inputs. is the same as in report
	data->boolData.push_back(0);//lsb
	data->boolData.push_back(1);
	data->boolData.push_back(1);
	data->boolData.push_back(1);
	data->boolData.push_back(0);
	data->boolData.push_back(1);//chnaged bit
	data->boolData.push_back(1);
	data->boolData.push_back(0);
	data->boolData.push_back(1);
	data->boolData.push_back(0);
	data->boolData.push_back(1);//msb
}

int Hamming::ErrorDetect() //used for data input. using int for tetsing(will be need to change to binray (vectory of bools?))
{
	VectorOut(data->boolData);	
	
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
	//TODO move most of this to its own funtion


	//---works out new pbit values--- 	
	GetPBits();//gets the pbits inclued
	getNewP();//generates new pbits
	
	XOR =  VectorXOR(newPBits, pbit);//gets the XOR vaules for testing with
	cout << "Vextor XOR:";
	VectorOut(XOR);
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

//TODO clean data dose not get the last bit?
int Hamming::getNewP()//recaulates the new plairty bits
{
	int isPCount = 0;//used to count thoru the know numbers if poliaty bits	

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

	int even;//used to see if the pbit toal trues is even
	for (int testbit = 0; testbit < polairtyBits.size(); testbit++)//loops throuh the bits to check for 
	{
		even = 0;
		cout << "Testbit:" << testbit<< endl;
		
		for (int count = 0; count <= data->boolData.size(); count++)		
		{
			cout << "num:" << count<< " | ";
			even += IntToBool(count, testbit);
		}
		//once all nums have been tested with that bit checks if the total is even.
		//if so will that newPbit to 0
		//if its odd sets newpbit to 1

		if (even % 2 == 0)//devide by 2 and check remander
		{//if even
			newPBits.push_back(0);
		}
		else 
		{//if odd
			newPBits.push_back(1);
		}

	}
	cout << "newPbits:";
	VectorOut(newPBits);
	return 0;
}

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

int Hamming::CheckXOR()
{
	bool error = false;//holds a flag for if thre is an error
	//this funtion will check the output for vectorXOR to see if there are any errors and if so will atempte to fix them
	for (auto const& value : XOR)//loops throu XOR to check if there are any true vales
	{
		if (value == 1)
		{
			error = true;
		}

		if (error == true)//if there is an error will atempted to fix it
		{

		}
		
	}
	return 0;
}
