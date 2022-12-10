/*************************************************************************
                           Trip  -  SOMETHINGXXXXXXXXXX
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Node> (fichier Node.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//------------------------------------------------------ Include personnel
#include "Node.h"
#include "Trip.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Node::Display ( ) const
// Algorithme :
// Displays the content of the node
{
    trip->Display();
} //----- Fin de Display

Node * Node::GetNext ( )
// Algorithme :
// Setter for the next node
{
    return next;
} //----- Fin de GetNext

Trip * Node::GetTrip ( )
// Algorithme :
//
{
    return const_cast<Trip *>(trip);
} //----- Fin de GetTrip

void Node::SetNext ( Node * aNode )
// Algorithme :
// Sets the next node to *aNode
{
    this->next = aNode;
} //----- Fin de SetNext

//------------------------------------------------- Surcharge d'opérateurs
bool Node::operator == ( const Node & aNode ) const
// Overwrites the == operator
// Nodes are equal if the trips they contain are equal
{
    return this->trip == aNode.trip;
} //----- Fin de operator ==

//-------------------------------------------- Constructeurs - destructeur
Node::Node ( )
// Algorithme :
// Default constructor
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Node>" << endl;
#endif
    trip = nullptr;
    next = nullptr;
} //----- Fin de Node (constructeur par défaut)

Node::Node ( Trip const * aTrip )
// Algorithme :
// Constructor
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Node>" << endl;
#endif
    trip = aTrip;
    next = nullptr;
} //----- Fin de Node (constructeur paramétré)

Node::~Node ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Node>" << endl;
#endif
    delete trip;
    delete next;
} //----- Fin de ~Node