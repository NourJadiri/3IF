#include "List.h"
#include "Node.h"
using namespace std;


List::List()
{
    first = nullptr;
    size = DEFAULT_LIST_SIZE;
}

List::List(Trip *aTrip)
{
    first = new Node(aTrip);
    size = 1;
}

void List::AddTrip(Trip *aTrip)
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
    if(first == nullptr)
    {
        cout << "Unfortunately, there are no trips in this list..." << endl;
        return;
    }

    int simpleTrip_number = 1 , composedTrip_number = 1;
    Node *current = first;

    while (current != nullptr)
    {

        if(current->getTrip()->GetType() == SIMPLE_TRIP)
        {
            cout << "Simple Trip " << simpleTrip_number << " : ";
            simpleTrip_number++;
        }
        else
        {
            cout << "Composed Trip " << composedTrip_number << " : ";
            composedTrip_number++;
        }
        current->Display();
/*        if (current->getTrip()->GetType() == SIMPLE_TRIP && current->getNext() != nullptr)
            cout << " - " ;
        else
            cout << endl;*/
        if(current->getTrip()->GetType() == SIMPLE_TRIP) cout<<endl;

        current = current->getNext();
    }

}

List::~List()
{
    delete first;
    size = DEFAULT_LIST_SIZE;
}

int List::Fetch(const Trip *aTrip)
// returns the index of the trip (ranging from 0 to size of the List)
// returns -1 if the trip is not found
{
    unsigned int i = 0;
    Node* current = first;

    while(i <= size)
    {
        if(*current->getTrip() == *aTrip) return i;
        current = current->getNext();
        i++;
    }
    return -1;
}

void List::FetchTrip(const char *start, const char *end) const
// Searches a trip by start and end
// Returns the trip if found, else returns a default null trip
{
    if (first == nullptr)
    {
        cerr << "error: Fetching in empty list" << endl;
        return;
    }

    Node *current = first;
    bool found = false;
    while(current != nullptr)
    {
        if(!strcmp(start,current->getTrip()->GetStart()) && !strcmp(end,current->getTrip()->GetEnd()))
        {
            if (!found)
            { // if this is the first trip found, print a txt
                cout << "Trip found!" << endl;
            }
            found = true;
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

/*void List::Sort ( )
/// TODO : A FINIR !!!
{
    if(first == nullptr || size == 1){
        cout << "Empty list or list with one node..."<<endl; /// TODO : Enlever cette ligne
        return;
    }

    List *sortedList = new List();
    List *temp = this;

    Node *minTrip = first;
    Node *iter = first;

    while(iter->getNext() != nullptr){
        if(strcmp(iter->getTrip()->GetStart(),minTrip->getTrip()->GetStart()) < 0)
        // Si iter est inferieur au min
        {
            minTrip = iter;
        }
        else if(!strcmp(iter->getTrip()->GetStart(),minTrip->getTrip()->GetStart()))
        // Si les deux trips ont la même start mais pas la même end
        {
            if(strcmp(iter->getTrip()->GetEnd(),minTrip->getTrip()->GetEnd()) < 0)
            {
                minTrip = iter;
            }
        }


        iter = iter->getNext();
    }

}
*/

Node * List::GetFirst() const
{
    return first;
}
