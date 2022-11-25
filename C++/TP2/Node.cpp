#include "Node.h"

Node::Node()
// Default constructor
{
    trip = Trip2();
    next = nullptr;
}

Node::Node(const Trip2 & atrip)
// Constructor
{
    trip = atrip;
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

void Node::Display()
// Displays the content of the node
{
    trip.Display();
}

Node::~Node()
// Destructor
{
    trip.~Trip2();
}

bool Node::operator==(const Node &aNode)const
// Overwrites the == operator
// Nodes are equal if the trips they contain are equal
{
    return this->trip == aNode.trip;
}

Trip2 Node::getTrip() {
    return trip;
}
