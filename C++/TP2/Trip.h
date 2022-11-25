#ifndef INC_3IF_TRIP_H
#define INC_3IF_TRIP_H

#include <iostream>
#include <cstring>

using namespace std;

class Trip {
protected:
    char* start ;
    char* end;

public:

    Trip();
    Trip(char* start ,char*  end);

    char* GetStart();
    char* GetEnd();

    bool operator == (const Trip & aTrip) const;

    virtual void Display();

    virtual ~Trip();
};


#endif //INC_3IF_TRIP_H
