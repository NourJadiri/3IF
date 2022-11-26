#include "Trip.h"
using namespace std;

Trip::Trip()
// Default constructor
{
    start = nullptr;
    end = nullptr;
    transport = nullptr;
}

Trip::Trip(const char* startCity, const char* endCity, const char* trspt)
// Constructor that takes start, end and transport as a parameter
{
    start = (char*)malloc(strlen(startCity)+1);
    end = (char*)malloc(strlen(endCity)+1);
    transport = (char*)malloc(strlen(trspt)+1);
    strcpy(start, startCity);
    strcpy(end, endCity);
    strcpy(transport, trspt);
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

bool Trip::operator== ( const Trip &aTrip ) const
// Two trips are equal if their start and their ends are the same
{
    return (!strcmp(start,aTrip.start) && !strcmp(end,aTrip.end));
}

void Trip::Display ( ) const
// Displays the trip
{
    cout << "from: " << start << " to: " << end << ", by " << transport << endl;
}

Trip::~Trip ( )
= default;


