#ifndef LIST_H
#define LIST_H
#define DEFAULT_LIST_SIZE 0
#include "Node.h"

class List : public Node
{
protected:
    Node *first;
    unsigned int size;

public:

    List();

    explicit List(Trip & aTrip);

    int Fetch(const Trip & aTrip);
    void FetchTrip(const char* start, const char* end) const;
    void AddTrip(const Trip & aTrip);
    void Display() const;
    int GetSize() const;
    void Sort ( );

    ~List();
};


#endif //LIST_H
