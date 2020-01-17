#include "hamming.h"

int VectorOut(vector<int> vOut) {//used to output the data in a vector

	for (int i = 0; i < vOut.size(); i++)
	{
		cout << vOut[i]<<"|";
	}
	cout << endl;
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
	bitset<noOfBits> pbit;//conatins the pbitd vaulues
	
	
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
		getNewP();
	

	//----gets values of p bits----
	
	
		int pBCount = 0;//used to count current pbit
		for (auto const& value : polairtyBits)//loops throu pbit and gets the value of polairty bits
		{
			cout << "P bit:" << value << " values is:" << data->boolData[value - 1] << endl;
			if (data->boolData[value - 1] == true)
			{
				pbit[pBCount] = 1;
			}
			pBCount++;

		}
		//----print pbit values
		
		for (size_t count = 0; count < pbit.size(); count++) {//loop throu 
			std::cout << pbit.test(count) << '\n';			
		}
			



	//would like to delete pBCount here if posable


	//----works out not pbits --- (move to getNewP when done)
		
		/**polairtyBits.push_back(-1);//add and end value

		for (int count = 1; count <= data->boolData.size(); count++)
		{			
			if (find(polairtyBits.begin(), polairtyBits.end(), count) == polairtyBits.end())//should only let non parity bits in
			{
				cout << "not a pbit:" << count << endl;
			}

		}**/



	//bitset test code
	//sets vales to test 1 and 2 then outputs the xor of thous two
	cout << "----Bitset tests----" << endl;
	bitset<4> test1;
	test1.set(1, true);
	test1.set(2, true);
	bitset<4> test2;
	test2.set(0, true);

	bitset<4> test3Oxr;
	test3Oxr=(test2 ^ test1);
	cout << test3Oxr << endl;
	for (size_t i = 0; i < test3Oxr.size(); ++i)//loop throu test3EXor
		std::cout << test3Oxr.test(i) << '\n';

	 int test4 = 3;
	bitset<4> bitest4(test4);//puts int to bitset 
	cout << bitest4;

	return 0;
}

int Hamming::getNewP()//recaulates the new plairty bits
{
	int isPCount = 0;//used to count thoru the know numbers if poliaty bits
	vector<int> cleanData;// all pbit will be set to -1

	//----sets all pbits to = -1----
	for (int postion = 1; postion < data->boolData.size(); postion++)//loop throu all of the data
	{
		if (postion != polairtyBits[isPCount])//will only let non Pbits through
		{
			cleanData.push_back(data->boolData[postion-1]);
			cout << "postion:" << postion << " | data in postion:" << data->boolData[postion] << " | isPCount:" << isPCount << " | Current Pbit checking for:" << polairtyBits[isPCount] << endl;
		}
		else
		{
			cleanData.push_back(-1);//all -1 are were the parity bit will go
			if (polairtyBits.size()-1!= isPCount){
				isPCount++;
			}			
		}
	}
	//----works out the new pbits----



	VectorOut(cleanData);
	return 0;
}