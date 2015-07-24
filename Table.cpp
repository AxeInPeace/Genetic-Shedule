#pragma once
#include "Table.h"
#include <algorithm>
#include <time.h>
#include <random>

Table::Table(void) {
	_job.resize(0);
	_tasks.resize(0);
//	_placesTime->resize(0);
}

/*
Table::Table(const Table& table) {
	_job.resize(table._job.size());
	_tasks.resize(table._tasks.size());

	Job* jobBuf;
	for(int i = 0; i < table._job.size(); i++) {
		jobBuf = new Job(*table._job[i]);
		_job[i] = jobBuf;
	}

	Task* taskBuf;
	for(int i = 0; i < table._tasks.size(); i++) {
		taskBuf = new Task(*table._tasks[i]);
		_tasks[i] = taskBuf;
	}

	this->_placesTime = table._placesTime;

}
*/

Table::~Table(void) {	
	/*
	for (int i = 0; i < _job.size(); i++) {
		delete _job[i];
	}
	*/
}

//==================================================================================================================
//INITIALIZATION AND BUILDING

void Table::include(Event& incEvent, int numOfDays, int startDay){
	int inc = 0;
	Event bufEv = incEvent;	
	Job* ptrToVE;
	int i = incEvent.startBorder().getDay();
	DAYSOFWEEK currDayOfWeek;

	switch(incEvent.getPer()) { 
		case 1: inc = 1; break;
		case 2: inc = 7; break;
		case 3: inc = 14; break;
		case 4: inc = 30; break;
		case 5: goto workdaysIncluding; break;
		default: 
			ptrToVE = new Event(incEvent);
			_job.push_back(ptrToVE);
			break;
	}
	
	for (i; i <= numOfDays; i += inc) {
		currDayOfWeek = DAYSOFWEEK(((i - 1) + startDay - 1) % 7 + 1);
		bufEv.setDay(i);
		bufEv.setWeekday(currDayOfWeek);
		ptrToVE = new Event(bufEv);		
		_job.push_back(ptrToVE);
	}	
	return;

workdaysIncluding:
	startDay = ((i - 1) + startDay - 1) % 7 + 1;
	for (i; i <= numOfDays; i ++) {		
		if (startDay < 6) { //if workDay
			bufEv.setDay(i);
			bufEv.setWeekday((DAYSOFWEEK)startDay);
			ptrToVE = new Event(bufEv);		
			_job.push_back(ptrToVE);
		}
		startDay = startDay % 7 + 1;
	}	

}

void Table::include(Task& ts){
	Job* ptrToVE;
	ptrToVE = new Task(ts);		
	_job.push_back(ptrToVE);	
}

int Table::findPlaceToInput (int leftBorder, int rightBorder, Task& inputTask) const {
	Time evToTaskTime;
	Time taskToNextEvTime;
	Time gap;
	for (int i = leftBorder; i <= rightBorder; i++) {
		evToTaskTime = *(_placesTime->timeToPass (_job[i]->getPlace(), inputTask.getPlace()) );
		taskToNextEvTime = *(_placesTime->timeToPass (inputTask.getPlace(), _job[i + 1]->getPlace()) );
		
		gap =  _job[i + 1]->startBorder().subtract(taskToNextEvTime);
		gap = gap.subtract(evToTaskTime);

		if (inputTask.lessDuration(_job[i]->endBorder(), gap))
			return i;
	};
	return -1;
}

int Table::inputAfter(int startPoint, Task& inputTask){
	int curEv = _job.size();
	int possiblePlace = findPlaceToInput(startPoint, curEv - 2, inputTask);
	if (possiblePlace == -1)
		possiblePlace = findPlaceToInput(0, startPoint - 1, inputTask);
	else
		return possiblePlace;
	
	if (possiblePlace == -1)
		return curEv - 1;
	else 
		return possiblePlace;
}

void Table::generation(std::vector<Task*> &tasks1) {
	sortEvents();
	_tasks = tasks1;

	int randEv, inputEv;
	DAYSOFWEEK weekday;

	for (unsigned int i = 0; i < _tasks.size(); i++){
		randEv = rand() % (_job.size());
		inputEv = this->inputAfter(randEv, *_tasks[i]);
						
		_tasks[i]->generate(_job[inputEv]->endBorder(), *(_placesTime->timeToPass (_job[inputEv]->getPlace(), _tasks[i]->getPlace()) ));
		weekday = _job[inputEv]->startBorder().getWeekday();
		_tasks[i]->setWeekday(weekday);
		this->include(*_tasks[i]);
		
		sortEvents();		
		_tasks[i] = (Task*)_job[inputEv + 1];
	}
}
/*
void Table::operator= (Table& copyTable){	
	
	for (unsigned int i = 0; i < copyTable._tasks.size(); i++) {
		this->_tasks.push_back(new Task(*copyTable._tasks[i]));	
	}

	for (unsigned int i = 0; i < copyTable._job.size(); i++) {
		this->_job.push_back(new Job(*copyTable._job[i]));	
	}

	this->_placesTime = copyTable._placesTime;
}
*/
//INITIALIZATION AND BUILDING
//==================================================================================================================


//==================================================================================================================
//GENETIC

