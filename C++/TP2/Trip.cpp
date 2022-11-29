#include "Trip.h"
using namespace std;

Trip::Trip()
// Default constructor
{
    start = nullptr;
    end = nullptr;
}

Trip::Trip(const char* startCity , const char* endCity)
// generic Constructor that takes start, end as a parameter
{
    start = new char[64];
    end = new char[64];
    strcpy(this->start, startCity);
    strcpy(this->end, endCity);

}

char *Trip::GetStart ( ) const
// returns attribute char* start
{
    return start;
}

char *Trip::GetEnd ( ) const
// returns attribute char* end
{
    return end;
}

void Trip::Display() const
// Displays the trip information
{
    cout << "Trip from " << start << " to " << end ;
}

bool Trip::operator== ( const Trip &aTrip ) const
// Two trips are equal if their start and their ends are the same
{
    return (!strcmp(start, aTrip.GetStart()) && !strcmp(end, aTrip.GetEnd()));
}



Trip::~Trip ( ){
    delete [] start;
    delete [] end;
}


