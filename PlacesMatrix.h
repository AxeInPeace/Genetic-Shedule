#pragma once

#include "Time.h"
#include <string>
#include <vector>


class PlacesMatrix
{
public:
	PlacesMatrix(void);
	~PlacesMatrix(void);	

	void init(unsigned int, std::ifstream&);
	Time* timeToPass(std::string, std::string); //return pointer to Time that needed to pass between two places

	void resize(int);
private:

	int _placesCount;
	std::vector<Time*> _matrix;
	std::vector<std::string> _places;


};

