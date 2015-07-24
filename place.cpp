#include "place.h"

Place::Place(){
    ;
}

Place::Place(std::string &st)
{
    name = st;
}

void Place::operator >>(std::string &st)
{
    name = st;
}

