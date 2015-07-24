#pragma once
#include "Task.h"
#include "Event.h"
#include <vector>
#include "Job.h"
#include "PlacesMatrix.h"

class Table
{
public:
	Table(void);
	//Table(const Table&);
	~Table(void);
	
	void include(PlacesMatrix* pl) {_placesTime = pl;};
	void include(Task&);
	void include(Event&, int, int);

	void generation(std::vector<Task*>&);
	inline void sortEvents(void);
	
	float fitness(void) const;
	float fitnessWithGovnom(void) const;
	Table * crossover(Table&, Table&);
	void mutation(void);
	
	bool operator < (Table&) const;
	bool operator == (Table&) const;
//	void operator = (Table&);
	bool equality(Table&) const;

	void output(void);

protected:
	std::vector<Job*> _job;
	std::vector<Task*> _tasks;
	PlacesMatrix* _placesTime;

	inline bool eventsSequently(void);
	inline bool compareForSort (Job* ve1, Job* ve2) {return *(ve1) < *(ve2);}

	int inputAfter(int, Task &);
	int findPlaceToInput(int, int, Task&) const;
	
	
};

