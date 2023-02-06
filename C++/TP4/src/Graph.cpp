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
#include "Log_Utils.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

template <typename T>
void insertSorted( std::list< shared_ptr<T> > & list , const shared_ptr<T> & value )
{
    auto comp = []( const shared_ptr<T> & a, const shared_ptr<T> & b )
    {
        return *b < *a;
    };
    auto it = lower_bound( list.begin(), list.end(), value , comp );
    list.insert( it, value );
}

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
        cout << *(i.second);
    }
}

list< shared_ptr<Node> > Graph::commandeDefaut()
{
    list < shared_ptr<Node> > top10;

    for (auto & node : nodes)
    {
        insertSorted( top10 , node.second );

        if ( top10.size( ) > 10 )
        {
            top10.pop_back( );
        }
    }

    return top10;
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

    AddNode( Node("-") );
    
    for ( auto const & log : fileManager->getLogs() )
    {
        AddNode( Node( log->getCible() , log->getShortReferer() ) );
        AddNode( Node( log->getShortReferer() ) );
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



