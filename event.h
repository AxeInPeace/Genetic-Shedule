#pragma once
#include "Job.h"
#include "Time.h"
#include <iostream>

enum Period {DAY = 1, WEEK, TWOWEEK, MONTH, WORKDAYS};

class Event : public Job 
{
public:
	Event(void);
	~Event(void);

	void init ();
	void init (std::ifstream&);
	void init (Time sTime, Time eTime, std::string plc, Period per);
	
	int getPer (void) const {return _period;}
	std::string getType (void) override {return "Event";}

private:
	Period _period;
};

