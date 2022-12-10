/*************************************************************************
                           Trip  -  description
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

Node * Node::GetNext ( )
{
    return next;
} //----- Fin de GetNext

Trip * Node::GetTrip ( )
{
    return const_cast<Trip *>(trip);
} //----- Fin de GetTrip

void Node::SetNext ( Node * aNode )
{
    this->next = aNode;
} //----- Fin de SetNext

//------------------------------------------------- Surcharge d'opérateurs
bool Node::operator == ( const Node & aNode ) const
// Algorithme :
// 2 Nodes sont égaux si les 2 trips qu'ils contiennent sont égaux
{
    return this->trip == aNode.trip;
} //----- Fin de operator ==

//-------------------------------------------- Constructeurs - destructeur
Node::Node ( )
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Node>" << endl;
#endif
    trip = nullptr;
    next = nullptr;
} //----- Fin de Node (constructeur par défaut)


/// la il faudrait faire passer en ref pour avoir copie en profondeur mais pb avec
/// la méthode pure virtuelle de Trip

Node::Node ( Trip const * aTrip )
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Node>" << endl;
#endif
    trip = aTrip ;
    next = nullptr;
} //----- Fin de Node (constructeur paramétré)

Node::~Node ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Node>" << endl;
#endif
    delete trip;
    delete next;
} //----- Fin de ~Node