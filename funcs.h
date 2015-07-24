#pragma once
#include <iostream>
#include <tchar.h>
#include <string>
#include <fstream>

using namespace std;

int tableCompare (const void * t1, const void * t2);

bool timeIsNotOut(tm &cur, tm &max);
bool cyclesIsNotOut(int cur, int max);

template <class inputType>
void getValue (ifstream& inStream, const string& invite, const string& errorVal, const inputType& leftBorder, const inputType& rightBorder, inputType& value){
	cout << invite;
	bool checkBorders;
	
	inStream >> value;

	checkBorders = value >= leftBorder && value <= rightBorder;
	if (!checkBorders) 
		cout << errorVal;
	
	cout << value << endl;
}
