#pragma once
#include "Job.h"

Job::Job(void) 
{
	_startTime.init(0, 0, 0);
	_endTime.init(0, 0, 0);
}

Job::~Job(void)
{
}

bool Job::operator < (const Job& ve1) const{
	if ((this->_startTime < ve1._startTime) && ((this->_endTime < ve1._startTime) || (this->_endTime == ve1._startTime)))
		return true;
	return false;
}

bool Job::operator == (const Job&j1) const{
	if ((this->_startTime == j1._startTime) && (this->_endTime == j1._endTime))
		return true;
	return false;
}

bool Job::operator != (const Job&j1) const{
	return !(*this == j1);
}

void Job::setDay (int newDay) {
	_startTime.setDay(newDay);
	_endTime.setDay(newDay);
	
}

void Job::setWeekday(DAYSOFWEEK newWeekday) {
	_startTime.setWeekday(newWeekday);
	_endTime.setWeekday(newWeekday);

}