float Table::fitness(void) const{	
	int numOfTasks = _tasks.size();
	int numOfJobs = _job.size();
	int startValue = int(numOfTasks * 10) + 24 * (_job[numOfTasks - 1]->endBorder()).getDay();
	
	//Проверить факт лишнего выезда и назначить штраф 
	std::string taskPlace = "";
	std::string ev1Place = "";
	std::string ev2Place = "";

	for (int i = 1; i < numOfJobs - 1; i++) {
		if (_job[i]->getType() == "Task") {
			taskPlace = _job[i]->getPlace();
			
			//Get nearest other places 
			for (int j = i - 1; j >= 0; j--) {
				if (_job[j]->getType() == "Event" || (_job[j]->getType() == "Task" && _job[j]->getPlace() != taskPlace)) { 
					ev1Place = _job[j]->getPlace();
					break;
				}
			}

			for (int j = i + 1; j < numOfJobs; j++) {
				if (_job[j]->getType() == "Event" || (_job[j]->getType() == "Task" && _job[j]->getPlace() != taskPlace)) {
					ev2Place = _job[j]->getPlace();
					break;
				}
			}		
			
			if((ev1Place != taskPlace) && (ev2Place != taskPlace || ev2Place == "") )
				startValue -= 20;
		}
	}

	//Назначить штраф за окна, в будние пропорционально окну.(За каждый час на 1).
	Time timeBetweenEvents;
	int numOfWeekday;
	for (int i = 0; i < numOfJobs - 1; i++) {
		timeBetweenEvents = (_job[i + 1]->startBorder()).subtract(_job[i]->endBorder());
		numOfWeekday = int(_job[i]->endBorder().getWeekday());

		if(numOfWeekday <= 5)
			startValue -= timeBetweenEvents.getHour();
	}		

	//Назначить поощрение за присутствие окон, в выходные пропорционально окну.(За каждый час на 1).
	for (int i = 0; i < numOfJobs - 1; i++) {
		timeBetweenEvents = (_job[i + 1]->startBorder()).subtract(_job[i]->endBorder());
		numOfWeekday = int(_job[i]->endBorder().getWeekday());

		if(numOfWeekday >= 6)
			startValue += timeBetweenEvents.getHour();
	}		

	// штраф за дедлайн (30 за каждый дедлайн)
	for (unsigned int i = 0; i < _tasks.size(); i++){
		if (_tasks[i]->getDeadline() < _tasks[i]->endBorder())
			startValue -= 30;
	}
	return float(startValue);
}



Table* Table::crossover(Table &t1, Table &fund) {
	Table* newTab = new Table;

	int inputEv; 
	int randEv;

	*newTab = fund;
	
	for (unsigned int i = 0; i < _tasks.size(); i++) {
		newTab->_tasks.push_back(new Task);
		if (rand() % 100 < 50) {
			*newTab->_tasks[i] = *this->_tasks[i];
			newTab->_job.push_back(newTab->_tasks[i]);

			newTab->sortEvents();
			if (!newTab->eventsSequently()) {
				randEv = rand() % _job.size();
				inputEv = this->inputAfter(randEv, *(newTab->_tasks[i]));
				(newTab->_tasks[i])->generate(_job[inputEv]->endBorder(), *(_placesTime->timeToPass (_job[inputEv]->getPlace(), _tasks[i]->getPlace()) ));		
			}
		}
		else {			
			*newTab->_tasks[i] = *t1._tasks[i];
			newTab->_job.push_back(newTab->_tasks[i]);

			newTab->sortEvents();
			if (!newTab->eventsSequently()) {
				randEv = rand() % _job.size();
				inputEv = this->inputAfter(randEv, *(newTab->_tasks[i]));
				(newTab->_tasks[i])->generate(_job[inputEv]->endBorder(), *(_placesTime->timeToPass (_job[inputEv]->getPlace(), _tasks[i]->getPlace()) ));		
			}
		}
	}	
			
	return newTab;	
}

void Table::mutation(void) { 
	this->sortEvents();
	int randEv = rand() % _job.size();

	for (int i = 0; i < _tasks.size(); i++) {
		if (rand() % 100 < 50){
			int inputEv = this->inputAfter(randEv, *(_tasks)[i]);
			_tasks[i]->generate(_job[inputEv]->endBorder(), 
								*(_placesTime->timeToPass (_job[inputEv]->getPlace(), _tasks[i]->getPlace()) ));
		}
	}
	
	this->sortEvents();	
}
//GENETIC

//==================================================================================================================

//==================================================================================================
//SORT AND COMPARE
inline int eventCompare(const void* e1, const void* e2) {
	if (*(Job*)e1 < *(Job*)e2)
		return -1;
	if (*(Job*)e1 == *(Job*)e2)
		return 0;
	return 1;
}

inline bool Table::eventsSequently(void) {
	Job ve1, ve2;
	for (unsigned int i = 0; i < _job.size() - 1; i++){
		ve1 = *(_job[i]);
		ve2 = *(_job[i + 1]);
		if (!(ve1 < ve2))
			return false;
	}
	return true;
}


inline void Table::sortEvents(void){
	std::sort(_job.begin(), _job.end(), [](Job *first, Job *second) {
		return *(first) < *(second);
	});
}

bool Table::operator < (Table &t1) const{return this->fitness() < t1.fitness();}
bool Table::operator == (Table &t1) const{return this->fitness() == t1.fitness();}

bool Table::equality(Table &t1) const {
	if (this->fitness() != t1.fitness())
		return false;
	return true;

	/*for (unsigned int i = 0; i < _job.size(); i++)
		if ( *(this->_job[i]) != *(t1._job[i]))
			return false;
	return true;*/

}

//SORT AND COMPARE
//==================================================================================================================

//==================================================================================================================
//OUTPUT
void Table::output (void) {
	Task t1;
	for (unsigned int i = 0; i < _job.size(); i++){
		_job[i]->startBorder().toStr();
		std::cout << " " ;
		_job[i]->endBorder().toStr();
		std::cout << " " << _job[i]->getPlace();
		_job[i]->printType();
		std::cout << std::endl;
		
	}
}
//OUTPUT
//==================================================================================================================

