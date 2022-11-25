#ifndef INC_3IF_LIST_H
#define INC_3IF_LIST_H
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
    void Fetch(char* start ,char* end) const;
    void Add(const Trip & aTrip);
    void Display() override;

    ~List();
};


#endif //INC_3IF_LIST_H
