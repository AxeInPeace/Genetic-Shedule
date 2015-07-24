#pragma once
#include "Job.h"
#include "Time.h"
#include <string>
#include <iostream>

class Task :
	public Job
{
public:
	Task (void);
	~Task (void);

	void init (void);
	void init (std::ifstream&);
	void generate (Time&, Time&);
	
	Time getDuration (void) const {return _duration;} //return the duration of task
	bool lessDuration(Time& startBorder, Time& endBorder);    // return true if duration of task is less than start and end borders
	Time getDeadline(void) const {return _deadline;}

	void printType(void) override {std::cout << " task"; }
	std::string getType (void) override {return "Task";}

protected:
	Time _duration;
	Time _deadline;
};

