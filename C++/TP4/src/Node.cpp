/*************************************************************************
                           Node  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Node> (fichier Node.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Node.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Node::AddReferer( const Referer & aReferer )
{
    if ( referers.count( aReferer ) > 0 )
    {
        referers[ aReferer ] += 1;
    }
    else
    {
        referers[ aReferer ] = 1;
    }
}

void Node::AddReferer( const Node & aNode )
{
    for( auto const & [ref , weigth] : aNode.referers )
    {
        this->AddReferer ( ref );
    }
}

const string & Node::GetName() const
{
    return name;
}

void Node::Display() const
{
    cout << "Cible : " << name << endl;
    cout << "Referers : " << endl;

    for ( auto const & [ref , weight] : referers)
    {
        cout << "\t" << ref << " : " << weight << endl;
    }
}


//----- Fin du constructeur de Node

//------------------------------------------------- Surcharge d'opérateurs

std::ostream &operator<<(ostream &os, Node &aNode) {
    os << "Cible : " << aNode.name << endl;
    cout << "Referers : " << endl;

    for ( auto const & [ref , weight] : aNode.referers)
    {
        cout << "\t" << ref << " : " << weight << endl;
    }

    return os;
}


//-------------------------------------------- Constructeurs - destructeur
Node::Node ( const Cible & uneCible, const Referer & unReferer )
// Algorithme :
//
{
    name = uneCible;
    referers.insert( std :: pair<Referer , int>( unReferer , 1 ) );
}

Node::Node( const Node & aNode )
{
    name = aNode.name;

    for( auto const & [ref , weight] : aNode.referers )
    {
        referers[ref] = weight;
    }
}

Node::Node()
{

}


Node::~Node ( ) = default;
// Algorithme :
//
// ----- Fin de ~Node


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

