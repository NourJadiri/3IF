#ifndef TRIP_H
#define TRIP_H

#include <iostream>
#include <cstring>


class Trip {
protected:
    char* start;
    char* end;
    char* transport;

public:

    Trip();
    explicit Trip(const char* start, const char*  end, const char* transport = nullptr);

    char* GetStart ( ) const;
    char* GetEnd ( ) const;

    bool operator == ( const Trip & aTrip ) const;

    virtual void Display ( ) const;

    virtual ~Trip ( );
};


#endif //TRIP_H
