#include "Trip.h"
using namespace std;

/*Trip::Trip()
// Default constructor
{
    start = "Null";
    end = "Null";
}*/ ///////////// je crois yen a pas besoin mais a verifier

Trip::Trip(char* start, char* end, char* transport)
// Constructor that takes start and end as a parameter
{
    this->start = start;
    this->end = end;
    this->transport = transport;
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

void Trip::Display() const
// Displays the trip
{
    cout << "Start : " << start << " , End : " << end << " by " << transport << endl;
}

Trip::~Trip()= default;


