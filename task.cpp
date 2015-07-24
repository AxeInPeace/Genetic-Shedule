#pragma once
#include "Task.h"
#include "funcs.h"

Task::Task(void)
{	
	_duration.init(0, 0, 0);
}


Task::~Task(void)
{
}

void Task::init (void){
	std::string durTimeString;
	std::string placeStr;
	
	std::cin >> durTimeString; 
	std::cin >> placeStr;
		
	_duration.parse(durTimeString);
	_place = placeStr;
	
}

void Task::init (std::ifstream& inputFile){
	std::string durTimeString;
	std::string placeStr;
	int deadlineDay;
	std::string deadlineTime;
	
	getValue(inputFile, "", "Error, value: ", std::string("00:00"), std::string("23:59"), durTimeString);
	
	getValue(inputFile, "", "Error, value: ", 0, 10000, deadlineDay);
	getValue(inputFile, "", "Error, value: ", std::string("00:00"), std::string("23:59"), deadlineTime);

	getValue(inputFile, "", "Error, value: ", std::string(""), std::string("ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ"), placeStr);

	_duration.parse(durTimeString);

	_deadline.parse(deadlineTime);
	_deadline.setDay(deadlineDay);

	_place = placeStr;
}

void Task::generate(Time& stBorder, Time& timeToPass) { 
	_startTime = stBorder + timeToPass;	
	_endTime = _startTime + _duration;
}

bool Task::lessDuration(Time& startBorder, Time& endBorder) {
	Time gap = endBorder.subtract(startBorder);
	return (this->getDuration() < gap);
}