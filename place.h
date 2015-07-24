#ifndef PLACE_H
#define PLACE_H

#include <string>


class Place
{
public:
    Place();
    Place(std::string &st);
    void operator >>(std::string &st);

private:
    std::string name;
};

#endif // PLACE_H
