#include "Trip.h"

Trip::Trip()
// Default constructor
{
    start = "Null";
    end = "Null";
}

Trip::Trip(char * start, char * end)
// Constructor that takes start and end as a parameter
{
    this->start = start;
    this->end = end;
}

char *Trip::GetStart()
// returns attribute char* start
{
    return start;
}

char *Trip::GetEnd()
// returns attribute char* end
{
    return end;
}

bool Trip::operator==(const Trip &aTrip) const
// Two trips are equal if their start and their ends are the same
{
    return (!strcmp(start,aTrip.start) && !strcmp(end,aTrip.end));
}

void Trip::Display()
// Displays the trip
{
    cout << "Start : " << start << " , End : " << end << endl;
}

Trip::~Trip()= default;


