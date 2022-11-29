#include "List.h"
#include "Node.h"
using namespace std;


List::List(){
    first = nullptr;
    size = DEFAULT_LIST_SIZE;
}

List::List(Trip & aTrip) {
    first = new Node(aTrip);
    size = 1;
}

void List::AddTrip(const Trip &aTrip)
// Adds a new Node(Trip) to the end of the list and increments size
{
    // If the list is empty , set the first element to the node created
    if(size == 0){
        first = new Node(aTrip);
        size++;
        return;
    }

    Node *current = first;

    // Parsing through the list till the last element
    while(current->getNext() != nullptr)
    {
        current = current->getNext();
    }

    current->setNext(new Node(aTrip));

    size++;
}

void List::Display () const
// Diplays the trips of the list
{
    // If the first element is null (list still empty)
    if(first == nullptr){
        cout << "Unfortunately, there are no trips in this list..." << endl;
        return;
    }

    Node *current = first;
    int i = 1;

    while (current != nullptr) {
        cout << "trip " << i << " -> ";
        current->Display();
        current = current->getNext();
        i++;
    }

}

List::~List(){
    delete first;
    size = DEFAULT_LIST_SIZE;
}

int List::Fetch(const Trip &aTrip)
// returns the index of the trip (ranging from 0 to size of the List)
// returns -1 if the trip is not found
{
    int i = 0;
    Node* current = first;

    while(i <= size){
        if(current->getTrip() == aTrip) return i;
        current = current->getNext();
        i++;
    }
    return -1;
}

void List::FetchTrip(const char *start, const char *end) const
// Searches a trip by start and end
// Returns the trip if found, else returns a default null trip
{
    if (first == nullptr) {
        cerr << "error: Fetching in empty list" << endl;
        return;
    }

    Trip aTrip = Trip(start, end);

    Node *current = first;
    int found = 0;
    while(current != nullptr){
        if(current->getTrip() == aTrip){
            if (!found)
            { // if this is the first trip found, print a txt
                cout << "Trip found!" << endl;
            }
            found = 1;
            cout << "\t-> ";
            current->Display();
        }
        current = current->getNext();
    }

    if (!found)
    {
        cout << "Trip from " << start << " to " << end << " does not exist..." << endl;
    }
}

int List::GetSize() const
{
    return size;
}