#pragma once
#include "PlacesMatrix.h"
#include <iostream>
#include "funcs.h"

PlacesMatrix::PlacesMatrix(void)
{
}


PlacesMatrix::~PlacesMatrix(void)
{
	for (int i = 0; i < _placesCount; i++){
		for (int j = i; j < _placesCount; j++) {
			delete _matrix[i * _placesCount + j];
		}
	}
}

void PlacesMatrix::init(unsigned int numOfPlaces, std::ifstream& inputFile){
	
	_placesCount = numOfPlaces;
	_places.resize(numOfPlaces);
	
	
	std::cout << "Input names of places\n";	
	for (unsigned int i = 0; i < numOfPlaces; i++) {
		getValue(inputFile, "", "Error, value:\n", std::string("") , std::string("ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ"), _places[i]);
	}

	//initilize half matrix with 0 because of symmetry of matrix
	_matrix.resize(numOfPlaces * numOfPlaces);
	for (unsigned int i = 0; i < numOfPlaces; i++){
		for ( unsigned int j = i; j < numOfPlaces; j++) {
		_matrix[i * numOfPlaces + j] = new Time(0, 0, 0);
		}
	}

	std::cout << "Input time in hh:mm format\n";
	std::string bufStr;
	std::string inviteStr = "";
	
	for (unsigned int i = 0; i < numOfPlaces; i++)
		for (unsigned int j = i + 1; j < numOfPlaces; j++) {			
			inviteStr = "Input time to pass distance between " + _places[i] + " and " + _places[j] + "\n";
			getValue(inputFile, inviteStr, "Error, value:\n", std::string("00:00"), std::string("23:59"), bufStr);			
			
			_matrix[i * numOfPlaces + j]->parse(bufStr);
			_matrix[j * numOfPlaces + i] = _matrix[i * numOfPlaces + j];
		}
}

Time* PlacesMatrix::timeToPass(std::string p1, std::string p2) {
	int p1id = 0, p2id = 0;
	
	for (int i = 0; i <_placesCount; i++) {
		if (_places[i] == p1)
			p1id = i;
		if (_places[i] == p2)
			p2id = i;
	}

	return _matrix[p1id * _placesCount + p2id]; 
}

void PlacesMatrix::resize(int newSize){
	_placesCount = newSize;
	_places.resize(newSize);
	_matrix.resize(newSize * newSize);
}

