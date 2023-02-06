/*************************************************************************
                           Node  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Node> (fichier Node.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <map>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Node.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Node::AddReferer ( const Referer & aReferer )
// Algorithme :
//
{
    if ( referers.count( aReferer ) > 0 )
    {
        referers[ aReferer ] += 1;
    }
    else
    {
        referers[ aReferer ] = 1;
    }
    hits++;
} //----- Fin de AddReferer

void Node::AddReferer ( const Node & aNode )
{
    for ( auto const & i : aNode.referers )
    {
        this->AddReferer ( i.first );
    }
} //----- Fin de AddReferer

const string & Node::GetName ( ) const
{
    return name;
} //----- Fin de GetName

void Node::Display ( ) const
// Algorithme :
//
{
    cout << "Cible : " << name << endl;
    cout << "Referers : " << endl;

    for ( auto const & i : referers)
    {
        cout << "\t" << i.first << " : " << i.second << endl;
    }
} //----- Fin de Display

int Node::GetHits ( ) const
{
    return hits;
} //----- Fin de GetHits


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & os, Node & aNode )
{
    os << aNode.name << " (" << aNode.hits << ( ( aNode.hits == 1 ) ? " hit)" : " hits)" ) << endl;
    return os;
} //----- Fin de operator <<

bool operator < ( Node & a, Node & b )
{
    return b.hits != a.hits ? b.hits > a.hits : b.name < a.name;
} //----- Fin de operator <


//-------------------------------------------- Constructeurs - destructeur
Node::Node ( const Cible & uneCible )
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Node>" << endl;
#endif
    name = uneCible;
    hits = 0;
} //----- Fin de Node (constructeur paramétré)

Node::Node ( const Cible & uneCible, const Referer & unReferer )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Node>" << endl;
#endif
    name = uneCible;
    hits = 1;
    referers.insert( std::pair< Referer, int >( unReferer, 1 ) );
} //----- Fin de Node (constructeur paramétré)

Node::Node( const Node & aNode )
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Node>" << endl;
#endif
    name = aNode.name;
    hits = aNode.hits;
    for ( auto const & i : aNode.referers )
    {
        referers[i.first] = i.second;
    }
} //----- Fin de Node (constructeur de copie)

Node::Node ( )
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Node>" << endl;
#endif
    name = "-";
    hits = 0;
} //----- Fin de Node (constructeur par défaut)

Node::~Node ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Node>" << endl;
#endif
} //----- Fin de ~Node