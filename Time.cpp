#pragma once
#include "Time.h"


Time::Time(void){}

Time::Time(int m, int h , int d){
	_min = m; 
	_hour = h;
	_day = d;
}

Time::~Time(void){}

Time Time::subtract(Time &t) const{
	int subtractDay = 0, subtractHour = 0, subtractMin = 0;
	
	subtractMin += this->_min - t._min;
	if (subtractMin < 0) {
		subtractMin += 60;
		subtractHour -= 1;
	}
		
	subtractHour += this->_hour - t._hour;
	if (subtractHour < 0) {
		subtractHour += 24;
		subtractDay -= 1;
	}
	
	subtractDay += this->_day - t._day;

	Time ans;
	ans.init(subtractMin, subtractHour, subtractDay);

	return ans;
};

void Time::randGeneration(Time lBord,Time rBord){
	_min = rand() % 60;
	_hour = rand() % 24;
	_day = 0;
};

void Time::init(int m, int h, int d){
	_min = m;
	_hour = h;
	_day = d;
}
	
void Time::parse(std::string &s){
	std::string h, m;
	h = s.substr(0, 2);
	m = s.substr(3, 2);

	_hour = std::stoi(h);
	_min = std::stoi(m);	
}

bool Time::operator <(const Time& t1) const {
	if (this->_day < t1._day)
		return true;
	if (this->_day > t1._day)
		return false;

	if (this->_hour < t1._hour)
		return true;
	if (this->_hour > t1._hour)
		return false;

	if (this->_min < t1._min)
		return true;
	if (this->_min > t1._min)
		return false;

	return false;
	
}

bool Time::operator ==(const Time&t1) const {
	if ((this->_day == t1._day) && (this->_hour == t1._hour) && (this->_min == t1._min))
		return true;
	return false;
}

Time Time::operator + (const Time& t1) const{
	Time newTime;
	newTime._min = (this->_min + t1._min);
	newTime._hour = this->_hour + t1._hour + newTime._min / 60;
	newTime._day = this->_day + t1._day + newTime._hour / 24;
	newTime._min %= 60;
	newTime._hour %= 24;
	
	return newTime;
}

void Time::toStr (void) const {
	printf("%3d %02d:%02d", _day, _hour, _min);
}