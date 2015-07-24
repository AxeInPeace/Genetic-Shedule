#pragma once
#include "Time.h"
#include <string>

class Job
{
public:
	Job (void);
	~Job (void);

	Time timeLeftTo (Job &nextJob); // Return how much time left from this event to argument event
	Time startBorder (void) const { return _startTime; }
	Time endBorder (void) const { return _endTime; }

	bool operator < (const Job&) const;
	bool operator == (const Job&) const;
	bool operator != (const Job&) const;

	std::string getPlace (void) const {return _place;}

	void setDay (int); 
	void setWeekday(DAYSOFWEEK);

	virtual void printType (void) {;}
	virtual std::string getType (void){return "Job";}
protected:
	Time _startTime, _endTime;
	std::string _place;
};