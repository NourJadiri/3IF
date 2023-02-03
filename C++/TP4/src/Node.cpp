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
#include <map>
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
    for( auto const & i : aNode.referers )
    {
        this->AddReferer ( i.first );
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

    for ( auto const & i : referers)
    {
        cout << "\t" << i.first << " : " << i.second << endl;
    }
}


//----- Fin du constructeur de Node

//------------------------------------------------- Surcharge d'opérateurs

std::ostream &operator<<( ostream &os, Node &aNode ) 
{
    os << "Noeud : " << aNode.name << endl;
    cout << "> Referers : " << endl;

    for ( auto const & i : aNode.referers)
    {
        cout << "\t" << i.first << " : " << i.second << endl;
    }

    return os;
}


//-------------------------------------------- Constructeurs - destructeur

Node::Node ( const Cible & uneCible )
{
    name = uneCible;
}

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

    for( auto const & i : aNode.referers )
    {
        referers[i.first] = i.second;
    }
}

Node::Node()
{
    name = "-";
}


Node::~Node ( ) = default;
// Algorithme :
//
// ----- Fin de ~Node


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

