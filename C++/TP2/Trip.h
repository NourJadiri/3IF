#ifndef TRIP_H
#define TRIP_H

#include <iostream>
#include <cstring>


class Trip {
protected:
    char* start{} ;
    char* end{};
    char* transport{};

public:

    //Trip();
    Trip(char* start = nullptr, char*  end = nullptr, char* transport = nullptr);

    char* GetStart();
    char* GetEnd();

    bool operator == (const Trip & aTrip) const;

    virtual void Display() const;

    virtual ~Trip();
};


#endif //TRIP_H
