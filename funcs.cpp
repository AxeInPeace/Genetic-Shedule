
//#include "funcs.h"
#include <iostream>
#include <tchar.h>
#include <string>
#include "Table.h"

using namespace std;

int tableCompare (const void * t1, const void * t2)
{
  if ( *(Table*)t1 < *(Table*)t2) return 1;
  if ( *(Table*)t1 == *(Table*)t2 ) return 0;
  return -1;
}

bool timeIsNotOut(tm &cur, tm &max) {
	if(cur.tm_min > max.tm_min) {
		cout << "Out of time" << endl;
		return false;
	}
	return true;
}

bool cyclesIsNotOut(int cur, int max) {
	if(cur > max)
		return false;
	return true;
}
