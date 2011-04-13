// KeyboardBeat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "windows.h"
#include "math.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	SYSTEMTIME start_time, check_time;
	int count, sentinel_milli, threshold;
	bool print_special_ok;

	GetSystemTime(&start_time);
	sentinel_milli = start_time.wMilliseconds;
	threshold = sentinel_milli + 500; // DTA 13Apr2011 - Make sure that the "1 second is transpiring" marker resides in the other "half" of each passing second.
	if (threshold > 999)
		threshold -= 999;
	print_special_ok = true;
	count = 0;
	
	while(true)
	{
		//Sleep(20); // DTA 11Apr2011 - this is bad: I don't know how to guarantee that control returns to this thread promptly enough to keep the output in rhythm.
					// I need to find another way to track elapsed time.

		GetSystemTime(&check_time);
		int curr_milli = check_time.wMilliseconds;

		if ( (abs(curr_milli - sentinel_milli) < 100) && print_special_ok)
		{
			cout << "~~~~~~~~~~~~~~~" << endl;
			print_special_ok = false;
		}
		if (count % 600000 == 0)
		{
			cout << check_time.wMilliseconds << endl;
			//cout << "~~~~~" << endl;
		}

		if (abs(curr_milli - threshold) < 100)
		{
			print_special_ok = true;
		}

		count++;
		if (count % 1048576 == 0)
			count = 0;
	}
	
	return 0;
}
