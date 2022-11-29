#ifndef TRIP_H
#define TRIP_H

#include <iostream>
#include <cstring>


class Trip {
protected:
    char* start;
    char* end;

public:

    Trip();
    explicit Trip(const char* start , const char* end);

    virtual char* GetStart ( ) const;
    virtual char* GetEnd ( ) const;

    virtual bool operator == ( const Trip & aTrip ) const;

    virtual void Display ( ) const = 0;

    virtual ~Trip ( );
};


#endif //TRIP_H
