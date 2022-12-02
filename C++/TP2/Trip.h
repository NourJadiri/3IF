#ifndef TRIP_H
#define TRIP_H

#include <iostream>
#include <cstring>

enum types { VIRTUAL , SIMPLE_TRIP , COMPOSED_TRIP };

class Trip {

protected:
    char* start;
    char* end;
    int type;

public:

    Trip();
    explicit Trip(const char* start , const char* end);

    virtual char* GetStart ( ) const;
    virtual char* GetEnd ( ) const;
    virtual int GetType() const;

    virtual bool operator == ( const Trip & aTrip ) const;

    virtual void Display ( ) const = 0;

    virtual ~Trip ( );
};


#endif //TRIP_H
