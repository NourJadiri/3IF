#include "Node.h"
#include "Trip.h"
#include "SimpleTrip.h"


Node::Node(const Trip & aTrip)
// Constructor
{
    trip = aTrip;
    next = nullptr;
}

Node* Node::getNext()
// Setter for the next node
{
    return next;
}

void Node::setNext(Node * aNode)
// Sets the next node to *aNode
{
    this->next = aNode;
}

void Node::Display() const
// Displays the content of the node
{
    trip.Display();
}

Node::~Node()
// Destructor
{

}

bool Node::operator== ( const Node &aNode )const
// Overwrites the == operator
// Nodes are equal if the trips they contain are equal
{
    return this->trip == aNode.trip;
}

Trip Node::getTrip() {
    return trip;
}
