// GATable.cpp: определяет точку входа для консольного приложения.
//
//#include "stdafx.h"
#include <time.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "Table.h"
#include "PlacesMatrix.h"
#include "Event.h"
#include "Task.h"
#include "funcs.h"

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");
	srand(unsigned int(time(NULL)));
	
	ifstream inputFile("вход.txt");

	int population = 0;
	getValue(inputFile, "Input number of population <10000\n", "Wrong number of population\n", 1, 10000, population);

	int days = 0;
	getValue(inputFile, "Input number of days in schedule <10000\n", "Wrong number of days\n", 1, 10000, days);

	int startDay = 1;
	getValue(inputFile, "Input position of the day of the week which start the shedule\n(1 - Monday, 2 - Thuesday, ...)", "Wrong number of day of the week", 1, 7, startDay);
	
	//Initialization of places matrix
	unsigned int numOfPlaces = 0;
	getValue(inputFile, "Input number of places <10000\n", "Wrong number of places\n", unsigned int(1), unsigned int(100), numOfPlaces);
	
	PlacesMatrix mat;
	mat.init(numOfPlaces, inputFile);

	//Initialization of events
	int numOfEvents = 0;
	getValue(inputFile, "Input number of events <10000\n", "Wrong number of events\n", 1, 10000, numOfEvents);

	vector<Event*> events;
	for (int i = 0; i < numOfEvents; i++) {
		events.push_back(new Event);
		events[i]->init(inputFile);	
	}

	//Initialization of tasks
	int numOfTasks = 0;
	getValue(inputFile, "Input number of tasks <10000\n", "Wrong number of tasks\n", 1, 10000, numOfTasks);
	
	vector<Task*> tasks;
	for (int i = 0; i < numOfTasks; i++) {
		tasks.push_back(new Task);
		tasks[i]->init(inputFile);
	}

	//Create Table for every solution(contains events only)
	Table fundamentalTable;
	fundamentalTable.include(&mat);

	for (int i = 0; i < numOfEvents; i++) 
		fundamentalTable.include(*events[i], days, startDay);

	//Create start Generation
	vector<Table> solutions;
	solutions.resize(population);
	for (int i = 0; i < population; i++){
		solutions[i] = fundamentalTable;
		solutions[i].generation(tasks);
	}

	cout << "Статистика до генетической обработки:" << endl;
	for (int i = 0; i < population; i++) {
		cout << solutions[i].fitness() << endl;
	}
	
	system("pause");

//============================================CYCLE=============================================
	//CYCLE PREPARATIONS
	unsigned int minutes = 0;	
	getValue(inputFile,  "Input max minutes to generate table\n", "\n", (unsigned int)1, (unsigned int)180, minutes);
	
	tm maxTime;
	maxTime.tm_min = minutes;

	unsigned int maxIter = 0;
	getValue(inputFile,  "Input max iterations to generate table\n", "\n", (unsigned int)1, (unsigned int)50000, maxIter);

	int curIter = 0;
	time_t compTime;
	time(&compTime);
	tm startTime;
	tm curTime;	
	gmtime_s(&curTime, &compTime);
	gmtime_s(&startTime, &compTime);

	vector<float> fitnessValue, likelyhood;
	fitnessValue.resize(population);
	likelyhood.resize(population);
	float sum = 0;
	
	//CYCLE 
	do {
		//Generate roulette
		sum = 0;
		for (int i = 0; i < population; i++) {
			fitnessValue[i] = solutions[i].fitness();
			sum += fitnessValue[i];
		}
		
		likelyhood[0] = fitnessValue[0] / sum;
		for (int i = 1; i < population; i++) {
			likelyhood[i] = fitnessValue[i] / sum + likelyhood[i - 1];
		}		
		
		//Crossover
		float randParant1 = 0, randParant2 = 0;
		Table *Child;
		for (int i = 0; i < population / 2; i++) {//50% children from population
			randParant1 = float(rand() % 1001) / 1000;
			randParant2 = float(rand() % 1001) / 1000;
			
			int parant1Num = 0, parant2Num = 0;

			if (randParant1 >= likelyhood[0]){
				for (int j = 1; j < population ; j++) {				
					if (likelyhood[j - 1] <= randParant1 && randParant1 <= likelyhood[j]){
						parant1Num = j;					
						break;
					}
				};
			}
			else
				parant1Num = 0;

			if (randParant2 >= likelyhood[0]){
				for (int j = 1; j < population ; j++) {				
					if (likelyhood[j - 1] <= randParant2 && randParant2 <= likelyhood[j]){
						parant2Num = j;					
						break;
					}
				};
			}
			else
				parant2Num = 0;

			if (parant1Num == parant2Num) 
				parant2Num = (parant2Num + 1) % population;
			
			Child = solutions[parant1Num].crossover(solutions[parant2Num], fundamentalTable);			
			solutions.push_back(*Child);			
		}

		//Mutation
		for (int i = population; i < 3 * population / 2; i++) 
			if (rand() % 100 < 15) {
				solutions[i].mutation();
			}

		//Natural selection	
		qsort(&solutions[0] ,3 * population / 2, sizeof(Table), tableCompare); //Сортируем по значению целевой функции.

		int pointToShift = population;
		if (solutions[0].equality(solutions[population / 2 - 1])){ //Если половина популяции одинаковая, то
			for (int i = population / 2; i < population; i++)	   //начиная с индекса pointToShift
				if(!solutions[0].equality(solutions[i])) { 
					pointToShift = i;
					break;
				}

			for (int i = 0; i <  population / 2; i++)			   //сдвигаем элементы до индекса population / 2.
				solutions[population / 2 + i] = solutions[pointToShift + i];
				
		}		
		solutions.resize(population);
		
		time(&compTime);
		gmtime_s(&curTime, &compTime);
		if (curTime.tm_min >= startTime.tm_min) 
			curTime.tm_min = curTime.tm_min - startTime.tm_min;
		else 
			curTime.tm_min = 60 + curTime.tm_min - startTime.tm_min;

		curIter++;		
	} 
	while(timeIsNotOut(curTime, maxTime) && cyclesIsNotOut(curIter, maxIter));

	cout << "Статистика после генетической обработки:" << endl;
	for (int i = 0; i < population; i++) {
		cout << solutions[i].fitness() << endl;
	}

	solutions[0].output();
	cout << solutions[0].fitness() << endl;
	if (solutions[0].equality(solutions[population / 2]))
		cout << "Более половины решений эквивалентны\n";		
	else 
		cout << "Не более половины решений эквивалентны\n";
	
	system("pause");
	inputFile.close();
	return 0;
}