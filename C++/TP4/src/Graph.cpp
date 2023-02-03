/*************************************************************************
                           Graph  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Graph> (fichier Graph.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Graph.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Graph::AddNode( const Node & aNode )
{
    const Cible & c = aNode.GetName();
    // Si une des cibles existe déjà dans notre graph
    if ( nodes.count( c ) > 0 )
    {
        // On ajoute les réferers de aNode dans le node qui est déja présent
        nodes[c]->AddReferer( aNode );
    }
    else
    {
        nodes[c] = make_shared<Node>( aNode );
    }
}
//----- Fin de ~Graph

void Graph::Display ( )
{
    for( auto const & i : nodes )
    {
        i.second->Display();
    }
}

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur


Graph::Graph ( )
// Algorithme :
//
{

} //----- Fin de Graph


Graph::Graph ( const string & path )
{
    fileManager = make_unique<LogFile_Manager>( path );

    AddNode( Node() );

    Node temp;
    
    for ( auto const & log : fileManager->getLogs() )
    {
        temp = Node( log->getCible() , log->getShortReferer() );
        AddNode( temp );
    }
}

Graph::~Graph ( )
// Algorithme :
//
{

}
//----- Fin de ~Graph
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

