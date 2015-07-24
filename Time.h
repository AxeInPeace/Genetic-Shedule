#pragma once
#include <string>

enum DAYSOFWEEK {MONDAY = 1, THUESDAY, WENDSDAY, THIRSDAY, FRIDAY, SATURDAY, SUNDAY};

class Time
{
public:
	Time(void);
	Time(int, int, int);
	~Time(void);

	Time subtract(Time &) const; //subtract time between this and argument
	void randGeneration(Time lBord, Time rBord); //Generate random time in current borders
	void init(int, int, int d = 0);	//Initializate values of day, hour and minute
	
	void parse(std::string &inStr); //Parse inStr which must be in hh:mm format to initilize hour and minute

	bool operator < (const Time&) const;
	bool operator == (const Time&) const;
	Time operator + (const Time&) const;

	void toStr (void) const; //TODO : std::string toStr

	DAYSOFWEEK getWeekday(void) const {return _weekDay;}
	int getDay(void) const {return _day;}
	int getHour(void) const {return _hour;}
	int getMinute(void) const {return _min;}


	void setDay(int newDay) {_day = newDay; }
	void setWeekday(DAYSOFWEEK newWeekDay) {_weekDay = newWeekDay;}
private:
	int _day; 
	int _hour; //[0,23]
	int _min; //[0, 59]
	DAYSOFWEEK _weekDay;//[1, 7]

};

