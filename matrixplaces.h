#ifndef MATRIXPLACES_H
#define MATRIXPLACES_H
#include <QVector>
#include "place.h"
#include <QTime>

class MatrixPlaces
{
public:
    MatrixPlaces();



private:
    QVector<Place> places;
    QVector<QVector<QTime> > distance; //time to pass the distance between places
};

#endif // MATRIXPLACES_H
