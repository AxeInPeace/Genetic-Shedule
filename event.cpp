#pragma once
#include "Event.h"
#include "funcs.h"

Event::Event(void)
{
}

Event::~Event(void)
{
}

void Event::init(){

	int stDay = 1;	
	std::string sTimeStr, eTimeStr;
	std::string placeStr;
	int per = 0;

	std::cout << "Input start day, start and end times in hh:mm format, place of event and period\n";
	std::cin >> stDay;
	std::cin >> sTimeStr >> eTimeStr;
	std::cin >> placeStr;
	std::cin >> per;

	_startTime.init(0, 0, stDay);
	_startTime.parse(sTimeStr);

	_endTime.init(0, 0, stDay);	
	_endTime.parse(eTimeStr);

	_place = placeStr;

	switch (per) {
	case 1:	_period = DAY; break;
	case 2: _period = WEEK; break;
	case 3: _period = TWOWEEK; break;
	case 4: _period = MONTH; break;
	case 5: _period = WORKDAYS; break;
	}	
}

void Event::init (std::ifstream& inputFile){
	int stDay = 1;	
	std::string sTimeStr, eTimeStr;
	std::string placeStr;
	int per = 0;

	getValue <int> (inputFile, "", "Error, value: ", 1, 10000, stDay);
	getValue <std::string> (inputFile, "", "Error, value: ", "00:00", "23:59", sTimeStr);
	getValue <std::string> (inputFile, "", "Error, value: ", "00:00", "23:59", eTimeStr);
	getValue <std::string> (inputFile, "", "Error, value: ", "", "ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ", placeStr);
	getValue <int> (inputFile, "", "Error, value: ", 1, 5, per);
	
	_startTime.init(0, 0, stDay);
	_endTime.init(0, 0, stDay);

	_startTime.parse(sTimeStr);
	_endTime.parse(eTimeStr);

	_place = placeStr;

	switch (per) {
	case 1:	_period = DAY; break;
	case 2: _period = WEEK; break;
	case 3: _period = TWOWEEK; break;
	case 4: _period = MONTH; break;
	case 5: _period = WORKDAYS; break;
	}	
}

void Event::init(Time sTime, Time eTime, std::string plc, Period per){
	_startTime = sTime;
	_endTime = eTime;
	_place = plc;
	_period = per;
}