/*************************************************************************
                           Node  -  Element de la liste chainee List
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
{
    trip->Display();
} //----- Fin de Display

Trip * Node::GetTrip ( ) const
{
    return const_cast<Trip *>(trip);
} //----- Fin de GetTrip

Node * Node::GetNext ( ) const
{
    return next;
} //----- Fin de GetNext

void Node::SetNext ( Node * aNode )
{
    this->next = aNode;
} //----- Fin de SetNext

//------------------------------------------------- Surcharge d'opérateurs
bool Node::operator == ( Node const & aNode ) const
// Algorithme :
// 2 Nodes sont égaux si les 2 trips qu'ils contiennent sont égaux
{
    return this->trip == aNode.trip;
} //----- Fin de operator ==

//-------------------------------------------- Constructeurs - destructeur
Node::Node ( )
// Constructeur par défaut de Node, initialisera tous les pointeurs à NULL
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Node>" << endl;
#endif
    trip = nullptr;
    next = nullptr;
} //----- Fin de Node (constructeur par défaut)

Node::Node ( Trip const * aTrip )
// Algorithme :
// Simple copie en surface de l'attribut trip
// next est forcément initialisé à NULL
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Node>" << endl;
#endif
    trip = aTrip ;
    next = nullptr;
} //----- Fin de Node (constructeur paramétré)

Node::~Node ( )
// Algorithme :
// La destruction d'un node impliquera la destruction de tous les Nodes suivants
{
#ifdef MAP
    cout << "Appel au destructeur de <Node>" << endl;
#endif
    delete trip;
    delete next;
} //----- Fin de ~Node